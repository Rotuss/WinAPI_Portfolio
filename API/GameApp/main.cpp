#include <Windows.h>
// GameApp -> �Ӽ� -> ��Ŀ -> �ý��� -> ����(â ���)
// GameApp -> �Ӽ� -> ��� -> ��������(��Ƽ ����Ʈ)
// GameApp -> �Ӽ� -> �Ϲ� -> ���/�߰� ���͸�(���ϴ� ��ġ�� �°� ��� ����)(���)
// GameApp -> �Ӽ� -> C/C++ -> �߰� ���� ���͸�(..\;)

// GameApp(����) -> ���� �߰�

// �� ����� ����ִ���, ��� ������Ʈ�� �ִ��� �˱� ����
#include <GameEngineBase/GameEngineWindow.h>

int APIENTRY WinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    GameEngineWindow::GetInst().CreateGameWindow(hInstance);
    GameEngineWindow::GetInst().ShowGameWindow();
}