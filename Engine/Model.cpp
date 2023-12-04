#include "Model.h"

namespace Model
{
	//���f�����
	struct ModelData
	{
		//FBX��
		Fbx* pfbx_;
		Transform transform_; //�g�����X�t�H�[��
		std::string filename_; //�t�@�C����
	};
	//���f���̃|�C���^���Ԃ�����ł����x�N�^
	std::vector<ModelData*>modelList;


};

int Model::Load(std::string fileName)
{
	//�ǂ�ō��
	ModelData* pData;
	pData = new ModelData;
	pData->filename_ = fileName;
	pData->pfbx_ = nullptr;

	//�t�@�C���l�[����������������ǂ܂Ȃ��I
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


	//modelList�ɓ����
	modelList.push_back(pData);
	//���ǂ񂾃��f���̃��f���ԍ���������
	return(modelList.size() - 1);

	//�t�@�C�����̃��f����ǂݍ���ŁA�������f�����̂��̂��������炻�̃��f���ԍ��i�z��̃C���f�N�b�X-1�j��Ԃ�
	//�������O�̃��f�����Ȃ�������A���f����ǂݍ���ŁA�x�N�^�ɒǉ�
}


void Model::SetTransform(int hModel, Transform transform)
{
	modelList[hModel]->transform_ = transform;
	//���f���ԍ��́AmodelList�̃C���f�N�b�X
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
	//���f���ԍ��́AmodelList�̃C���f�N�b�X
	modelList[hModel]->pfbx_->Draw(modelList[hModel]->transform_);
}

void Model::Release()
{
	bool isRefferd = false; //�Q�Ƃ��Ă��邩
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
