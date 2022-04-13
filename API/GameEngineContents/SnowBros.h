#pragma once
#include <GameEngine/GameEngine.h>
// GameEngineContents -> �Ӽ� -> C/C++ -> �߰� ���� ���͸�(..\;)
// +) GameEngineContents(����) -> ���� �߰� -> GameEngineBase, GameEngine
// GameEngineContents -> �Ӽ� -> �Ϲ� -> ���� ����(���� ���̺귯��)
// GameEngineContents -> �Ӽ� -> �Ϲ� -> ��� ���͸� ���� -> VC++ ���͸� -> ���̺귯�� ���͸� �ٿ��ֱ�

// ���� : 
class SnowBros : public GameEngine
{
public:
	// constrcuter destructer
	SnowBros();
	~SnowBros();

	// delete Function
	SnowBros(const SnowBros& _Other) = delete;
	SnowBros(SnowBros&& _Other) noexcept = delete;
	SnowBros& operator=(const SnowBros& _Other) = delete;
	SnowBros& operator=(SnowBros&& _Other) noexcept = delete;

	void GameInit() override;
	void GameLoop() override;
	void GameEnd() override;

protected:

private:
};

