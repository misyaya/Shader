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
    //移動行列作成
    matTranslate_ = XMMatrixTranslation(position_.x,position_.y,position_.z);

  //回転行列作成
    XMMATRIX rotateX, rotateY, rotateZ;
    rotateX = XMMatrixRotationX(XMConvertToRadians(rotate_.x)); //X軸回転行列
    rotateY = XMMatrixRotationY(XMConvertToRadians(rotate_.y)); //Y軸回転行列
    rotateZ = XMMatrixRotationZ(XMConvertToRadians(rotate_.z)); //Z軸回転行列
                  //合体！ 
    matRotate_ = rotateZ * rotateX * rotateY;

  //拡大行列作成
    matScale_ = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
}

XMMATRIX Transform::GetWorldMatrix()
{
    if (pParent_ != nullptr) //if(pParent_)でも可
    {  
        //親があったら親のワールドマトリクスを掛ける
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