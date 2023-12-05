#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class Stage : public GameObject
{
    int hGround_;    //���f���ԍ�
    int hBall_;
    int hArrowX_;
    int hArrowY_;
    int hArrowZ_;
    int hLight_;

    Transform ground;
    Transform ball;
    Transform arrowX;
    Transform arrowY;
    Transform arrowZ;
    Transform light;

    struct CBUFF_STAGESCENE
    {
        XMFLOAT4 lightPosition;
    };
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
};