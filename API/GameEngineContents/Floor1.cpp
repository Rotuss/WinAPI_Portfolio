#include "Floor1.h"
#include "BackGround.h"
#include "FloorLogo.h"
#include "PlayUI.h"
#include "Life.h"
#include "Score.h"
#include "Nick.h"
#include "RedDemon.h"
#include "ContentsEnums.h"
#include "PlayUI.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

Floor1::Floor1()
	:LogoTime_(2.0f)
{
}

Floor1::~Floor1()
{
}

void Floor1::Loading()
{
	{
		BackGround* Actor = CreateActor<BackGround>(0);
		Actor->GetRenderer()->SetImage("Floor1.bmp");

		float4 BackActor = {};
		BackActor.x = (Actor->GetRenderer()->GetImage()->GetScale().Half().x);
		BackActor.y = (Actor->GetRenderer()->GetImage()->GetScale().Half().y);

		Actor->GetRenderer()->SetPivot(BackActor);
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
		Player->SetPosition({400,710});
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
	}
}

void Floor1::Update()
{
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
	//Nick::BgmPlayer_ = GameEngineSound::SoundPlayControl("SnowBros_Stage_Theme1.mp3");
	Time_ = 5.0f;
}

void Floor1::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}
