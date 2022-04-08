#include "GameEngineRenderer.h"
#include "GameEngineImageManager.h"
#include "GameEngine.h"
#include <GameEngineBase/GameEngineDebug.h>

// 이용할 수 있는 이유 : 속성 -> VC++ 디렉터리 -> 라이브러리 디렉터리(그 중에서 기본 그래픽처리에 대한 라이브러리가 msimg32.lib)
#pragma comment(lib, "msimg32.lib")

GameEngineRenderer::GameEngineRenderer()
	: Image_(nullptr)
	, PivotType_(RenderPivot::CENTER)
	, ScaleMode_(RenderScaleMode::IMAGE)
	, RenderImagePivot_({ 0, 0 })
	, TransColor_(RGB(255, 0, 255))
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
}

void GameEngineRenderer::SetIndex(size_t _Index, float4 _Scale)
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

void GameEngineRenderer::Render()
{
	if (nullptr == Image_)
	{
		MsgBoxAssert("렌더러에 이미지가 세팅되어 있지 않으면 렌더링이 안됩니다.");
	}

	float4 RenderPos = GetActor()->GetPosition() + RenderPivot_;

	switch (PivotType_)
	{
	case RenderPivot::CENTER:
		GameEngine::BackBufferImage()->TransCopy(Image_, RenderPos - RenderScale_.Half(), RenderScale_, RenderImagePivot_, RenderImageScale_, TransColor_);
		break;
	case RenderPivot::BOT:
		GameEngine::BackBufferImage()->TransCopy(Image_, RenderPos, RenderScale_, RenderImagePivot_, RenderImageScale_, TransColor_);
		break;
	default:
		break;
	}
}
