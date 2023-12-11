#pragma once
#include <string>
#include <vector>
#include "Fbx.h"


//-----------------------------------------------------------
//3Dモデル（FBXファイル）を管理する
//-----------------------------------------------------------
namespace Model
{
	//モデル情報
	struct ModelData
	{
		//FBX名
		Fbx* pfbx_;
		Transform transform_; //トランスフォーム
		std::string filename_; //ファイル名
	};


	//読み込み
	int Load(std::string fileName);
	void SetTransform(int hModel, Transform transform);
	Fbx* GetModel(int _hModel);
	//描画
	void Draw(int hModel);
	//解放
	void Release();

	//レンダリング状態の切り替え
	void ToggleRenderState();

};
