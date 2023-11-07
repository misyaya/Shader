#pragma once

#include <string>
#include <list>
#include "Transform.h"
#include "Direct3D.h"

using std::string;
using std::list;

class SphereCollider;

class GameObject
{
protected:
	list<GameObject*> childList_;
	Transform	transform_;
	GameObject*	pParent_;
	string		objectName_;
	SphereCollider* pCollider_;
	bool IsDead_;

public:
	GameObject();
	GameObject(GameObject* parent, const std::string& name);
	~GameObject();

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Release()  = 0;


	void UpdateSub();
	void DrawSub();
	void ReleaseSub();
	void KillMe();

	void SetPosition(XMFLOAT3 position);
	void SetPosition(float x, float y, float z);
	void SetRotate(XMFLOAT3 rotate);
	void SetRotate(float x, float y, float z);
	void SetScale(XMFLOAT3 scale);
	void SetScale(float x, float y, float z);

	GameObject* FindChildObject(string _objName);
	GameObject* GetRootJob();
	GameObject* FindObject(string _objName);
	void AddCollider(SphereCollider* pCollider);
	void Collision(GameObject* pTarget);
	void RoundRobin(GameObject* pTarget);

	virtual void OnCollision(GameObject* pTaregt){}

public:
	//テンプレートの定義
	template <class T>
	GameObject* Instantiate(GameObject* parent)
	{
		T* pObject;
		pObject = new T(parent);
		pObject->Initialize();
		childList_.push_back(pObject);
		return pObject;
	}
};