#pragma once

#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include <vector>
#include "Transform.h"
#include "Direct3D.h"


#pragma comment(lib, "LibFbxSDK-MD.lib")
#pragma comment(lib, "LibXml2-MD.lib")
#pragma comment(lib, "zlib-MD.lib")

class Texture;  //前方宣言

class Fbx
{
public :
	//マテリアル
	struct MATERIAL
	{
		Texture* pTexture_; //これがポインタだからincludeじゃなくて前方宣言でいい
		Texture* pNormalTexture;
		XMFLOAT4 diffuse;
		XMFLOAT4 ambient;
		XMFLOAT4 specular;
		float shininess;
	};
private:
	//ambient specular shinessも追加する
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP;				//wvp ワールドビュープロジェクション
		XMMATRIX    matW;				//w ワールド変換のみ
		XMMATRIX	matNormal;			//スケール×平行移動の逆行列
		XMFLOAT4	diffuseColor;		//拡散反射光＝マテリアルの色
		XMFLOAT4	ambientColor;		//環境光
		XMFLOAT4	specularColor;		//鏡面反射＝ハイライト
		FLOAT		shininess;
		BOOL		isTextured;			//テクスチャ貼ってあるかどうか
		BOOL		isNormalTexture;
	};

	struct VERTEX
	{
		XMVECTOR position; //位置
		XMVECTOR uv;	   //テクスチャ位置
		XMVECTOR normal;   //法線
		XMVECTOR tangent;  //接線
	};


	int vertexCount_;	//頂点数
	int polygonCount_;	//ポリゴン数
	int materialCount_;	//マテリアルの個数


	ID3D11Buffer* pVertexBuffer_;      //頂点バッファ
	ID3D11Buffer** pIndexBuffer_;      //インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;    //コンスタントバッファ
	MATERIAL* pMaterialList_;
	std::vector <int> indexCount_;

	void InitVertex(fbxsdk::FbxMesh* mesh);
	void InitIndex(fbxsdk::FbxMesh* mesh);
	void IntConstantBuffer();
	void InitMaterial(fbxsdk::FbxNode* pNode);
	bool IsFlatColor_;
	XMFLOAT4 dColor_;
	XMFLOAT4 lightSourcePosition_;
	Texture* pToonTex_;
public:

	Fbx();
	HRESULT Load(std::string fileName);
	void SetLightPos(XMFLOAT4& pos);
	XMFLOAT4 GetLightPos() { return (lightSourcePosition_); }
	void Draw(Transform& transform);
	void Release();

	static bool CompareMaterials(const MATERIAL& a, const MATERIAL& b);

};
