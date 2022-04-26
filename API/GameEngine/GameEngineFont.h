#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineMath.h>
#include <Windows.h>
#include <vector>

// Ό³Έν : 
class GameEngineFont
{
public:
	// constrcuter destructer
	GameEngineFont();
	~GameEngineFont();

	// delete Function
	GameEngineFont(const GameEngineFont& _Other) = delete;
	GameEngineFont(GameEngineFont&& _Other) noexcept = delete;
	GameEngineFont& operator=(const GameEngineFont& _Other) = delete;
	GameEngineFont& operator=(GameEngineFont&& _Other) noexcept = delete;

	bool Load(const std::string& _Path);
	void Draw(const std::string& _Text, float4 _Postion, float _Size, float _Weight);

protected:

private:
	HFONT hFont_;
	HFONT oldFont_;
	std::string FontName_;
};

