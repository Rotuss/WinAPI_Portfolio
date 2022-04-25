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

// �ƹ��� Ű�� ������ �ʾҴٸ� false, � Ű�� ���ȴٸ� true
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

// Ű �ݺ� �Է½� ���ŷο� �����ִ� �Լ�
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
	// Nick���� ��ġ�� ���ϴ� ���� �ƴ�, �� Floor���� �����ؾ��ϹǷ� ���⼭ �����ϴ� ���� �ƴ�. �� Floor���� �۾�
	//SetPosition(GameEngineWindow::GetScale().Half());
	//SetScale({ 50,50 });

	// �ݸ��� ��Ʈ�ڽ�
	PlayerCollision_ = CreateCollision("PlayerHitBox", {68, 100});

	// �ִϸ��̼�
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
	// ����, ���� �̹����� �ִϸ��̼��� �����Ű���� �� �� ���
	//NickAnimationRender_->CreateFolderAnimation("������", "Walk_Right", 0, 3, 0.1f, true);
	NickAnimationRender_->ChangeAnimation("Appear");
	NickAnimationRender_->SetPivotType(RenderPivot::CENTER);

	//AnimationName_ = "Idle_";
	CurrentDir_ = NickDir::RIGHT;
	CurrentState_ = NickState::APPEAR;
	
	// ���� Ȯ���� �ӽ� ����
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

	// �������� ���͸� ã�� �� �ֵ��� ����(ĳĪ)
	//LevelRegist("MainPlayer");
}

void Nick::Update()
{
	// �����Լ�, State
	DirAnimationCheck();
	StateUpdate();
	CollisionFloorCheck();

	GetLevel()->SetCameraPos(GetPosition() - GameEngineWindow::GetInst().GetScale().Half());
	CameraLock();

	NextCheck();
	WallCheck();
	// �߷� ���� => ����?(�߷� �����Ͽ� ���� ���� ��� �¿� �������� ���� ������ �� ����)
	{
		// Player ��ġ���� 
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
	// ������� ���
	/*
	if (2.5f < GameEngineInput::GetInst()->GetTime("SnowBullet"))
	{
		SnowBullet* Ptr = GetLevel()->CreateActor<SnowBullet>();
		Ptr->SetPosition(GetPosition());
	}
	*/
	// Ű�� ������ ������
	//if (0 != GetAsyncKeyState())
	//{
	//
	//}
}

// �������� �� ���� ������
void Nick::Render()
{
	//DebugRectRender();
	
	/*
	GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find("Nick_Idle.bmp");
	if (nullptr == FindImage)
	{
		MsgBoxAssert("�̹����� ã�� ���� �����ϴ�.");
	}
	// GameEngine�� static�� ����? => ����, 2�� ��� �ʿ䰡 X, �̱���� ����
	GameEngine::BackBufferImage()->BitCopyCenter(FindImage, GetPosition());
	*/
	Time_ += GameEngineTime::GetDeltaTime();
	std::string Text = std::to_string(Time_);
	TextOutA(GameEngine::BackBufferImage()->ImageDC(), 0, 0, Text.c_str(), Text.size());
}

void Nick::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	// ���� ����ó�� �����ϱ� ���� static Nick�� ���� ������ �� �����ͷ� ����
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
		MsgBoxAssert("�� �浹�� �̹����� ã�� ���߽��ϴ�.");
	}
}