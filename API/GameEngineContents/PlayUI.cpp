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
	// 화면 하단 UI Render 생성
	{
		GameEngineRenderer* Renderer = CreateRenderer("UI.bmp");

		float4 TopUIPivot = GameEngineWindow::GetScale().Half();
		TopUIPivot.y = 0.0f;
		TopUIPivot.y += Renderer->GetImage()->GetScale().Half().y;
		Renderer->SetPivot(TopUIPivot);
		
		Renderer->CameraEffectOff();
	}
}