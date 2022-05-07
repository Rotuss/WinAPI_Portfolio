#include "Floor1.h"
#include "BackGround.h"
#include "FloorLogo.h"
#include "PlayUI.h"
#include "Life.h"
#include "Score.h"
#include "Nick.h"
#include "RedDemon.h"
#include "ContentsEnums.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

Floor1::Floor1()
	: LogoTime_(2.0f)
	, NextFloorTime_(5.0f)
	, LogoShow_(true)
	, CameraCheck_(true)
{
}

Floor1::~Floor1()
{
}

void Floor1::Loading()
{
}

void Floor1::Update()
{
	/*
	if (true == LogoShow_)
	{
		LogoActor = CreateActor<FloorLogo>(2);
		LogoActor->GetRenderer()->SetImage("Floor01_Logo.bmp");
		LogoActor->GetRenderer()->SetPivot({ GameEngineWindow::GetScale().Half().x,GameEngineWindow::GetScale().Half().y - 25.f });

		LogoShow_ = false;
	}
	else if (false == LogoShow_)
	{
		LogoTime_ -= GameEngineTime::GetDeltaTime();
		if (LogoTime_ <= 0)
		{
			LogoActor->Off();
		}
	}
	*/
	
	if (0 == Enemycount_)
	{
		NextFloorTime_ -= GameEngineTime::GetDeltaTime();
		if (NextFloorTime_ <= 0)
		{
			if (true == CameraCheck_)
			{
				CameraMoveUp();
			}
		}
	}
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GameEngine::GetInst().ChangeLevel("Floor2");
	}
	if (true == GameEngineInput::GetInst()->IsDown("Debug"))
	{
		GameEngineLevel::IsDebugModeSwitch();
	}
}

void Floor1::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	Nick::BgmPlayer_ = GameEngineSound::SoundPlayControl("SnowBros_Floor_Track.mp3");
	Time_ = 5.0f;
	CameraCheck_ = true;
	if (GetCameraPos().y <= -896)
	{
		float4 CurrentCametaPos = GetCameraPos();
		CurrentCametaPos.y = 0;
		SetCameraPos(CurrentCametaPos);
	}
	{
		BackGround* Actor = CreateActor<BackGround>(0);
		Actor->GetRenderer()->SetImage("Floor1.bmp");
		Actor->GetRenderer()->SetPivot({ GameEngineWindow::GetScale().Half().x,0 });
		//Actor->CreateCollision("Next", { 100, 100 }, { 200, -300 });
		//Actor->CreateCollision("Wall", { 100, 100 }, { 0, 0 });
	}

	{
		//FloorLogo* Actor = CreateActor<FloorLogo>(2);
		//Actor->GetRenderer()->SetImage("Floor01_Logo.bmp");
		//Actor->GetRenderer()->SetPivot({ GameEngineWindow::GetScale().Half().x,GameEngineWindow::GetScale().Half().y - 25.f });
	}

	{
		PlayUI* Actor = CreateActor<PlayUI>(0);

		LifeUI = CreateActor<Life>(1);
		ScoreUI = CreateActor<Score>(1);
	}

	{
		Nick* Player = CreateActor<Nick>(10);
		Player->SetPosition({ 400,727 });
	}

	{
		// 시간 맞춰주기
		RedDemon* RedDemon0 = CreateActor<RedDemon>((int)ORDER::MONSTER);
		RedDemon0->SetPosition({ 330,0 });

		RedDemon* RedDemon1 = CreateActor<RedDemon>((int)ORDER::MONSTER);
		RedDemon1->SetPosition({ 180,0 });

		RedDemon* RedDemon2 = CreateActor<RedDemon>((int)ORDER::MONSTER);
		RedDemon2->SetPosition({ 840,0 });

		RedDemon* RedDemon3 = CreateActor<RedDemon>((int)ORDER::MONSTER);
		RedDemon3->SetPosition({ 280,0 });

		Enemycount_ = 4;
	}
}

void Floor1::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Reset();
}

void Floor1::CameraMoveUp()
{
	// 레벨체인지 나갈 때
	CameraCheck_ = true;
	float4 CurrentCametaPos = GetCameraPos();
	CurrentCametaPos.y -= GameEngineTime::GetDeltaTime() * 200;
	SetCameraPos(CurrentCametaPos);

	if (CurrentCametaPos.y <= -896)
	{
		CurrentCametaPos.y = -896;
		GameEngine::GetInst().ChangeLevel("Floor2");
		CameraCheck_ = false;
		NextFloorTime_ = 5.0f;
	}
}
