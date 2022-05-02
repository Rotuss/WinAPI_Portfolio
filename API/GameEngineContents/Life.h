#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>

// Ό³Έν : 
class Life : public GameEngineActor
{
public:
	// constrcuter destructer
	Life();
	~Life();

	// delete Function
	Life(const Life& _Other) = delete;
	Life(Life&& _Other) noexcept = delete;
	Life& operator=(const Life& _Other) = delete;
	Life& operator=(Life&& _Other) noexcept = delete;

	static int LifeUI_;

	void LifeNum(const int& _Other)
	{
		LifeUI_ -= _Other;
	}

protected:

private:
	GameEngineRenderer* Actor;
	GameEngineRenderer* Count;
	
	void Start() override;
	void Update() override;
	void Render() override;
};

