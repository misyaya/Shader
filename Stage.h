#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class Stage : public GameObject
{
    int hGround_;    //モデル番号
    int hBall_;
    int hArrowX_;
    int hArrowY_;
    int hArrowZ_;
    int hWall_;

    Transform ground;
    Transform ball;
    Transform arrowX;
    Transform arrowY;
    Transform arrowZ;
    Transform wall;
public:
    //コンストラクタ
    Stage(GameObject* parent);

    //デストラクタ
    ~Stage();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};