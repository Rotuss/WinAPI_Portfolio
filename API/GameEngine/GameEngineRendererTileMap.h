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
class GameEngineImage;
class GameEngineRendererTileMap;
class Tile
{
	friend GameEngineRendererTileMap;
public:
	virtual ~Tile() = 0
	{

	}

protected:

private:
	GameEngineRenderer* Renderer;
};
// ���� : ������ �ִ� Ÿ�ϸ�
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

	// Ÿ�� ���� �� ��ü�� ����
	void TileRangeSetting(int _X, int _Y, float4 _TileScale)
	{
		if (0 >= _X)
		{
			MsgBoxAssert("0�� ������ Ÿ�ϸ��� ���� �� �����ϴ�.");
			return;
		}
		if (0 >= _Y)
		{
			MsgBoxAssert("0�� ������ Ÿ�ϸ��� ���� �� �����ϴ�.");
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

	template<typename TileType>
	TileType* GetTile(int _X, int _Y)
	{
		if (0 > _X)
		{
			MsgBoxAssert("0 ������ �ε����� ������ �� �����ϴ�.");
		}
		if (0 > _Y)
		{
			MsgBoxAssert("0 ������ �ε����� ������ �� �����ϴ�.");
		}
		if (_Y >= Tiles_.size())
		{
			MsgBoxAssert("������ �ѱ� �� �����ϴ�.");
		}
		if (_X >= Tiles_[0].size())
		{
			MsgBoxAssert("������ �ѱ� �� �����ϴ�.");
		}
		return reinterpret_cast<TileType*>(Tiles_[_Y][_X]);
	}

	bool IsTile(int _X, int _Y)
	{
		return GetTile<Tile>(_X, _Y) == nullptr;
	}

	template<typename TileType>
	TileType* CreateTile(const float4& _Pos, const std::string& _Image, int _Order = static_cast<int>(EngineMax::RENDERORDERMAX))
	{
		TileIndex Index = GetTileIndex(_Pos);
		return CreateTile<TileType>(Index.X, Index.Y, _Image);
	}
	// Ÿ�� �̹����� �ϳ��� ���� ��
	template<typename TileType>
	TileType* CreateTile(int _X, int _Y, const std::string& _Image, int _Order = static_cast<int>(EngineMax::RENDERORDERMAX))
	{
		Tile* FindTile = GetTile<Tile>(_X, _Y);
		if (nullptr == FindTile)
		{
			FindTile = new TileType();
			FindTile->Renderer = Master_->CreateRenderer(_Image, _Order);
		}
		else
		{
			FindTile->Renderer->SetImage(_Image);
		}
		FindTile->Renderer->SetPivot(GetWorldPosition(_X, _Y));
		Tiles_[_Y][_X] = FindTile;

		return reinterpret_cast<TileType*>(FindTile);
	}
	// Ÿ�� �̹����� �ϳ��� �� ������ Cut���� ��
	template<typename TileType>
	TileType* CreateTile(int _X, int _Y, const std::string& _Image, int _Index, int _Order = static_cast<int>(EngineMax::RENDERORDERMAX))
	{
		TileType* Tile = CreateTile(_X, _Y, _Image);
		Tile->Renderer->SetIndex(_Index);
		Tile->Renderer->SetPivot(GetWorldPosition(_X, _Y));
		return reinterpret_cast<TileType*>(Tile);
	}
	void DeleteTile(int _X, int _Y);
	float4 GetWorldPosition(int _X, int _Y);
	TileIndex GetTileIndex(const float4& _Pos);

protected:

private:
	//std::vector<std::vector<GameEngineRenderer*>> Tiles_;
	std::vector<std::vector<Tile*>> Tiles_;
	GameEngineActor* Master_;

	// Ÿ�� 1ĭ�� ũ��
	float4 TileScale_;
	float4 TileScaleHalf_;
};

