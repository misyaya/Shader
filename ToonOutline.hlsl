//───────────────────────────────────────
// テクスチャ＆サンプラーデータのグローバル変数定義
//───────────────────────────────────────
Texture2D		g_texture : register(t0);	//テクスチャー
SamplerState	g_sampler : register(s0);	//サンプラー

Texture2D		g_toon_texture : register(t1);

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
float4 VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL)
{
	//ピクセルシェーダーへ渡す情報
	//VS_OUT outData = (VS_OUT)0;
	
	//ローカル座標に、ワールド・ビュー・プロジェクション行列をかけて
	//スクリーン座標に変換し、ピクセルシェーダーへ

	normal.w = 0;
	pos = pos + normal * 0.05;

	pos = mul(pos, matWVP);

	return pos;
}

//───────────────────────────────────────
// ピクセルシェーダ
//───────────────────────────────────────
float4 PS(VS_OUT inData) : SV_Target
{
	return float4(0, 0, 0, 1);
}