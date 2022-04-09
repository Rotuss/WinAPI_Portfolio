#include "GameEngineActor.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>

GameEngineActor::GameEngineActor()
	:Level_(nullptr)
{
}

GameEngineActor::~GameEngineActor()
{
	std::list<GameEngineRenderer*>::iterator StartIter = RenderList_.begin();
	std::list<GameEngineRenderer*>::iterator EndIter = RenderList_.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr == (*StartIter))
		{
			continue;
		}
		delete (*StartIter);
		(*StartIter) = nullptr;
	}
}

void GameEngineActor::DebugRectRender()
{
	GameEngineRect DebugRect(Position_, Scale_);
	
	Rectangle(GameEngine::BackBufferDC(), DebugRect.CenterLeft(), DebugRect.CenterTop(), DebugRect.CenterRight(), DebugRect.CenterBot());
}

GameEngineRenderer* GameEngineActor::CreateRenderer(RenderPivot _PivotType, const float4& _PivotPos)
{
	GameEngineRenderer* NewRenderer = new GameEngineRenderer();

	NewRenderer->SetActor(this);
	NewRenderer->SetPivotType(_PivotType);
	NewRenderer->SetPivot(_PivotPos);

	RenderList_.push_back(NewRenderer);
	return NewRenderer;
}

GameEngineRenderer* GameEngineActor::CreateRenderer(const std::string& _ImageName, RenderPivot _PivotType /*= RenderPivot::CENTER*/, const float4& _PivotPos /*= { 0, 0 }*/)
{
	GameEngineRenderer* NewRenderer = new GameEngineRenderer();

	NewRenderer->SetActor(this);
	NewRenderer->SetImage(_ImageName);
	NewRenderer->SetPivotType(_PivotType);
	NewRenderer->SetPivot(_PivotPos);

	RenderList_.push_back(NewRenderer);
	return NewRenderer;
}

GameEngineRenderer* GameEngineActor::CreateRendererToScale(const std::string& _ImageName, const float4& _Scale, RenderPivot _PivotType, const float4& _PivotPos)
{
	GameEngineRenderer* NewRenderer = new GameEngineRenderer();

	NewRenderer->SetActor(this);
	NewRenderer->SetImage(_ImageName);
	NewRenderer->SetScale(_Scale);
	NewRenderer->SetPivotType(_PivotType);
	NewRenderer->SetPivot(_PivotPos);

	RenderList_.push_back(NewRenderer);
	
	return NewRenderer;
}

void GameEngineActor::Rendering()
{
	StartRenderIter = RenderList_.begin();
	EndRenderIter = RenderList_.end();

	for (; StartRenderIter != EndRenderIter; ++StartRenderIter)
	{
		(*StartRenderIter)->Render();
	}
}
