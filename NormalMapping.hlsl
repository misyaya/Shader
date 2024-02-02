//───────────────────────────────────────
// テクスチャ＆サンプラーデータのグローバル変数定義
//───────────────────────────────────────
Texture2D		g_texture : register(t0);	//テクスチャー
SamplerState	g_sampler : register(s0);	//サンプラー
Texture2D		normalTex : register(t1);

//───────────────────────────────────────
 // コンスタントバッファ
// DirectX 側から送信されてくる、ポリゴン頂点以外の諸情報の定義
//───────────────────────────────────────
cbuffer gmodel:register(b0)
{
	float4x4	matWVP;			//ワールド・ビュー・プロジェクションの合成行列
	float4x4	matW;			//ワールド行列
	float4x4    matNormal;		//法線変形用の行列
	float4		diffuseColor;	//拡散反射光＝マテリアルの色
	float4		ambientColor;	//環境光
	float4		specularColor;	//鏡面反射＝ハイライト
	float		shininess;
	int			isTextured;		//テクスチャ貼ってあるかどうか
	int			isNormalTextured;	//ノーマルマップがあるかどうか
};

cbuffer gmodel:register(b1)
{
	float4      lightPosition;//光源の位置(平行光源の時は、その位置から原点へのベクトル)
	float4      eyePosition;//視点位置 = カメラ位置
};

//───────────────────────────────────────
// 頂点シェーダー出力＆ピクセルシェーダー入力データ構造体
//───────────────────────────────────────
struct VS_OUT
{
	float4 pos    : SV_POSITION;	//ピクセル位置
	float2 uv     : TEXCOORD;		//UV座標
	float4 eyev   : POSITION;       //ワールド座標用に変換された視線ベクトル
	float4 Neyev  : POSITION1;		//ノーマルマップ用の説空間に変換された視線ベクトル
	float4 normal : NORMAL;			//法線ベクトル
	float4 light  : POSITION2;		//ライトを接空間に変換したベクトル
	float4 color  : COLOR;			//色（明るさ）
};

//───────────────────────────────────────
// 頂点シェーダ
//───────────────────────────────────────
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL, float4 tangent : TANGENT)
{
	//ピクセルシェーダーへ渡す情報
	VS_OUT outData = (VS_OUT)0;

	//ローカル座標に、ワールド・ビュー・プロジェクション行列をかけて
	//スクリーン座標に変換し、ピクセルシェーダーへ
	outData.pos = mul(pos, matWVP);
	outData.uv = (float2)uv;

	float3 binormal = cross(tangent, normal);
	//float4 binormal = { tmp, 0 };
	binormal = mul(binormal, matNormal);
	binormal = normalize(binormal);

	//法線を回転
	outData.normal = normalize(mul(normal, matNormal));
	normal.w = 0;

	tangent = mul(tangent, matNormal);
	
	tangent = normalize(tangent);
	tangent.w = 0;
	//float4 posw = mul(pos, matW);
	//outData.eyev = normalize(posw - eyePosition); //ワールド座標の視線ベクトル
	float4 eye = normalize(mul(pos,matW) - eyePosition);
	outData.eyev = eye;


	outData.Neyev.x = dot(eye, tangent); //接空間の視線ベクトル
	outData.Neyev.y = dot(eye, binormal);
	outData.Neyev.z = dot(eye, outData.normal);
	outData.Neyev.w = 0;

	float4 light = normalize(lightPosition);
	light.w = 0;
	//light = normalize(light);

	outData.color = mul(light, outData.normal);
	outData.color.w = 0.0;

	outData.light.x = dot(light, tangent); //接空間の光源ベクトル
	outData.light.y = dot(light, binormal);
	outData.light.z = dot(light, outData.normal);
	outData.light.w = 0;

	//まとめて出力
	return outData;
}

//───────────────────────────────────────
// ピクセルシェーダ
//───────────────────────────────────────
float4 PS(VS_OUT inData) : SV_Target
{
	float4 lightSource = float4(1.0, 1.0, 1.0, 0.0);     //ライト色＆明るさ  Iin
	float4 diffuse;
	float4 ambient;

	if (isNormalTextured)
	{
		//inData.light = normalize(inData.light);

		
		float4 tmpNormal = normalTex.Sample(g_sampler, inData.uv) * 2.0f - 1.0f;
		tmpNormal = normalize(tmpNormal);
		tmpNormal.w = 0;
		

		float4 NL = clamp(dot(normalize(inData.light), tmpNormal),0,1);
		float4 reflection = reflect(inData.light, tmpNormal);
		float4 specular = pow(saturate(dot(reflection, inData.Neyev)), shininess) * specularColor;


		if(isTextured != 0)
		{
			diffuse = lightSource * g_texture.Sample(g_sampler, inData.uv) * NL;
			ambient = lightSource * g_texture.Sample(g_sampler, inData.uv) * ambientColor;
		}
		else
		{
			diffuse = lightSource * diffuseColor * NL;
			ambient = lightSource * diffuseColor * ambientColor;
		}
		return diffuse + ambient + specular;
	}
	else
	{
		float4 reflection = reflect(normalize(lightPosition), inData.normal);
		//ここでspecularColor(スペキュラーの値が入っている)を掛けることでハイライト有のやつだけハイライトがつく
		float4 specular = pow(saturate(dot(reflection,inData.eyev)), shininess) * specularColor;

		if (isTextured == 0)
		{
			diffuse = lightSource * diffuseColor * inData.color;
			ambient = lightSource * diffuseColor * ambientColor;
		}
		else
		{
			diffuse = lightSource * g_texture.Sample(g_sampler, inData.uv) * inData.color;
			ambient = lightSource * g_texture.Sample(g_sampler, inData.uv) * ambientColor;
		}
		float4 result = diffuse + ambient + specular;

		if (isTextured)
			result.a = inData.uv.x;
		return result;

		return diffuse + ambient + specular;
	}
}