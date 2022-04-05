#include "Player.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineImageManager.h>

Player::Player()
{
}

Player::~Player()
{
}

void Player::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 50,50 });

	// CreateRenderer("Nick_Idle.bmp", RenderPivot::CENTER, { 0, 0 });
	CreateRenderer("Nick_Idle.bmp");
	CreateRendererToScale("HPBar.bmp", float4(300.0f, 20.0f), RenderPivot::CENTER, float4(0.0f, -100.0f));
}

// �������� �� ���� ������
void Player::Render()
{
	//DebugRectRender();
	
	/*
	GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find("Nick_Idle.bmp");
	if (nullptr == FindImage)
	{
		MsgBoxAssert("�̹����� ã�� ���� �����ϴ�.");
	}
	// GameEngine�� static�� ����? => ����, 2�� ��� �ʿ䰡 X, �̱���� ����
	GameEngine::BackBufferImage()->BitCopyCenter(FindImage, GetPosition());
	*/
}
