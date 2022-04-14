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
	: MoveDir_(float4::ZERO)
	, Speed_(500.0f)
	, AccSpeed_(500.0f)
	, Gravity_(100.0f)
	, Time_(0.0f)
{
}

Nick::~Nick()
{
}

// 아무런 키도 눌리지 않았다면 false, 어떤 키든 눌렸다면 true
bool Nick::IsMoveKey()
{
	if (false == GameEngineInput::GetInst()->IsPress("MoveLeft") &&
		false == GameEngineInput::GetInst()->IsPress("MoveRight") &&
		false == GameEngineInput::GetInst()->IsPress("MoveUp") &&
		false == GameEngineInput::GetInst()->IsPress("MoveDown"))
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
		case NickState::IDLE:
			IdleStart();
			break;
		case NickState::MOVE:
			MoveStart();
			break;
		case NickState::JUMP:
			JumpStart();
			break;
		case NickState::ATTACK:
			AttackStart();
			break;
		case NickState::MAX:
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
	case NickState::IDLE:
		IdleUpdate();
		break;
	case NickState::MOVE:
		MoveUpdate();
		break;
	case NickState::JUMP:
		JumpUpdate();
		break;
	case NickState::ATTACK:
		AttackUpdate();
		break;
	case NickState::MAX:
		break;
	default:
		break;
	}
}

// 키 반복 입력시 번거로움 덜어주는 함수
void NickChangeAnimation(const std::string& _Name)
{
	//NickAnimationRender_->ChangeAnimation(_Name);
	//NickAnimationRender_->ChangeAnimation(_Name);
	//NickAnimationRender_->ChangeAnimation(_Name);
	//NickAnimationRender_->ChangeAnimation(_Name);
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
		NickAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText);
	}
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
	NickAnimationRender_ = CreateRenderer();
	NickAnimationRender_->CreateAnimation("Nick_Walk_Right.bmp", "Walk_Right", 0, 3, 0.1f, true);
	NickAnimationRender_->CreateAnimation("Nick_Walk_Left.bmp", "Walk_Left", 0, 3, 0.1f, true);
	// 만일, 폴더 이미지로 애니메이션을 실행시키고자 할 때 사용
	//NickAnimationRender_->CreateFolderAnimation("폴더명", "Walk_Right", 0, 3, 0.1f, true);
	NickAnimationRender_->ChangeAnimation("Walk_Right");

	AnimationName_ = "Walk_";
	CurrentDir_ = NickDir::RIGHT;
	//CreateRenderer("Snow_Bullet.bmp");
	//CreateRendererToScale("HPBar.bmp", float4(300.0f, 20.0f), RenderPivot::CENTER, float4(0.0f, -100.0f));
	
	// 알파 확인차 임시 생성
	/*
	Render_ = CreateRendererToScale("Idle.bmp", {300,300}, 100);
	Render_->SetPivot({ 100.0f,0.0f });
	Render_->SetAlpha(100);
	*/
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
	StateUpdate();
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
	Time_ += GameEngineTime::GetDeltaTime();
	std::string Text = std::to_string(Time_);
	TextOutA(GameEngine::BackBufferImage()->ImageDC(), 0, 0, Text.c_str(), Text.size());
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
