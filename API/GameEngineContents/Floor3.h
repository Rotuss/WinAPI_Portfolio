#pragma once
#include <GameEngine/GameEngineLevel.h>

// ���� : 
class Floor3 : public GameEngineLevel
{
public:
	// constrcuter destructer
	Floor3();
	~Floor3();

	// delete Function
	Floor3(const Floor3& _Other) = delete;
	Floor3(Floor3&& _Other) noexcept = delete;
	Floor3& operator=(const Floor3& _Other) = delete;
	Floor3& operator=(Floor3&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart() override;

private:
};

