#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν : 
class SelectBackGround : public GameEngineActor
{
public:
	// constrcuter destructer
	SelectBackGround();
	~SelectBackGround();

	// delete Function
	SelectBackGround(const SelectBackGround& _Other) = delete;
	SelectBackGround(SelectBackGround&& _Other) noexcept = delete;
	SelectBackGround& operator=(const SelectBackGround& _Other) = delete;
	SelectBackGround& operator=(SelectBackGround&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Render() override;

private:
};

