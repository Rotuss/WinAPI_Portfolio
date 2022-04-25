#pragma once
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngine/GameEngineLevel.h>

// ���� : 
class TitleMainLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	TitleMainLevel();
	~TitleMainLevel();

	// delete Function
	TitleMainLevel(const TitleMainLevel& _Other) = delete;
	TitleMainLevel(TitleMainLevel&& _Other) noexcept = delete;
	TitleMainLevel& operator=(const TitleMainLevel& _Other) = delete;
	TitleMainLevel& operator=(TitleMainLevel&& _Other) noexcept = delete;

	GameEngineSoundPlayer BgmPlayer_;

protected:
	// ���� ��� ���� ���� protected�� �־��. Engine���� Loading�� ��������ַ� �ϴ� ��. �׷����� �ٸ� ������ Loading�� �� �����Ű�� �ȵ�(�� �� ������ �ϸ� �ȵ�)
	void Loading() override;
	void Update() override;

	void LevelChangeStart(GameEngineLevel* _NextLevel) override;
	void LevelChangeEnd(GameEngineLevel* _PrevLevel) override;

private:
};

