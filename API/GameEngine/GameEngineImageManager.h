#pragma once
#include <map>
#include <string>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineImage.h"

// 기본적으로 리소스는 그냥 사용 가능하지만 관리되는 리소스들은 전부 이름이 존재한다 보고 사용
// 설명 : 
class GameEngineImageManager
{
public:
	// constrcuter destructer
	GameEngineImageManager();
	~GameEngineImageManager();

	// delete Function
	GameEngineImageManager(const GameEngineImageManager& _Other) = delete;
	GameEngineImageManager(GameEngineImageManager&& _Other) noexcept = delete;
	GameEngineImageManager& operator=(const GameEngineImageManager& _Other) = delete;
	GameEngineImageManager& operator=(GameEngineImageManager&& _Other) noexcept = delete;

	// 이미지를 만들어주는 함수
	GameEngineImage* Create(const std::string& _Name, float4 _Scale);

	static GameEngineImageManager* GetInst()
	{
		return Inst_;
	}

	static void Destroy()
	{
		if (nullptr == Inst_)
		{
			return;
		}
		delete Inst_;
		Inst_ = nullptr;
	}

protected:

private:
	std::map<std::string, GameEngineImage*> AllRes;

	static GameEngineImageManager* Inst_;
};

