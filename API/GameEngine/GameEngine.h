#pragma once
#include <map>
#include <string>
#include <GameEngineBase/GameEngineDebug.h>
// GameEngine -> �Ӽ� -> C/C++ -> �߰� ���� ���͸�(..\;)
// +) GameEngine(����) -> ���� �߰� -> GameEngineBase
// GameEngine -> �Ӽ� -> �Ϲ� -> ���� ����(���� ���̺귯��)

// ���ӿ����̶�? => ���� �� ��ü�� �������� ���� �������� ���. �������̽��� ����
// ���� : 
class GameEngineImage;
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

	static inline GameEngineImage* BackBufferImage()
	{
		return BackBufferImage_;
	}

	static HDC BackBufferDC();

	// ���� ���� �����ӿ�ũ���� GameEngine�� �� 3������ �������� ������ ������ ��� �ȵ�
	virtual void GameInit() = 0;
	virtual void GameLoop() = 0;
	virtual void GameEnd() = 0;

	template<typename GameType>
	static void Start()
	{
		GameEngineDebug::LeakCheckOn();
		
		// SnowBros MyGame;
		GameType UserGame;
		UserContents_ = &UserGame;

		WindowCreate();
		EngineEnd();
	}

	static GameEngine& GlobalEngine()
	{
		if (nullptr == UserContents_)
		{
			MsgBoxAssert("GEngine Error. Engine Is Not Start");
		}
		return *UserContents_;
	}

	void ChangeLevel(const std::string& _Name);

protected:
	// GameEngine ���忡���� Level Class�� ��ü�� �������� ��. ������ �������� �ϴ� Level�� ����! ����, template�� ����
	template<typename LevelType>
	void CreateLevel(const std::string& _Name)
	{
		LevelType* NewLevel = new LevelType();
		GameEngineLevel* Level = NewLevel;
		NewLevel->SetName(_Name);
		Level->Loading();
		AllLevel_.insert(std::make_pair(_Name, NewLevel));
	}

private:
	static std::map<std::string, GameEngineLevel*> AllLevel_;
	
	static GameEngineLevel* CurrentLevel_;
	static GameEngineLevel* NextLevel_;
	static GameEngine*		UserContents_;
	static GameEngineImage* BackBufferImage_;

	static void WindowCreate();
	static void EngineInit();
	static void EngineLoop();
	static void EngineEnd();
};

// ������ �������̽��� ����
/*
class IGameEngineInstance
{
	virtual void GameInit() = 0;
	virtual void GameLoop() = 0;
	virtual void GameEnd() = 0;
};
*/