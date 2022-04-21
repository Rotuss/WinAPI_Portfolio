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
	// 만약 엔터가 눌렸으면 SelectTitle 화면으로 이동
	if (true == GameEngineInput::GetInst()->IsPress("TitleSelect"))
	{
		// IconUI 좌우설정 미완
		/*
		if (true == GameEngineInput::GetInst()->IsPress("Right"))
		{
			SetPosition(GameEngineWindow::GetScale().Half() - float4{ 0,-305 });
			CreateRenderer("SelectUIIcon.bmp");
		}
		else if (true == GameEngineInput::GetInst()->IsPress("Left"))
		{
			SetPosition(GameEngineWindow::GetScale().Half() - float4{ 315,-305 });
			CreateRenderer("SelectUIIcon.bmp");
		}
		*/
		//else
		{
			SetPosition(GameEngineWindow::GetScale().Half() - float4{ 315,-305 });
			CreateRenderer("SelectUIIcon.bmp");
		}
	}
}
