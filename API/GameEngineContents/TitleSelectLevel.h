#pragma once
#include <GameEngine/GameEngineLevel.h>

// ���� : 
class TitleSelectLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	TitleSelectLevel();
	~TitleSelectLevel();

	// delete Function
	TitleSelectLevel(const TitleSelectLevel& _Other) = delete;
	TitleSelectLevel(TitleSelectLevel&& _Other) noexcept = delete;
	TitleSelectLevel& operator=(const TitleSelectLevel& _Other) = delete;
	TitleSelectLevel& operator=(TitleSelectLevel&& _Other) noexcept = delete;

protected:
	// ���� ��� ���� ���� protected�� �־��. Engine���� Loading�� ��������ַ� �ϴ� ��. �׷����� �ٸ� ������ Loading�� �� �����Ű�� �ȵ�(�� �� ������ �ϸ� �ȵ�)
	void Loading() override;
	void Update() override;

	void LevelChangeStart(GameEngineLevel* _NextLevel) override;
	void LevelChangeEnd(GameEngineLevel* _PrevLevel) override;

private:
};

