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
}

void GameEngineRenderer::Render()
{
	if (nullptr == Image_)
	{
		MsgBoxAssert("렌더러에 이미지가 세팅되어 있지 않으면 렌더링이 안됩니다.");
	}

	float4 RenderPos = GetActor()->GetPosition() + RenderPivot_;
	float4 RenderScale = RenderScale_;

	switch (ScaleMode_)
	{
	case RenderScaleMode::IMAGE:
		RenderScale = Image_->GetScale();
		break;
	case RenderScaleMode::USER:
		break;
	default:
		break;
	}

	switch (PivotType_)
	{
	case RenderPivot::CENTER:
		GameEngine::BackBufferImage()->TransCopyCenterScale(Image_, RenderPos, RenderScale, TransColor_);
		break;
	case RenderPivot::BOT:
		GameEngine::BackBufferImage()->TransCopyCenterScale(Image_, RenderPos, RenderScale, TransColor_);
		break;
	default:
		break;
	}
}
