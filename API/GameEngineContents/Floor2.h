#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν : 
class Floor2 : public GameEngineLevel
{
public:
	// constrcuter destructer
	Floor2();
	~Floor2();

	// delete Function
	Floor2(const Floor2& _Other) = delete;
	Floor2(Floor2&& _Other) noexcept = delete;
	Floor2& operator=(const Floor2& _Other) = delete;
	Floor2& operator=(Floor2&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart() override;

private:
};

