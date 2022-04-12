#include "GameEngineRendererTileMap.h"

GameEngineRenderer* GameEngineRendererTileMap::CreateTile(int _X, int _Y, const std::string& _Image)
{
	GameEngineRenderer* Renderer = Master_->CreateRenderer(_Image);
	//Renderer->SetPivot();
	return Renderer;
}

GameEngineRenderer* GameEngineRendererTileMap::CreateTile(int _X, int _Y, const std::string& _Image, int _Index)
{
	GameEngineRenderer* Renderer = CreateTile(_X, _Y, _Image);
	Renderer->SetIndex(_Index);
	return Renderer;
}

void GameEngineRendererTileMap::DeleteTile(int _X, int _Y)
{
}

float4 GameEngineRendererTileMap::GetWorldPosition(int _X, int _Y)
{
	float4 ReturnPos = TileScale_;

	ReturnPos.x *= _X;
	ReturnPos.y *= _Y;
	ReturnPos += TileScaleHalf_;
	return ReturnPos;
}
