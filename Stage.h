#pragma once
#include "Engine/GameObject.h"

struct CBUFF_STAGESCENE
{
    XMFLOAT4 lightPosition;
    XMFLOAT4 eyePos;

};


//���������Ǘ�����N���X
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
    //�R���X�g���N�^
    Stage(GameObject* parent);

    //�f�X�g���N�^
    ~Stage();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    void SetLightPos(XMFLOAT4& _pos) { lightSourcePosition_ = _pos; }
    XMFLOAT4 GetLightPos() { return(lightSourcePosition_); };
};