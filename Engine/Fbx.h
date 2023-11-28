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
	//マテリアル
	struct MATERIAL
	{
		Texture*    pTexture_; //これがポインタだからincludeじゃなくて前方宣言でいい
		XMFLOAT4	diffuse;
	};

	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP;  //wvp
		XMMATRIX	matNormal; //ワールド変換だけのやつ
		XMFLOAT4	diffuseColor;		// ディフューズカラー（マテリアルの色）
		BOOL		isTexture;		// テクスチャ貼ってあるかどうか
		XMFLOAT4	lightDirection; //光源方向
		XMFLOAT4	eyePos; //視点
		
	};

	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
		XMVECTOR normal;
	};


	int vertexCount_;	//頂点数
	int polygonCount_;	//ポリゴン数
	int materialCount_;	//マテリアルの個数


	ID3D11Buffer* pVertexBuffer_;      //頂点バッファ
	ID3D11Buffer** pIndexBuffer_;       //インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;    //コンスタントバッファ
	MATERIAL* pMaterialList_;
	std::vector <int> indexCount_;

	void InitVertex(fbxsdk::FbxMesh* mesh);
	void InitIndex(fbxsdk::FbxMesh* mesh);
	void IntConstantBuffer();
	void InitMaterial(fbxsdk::FbxNode* pNode);

public:

	Fbx();
	HRESULT Load(std::string fileName);
	void Draw(Transform& transform);
	void Release();
};