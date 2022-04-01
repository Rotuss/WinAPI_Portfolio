#include "GameEngineActor.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngine.h>

GameEngineActor::GameEngineActor()
	:Level_(nullptr)
{
}

GameEngineActor::~GameEngineActor()
{
}

void GameEngineActor::DebugRectRender()
{
	GameEngineRect DebugRect(Position_, Scale_);
	
	Rectangle(GameEngine::BackBufferDC(), DebugRect.CenterLeft(), DebugRect.CenterTop(), DebugRect.CenterRight(), DebugRect.CenterBot());
}

GameEngineRenderer* GameEngineActor::CreateRenderer(const std::string& _ImageName, RenderPivot _PivotType /*= RenderPivot::CENTER*/, const float4& _PivotPos /*= { 0, 0 }*/)
{
	return;
}
