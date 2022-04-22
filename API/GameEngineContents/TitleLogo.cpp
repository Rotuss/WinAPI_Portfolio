#include "TitleLogo.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>

TitleLogo::TitleLogo()
{
}

TitleLogo::~TitleLogo()
{
}

void TitleLogo::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	
	GameEngineRenderer* PushStart_ = CreateRenderer(2,RenderPivot::CENTER, { 0, 208 });;
	PushStart_->CreateAnimation("Push_Start.bmp", "Push_Start", 0, 1, 0.5f, true);
	PushStart_->ChangeAnimation("Push_Start");
}

void TitleLogo::Update()
{
	// ���� ���Ͱ� �������� SelectTitle ȭ������ �̵�
	if (true == GameEngineInput::GetInst()->IsPress("LevelChange"))
	{
		GameEngine::GetInst().ChangeLevel("TitleSelect");
	}
}
