#pragma once
#include <GameEngine/GameEngineLevel.h>

// ���� : 
class TitleLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	TitleLevel();
	~TitleLevel();

	// delete Function
	TitleLevel(const TitleLevel& _Other) = delete;
	TitleLevel(TitleLevel&& _Other) noexcept = delete;
	TitleLevel& operator=(const TitleLevel& _Other) = delete;
	TitleLevel& operator=(TitleLevel&& _Other) noexcept = delete;

protected:
	// ���� ��� ���� ���� protected�� �־��. Engine���� Loading�� ��������ַ� �ϴ� ��. �׷����� �ٸ� ������ Loading�� �� �����Ű�� �ȵ�(�� �� ������ �ϸ� �ȵ�)
	void Loading() override;
	void Update() override;

private:
};

