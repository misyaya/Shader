#pragma once
#include <string>
#include <vector>
#include "Fbx.h"
#include "Transform.h"

//-----------------------------------------------------------
//3Dモデル（FBXファイル）を管理する
//-----------------------------------------------------------
namespace Model
{
	//読み込み
	int Load(std::string fileName);
	void SetTransform(int hModel, Transform transform);
	void SetLightPosition(XMFLOAT4 _lightpos);
	Fbx* GetModel(int _hModel);
	//描画
	void Draw(int hModel);
	//解放
	void Release();

};
