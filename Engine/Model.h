#pragma once
#include <string>
#include <vector>
#include "Fbx.h"


//-----------------------------------------------------------
//3D���f���iFBX�t�@�C���j���Ǘ�����
//-----------------------------------------------------------
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


	//�ǂݍ���
	int Load(std::string fileName);
	void SetTransform(int hModel, Transform transform);
	Fbx* GetModel(int _hModel);
	//�`��
	void Draw(int hModel);
	//���
	void Release();

	//�����_�����O��Ԃ̐؂�ւ�
	void ToggleRenderState();

};
