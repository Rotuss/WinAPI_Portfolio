#pragma once

// 설명 : 
class GameEngineMath
{
public:
	// constrcuter destructer
	GameEngineMath();
	~GameEngineMath();

	// delete Function
	GameEngineMath(const GameEngineMath& _Other) = delete;
	GameEngineMath(GameEngineMath&& _Other) noexcept = delete;
	GameEngineMath& operator=(const GameEngineMath& _Other) = delete;
	GameEngineMath& operator=(GameEngineMath&& _Other) noexcept = delete;

protected:

private:
};

class float4
{
public:
	float x;
	float y;
	float z;
	float w;

	//==========================================================

	int ix()
	{
		return static_cast<int>(x);
	}

	int iy()
	{
		return static_cast<int>(y);
	}

	int iz()
	{
		return static_cast<int>(z);
	}

	int iw()
	{
		return static_cast<int>(w);
	}

	//==========================================================

	// 절반 크기
	int hix()
	{
		return static_cast<int>(x * 0.5f);
	}

	int hiy()
	{
		return static_cast<int>(y * 0.5f);
	}

	int hiz()
	{
		return static_cast<int>(z * 0.5f);
	}

	float4 Half()
	{
		return { x * 0.5f , y * 0.5f , z * 0.5f , 1.0f };
	}

	//==========================================================

	bool IsZero2D()
	{
		return x == 0.0f && y == 0.0f;
	}

	//==========================================================

	float4()
		: x(0.0f), y(0.0f), z(0.0f), w(1.0f)
	{

	}

	float4(float _x, float _y)
		: x(_x), y(_y), z(0.0f), w(1.0f)
	{

	}

	float4(float _x, float _y, float _z)
		: x(_x), y(_y), z(_z), w(1.0f)
	{

	}

	float4(float _x, float _y, float _z ,float _w)
		: x(_x), y(_y), z(_z), w(_w)
	{

	}
};

struct GameEngineRect
{
public:
	float4 Pos;
	float4 Scale;

	int CenterLeft()
	{
		return Pos.ix() - Scale.hix();
	}

	int CenterRight()
	{
		return Pos.ix() + Scale.hix();
	}

	int CenterTop()
	{
		return Pos.iy() - Scale.hiy();
	}
	
	int CenterBot()
	{
		return Pos.iy() + Scale.hiy();
	}
	GameEngineRect(float4 _Pos, float4 _Scale)
		: Pos(_Pos)
		, Scale(_Scale)
	{ }
};