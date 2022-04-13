#pragma once
#include <GameEngine/GameEngine.h>
// GameEngineContents -> 속성 -> C/C++ -> 추가 포함 디렉터리(..\;)
// +) GameEngineContents(참조) -> 참조 추가 -> GameEngineBase, GameEngine
// GameEngineContents -> 속성 -> 일반 -> 구성 형식(정적 라이브러리)
// GameEngineContents -> 속성 -> 일반 -> 출력 디렉터리 복사 -> VC++ 디렉터리 -> 라이브러리 디렉터리 붙여넣기

// 설명 : 
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

