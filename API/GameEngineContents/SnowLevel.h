#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν : 
class SnowLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	SnowLevel();
	~SnowLevel();

	// delete Function
	SnowLevel(const SnowLevel& _Other) = delete;
	SnowLevel(SnowLevel&& _Other) noexcept = delete;
	SnowLevel& operator=(const SnowLevel& _Other) = delete;
	SnowLevel& operator=(SnowLevel&& _Other) noexcept = delete;
	
	int Enemycount_;

protected:

private:
};

