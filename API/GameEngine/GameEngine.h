#pragma once
#include <map>
#include <string>
// GameEngine -> 속성 -> C/C++ -> 추가 포함 디렉터리(..\;)
// +) GameEngine(참조) -> 참조 추가 -> GameEngineBase
// GameEngine -> 속성 -> 일반 -> 구성 형식(정적 라이브러리)

// 게임엔진이란? => 게임 그 자체의 시작점과 끝점 실행중을 담당. 인터페이스만 제공
// 설명 : 
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

	// 직접 만든 프레임워크에서 GameEngine에 이 3가지를 구현하지 않으면 내용이 없어도 안됨
	virtual void GameInit() = 0;
	virtual void GameLoop() = 0;
	virtual void GameEnd() = 0;

protected:
	// GameEngine 입장에서는 Level Class의 실체가 무엇인지 모름. 하지만 만들어줘야 하는 Level은 많음! 따라서, template로 구현
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

