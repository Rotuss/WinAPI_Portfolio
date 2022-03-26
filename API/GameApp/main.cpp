#include <Windows.h>
// GameApp -> �Ӽ� -> ��Ŀ -> �ý��� -> ����(â ���)
// GameApp -> �Ӽ� -> ��� -> ��������(��Ƽ ����Ʈ)
// GameApp -> �Ӽ� -> �Ϲ� -> ���/�߰� ���͸�(���ϴ� ��ġ�� �°� ��� ����)(���)
// GameApp -> �Ӽ� -> C/C++ -> �߰� ���� ���͸�(..\;)

// GameApp(����) -> ���� �߰� -> GameEngineBase, GameEngine, GameEngineContents

// �� ����� ����ִ���, ��� ������Ʈ�� �ִ��� �˱� ����
#include <GameEngineBase//GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineContents/SnowBros.h>

SnowBros MyGame;

void GameInit()
{
    // �ؽ�ó�� �ε��ϰ� �غ��ϰ� ������Ʈ�� �̸� ����� ���� ���� GameLoop���� ������ ����

    MyGame.GameInit();
}

void GameLoop()
{
    // �� �������� ����
    MyGame.GameLoop();
}

int APIENTRY WinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    GameEngineDebug::LeakCheckOn();
    GameEngineWindow::GetInst().CreateGameWindow(hInstance, "GameWindow");
    GameEngineWindow::GetInst().ShowGameWindow();
    GameEngineWindow::GetInst().MessageLoop(GameInit, GameLoop);
    GameEngineWindow::Destroy();

    MyGame.GameEnd();
}