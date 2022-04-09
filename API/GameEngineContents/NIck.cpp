#include "Nick.h"
#include "SnowBullet.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>

Nick::Nick()
	: Speed_(100.0f)
	, Gravity_(100.0f)
{
}

Nick::~Nick()
{
}

void Nick::Start()
{
	// Nick에서 위치를 정하는 것이 아닌, 각 Floor에서 지정해야하므로 여기서 구현하는 것이 아님. 각 Floor에서 작업
	//SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 50,50 });

	//GameEngineRenderer* Render = CreateRenderer("Nick_Right_Walk.bmp");
	//Render->SetIndex(0);
	//Render->SetPivotType(RenderPivot::BOT);

	// 애니메이션
	GameEngineRenderer* Render = CreateRenderer();
	Render->CreateAnimation("Nick_Right_Walk.bmp", "Right_Walk", 0, 3, 0.1f, true);
	Render->ChangeAnimation("Right_Walk");
	//Render->CreateAnimation("Nick_Right_Walk.bmp", "Right_Walk", 0, 3, 0.1f, false);

	//CreateRenderer("Snow_Bullet.bmp");
	//CreateRendererToScale("HPBar.bmp", float4(300.0f, 20.0f), RenderPivot::CENTER, float4(0.0f, -100.0f));

	if (false == GameEngineInput::GetInst()->IsKey("MoveLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("MoveLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("MoveRight", 'D');
		GameEngineInput::GetInst()->CreateKey("MoveUp", 'W');
		GameEngineInput::GetInst()->CreateKey("MoveDown", 'S');
		GameEngineInput::GetInst()->CreateKey("Jump", VK_LSHIFT);
		GameEngineInput::GetInst()->CreateKey("SnowBullet", VK_SPACE);
	}
}

void Nick::Update()
{
	FloorColImage_ = GameEngineImageManager::GetInst()->Find("Colfloor01.bmp");
	if (nullptr == FloorColImage_)
	{
		MsgBoxAssert("Floor 충돌용 이미지를 찾지 못했습니다.");
	}

	float4 CheckPos_;
	float4 MoveDir_ = float4::ZERO;

	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		// -1.0f * DT
		MoveDir_ = float4::LEFT;
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir_ = float4::RIGHT;
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		MoveDir_ = float4::UP;
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		MoveDir_ = float4::DOWN;
	}
	{
		float4 NextPos = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
		float4 CheckPos = NextPos + float4(0.0f, 50.0f);

		int Color = FloorColImage_->GetImagePixel(CheckPos);

		if (RGB(0, 0, 0) != Color)
		{
			SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
		}
	}
	GetLevel()->SetCameraPos(GetPosition() - GameEngineWindow::GetInst().GetScale().Half());
	// 중력 적용 => 뮨제?(중력 적용하여 땅에 닿을 경우 좌우 움직임이 막혀 움직일 수 없음)
	{
		// Player 위치에서 
		//int Color = FloorColImage_->GetImagePixel(GetPosition() + float4(0.0f, 50.0f));

		//AccGravity_ += GameEngineTime::GetDeltaTime() * Gravity_;
		//if (RGB(0, 0, 0) == Color)
		//{
		//	AccGravity_ = 0.0f;
		//}
		//SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * AccGravity_);
	}
	if (true == GameEngineInput::GetInst()->IsDown("SnowBullet"))
	{
		SnowBullet* Ptr = GetLevel()->CreateActor<SnowBullet>();
		Ptr->SetPosition(GetPosition());
	}
	// 기모으기 기능
	/*
	if (2.5f < GameEngineInput::GetInst()->GetTime("SnowBullet"))
	{
		SnowBullet* Ptr = GetLevel()->CreateActor<SnowBullet>();
		Ptr->SetPosition(GetPosition());
	}
	*/
	// 키를 누르면 움직임
	//if (0 != GetAsyncKeyState())
	//{
	//
	//}
}

// 렌더러가 다 돌고 렌더링
void Nick::Render()
{
	//DebugRectRender();
	
	/*
	GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find("Nick_Idle.bmp");
	if (nullptr == FindImage)
	{
		MsgBoxAssert("이미지를 찾을 수가 없습니다.");
	}
	// GameEngine이 static인 이유? => 편함, 2개 띄울 필요가 X, 싱글톤과 유사
	GameEngine::BackBufferImage()->BitCopyCenter(FindImage, GetPosition());
	*/
}
