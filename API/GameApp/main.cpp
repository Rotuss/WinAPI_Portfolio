#include <Windows.h>
// GameApp -> 속성 -> 링커 -> 시스템 -> 하위(창 모드)
// GameApp -> 속성 -> 고급 -> 문자집합(멀티 바이트)
// GameApp -> 속성 -> 일반 -> 출력/중간 디렉터리(원하는 위치에 맞게 경로 설정)(모두)
// GameApp -> 속성 -> C/C++ -> 추가 포함 디렉터리(..\;)

// GameApp(참조) -> 참조 추가

// 이 헤더가 어디있는지, 어느 프로젝트에 있는지 알기 위해
#include <GameEngineBase/GameEngineWindow.h>

int APIENTRY WinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    GameEngineWindow::GetInst().CreateGameWindow(hInstance);
    GameEngineWindow::GetInst().ShowGameWindow();
}