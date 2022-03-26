#pragma once
#include <map>
#include <string>
// GameEngine -> �Ӽ� -> C/C++ -> �߰� ���� ���͸�(..\;)
// +) GameEngine(����) -> ���� �߰� -> GameEngineBase
// GameEngine -> �Ӽ� -> �Ϲ� -> ���� ����(���� ���̺귯��)

// ���ӿ����̶�? => ���� �� ��ü�� �������� ���� �������� ���. �������̽��� ����
// ���� : 
class GameEngineLevel;
class GameEngine
{
public:
	// constrcuter destructer
	GameEngine();
	~GameEngine();

	// delete Function
	GameEngine(const GameEngine& _Other) = delete;
	GameEngine(GameEngine&& _Other) noexcept = delete;
	GameEngine& operator=(const GameEngine& _Other) = delete;
	GameEngine& operator=(GameEngine&& _Other) noexcept = delete;

	// ���� ���� �����ӿ�ũ���� GameEngine�� �� 3������ �������� ������ ������ ��� �ȵ�
	virtual void GameInit() = 0;
	virtual void GameLoop() = 0;
	virtual void GameEnd() = 0;

protected:
	// GameEngine ���忡���� Level Class�� ��ü�� �������� ��. ������ �������� �ϴ� Level�� ����! ����, template�� ����
	template<typename LevelType>
	void CreateLevel(const std::string& _Name)
	{
		LevelType* NewLevel = new LevelType();
		NewLevel->SetName(_Name);
		NewLevel->Loading();
		AllLevel_.insert(std::make_pair(_Name, NewLevel));
	}

private:
	std::map<std::string, GameEngineLevel*> AllLevel_;
};

