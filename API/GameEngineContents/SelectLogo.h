#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν : 
class SelectLogo : public GameEngineActor
{
public:
	// constrcuter destructer
	SelectLogo();
	~SelectLogo();

	// delete Function
	SelectLogo(const SelectLogo& _Other) = delete;
	SelectLogo(SelectLogo&& _Other) noexcept = delete;
	SelectLogo& operator=(const SelectLogo& _Other) = delete;
	SelectLogo& operator=(SelectLogo&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;

private:
};

