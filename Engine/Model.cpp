#include "Model.h"

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
	//モデルのポインタをぶち込んでおくベクタ
	std::vector<ModelData*>modelList;


};

int Model::Load(std::string fileName)
{
	//読んで作る
	ModelData* pData;
	pData = new ModelData;
	pData->filename_ = fileName;
	pData->pfbx_ = nullptr;

	//ファイルネームが同じだったら読まない！
	for (auto& e : modelList)
	{
		if (e->filename_ == fileName)
		{
			pData->pfbx_ = e->pfbx_;
			break;
		}
	}

	
	if (pData->pfbx_ == nullptr)
	{
		pData->pfbx_ = new Fbx;
		pData->pfbx_->Load(fileName);
	}


	//modelListに入れる
	modelList.push_back(pData);
	//今読んだモデルのモデル番号をかえす
	return(modelList.size() - 1);

	//ファイル名のモデルを読み込んで、同じモデル名のものがあったらそのモデル番号（配列のインデクッス-1）を返す
	//同じ名前のモデルがなかったら、モデルを読み込んで、ベクタに追加
}


void Model::SetTransform(int hModel, Transform transform)
{
	modelList[hModel]->transform_ = transform;
	//モデル番号は、modelListのインデクッス
}

void Model::SetLightPosition(XMFLOAT4 _lightpos)
{
}

Fbx* Model::GetModel(int _hModel)
{
	return nullptr;
}


void Model::Draw(int hModel)
{
	//モデル番号は、modelListのインデクッス
	modelList[hModel]->pfbx_->Draw(modelList[hModel]->transform_);
}

void Model::Release()
{
	bool isRefferd = false; //参照しているか
	for (int i = 0; i < modelList.size(); i++)
	{
		for (int j = i + 1; j < modelList.size(); j++)
		{
			if (modelList[i]->pfbx_ == modelList[j]->pfbx_)
			{
				isRefferd = true;
				break;
			}
		}
		if (isRefferd == false)
		{
			SAFE_DELETE(modelList[i]->pfbx_);
		}
		SAFE_DELETE(modelList[i]);
	}
	modelList.clear();
}
