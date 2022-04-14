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

// �ƹ��� Ű�� ������ �ʾҴٸ� false, � Ű�� ���ȴٸ� true
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
	// Nick���� ��ġ�� ���ϴ� ���� �ƴ�, �� Floor���� �����ؾ��ϹǷ� ���⼭ �����ϴ� ���� �ƴ�. �� Floor���� �۾�
	//SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 50,50 });

	//GameEngineRenderer* Render = CreateRenderer("Nick_Right_Walk.bmp");
	//Render->SetIndex(0);
	//Render->SetPivotType(RenderPivot::BOT);

	PlayerCollision_ = CreateCollision("PlayerHitBox", {100, 100});

	// �ִϸ��̼�
	NickAnimationRender_ = CreateRenderer();
	NickAnimationRender_->CreateAnimation("Nick_Walk_Right.bmp", "Walk_Right", 0, 3, 0.1f, true);
	NickAnimationRender_->CreateAnimation("Nick_Walk_Left.bmp", "Walk_Left", 0, 3, 0.1f, true);
	// ����, ���� �̹����� �ִϸ��̼��� �����Ű���� �� �� ���
	//NickAnimationRender_->CreateFolderAnimation("������", "Walk_Right", 0, 3, 0.1f, true);
	NickAnimationRender_->ChangeAnimation("Walk_Right");

	AnimationName_ = "Walk_";
	CurrentDir_ = NickDir::RIGHT;
	//CreateRenderer("Snow_Bullet.bmp");
	//CreateRendererToScale("HPBar.bmp", float4(300.0f, 20.0f), RenderPivot::CENTER, float4(0.0f, -100.0f));
	
	// ���� Ȯ���� �ӽ� ����
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
	// �����Լ�, State
	
	DirAnimationCheck();
	StateUpdate();
	FloorColImage_ = GameEngineImageManager::GetInst()->Find("Colfloor01.bmp");
	if (nullptr == FloorColImage_)
	{
		MsgBoxAssert("Floor �浹�� �̹����� ã�� ���߽��ϴ�.");
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
