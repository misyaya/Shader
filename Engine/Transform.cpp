#include "Transform.h"

Transform::Transform()
    :matTranslate_(XMMatrixIdentity()),matRotate_(XMMatrixIdentity()),matScale_(XMMatrixIdentity()),
    position_(0,0,0),rotate_(0,0,0),scale_(1,1,1)
{
}

Transform::~Transform()
{
}

void Transform::Calclation()
{
    //�ړ��s��쐬
    matTranslate_ = XMMatrixTranslation(position_.x,position_.y,position_.z);

  //��]�s��쐬
    XMMATRIX rotateX, rotateY, rotateZ;
    rotateX = XMMatrixRotationX(XMConvertToRadians(rotate_.x)); //X����]�s��
    rotateY = XMMatrixRotationY(XMConvertToRadians(rotate_.y)); //Y����]�s��
    rotateZ = XMMatrixRotationZ(XMConvertToRadians(rotate_.z)); //Z����]�s��
                  //���́I 
    matRotate_ = rotateZ * rotateX * rotateY;

  //�g��s��쐬
    matScale_ = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
}

XMMATRIX Transform::GetWorldMatrix()
{
    if (pParent_ != nullptr) //if(pParent_)�ł���
    {  
        //�e����������e�̃��[���h�}�g���N�X���|����
        return  matScale_ * matRotate_ * matTranslate_ * pParent_->GetWorldMatrix();
    }
    else
    {
        return matScale_ * matRotate_ * matTranslate_;
    }
}

XMMATRIX Transform::GetNormalMatrix()
{
    return matRotate_ * XMMatrixInverse(nullptr, matScale_);
}