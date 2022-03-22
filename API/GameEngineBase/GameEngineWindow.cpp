#include "GameEngineWindow.h"
#include "GameEngineDebug.h"
// GameEngineBase가 exe 파일 만들 필요X. => 라이브러리 프로젝트
// GameEngineBase -> 속성 -> 일반 -> 구성 형식(정적 라이브러리)

// 전역 함수
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    return DefWindowProc(hWnd, message, wParam, lParam);
}

GameEngineWindow* GameEngineWindow::Inst_ = new GameEngineWindow();


GameEngineWindow::GameEngineWindow()
    : hInst_(nullptr)
    , hWnd_(nullptr)
{
}

GameEngineWindow::~GameEngineWindow()
{

}

void GameEngineWindow::RegClass(HINSTANCE _hInst)
{
    WNDCLASSEXA wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = _hInst;
    wcex.hIcon = nullptr;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = "GameEngineWindowClass";
    wcex.hIconSm = nullptr;

    RegisterClassExA(&wcex);
}

void GameEngineWindow::CreateGameWindow(HINSTANCE _hInst, const std::string& _Title)
{
    // 2번 이상 호출될 경우를 대비하여 막아 놓음
    if (nullptr != hInst_)
    {
        //GameEngineDebug::MsgBoxAssert("윈도우를 2번 띄우려고 했습니다.");
        MsgBoxAssert("윈도우를 2번 띄우려고 했습니다.");
        return;
    }
    
    Title_ = _Title;
    // 틀래스 등록은 한 번만!
    hInst_ = _hInst;
    RegClass(_hInst);

    hWnd_ = CreateWindowExA(0L, "GameEngineWindowClass", Title_.c_str(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, _hInst, nullptr);

    if (!hWnd_)
    {
        return;
    }
}

void GameEngineWindow::ShowGameWindow()
{
    if (nullptr == hWnd_)
    {
        //GameEngineDebug::MsgBoxAssert("메인 윈도우가 만들어지지 않았습니다. 화면에 출력할 수 없습니다.");
        MsgBoxAssert("메인 윈도우가 만들어지지 않았습니다. 화면에 출력할 수 없습니다.");
        return;
    }
    ShowWindow(hWnd_, SW_SHOW);
    UpdateWindow(hWnd_);
}
