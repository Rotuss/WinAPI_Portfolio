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
#include <GameEngine/GameEngineCollision.h>

Nick::Nick()
	: Speed_(100.0f)
	, Gravity_(100.0f)
{
}

Nick::~Nick()
{
}

// 아무런 키도 눌리지 않았다면 false, 어떤 키든 눌렸다면 true
bool Nick::IsMoveKey()
{
	if (false == GameEngineInput::GetInst()->IsDown("MoveLeft") &&
		false == GameEngineInput::GetInst()->IsDown("MoveRight") &&
		false == GameEngineInput::GetInst()->IsDown("MoveUp") &&
		false == GameEngineInput::GetInst()->IsDown("MoveDown"))
	{
		return false;
	}
	return true;
}

void Nick::ChangeState(NickState _State)
{
	if (CurrentState_ != _State)
	{
		switch (_State)
		{
		case IDLE:
			IdleStart();
			break;
		case MOVE:
			MoveStart();
			break;
		case ATTACK:
			AttackStart();
			break;
		case MAX:
			break;
		default:
			break;
		}
	}

	CurrentState_ = _State;
}

void Nick::StateUpdate()
{
	switch (CurrentState_)
	{
	case IDLE:
		IdleUpdate();
		break;
	case MOVE:
		MoveUpdate();
		break;
	case ATTACK:
		AttackUpdate();
		break;
	case MAX:
		break;
	default:
		break;
	}
}

void Nick::DirAnimationCheck()
{
	std::string ChangeName_;

	NickDir CheckDir_ = CurrentDir_;
	std::string ChangeDirText = "Right";

	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		CheckDir_ = NickDir::RIGHT;
		ChangeDirText = "Right";
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		CheckDir_ = NickDir::LEFT;
		ChangeDirText = "Left";
	}

	if (CheckDir_ != CurrentDir_)
	{
		NickAnimationRender->ChangeAnimation(AnimationName_ + ChangeDirText);
	}
}

void Nick::NickStateUpdate()
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

	PlayerCollision_ = CreateCollision("PlayerHitBox", {100, 100});

	// 애니메이션
	NickAnimationRender = CreateRenderer();
	NickAnimationRender->CreateAnimation("Nick_Walk_Right.bmp", "Walk_Right", 0, 3, 0.1f, true);
	NickAnimationRender->CreateAnimation("Nick_Walk_Left.bmp", "Walk_Left", 0, 3, 0.1f, true);
	NickAnimationRender->ChangeAnimation("Walk_Right");
	NickAnimationRender->ChangeAnimation("Walk_Left");
	//Render->CreateAnimation("Nick_Right_Walk.bmp", "Right_Walk", 0, 3, 0.1f, false);

	AnimationName_ = "Walk_";
	CurrentDir_ = NickDir::RIGHT;
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
	// 공통함수, State
	
	DirAnimationCheck();
	NickStateUpdate();
	FloorColImage_ = GameEngineImageManager::GetInst()->Find("Colfloor01.bmp");
	if (nullptr == FloorColImage_)
	{
		MsgBoxAssert("Floor 충돌용 이미지를 찾지 못했습니다.");
	}

	float4 CheckPos_;
	float4 MoveDir_ = float4::ZERO;
	/*
	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
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
	*/
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
	
	if (0 > GetLevel()->GetCameraPos().x)
	{
		float4 CurrentCameraPos = GetLevel()->GetCameraPos();
		CurrentCameraPos.x = 0;
		GetLevel()->SetCameraPos(CurrentCameraPos);
	}
	if (0 > GetLevel()->GetCameraPos().y)
	{
		float4 CurrentCameraPos = GetLevel()->GetCameraPos();
		CurrentCameraPos.y = 0;
		GetLevel()->SetCameraPos(CurrentCameraPos);
	}

	float FloorScaleX = 1024;
	float FloorScaleY = 964;
	float CameraRectX = 1024;
	float CameraRectY = 964;
	if (FloorScaleX <= GetLevel()->GetCameraPos().x + CameraRectX)
	{
		float4 CurrentCameraPos = GetLevel()->GetCameraPos();
		CurrentCameraPos.x = GetLevel()->GetCameraPos().x - (GetLevel()->GetCameraPos().x + CameraRectX - FloorScaleX);
		GetLevel()->SetCameraPos(CurrentCameraPos);
	}
	if (FloorScaleY <= GetLevel()->GetCameraPos().y + CameraRectY)
	{
		float4 CurrentCameraPos = GetLevel()->GetCameraPos();
		CurrentCameraPos.y = GetLevel()->GetCameraPos().y - (GetLevel()->GetCameraPos().y + CameraRectY - FloorScaleY);
		GetLevel()->SetCameraPos(CurrentCameraPos);
	}
	NextCheck();
	WallCheck();
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
	/*
	if (true == GameEngineInput::GetInst()->IsDown("SnowBullet"))
	{
		SnowBullet* Ptr = GetLevel()->CreateActor<SnowBullet>();
		Ptr->SetPosition(GetPosition());
	}
	*/
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

void Nick::NextCheck()
{
	if (true == PlayerCollision_->CollisionCheck("Next", CollisionType::RECT, CollisionType::RECT))
	{
		//GameEngine::GetInst().ChangeLevel("")
	}
}

void Nick::WallCheck()
{
	std::vector<GameEngineCollision*> ColList;
	if (true == PlayerCollision_->CollisionResult("Wall", ColList, CollisionType::RECT, CollisionType::RECT))
	{
		for (size_t i = 0; i < ColList.size(); ++i)
		{
			ColList[i]->Death();
		}
	}
}
