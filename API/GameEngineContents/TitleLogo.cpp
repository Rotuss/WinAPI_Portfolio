#include "TitleLogo.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>

TitleLogo::TitleLogo()
	: EnterCheck_(false)
	, DirCheck_(false)
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
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange") && true == EnterCheck_ && true == DirCheck_)
	{
		GameEngine::GetInst().ChangeLevel("Floor1");
		EnterCheck_ = false;
	}
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange") && false == EnterCheck_)
	{
		SetPosition(GameEngineWindow::GetScale().Half() - float4{ 315,-305 });
		CreateRenderer("SelectUIIcon.bmp");
		EnterCheck_ = true;
		DirCheck_ = true;
	}

	if (true == EnterCheck_)
	{
		if (true == GameEngineInput::GetInst()->IsDown("Left"))
		{
			SetPosition(GameEngineWindow::GetScale().Half() - float4{ 315,-305 });
			CreateRenderer("SelectUIIcon.bmp");
			DirCheck_ = true;
		}
		else if (true == GameEngineInput::GetInst()->IsDown("Right"))
		{
			SetPosition(GameEngineWindow::GetScale().Half() - float4{ 0,-305 });
			CreateRenderer("SelectUIIcon.bmp");
			DirCheck_ = false;
		}
	}
}
