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
	// Actor�� ȭ�� �߾ӿ� ��ġ
	{
		float4 Pos = GameEngineWindow::GetScale().Half();
		SetPosition(Pos);
	}

	// ȭ�� �ϴ� UI Render ����
	{
		GameEngineRenderer* Renderer = CreateRenderer("UI.bmp");

		float4 BotUIPivot = GameEngineWindow::GetScale().Half();
		BotUIPivot.x = 0.0f;
		BotUIPivot.y -= Renderer->GetImage()->GetScale().Half().y;
		Renderer->SetPivot(BotUIPivot);
		
		Renderer->CameraEffectOff();
	}
}