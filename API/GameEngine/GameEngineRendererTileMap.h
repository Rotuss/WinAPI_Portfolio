#pragma once
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <vector>

struct TileIndex
{
public:
	int X;
	int Y;
};
// 설명 : 제한이 있는 타일맵
class GameEngineImage;
class GameEngineRendererTileMap
{
public:
	// constrcuter destructer
	GameEngineRendererTileMap(GameEngineActor* _Actor)
		:Master_(_Actor)
	{
	}
	virtual ~GameEngineRendererTileMap()
	{
	}

	// delete Function
	GameEngineRendererTileMap(const GameEngineRendererTileMap& _Other) = delete;
	GameEngineRendererTileMap(GameEngineRendererTileMap&& _Other) noexcept = delete;
	GameEngineRendererTileMap& operator=(const GameEngineRendererTileMap& _Other) = delete;
	GameEngineRendererTileMap& operator=(GameEngineRendererTileMap&& _Other) noexcept = delete;

	void TileRangeSetting(int _X, int _Y, float4 _TileScale)
	{
		if (0 >= _X)
		{
			MsgBoxAssert("0개 이하의 타일맵을 만들 수 없습니다.");
			return;
		}
		if (0 >= _Y)
		{
			MsgBoxAssert("0개 이하의 타일맵을 만들 수 없습니다.");
			return;
		}

		Tiles_.resize(_Y);

		for (size_t y = 0; y < Tiles_.size(); ++y)
		{
			Tiles_[y].resize(_X);
			
			for (size_t x = 0; x < Tiles_[y].size(); ++x)
			{
				Tiles_[y][x] = nullptr;
			}
			//memset(&Tiles_[i], 0, sizeof(int*) * _X);
		}
		TileScale_ = _TileScale;
		TileScaleHalf_ = _TileScale.Half();
	}

	GameEngineRenderer* GetTile(int _X, int _Y)
	{
		if (0 > _X)
		{
			MsgBoxAssert("0 이하의 인덱스는 존재할 수 없습니다.");
		}
		if (0 > _Y)
		{
			MsgBoxAssert("0 이하의 인덱스는 존재할 수 없습니다.");
		}
		if (_Y >= Tiles_.size())
		{
			MsgBoxAssert("범위를 넘길 수 없습니다.");
		}
		if (_X >= Tiles_[0].size())
		{
			MsgBoxAssert("범위를 넘길 수 없습니다.");
		}
		return Tiles_[_Y][_X];
	}

	//bool IsTile(int _X, int _Y)
	//{
	//	return GetTile(_X, _Y) = nullptr;
	//}

	GameEngineRenderer* CreateTile(const float4& _Pos, const std::string& _Image, int _Order = static_cast<int>(EngineMax::RENDERORDERMAX));
	// 타일 이미지가 하나씩 있을 때
	GameEngineRenderer* CreateTile(int _X, int _Y, const std::string& _Image, int _Order = static_cast<int>(EngineMax::RENDERORDERMAX));
	// 타일 이미지가 하나에 모여 있지만 Cut했을 때
	GameEngineRenderer* CreateTile(int _X, int _Y, const std::string& _Image, int _Index, int _Order = static_cast<int>(EngineMax::RENDERORDERMAX));
	void DeleteTile(int _X, int _Y);
	float4 GetWorldPosition(int _X, int _Y);
	TileIndex GetTileIndex(const float4& _Pos);

protected:

private:
	std::vector<std::vector<GameEngineRenderer*>> Tiles_;
	GameEngineActor* Master_;

	// 타일 1칸의 크기
	float4 TileScale_;
	float4 TileScaleHalf_;
};

