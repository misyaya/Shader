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

    //コンスタントバッファの作成
    HRESULT hr;
    hr = Direct3D::pDevice_->CreateBuffer(&cb, nullptr, &pCBStageScene_);
    if (FAILED(hr))
    {
        MessageBox(NULL, "コンスタントバッファの作成に失敗しました", "エラー", MB_OK);
    }

}

//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"),
    hArrowX_(-1), hArrowY_(-1), hArrowZ_(-1), hDonuts_(-1), hLight_(-1), lightSourcePosition_(),hDice_(-1),hWater_(-1)
{
}

//デストラクタ
Stage::~Stage()
{
}

//初期化
void Stage::Initialize()
{
    //Xアロー
    hArrowX_ = Model::Load("Assets/arrow.fbx");
    assert(hArrowX_ >= 0);

    //Yアロー
    hArrowY_ = Model::Load("Assets/arrow.fbx");
    assert(hArrowY_ >= 0);

    //Xアロー
    hArrowZ_ = Model::Load("Assets/arrow.fbx");
    assert(hArrowZ_ >= 0);

    //ドーナツ
    hDonuts_ = Model::Load("Assets/ball.fbx");
    assert(hDonuts_ >= 0);

    //ライトの誘導の玉
    hLight_ = Model::Load("Assets/light.fbx");
    assert(hLight_ >= 0);

    hDice_ = Model::Load("Assets/dice.fbx");
    assert(hDice_ >= 0);

    hWater_ = Model::Load("Assets/Water.fbx");
    assert(hWater_ >= 0);


    arrowX.scale_ = XMFLOAT3(0.2f, 0.2f, 0.2f);
    arrowX.position_ = XMFLOAT3(0.0f, 0.5f, -1.0f);

    arrowY.scale_ = XMFLOAT3(0.2f, 0.2f, 0.2f);
    arrowY.rotate_.z = 90.0f;
    arrowY.position_ = XMFLOAT3(0.0f, 0.5f, -1.0f);

    arrowZ.scale_ = XMFLOAT3(0.2f, 0.2f, 0.2f);
    arrowZ.rotate_.y = 270.0f;
    arrowZ.position_ = XMFLOAT3(0.0f, 0.5f, -1.0f);

    water_.position_.y = -1.0f;

    transform_.position_.z = -1.0f;
    //transform_.position_.x = 3.0f;

    Camera::SetPosition(XMFLOAT3(0, 0, -10));
    Camera::SetTarget(XMFLOAT3(0, 0, 0));;

    IntConstantBuffer();
}

//更新
void Stage::Update()
{
    Model::GetModel(hLight_)->SetLightPos(lightSourcePosition_);

    donutsTr.rotate_.y += 0.5f;

    if (Input::IsKey(DIK_RIGHT))
    {
        XMFLOAT4 p = GetLightPos();
        XMFLOAT4 margin{ p.x + 0.1f, p.y + 0.0f, p.z + 0.0f, p.w + 0.0f };

        SetLightPos(margin);
    }

    if (Input::IsKey(DIK_LEFT))
    {
        XMFLOAT4 p = GetLightPos();
        XMFLOAT4 margin{ p.x - 0.1f, p.y - 0.0f, p.z - 0.0f, p.w - 0.0f };

        SetLightPos(margin);
    }

    if (Input::IsKey(DIK_UP))
    {
        XMFLOAT4 p = GetLightPos();
        XMFLOAT4 margin{ p.x - 0.0f, p.y + 0.1f, p.z - 0.0f, p.w - 0.0f };

       SetLightPos(margin);

    }

    if (Input::IsKey(DIK_DOWN))
    {
        XMFLOAT4 p = GetLightPos();
        XMFLOAT4 margin{ p.x - 0.0f, p.y - 0.1f, p.z - 0.0f, p.w - 0.0f };

        SetLightPos(margin);
    }

    if (Input::IsKey(DIK_W))
    {
        XMFLOAT4 p = GetLightPos();
        XMFLOAT4 margin{ p.x - 0.0f, p.y - 0.0f, p.z + 0.1f, p.w + 0.0f };

        SetLightPos(margin);
    }

    if (Input::IsKey(DIK_S))
    {
        XMFLOAT4 p = GetLightPos();
        XMFLOAT4 margin{ p.x - 0.0f, p.y - 0.0f, p.z - 0.1f, p.w - 0.0f };

        SetLightPos(margin);
    }


    XMFLOAT4 tmp{ GetLightPos() };
    light.position_ = { tmp.x, tmp.y, tmp.z };

    CBUFF_STAGESCENE cb;
    cb.lightPosition = lightSourcePosition_;
    XMStoreFloat4(&cb.eyePos, Camera::GetEyePosition());

    Direct3D::pContext_->UpdateSubresource(pCBStageScene_, 0, NULL, &cb, 0, 0);

    Direct3D::pContext_->VSSetConstantBuffers(1, 1, &pCBStageScene_); //頂点シェーダー用
    Direct3D::pContext_->PSSetConstantBuffers(1, 1, &pCBStageScene_); //ピクセルシェーダー用


}

//描画
void Stage::Draw()
{
    Model::SetTransform(hDice_, transform_);
    Model::Draw(hDice_);

   /* Model::SetTransform(hArrowX_, arrowX);
    Model::Draw(hArrowX_);

    Model::SetTransform(hArrowY_, arrowY);
    Model::Draw(hArrowY_);

    Model::SetTransform(hArrowZ_, arrowZ);
    Model::Draw(hArrowZ_);*/

    Model::SetTransform(hDonuts_, donutsTr);
    Model::Draw(hDonuts_);

    Model::SetTransform(hLight_, light);
    Model::Draw(hLight_);

 

    Model::SetTransform(hWater_, water_);
    Model::Draw(hWater_);
}

//開放
void Stage::Release()
{
}