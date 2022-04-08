#include "Player.h"
#include "SnowBullet.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>

Player::Player()
	: Speed_(100.0f)
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
	//CreateRenderer("Nick_Idle.bmp");
	GameEngineRenderer* Render = CreateRendererToScale("Right_Beam_Kirby.bmp", { 300, 300 });
	Render->SetIndex(10);

	CreateRenderer("Snow_Bullet.bmp");
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

void Player::Update()
{
	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		// -1.0f * DT
		SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * Speed_);
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * Speed_);
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		SetMove(float4::UP * GameEngineTime::GetDeltaTime() * Speed_);
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_);
	}
	if (true == GameEngineInput::GetInst()->IsDown("SnowBullet"))
	{
		SnowBullet* Ptr = GetLevel()->CreateActor<SnowBullet>();
		Ptr->SetPosition(GetPosition());
	}
	// 키를 누르면 움직임
	//if (0 != GetAsyncKeyState())
	//{
	//
	//}
}

// 렌더러가 다 돌고 렌더링
void Player::Render()
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
