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

int APIENTRY WinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    GameEngine::Start<SnowBros>();
}