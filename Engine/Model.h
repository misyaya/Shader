#pragma once
#include <string>
#include <vector>
#include "Fbx.h"
#include "Transform.h"

//-----------------------------------------------------------
//3D���f���iFBX�t�@�C���j���Ǘ�����
//-----------------------------------------------------------
namespace Model
{
	//�ǂݍ���
	int Load(std::string fileName);
	void SetTransform(int hModel, Transform transform);
	//�`��
	void Draw(int hModel);
	//���
	void Release();

};
