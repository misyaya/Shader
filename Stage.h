#pragma once
#include "Engine/GameObject.h"

struct CBUFF_STAGESCENE
{
    XMFLOAT4 lightPosition;
    XMFLOAT4 eyePos;

};


//◆◆◆を管理するクラス
class Stage : public GameObject
{

    int hArrowX_;
    int hArrowY_;
    int hArrowZ_;
    int hDonuts_;
    int hLight_;


    Transform arrowX;
    Transform arrowY;
    Transform arrowZ;
    Transform light;

    ID3D11Buffer* pCBStageScene_;

    void IntConstantBuffer();
    XMFLOAT4 lightSourcePosition_;
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

    void SetLightPos(XMFLOAT4& _pos) { lightSourcePosition_ = _pos; }
    XMFLOAT4 GetLightPos() { return(lightSourcePosition_); };
};