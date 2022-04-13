#pragma once
#include <map>
#include "GameEngineNameObject.h"
#include "ThirdParty/inc/fmod.hpp"

// 설명 : 
class GameEngineSoundPlayer;
class GameEngineSound : public GameEngineNameObject
{
public:
	// constrcuter destructer
	GameEngineSound();
	~GameEngineSound();

	// delete Function
	GameEngineSound(const GameEngineSound& _Other) = delete;
	GameEngineSound(GameEngineSound&& _Other) noexcept = delete;
	GameEngineSound& operator=(const GameEngineSound& _Other) = delete;
	GameEngineSound& operator=(GameEngineSound&& _Other) noexcept = delete;

protected:
	bool Load(const std::string& _Path);

private:
	FMOD::Sound* Sound;
	//====================ManagementSound=======================
public:
	// 사운드 재생 1회(도중에 멈춤 불가)
	static GameEngineSoundPlayer SoundPlayControl(const std::string& _Name);
	static void SoundPlayOneShot(const std::string& _Name);
	static void Update();

protected:

private:
	
	//=======================Management=========================
public:
	static GameEngineSound* FindRes(const std::string& _Name);
	static GameEngineSound* LoadRes(const std::string& _Path);
	static GameEngineSound* LoadRes(const std::string& _Path, const std::string& _Name);

	static void AllResourcesDestroy();

protected:

private:
	static std::map<std::string, GameEngineSound*> AllRes_;
};

// 사운드 재생을 제어할 수 있는 기능들
class GameEngineSound;
class GameEngineSoundPlayer
{
	friend GameEngineSound;
public:
	GameEngineSoundPlayer();
	~GameEngineSoundPlayer();
	
	void Stop();
	GameEngineSoundPlayer(const GameEngineSoundPlayer& _Other);

private:
	GameEngineSoundPlayer(GameEngineSound* _Sound, FMOD::Channel* _ControlHandle);

	GameEngineSound* Sound_;
	FMOD::Channel* ControlHandle_;
};