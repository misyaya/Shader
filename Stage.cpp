#include "Stage.h"
#include "Engine/Model.h"

//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"), hGround_(-1), hBall_(-1), hArrowX_(-1),hWall_(-1)
{
}

//デストラクタ
Stage::~Stage()
{
}

//初期化
void Stage::Initialize()
{
    // 床
    hGround_ = Model::Load("Assets/ground.fbx");
    assert(hGround_ >= 0);

    // ボール
    hBall_ = Model::Load("Assets/ball.fbx");
    assert(hBall_ >= 0);

    // Xアロー
    hArrowX_ = Model::Load("Assets/arrow.fbx");
    assert(hArrowX_ >= 0);

    // Yアロー
    hArrowY_ = Model::Load("Assets/arrow.fbx");
    assert(hArrowY_ >= 0);

    // Xアロー
    hArrowZ_ = Model::Load("Assets/arrow.fbx");
    assert(hArrowZ_ >= 0);

    // 
    hWall_ = Model::Load("Assets/wall3.fbx");
    assert(hWall_ >= 0);

    ground.scale_ = XMFLOAT3(5.0f,5.0f,5.0f);

    //ball.position_ = XMFLOAT3(2.0f, 0.5f, 0.5f);
    ball.position_ = XMFLOAT3(2.0f, 0.5f, 0.5f);


    arrowX.scale_ = XMFLOAT3(0.2f,0.2f,0.2f);
    arrowX.position_ = XMFLOAT3(0.0f,0.5f,-1.0f);

    arrowY.scale_ = XMFLOAT3(0.2f, 0.2f, 0.2f);
    arrowY.rotate_.z = 90.0f;
    arrowY.position_ = XMFLOAT3(0.0f, 0.5f, -1.0f);
    
    arrowZ.scale_ = XMFLOAT3(0.2f, 0.2f, 0.2f);
    arrowZ.rotate_.y = 270.0f;
    arrowZ.position_ = XMFLOAT3(0.0f, 0.5f, -1.0f);

    wall.position_ = XMFLOAT3(0.0f, 1.5f, 0.0f);
}

//更新
void Stage::Update()
{
    wall.rotate_.y += 0.5f;
}

//描画
void Stage::Draw()
{
   Model::SetTransform(hGround_, ground);
   Model::Draw(hGround_);

   Model::SetTransform(hBall_, ball);
   Model::Draw(hBall_);

   Model::SetTransform(hArrowX_, arrowX);
   Model::Draw(hArrowX_);

   Model::SetTransform(hArrowY_, arrowY);
   Model::Draw(hArrowY_);

   Model::SetTransform(hArrowZ_, arrowZ);
   Model::Draw(hArrowZ_);

   Model::SetTransform(hWall_,wall);
   Model::Draw(hWall_);
}

//開放
void Stage::Release()
{
}