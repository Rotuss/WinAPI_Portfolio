#include "PlayUI.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

PlayUI::PlayUI()
{
}

PlayUI::~PlayUI()
{
}

void PlayUI::Start()
{
	// Actor를 화면 중앙에 배치
	{
		float4 Pos = GameEngineWindow::GetScale().Half();
		SetPosition(Pos);
	}

	// 화면 하단 UI Render 생성
	{
		GameEngineRenderer* Renderer = CreateRenderer("UI.bmp");

		float4 BotUIPivot = GameEngineWindow::GetScale().Half();
		BotUIPivot.x = 0.0f;
		BotUIPivot.y -= Renderer->GetImage()->GetScale().Half().y;
		Renderer->SetPivot(BotUIPivot);
		
		Renderer->CameraEffectOff();
	}
}