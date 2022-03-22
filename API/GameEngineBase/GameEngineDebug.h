#pragma once
#include <string>
#include <Windows.h>
#include <assert.h>
#include <crtdbg.h>

// 설명 : 
class GameEngineDebug
{
public:
	static void LeakCheckOn();
	// &로 받는 이유 : 메모리 넘기는 인자를 아끼고 넘어간 인자의 비용, 명시(내용을 수정하지 않을거임)
	// static void MsgBoxAssert(const std::string& _Text);

protected:

private:
	// constrcuter destructer
	GameEngineDebug();
	~GameEngineDebug();

	// delete Function
	GameEngineDebug(const GameEngineDebug& _Other) = delete;
	GameEngineDebug(GameEngineDebug&& _Other) noexcept = delete;
	GameEngineDebug& operator=(const GameEngineDebug& _Other) = delete;
	GameEngineDebug& operator=(GameEngineDebug&& _Other) noexcept = delete;
	
};

#define MsgBoxAssert(Text)	MessageBeep(0); \
							MessageBoxA(nullptr, Text, "Error", MB_OK); \
							assert(false);
