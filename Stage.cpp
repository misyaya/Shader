#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"

namespace {
    const XMFLOAT4 DEF_LIGHTPOSITION{ 1, 2, 1, 0 };
}

void Stage::IntConstantBuffer()
{
    D3D11_BUFFER_DESC cb;
    cb.ByteWidth = sizeof(CBUFF_STAGESCENE);
    cb.Usage = D3D11_USAGE_DEFAULT;
    cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cb.CPUAccessFlags = 0;
    cb.MiscFlags = 0;
    cb.StructureByteStride = 0;

    //�R���X�^���g�o�b�t�@�̍쐬
    HRESULT hr;
    hr = Direct3D::pDevice_->CreateBuffer(&cb, nullptr, &pCBStageScene_);
    if (FAILED(hr))
    {
        MessageBox(NULL, "�R���X�^���g�o�b�t�@�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
    }

 
}

//�R���X�g���N�^
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"), hDonuts_(-1),lightSourcePosition_()
{
}

//�f�X�g���N�^
Stage::~Stage()
{
}

//������
void Stage::Initialize()
{
    // X�A���[
    hArrowX_ = Model::Load("Assets/arrow.fbx");
    assert(hArrowX_ >= 0);

    // Y�A���[
    hArrowY_ = Model::Load("Assets/arrow.fbx");
    assert(hArrowY_ >= 0);

    // X�A���[
    hArrowZ_ = Model::Load("Assets/arrow.fbx");
    assert(hArrowZ_ >= 0);

    hDonuts_ = Model::Load("Assets/donuts.fbx");
    assert(hDonuts_ >= 0);

    IntConstantBuffer();
}

//�X�V
void Stage::Update()
{
    Model::GetModel(hLight_)->SetLightPos(lightSourcePosition_);

    if (Input::IsKey(DIK_RIGHT))
    {
        XMFLOAT4 p = Model::GetModel(hLight_)->GetLightPos();
        XMFLOAT4 margin{ p.x + 0.1f, p.y + 0.0f, p.z + 0.0f, p.w + 0.0f };

        Model::SetLightPosition(margin);
    }
    if (Input::IsKey(DIK_LEFT))
    {
        XMFLOAT4 p = Model::GetModel(hLight_)->GetLightPos();
        XMFLOAT4 margin{ p.x - 0.1f, p.y - 0.0f, p.z - 0.0f, p.w - 0.0f };

        Model::SetLightPosition(margin);
    }

    if (Input::IsKey(DIK_UP))
    {
        XMFLOAT4 p = Model::GetModel(hLight_)->GetLightPos();
        XMFLOAT4 margin{ p.x - 0.0f, p.y + 0.1f, p.z - 0.0f, p.w - 0.0f };

        Model::SetLightPosition(margin);
    }

    if (Input::IsKey(DIK_DOWN))
    {
        XMFLOAT4 p = Model::GetModel(hLight_)->GetLightPos();
        XMFLOAT4 margin{ p.x - 0.0f, p.y - 0.1f, p.z - 0.0f, p.w - 0.0f };

        Model::SetLightPosition(margin);
    }

    if (Input::IsKey(DIK_W))
    {
        XMFLOAT4 p = Model::GetModel(hLight_)->GetLightPos();
        XMFLOAT4 margin{ p.x - 0.0f, p.y - 0.0f, p.z + 0.1f, p.w + 0.0f };

        Model::SetLightPosition(margin);

        light.position_.z += 0.1f;
    }

    if (Input::IsKey(DIK_S))
    {
        XMFLOAT4 p = Model::GetModel(hLight_)->GetLightPos();
        XMFLOAT4 margin{ p.x - 0.0f, p.y - 0.0f, p.z - 0.1f, p.w + 0.0f };

        Model::SetLightPosition(margin);
        light.position_.z -= 0.1f;
    }

    XMFLOAT4 tmp{ Model::GetModel(hLight_)->GetLightPos() };
    light.position_ = { tmp.x, tmp.y, tmp.z };

    CBUFF_STAGESCENE cb;
    cb.lightPosition = lightSourcePosition_;
    XMStoreFloat4(&cb.eyePos, Camera::GetEyePosition());
    
    Direct3D::pContext_->UpdateSubresource(pCBStageScene_, 0, NULL, &cb, 0, 0);

    Direct3D::pContext_->VSSetConstantBuffers(1, 1, &pCBStageScene_); //���_�V�F�[�_�[�p
    Direct3D::pContext_->PSSetConstantBuffers(1, 1, &pCBStageScene_); //�s�N�Z���V�F�[�_�[�p
}

//�`��
void Stage::Draw()
{
   Model::SetTransform(hDonuts_, transform_);
   Model::Draw(hDonuts_);
}

//�J��
void Stage::Release()
{
}