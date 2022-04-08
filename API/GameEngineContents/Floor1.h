#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν : 
class Floor1 : public GameEngineLevel
{
public:
	// constrcuter destructer
	Floor1();
	~Floor1();

	// delete Function
	Floor1(const Floor1& _Other) = delete;
	Floor1(Floor1&& _Other) noexcept = delete;
	Floor1& operator=(const Floor1& _Other) = delete;
	Floor1& operator=(Floor1&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart() override;

private:
};

