#include "GameEngineRendererTileMap.h"

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

TileIndex GameEngineRendererTileMap::GetTileIndex(const float4& _Pos)
{
	return {static_cast<int>(_Pos.x / TileScale_.x), static_cast<int>(_Pos.y / TileScale_.y) };
}
