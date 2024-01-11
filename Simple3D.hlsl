//───────────────────────────────────────
// テクスチャ＆サンプラーデータのグローバル変数定義
//───────────────────────────────────────
Texture2D	g_texture : register(t0);	//テクスチャー
SamplerState	g_sampler : register(s0);	//サンプラー

//───────────────────────────────────────
 // コンスタントバッファ
// DirectX 側から送信されてくる、ポリゴン頂点以外の諸情報の定義
//───────────────────────────────────────
cbuffer gmodel:register(b0)
{
	float4x4	matWVP;			// ワールド・ビュー・プロジェクションの合成行列
	float4x4	matW;			//ワールド行列
	float4x4    matNormal;		//ワールド行列
	float4		diffuseColor;	// 拡散反射光＝マテリアルの色
	float4		ambientColor;	// 環境光
	float4		specularColor;	// 鏡面反射＝ハイライト
	float		shininess;
	bool		isTextured;		// テクスチャ貼ってあるかどうか
};

cbuffer gmodel:register(b1)
{
	float4      lightPosition;
	float4      eyePosition;
};

//───────────────────────────────────────
// 頂点シェーダー出力＆ピクセルシェーダー入力データ構造体
//───────────────────────────────────────
struct VS_OUT
{
	float4 pos    : SV_POSITION;	//位置
	float2 uv     : TEXCOORD;		//UV座標
	float4 color  : COLOR;          //色（明るさ）
	float4 eyev   : POSITION;       //視線ベクトル
	float4 normal : NORMAL;
};

//───────────────────────────────────────
// 頂点シェーダ
//───────────────────────────────────────
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL)
{
	//ピクセルシェーダーへ渡す情報
	VS_OUT outData = (VS_OUT)0;

	//ローカル座標に、ワールド・ビュー・プロジェクション行列をかけて
	//スクリーン座標に変換し、ピクセルシェーダーへ
	outData.pos = mul(pos, matWVP);
	outData.uv = uv;

	//法線を回転
	normal.w = 0;
	normal = mul(normal, matNormal);
	normal = normalize(normal);
	outData.normal = normal;

	float4 light = normalize(lightPosition);
	light = normalize(light);

	outData.color = saturate(dot(normal, light));
	float4 posw = mul(pos, matW);
	outData.eyev = eyePosition - posw;

	//outData.color = clamp(dot(normal, light), 0, 1);


	//まとめて出力
	return outData;
}

//───────────────────────────────────────
// ピクセルシェーダ
//───────────────────────────────────────
float4 PS(VS_OUT inData) : SV_Target
{
	float4 lightSource = float4(1.0, 1.0, 1.0, 0.0);     //ライト色＆明るさ  Iin
	float4 ambientSource = ambientColor;   //アンビエント係数  Ka  直接かければいいだけだからこの変数別にいらないかも
	float4 diffuse;
	float4 ambient;
	float4 NL = dot(inData.normal, normalize(lightPosition));
	float4 reflect = normalize(2 * NL * inData.normal - normalize(lightPosition));  //入射光の反射ベクトル
	//ここでspecularColor(スペキュラーの値が入っている)を掛けることでハイライト有のやつだけハイライトがつく
	float4 specular = pow(saturate(dot(reflect, normalize(inData.eyev))), shininess) * specularColor;
	
	if (isTextured == false)
	{
		diffuse = lightSource * diffuseColor * inData.color;
		ambient = lightSource * diffuseColor * ambientColor;
	}
	else
	{
		diffuse = lightSource * g_texture.Sample(g_sampler, inData.uv) * inData.color;
		ambient = lightSource * g_texture.Sample(g_sampler, inData.uv) * ambientColor;
	}


	/*if (abs(dot(inData.normal, normalize(inData.eyev))) < 0.3)
		return float4(0, 0, 0, 0);
	else
		return (diffuse + ambient + specular);*/

	return (diffuse + ambient + specular);


	//specular = pow(saturate(dot(diffues,ambient),))


	//float4 output = g_texture.Sample(g_sampler, inData.uv);
	//float4 output = g_texture.Sample(g_sampler, inData.uv);

	//グレースケール変換
	//float grayValue = dot(output.rgb, float3(0.298912, 0.586611, 0.114478));
	//float4 grayColor = float4(grayValue, grayValue, grayValue, output.a);

	//float4 output = floor(g_texture.Sample(g_sampler, inData.uv)*8.0)/8;


	//return grayColor;

}