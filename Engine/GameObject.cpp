#include "GameObject.h"
#include "SphereCollider.h"

GameObject::GameObject()
	:pParent_(nullptr),IsDead_(false)
{
}

GameObject::GameObject(GameObject* parent, const std::string& name)
	:pParent_(parent),objectName_(name), IsDead_(false),pCollider_(nullptr)
{
	if (parent != nullptr)
		this->transform_.pParent_ = &(parent->transform_);
}

GameObject::~GameObject()
{
}

void GameObject::UpdateSub()
{
	Update();

	RoundRobin(GetRootJob());
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	{
		(*itr)->UpdateSub();
	}
	for (auto itr = childList_.begin(); itr != childList_.end();)
	{
		if ((*itr)->IsDead_ == true)
		{
			(*itr)->ReleaseSub();
			SAFE_DELETE(*itr);
			itr = childList_.erase(itr);
		}
		else
		{
			itr++;
		}
	}
}

void GameObject::DrawSub()
{
	Draw();
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
		(*itr)->DrawSub();
}

void GameObject::ReleaseSub()
{
	Release();

	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	{	(*itr)->ReleaseSub();
		SAFE_DELETE(*itr);
	}
}

void GameObject::KillMe()
{
	IsDead_ = true;
}

void GameObject::SetPosition(XMFLOAT3 position)
{
	transform_.position_ = position;
}

void GameObject::SetPosition(float x, float y, float z)
{
	SetPosition(XMFLOAT3(x, y, z));
}

void GameObject::SetRotate(XMFLOAT3 rotate)
{
	transform_.rotate_ = rotate;
}

void GameObject::SetRotate(float x, float y, float z)
{
	SetRotate(XMFLOAT3(x, y, z));
}

void GameObject::SetScale(XMFLOAT3 scale)
{
	transform_.scale_ = scale;
}

void GameObject::SetScale(float x, float y, float z)
{
	SetScale(XMFLOAT3(x, y, z));
}

GameObject* GameObject::FindChildObject(string _objName)
{
	if (_objName == this->objectName_)
	{
		return(this); //������_objName�̃I�u�W�F�N�g�������I
	}
	else
	{
		//for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
		for(auto itr:childList_) //���Ɠ����Ӗ�
		{
			GameObject* obj = itr->FindChildObject(_objName);
			if (obj != nullptr)
				return obj;
		}
	}
	return nullptr;
}

/// <summary>
/// �ċN�Ăяo����RootJob��T���Ă��̃A�h���X��Ԃ��֐�
/// </summary>
/// <returns>RootJob�̃A�h���X(GameObject * �^)</returns>
GameObject* GameObject::GetRootJob()
{
	//�e�����邩�m�F
	if (pParent_ == nullptr)
		return this;
	
	//�����炻�̐e�̐e�𒲂ׂ�
	return pParent_->GetRootJob();
}

GameObject* GameObject::FindObject(string _objName)
{
	return GetRootJob()->FindChildObject(_objName);
}

void GameObject::AddCollider(SphereCollider* pCollider)
{
	pCollider_ = pCollider;
}

void GameObject::Collision(GameObject* pTarget)
{
	if (pTarget == this || pTarget->pCollider_ == nullptr)
		return; //�������g�Ƃ̓����蔻��A�܂��̓^�[�Q�b�g�ɃR���C�_�[���A�^�b�`����Ă��Ȃ�
	/*XMVECTOR v{ transform_.position_.x - pTarget->transform_.position_.x,
				transform_.position_.y - pTarget->transform_.position_.y,
				transform_.position_.z - pTarget->transform_.position_.z,
				0 };
	XMVECTOR dist = XMVector3Dot(v, v);*/
	float dist = (transform_.position_.x - pTarget->transform_.position_.x) * (transform_.position_.x - pTarget->transform_.position_.x)
		+ (transform_.position_.y - pTarget->transform_.position_.y) * (transform_.position_.y - pTarget->transform_.position_.y)
		+ (transform_.position_.z - pTarget->transform_.position_.z) * (transform_.position_.z - pTarget->transform_.position_.z);
	float  rDist = (this->pCollider_->GetRadius() + pTarget->pCollider_->GetRadius()) * (this->pCollider_->GetRadius() + pTarget->pCollider_->GetRadius());
	
	
	//�����ƃ^�[�Q�b�g�̋����@<= R1+R2�Ȃ�
	//�����A�����̃R���C�_�[�ƃ^�[�Q�b�g���Ԃ����Ă�����
	//onCollision(pTarget)���Ăяo���I
	if (dist <= rDist)
	{
		//onCollision();���Ăڂ��I
		OnCollision(pTarget);
	}
		
}

void GameObject::RoundRobin(GameObject* pTarget)
{
	if (pCollider_ == nullptr)
		return;
	if(pTarget->pCollider_ != nullptr)
		Collision(pTarget);

	//�����̎q���O���ƃ^�[�Q�b�g
	for (auto itr = pTarget->childList_.begin(); itr != pTarget->childList_.end(); itr++)
		RoundRobin(*itr);


}
