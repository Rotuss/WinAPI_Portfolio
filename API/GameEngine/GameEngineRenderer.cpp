#include "GameEngineRenderer.h"
#include "GameEngineImageManager.h"
#include "GameEngine.h"
#include "GameEngineLevel.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTime.h>

// 이용할 수 있는 이유 : 속성 -> VC++ 디렉터리 -> 라이브러리 디렉터리(그 중에서 기본 그래픽처리에 대한 라이브러리가 msimg32.lib)
#pragma comment(lib, "msimg32.lib")

GameEngineRenderer::GameEngineRenderer()
	: Image_(nullptr)
	, PivotType_(RenderPivot::CENTER)
	, ScaleMode_(RenderScaleMode::IMAGE)
	, RenderImagePivot_({ 0, 0 })
	, SortingPivot_(float4::ZERO)
	, TransColor_(RGB(255, 0, 255))
	, Alpha_(255)
	, Pause_(false)
	, IsCameraEffect_(true)
	, RotZ_(0.0f)
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
		MsgBoxAssertString(_Name + "존재하지 않는 이미지를 렌더러에 세팅하려고 했습니다.");
		return;
	}
	Image_ = FindImage;
	SetImageScale();
}

void GameEngineRenderer::SetImageScale()
{
	if (nullptr == Image_)
	{
		MsgBoxAssert("존재하지 않는 이미지로 크기를 조절하려고 했습니다.");
		return;
	}
	ScaleMode_ = RenderScaleMode::IMAGE;
	RenderScale_ = Image_->GetScale();
	RenderImageScale_ = Image_->GetScale();
	RenderImagePivot_ = float4::ZERO;
}

void GameEngineRenderer::SetIndex(size_t _Index, const float4& _Scale)
{
	if (false == Image_->IsCut())
	{
		MsgBoxAssert("이미지를 부분적으로 사용할 수 있게 자르지 않은 이미지입니다.");
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

void GameEngineRenderer::SetImageAnimationReset(const std::string& _Name)
{
	SetImage(_Name);
	CurrentAnimation_ = nullptr;
}

void GameEngineRenderer::SetOrder(int _Order)
{
	if (nullptr == GetActor())
	{
		MsgBoxAssert("액터가 세팅되지 않습니다.");
	}
	if (nullptr == GetActor()->GetLevel())
	{
		MsgBoxAssert("레벨이 세팅되지 않습니다.");
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
		MsgBoxAssert("렌더러에 이미지가 세팅되어 있지 않으면 렌더링이 안됩니다.");
	}

	float4 RenderPos = GetActor()->GetPosition() + RenderPivot_;

	if (true == IsCameraEffect_)
	{
		RenderPos -= GetActor()->GetLevel()->GetCameraPos();
	}

	switch (PivotType_)
	{
	case RenderPivot::CENTER:
		if (Alpha_ != 255)
		{
			GameEngine::BackBufferImage()->AlphaCopy(Image_, RenderPos - RenderScale_.Half(), RenderScale_, RenderImagePivot_, RenderImageScale_, Alpha_);
		}
		else if (RotZ_ != 0.0f)
		{
			GameEngine::BackBufferImage()->PlgCopy(Image_, RenderPos - RenderScale_.Half(), RenderScale_, RenderImagePivot_, RenderImageScale_, RotZ_, RotationFilterImage_);
			// GameEngine::BackBufferImage()->PlgCopy(Image_, RenderPos - RenderScale_.Half(), RenderScale_, RenderImagePivot_, RenderImageScale_, Alpha_);
		}
		else
		{
			GameEngine::BackBufferImage()->TransCopy(Image_, RenderPos - RenderScale_.Half(), RenderScale_, RenderImagePivot_, RenderImageScale_, TransColor_);
		}
		break;
	case RenderPivot::BOT:
	{	
		float4 Scale = RenderScale_.Half();
		Scale.y *= 2.0f;
		if (Alpha_ != 255)
		{
			GameEngine::BackBufferImage()->AlphaCopy(Image_, RenderPos - Scale, RenderScale_, RenderImagePivot_, RenderImageScale_, Alpha_);
		}
		else if (RotZ_ != 0.0f)
		{
			GameEngine::BackBufferImage()->PlgCopy(Image_, RenderPos - Scale, RenderScale_, RenderImagePivot_, RenderImageScale_, RotZ_, RotationFilterImage_);
		}
		else
		{
			GameEngine::BackBufferImage()->TransCopy(Image_, RenderPos - Scale, RenderScale_, RenderImagePivot_, RenderImageScale_, TransColor_);
		}
		break;
	}
	default:
		break;
	}
}

void GameEngineRenderer::SetRotationFilter(const std::string& _ImageName)
{
	GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find(_ImageName);
	if (nullptr == FindImage)
	{
		MsgBoxAssertString(_ImageName + "존재하지 않는 이미지를 렌더러에 세팅하려고 했습니다.");
		return;
	}
	RotationFilterImage_ = FindImage;
}

//=========================Animation========================
void GameEngineRenderer::CreateAnimation(const std::string& _Image, const std::string& _Name, int _StartIndex, int _EndIndex, float _InterTime, bool _Loop)
{
	GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find(_Image);
	if (nullptr == FindImage)
	{
		MsgBoxAssertString(_Name + "존재하지 않는 이미지로 애니메이션을 생성하려고 했습니다.");
		return;
	}

	if (Animations_.end() != Animations_.find(_Name))
	{
		MsgBoxAssert("이미 존재하는 애니메이션을 재생성하려고 했습니다.");
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
		MsgBoxAssertString(_Name + "존재하지 않는 이미지로 애니메이션을 생성하려고 했습니다.");
		return;
	}

	if (Animations_.end() != Animations_.find(_Name))
	{
		MsgBoxAssert("이미 존재하는 애니메이션을 재생성하려고 했습니다.");
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
		MsgBoxAssertString(_Name + "존재하지 않는 이미지로 애니메이션을 생성하려고 했습니다.");
		return;
	}

	if (Animations_.end() != Animations_.find(_Name))
	{
		MsgBoxAssert("이미 존재하는 애니메이션을 재생성하려고 했습니다.");
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
		MsgBoxAssert("존재하지 않는 애니메이션으로 바꾸려고 했습니다.");
		return;
	}
	if (nullptr != CurrentAnimation_ && CurrentAnimation_->GetNameConstPtr() == _Name)
	{
		return;
	}
	CurrentAnimation_ = &FindIter->second;
	if (nullptr != CurrentAnimation_)
	{
		CurrentAnimation_->Reset();
	}
}

bool GameEngineRenderer::IsEndAnimation()
{
	return CurrentAnimation_->IsEnd_;
}

bool GameEngineRenderer::IsAnimationName(const std::string& _Name)
{
	return CurrentAnimation_->GetNameConstRef() == _Name;
}

const GameEngineRenderer::FrameAnimation* GameEngineRenderer::FindAnimation(const std::string& _Name)
{
	std::map<std::string, FrameAnimation>::iterator FindIter = Animations_.find(_Name);

	if (Animations_.end() == FindIter)
	{
		return nullptr;
	}
	return &FindIter->second;
}

void GameEngineRenderer::FrameAnimation::Update()
{
	IsEnd_ = false;
	if (false == Renderer_->Pause_)
	{
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
	}
	
	if (nullptr != Image_)
	{
		Renderer_->Image_ = Image_;
		if (Renderer_->ScaleMode_ == RenderScaleMode::USER)
		{
			Renderer_->SetIndex(CurrentFrame_, Renderer_->RenderScale_);
		}
		else
		{
			Renderer_->SetIndex(CurrentFrame_);
		}
	}
	else if (nullptr != FolderImage_)
	{
		Renderer_->Image_ = FolderImage_->GetImage(CurrentFrame_);
		Renderer_->SetImageScale();
	}
}
