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

Nick* Nick::MainPlayer = nullptr;

Nick::Nick()
	: MoveDir_(float4::ZERO)
	, Speed_(200.0f)
	//, Gravity_(100.0f)
	, Time_(0.0f)
	, AppTime_(1.0f)
	, DTime_(0.5f)
	, LifeCount_(2)
{
}

Nick::~Nick()
{
}

// 아무런 키도 눌리지 않았다면 false, 어떤 키든 눌렸다면 true
bool Nick::IsMoveKey()
{
	if (false == GameEngineInput::GetInst()->IsPress("MoveLeft") &&
		false == GameEngineInput::GetInst()->IsPress("MoveRight"))
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
		case NickState::DOWN:
			DownStart();
			break;
		case NickState::ATTACK:
			AttackStart();
			break;
		case NickState::PUSH:
			PushStart();
			break;
		case NickState::APPEAR:
			AppearStart();
			break;
		case NickState::DEATH:
			DeathStart();
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
	case NickState::DOWN:
		DownUpdate();
		break;
	case NickState::ATTACK:
		AttackUpdate();
		break;
	case NickState::PUSH:
		PushUpdate();
		break;
	case NickState::APPEAR:
		AppearUpdate();
		break;
	case NickState::DEATH:
		DeathUpdate();
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
	NickDir CheckDir_ = CurrentDir_;

	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		CheckDir_ = NickDir::RIGHT;
		ChangeDirText_ = "Right";
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		CheckDir_ = NickDir::LEFT;
		ChangeDirText_ = "Left";
	}

	if (CheckDir_ != CurrentDir_)
	{
		NickAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
		CurrentDir_ = CheckDir_;
	}
}

void Nick::Start()
{
	// Nick에서 위치를 정하는 것이 아닌, 각 Floor에서 지정해야하므로 여기서 구현하는 것이 아님. 각 Floor에서 작업
	//SetPosition(GameEngineWindow::GetScale().Half());
	//SetScale({ 50,50 });

	// 콜리전 히트박스
	PlayerCollision_ = CreateCollision("PlayerHitBox", {68, 100});

	// 애니메이션
	NickAnimationRender_ = CreateRenderer();
	
	NickAnimationRender_->CreateAnimation("Nick_Idle_Right.bmp", "Idle_Right", 0, 0, 0.0f, false);
	NickAnimationRender_->CreateAnimation("Nick_Idle_Left.bmp", "Idle_Left", 0, 0, 0.0f, false);

	NickAnimationRender_->CreateAnimation("Nick_Move_Right.bmp", "Move_Right", 0, 2, 0.12f, true);
	NickAnimationRender_->CreateAnimation("Nick_Move_Left.bmp", "Move_Left", 0, 2, 0.12f, true);
	
	NickAnimationRender_->CreateAnimation("Nick_Jump_Right.bmp", "Jump_Right", 0, 4, 0.1f, false);
	NickAnimationRender_->CreateAnimation("Nick_Jump_Left.bmp", "Jump_Left", 0, 4, 0.1f, false);

	NickAnimationRender_->CreateAnimation("Nick_Down_Right.bmp", "Down_Right", 0, 0, 0.0f, false);
	NickAnimationRender_->CreateAnimation("Nick_Down_Left.bmp", "Down_Left", 0, 0, 0.0f, false);
	
	NickAnimationRender_->CreateAnimation("Nick_Shooting_Right.bmp", "Attack_Right", 0, 1, 0.1f, false);
	NickAnimationRender_->CreateAnimation("Nick_Shooting_Left.bmp", "Attack_Left", 0, 1, 0.1f, false);

	NickAnimationRender_->CreateAnimation("Nick_Push_Right.bmp", "Push_Right", 0, 2, 0.1f, true);
	NickAnimationRender_->CreateAnimation("Nick_Push_Left.bmp", "Push_Left", 0, 2, 0.1f, true);

	NickAnimationRender_->CreateAnimation("Appear.bmp", "Appear", 0, 3, 0.1f, true);
	NickAnimationRender_->CreateAnimation("Nick_Death.bmp", "Death", 0, 2, 0.1f, false);
	// 만일, 폴더 이미지로 애니메이션을 실행시키고자 할 때 사용
	//NickAnimationRender_->CreateFolderAnimation("폴더명", "Walk_Right", 0, 3, 0.1f, true);
	NickAnimationRender_->ChangeAnimation("Appear");
	NickAnimationRender_->SetPivotType(RenderPivot::CENTER);

	//AnimationName_ = "Idle_";
	CurrentDir_ = NickDir::RIGHT;
	CurrentState_ = NickState::APPEAR;
	
	// 알파 확인차 임시 생성
	/*
	Render_ = CreateRendererToScale("Idle.bmp", {300,300}, 100);
	Render_->SetPivot({ 100.0f,0.0f });
	Render_->SetAlpha(100);
	*/
	if (false == GameEngineInput::GetInst()->IsKey("MoveLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("MoveLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("MoveRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("Jump", VK_LSHIFT);
		GameEngineInput::GetInst()->CreateKey("Attack", VK_SPACE);
	}

	// 레벨에서 액터를 찾을 수 있도록 해줌(캐칭)
	//LevelRegist("MainPlayer");
}

void Nick::Update()
{
	// 공통함수, State
	DirAnimationCheck();
	StateUpdate();
	CollisionFloorCheck();

	GetLevel()->SetCameraPos(GetPosition() - GameEngineWindow::GetInst().GetScale().Half());
	CameraLock();

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

void Nick::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	// 전역 변수처럼 관리하기 쉽게 static Nick에 레벨 시작할 때 포인터로 저장
	MainPlayer = this;
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

void Nick::CameraLock()
{
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
}

void Nick::CollisionFloorCheck()
{
	if (strcmp(GetLevel()->GetNameConstPtr(), "Floor1") == 0)
	{
		FloorColImage_ = GameEngineImageManager::GetInst()->Find("ColFloor1.bmp");
	}
	else if (strcmp(GetLevel()->GetNameConstPtr(), "Floor2") == 0)
	{
		FloorColImage_ = GameEngineImageManager::GetInst()->Find("ColFloor2.bmp");
	}

	if (nullptr == FloorColImage_)
	{
		MsgBoxAssert("맵 충돌용 이미지를 찾지 못했습니다.");
	}
}