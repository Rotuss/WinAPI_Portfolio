#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν : 
class ScoreMoveUp : public GameEngineActor
{
public:
	// constrcuter destructer
	ScoreMoveUp();
	~ScoreMoveUp();

	// delete Function
	ScoreMoveUp(const ScoreMoveUp& _Other) = delete;
	ScoreMoveUp(ScoreMoveUp&& _Other) noexcept = delete;
	ScoreMoveUp& operator=(const ScoreMoveUp& _Other) = delete;
	ScoreMoveUp& operator=(ScoreMoveUp&& _Other) noexcept = delete;

	int Type_;

protected:

private:
	GameEngineRenderer* Actor_;

	float Time_;

	void Start() override;
	void Update() override;
	void Render() override;
};

