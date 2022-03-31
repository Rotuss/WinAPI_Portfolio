#pragma once
#include <map>
#include <string>
#include <GameEngineBase/GameEngineDebug.h>
// GameEngine -> 속성 -> C/C++ -> 추가 포함 디렉터리(..\;)
// +) GameEngine(참조) -> 참조 추가 -> GameEngineBase
// GameEngine -> 속성 -> 일반 -> 구성 형식(정적 라이브러리)

// 게임엔진이란? => 게임 그 자체의 시작점과 끝점 실행중을 담당. 인터페이스만 제공
// 설명 : 
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

	// 직접 만든 프레임워크에서 GameEngine에 이 3가지를 구현하지 않으면 내용이 없어도 안됨
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
	// GameEngine 입장에서는 Level Class의 실체가 무엇인지 모름. 하지만 만들어줘야 하는 Level은 많음! 따라서, template로 구현
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

// 오로지 인터페이스만 제공
/*
class IGameEngineInstance
{
	virtual void GameInit() = 0;
	virtual void GameLoop() = 0;
	virtual void GameEnd() = 0;
};
*/