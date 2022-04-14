#include "GameEngineRenderer.h"
#include "GameEngineImageManager.h"
#include "GameEngine.h"
#include "GameEngineLevel.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTime.h>

// �̿��� �� �ִ� ���� : �Ӽ� -> VC++ ���͸� -> ���̺귯�� ���͸�(�� �߿��� �⺻ �׷���ó���� ���� ���̺귯���� msimg32.lib)
#pragma comment(lib, "msimg32.lib")

GameEngineRenderer::GameEngineRenderer()
	: Image_(nullptr)
	, PivotType_(RenderPivot::CENTER)
	, ScaleMode_(RenderScaleMode::IMAGE)
	, RenderImagePivot_({ 0, 0 })
	, TransColor_(RGB(255, 0, 255))
	, IsCameraEffect_(true)
{
}

GameEngineRenderer::~GameEngineRenderer()
{
}

void GameEngineRenderer::SetImage(const std::string& _Name)
{
	GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find(_Name);
	if (nullptr == FindImage)
	{
		MsgBoxAssertString(_Name + "�������� �ʴ� �̹����� �������� �����Ϸ��� �߽��ϴ�.");
		return;
	}
	Image_ = FindImage;
	SetImageScale();
}

void GameEngineRenderer::SetImageScale()
{
	if (nullptr == Image_)
	{
		MsgBoxAssert("�������� �ʴ� �̹����� ũ�⸦ �����Ϸ��� �߽��ϴ�.");
		return;
	}
	ScaleMode_ = RenderScaleMode::IMAGE;
	RenderScale_ = Image_->GetScale();
	RenderImageScale_ = Image_->GetScale();
}

void GameEngineRenderer::SetIndex(size_t _Index, const float4& _Scale)
{
	if (false == Image_->IsCut())
	{
		MsgBoxAssert("�̹����� �κ������� ����� �� �ְ� �ڸ��� ���� �̹����Դϴ�.");
		return;
	}
	RenderImagePivot_ = Image_->GetCutPivot(_Index);
	if (-1.0f == _Scale.x || -1.0f == _Scale.y)
	{
		RenderScale_ = Image_->GetCutScale(_Index);
	}
	else
	{
		RenderScale_ = _Scale;
	}
	RenderImageScale_ = Image_->GetCutScale(_Index);
}

void GameEngineRenderer::SetOrder(int _Order)
{
	if (nullptr == GetActor())
	{
		MsgBoxAssert("���Ͱ� ���õ��� �ʽ��ϴ�.");
	}
	if (nullptr == GetActor()->GetLevel())
	{
		MsgBoxAssert("������ ���õ��� �ʽ��ϴ�.");
	}

	if (_Order == GetOrder())
	{
		return;
	}
	GetActor()->GetLevel()->ChangeRenderOrder(this, _Order);
}

void GameEngineRenderer::Render()
{
	if (nullptr != CurrentAnimation_)
	{
		CurrentAnimation_->Update();
	}
	
	if (nullptr == Image_)
	{
		MsgBoxAssert("�������� �̹����� ���õǾ� ���� ������ �������� �ȵ˴ϴ�.");
	}

	float4 RenderPos = GetActor()->GetPosition() + RenderPivot_;

	if (true == IsCameraEffect_)
	{
		RenderPos -= GetActor()->GetLevel()->GetCameraPos();
	}

	switch (PivotType_)
	{
	case RenderPivot::CENTER:
		GameEngine::BackBufferImage()->TransCopy(Image_, RenderPos - RenderScale_.Half(), RenderScale_, RenderImagePivot_, RenderImageScale_, TransColor_);
		break;
	case RenderPivot::BOT:
	{	
		float4 Scale = RenderScale_.Half();
		Scale.y *= 2.0f;
		GameEngine::BackBufferImage()->TransCopy(Image_, RenderPos - Scale, RenderScale_, RenderImagePivot_, RenderImageScale_, TransColor_);
		break;
	}
	default:
		break;
	}
}

//=========================Animation========================
void GameEngineRenderer::CreateAnimation(const std::string& _Image, const std::string& _Name, int _StartIndex, int _EndIndex, float _InterTime, bool _Loop)
{
	GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find(_Image);
	if (nullptr == FindImage)
	{
		MsgBoxAssertString(_Name + "�������� �ʴ� �̹����� �ִϸ��̼��� �����Ϸ��� �߽��ϴ�.");
		return;
	}

	if (Animations_.end() != Animations_.find(_Name))
	{
		MsgBoxAssert("�̹� �����ϴ� �ִϸ��̼��� ������Ϸ��� �߽��ϴ�.");
		return;
	}

	FrameAnimation& NewAnimation = Animations_[_Name];
	NewAnimation.SetName(_Name);
	NewAnimation.TimeKey_ = 0;
	NewAnimation.Renderer_ = this;
	NewAnimation.Image_ = FindImage;
	NewAnimation.CurrentFrame_ = _StartIndex;
	NewAnimation.StartFrame_ = _StartIndex;
	NewAnimation.EndFrame_ = _EndIndex;
	NewAnimation.CurrentInterTime_ = _InterTime;
	NewAnimation.InterTime_ = _InterTime;
	NewAnimation.Loop_ = _Loop;
}

void GameEngineRenderer::CreateFolderAnimation(const std::string& _Image, const std::string& _Name, int _StartIndex, int _EndIndex, float _InterTime, bool _Loop)
{
	GameEngineFolderImage* FindImage = GameEngineImageManager::GetInst()->FolderImageFind(_Image);
	if (nullptr == FindImage)
	{
		MsgBoxAssertString(_Name + "�������� �ʴ� �̹����� �ִϸ��̼��� �����Ϸ��� �߽��ϴ�.");
		return;
	}

	if (Animations_.end() != Animations_.find(_Name))
	{
		MsgBoxAssert("�̹� �����ϴ� �ִϸ��̼��� ������Ϸ��� �߽��ϴ�.");
		return;
	}

	FrameAnimation& NewAnimation = Animations_[_Name];
	NewAnimation.SetName(_Name);
	NewAnimation.TimeKey_ = 0;
	NewAnimation.Renderer_ = this;
	NewAnimation.FolderImage_ = FindImage;
	NewAnimation.CurrentFrame_ = _StartIndex;
	NewAnimation.StartFrame_ = _StartIndex;
	NewAnimation.EndFrame_ = _EndIndex;
	NewAnimation.CurrentInterTime_ = _InterTime;
	NewAnimation.InterTime_ = _InterTime;
	NewAnimation.Loop_ = _Loop;
}

void GameEngineRenderer::CreateFolderAnimationTimeKey(const std::string& _Image, const std::string& _Name, int _TimeScaleKey, int _StartIndex, int _EndIndex, float _InterTime, bool _Loop)
{
	GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find(_Image);
	if (nullptr == FindImage)
	{
		MsgBoxAssertString(_Name + "�������� �ʴ� �̹����� �ִϸ��̼��� �����Ϸ��� �߽��ϴ�.");
		return;
	}

	if (Animations_.end() != Animations_.find(_Name))
	{
		MsgBoxAssert("�̹� �����ϴ� �ִϸ��̼��� ������Ϸ��� �߽��ϴ�.");
		return;
	}

	FrameAnimation& NewAnimation = Animations_[_Name];
	NewAnimation.SetName(_Name);
	NewAnimation.Renderer_ = this;
	NewAnimation.Image_ = FindImage;
	NewAnimation.TimeKey_ = _TimeScaleKey;
	NewAnimation.CurrentFrame_ = _StartIndex;
	NewAnimation.StartFrame_ = _StartIndex;
	NewAnimation.EndFrame_ = _EndIndex;
	NewAnimation.CurrentInterTime_ = _InterTime;
	NewAnimation.InterTime_ = _InterTime;
	NewAnimation.Loop_ = _Loop;
}

void GameEngineRenderer::ChangeAnimation(const std::string& _Name)
{
	std::map<std::string, FrameAnimation>::iterator FindIter = Animations_.find(_Name);

	if (Animations_.end() == FindIter)
	{
		MsgBoxAssert("�������� �ʴ� �ִϸ��̼����� �ٲٷ��� �߽��ϴ�.");
		return;
	}

	CurrentAnimation_ = &FindIter->second;
}

bool GameEngineRenderer::IsEndAnimation()
{
	return CurrentAnimation_->IsEnd_;
}

bool GameEngineRenderer::IsAnimationName(const std::string& _Name)
{
	return CurrentAnimation_->GetNameConstRef() == _Name;
}

void GameEngineRenderer::FrameAnimation::Update()
{
	IsEnd_ = false;
	CurrentInterTime_ -= GameEngineTime::GetInst()->GetDeltaTime();

	if (0 >= CurrentInterTime_)
	{
		CurrentInterTime_ = InterTime_;
		++CurrentFrame_;

		if (EndFrame_ < CurrentFrame_)
		{
			if (true == Loop_)
			{
				IsEnd_ = true;
				CurrentFrame_ = StartFrame_;
			}
			else
			{
				IsEnd_ = true;
				CurrentFrame_ = EndFrame_;
			}
		}
	}
	if (nullptr != Image_)
	{
		Renderer_->Image_ = Image_;
		Renderer_->SetIndex(CurrentFrame_);
	}
	else if (nullptr != FolderImage_)
	{
		Renderer_->Image_ = FolderImage_->GetImage(CurrentFrame_);
		Renderer_->SetImageScale();
	}
}