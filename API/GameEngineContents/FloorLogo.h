#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν : 
class FloorLogo : public GameEngineActor
{
public:
	// constrcuter destructer
	FloorLogo();
	~FloorLogo();

	// delete Function
	FloorLogo(const FloorLogo& _Other) = delete;
	FloorLogo(FloorLogo&& _Other) noexcept = delete;
	FloorLogo& operator=(const FloorLogo& _Other) = delete;
	FloorLogo& operator=(FloorLogo&& _Other) noexcept = delete;

	GameEngineRenderer* GetRenderer()
	{
		return Image_;
	}

protected:
	void Start() override;
	void Render() override;

private:
	GameEngineRenderer* Image_;
};

