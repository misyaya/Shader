#include "TestScene.h"
#include "Stage.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Engine/Camera.h"

TestScene::TestScene(GameObject* parent)
	:GameObject(parent, "TestScene")
{
}

void TestScene::Initialize()
{

	Instantiate<Stage>(this);

	Camera::SetPosition(XMFLOAT3(2, 6, -8));

	Camera::SetTarget(XMFLOAT3(0, 2, 0));
}

void TestScene::Update()
{
}

void TestScene::Draw()
{
}

void TestScene::Release()
{
}
