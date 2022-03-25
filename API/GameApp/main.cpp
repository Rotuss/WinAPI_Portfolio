#include <Windows.h>
// GameApp -> �Ӽ� -> ��Ŀ -> �ý��� -> ����(â ���)
// GameApp -> �Ӽ� -> ��� -> ��������(��Ƽ ����Ʈ)
// GameApp -> �Ӽ� -> �Ϲ� -> ���/�߰� ���͸�(���ϴ� ��ġ�� �°� ��� ����)(���)
// GameApp -> �Ӽ� -> C/C++ -> �߰� ���� ���͸�(..\;)

// GameApp(����) -> ���� �߰�

// �� ����� ����ִ���, ��� ������Ʈ�� �ִ��� �˱� ����
#include <GameEngineBase//GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>

void SnowBroLoop()
{
    // �� �������� ����
    Rectangle(GameEngineWindow::GETDC(), 100, 100, 200, 200);
}

int APIENTRY WinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    GameEngineDebug::LeakCheckOn();
    GameEngineWindow::GetInst().CreateGameWindow(hInstance, "GameWindow");
    GameEngineWindow::GetInst().ShowGameWindow();
    GameEngineWindow::GetInst().MessageLoop(SnowBroLoop);
    GameEngineWindow::Destroy();
}