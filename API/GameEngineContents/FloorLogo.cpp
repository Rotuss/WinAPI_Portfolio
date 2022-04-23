#include "FloorLogo.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>

FloorLogo::FloorLogo()
{
}

FloorLogo::~FloorLogo()
{
}

void FloorLogo::Start()
{
	Image_ = CreateRenderer();
}

void FloorLogo::Render()
{
}
