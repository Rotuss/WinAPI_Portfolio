#include "GameEngineWindow.h"
// GameEngineBase가 exe 파일 만들 필요X. => 라이브러리 프로젝트
// GameEngineBase -> 속성 -> 일반 -> 구성 형식(정적 라이브러리)

// 전역 함수
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    return DefWindowProc(hWnd, message, wParam, lParam);
}

GameEngineWindow* GameEngineWindow::Inst_ = new GameEngineWindow();


GameEngineWindow::GameEngineWindow()
{
}

GameEngineWindow::~GameEngineWindow()
{

}

void GameEngineWindow::CreateGameWindow(HINSTANCE _hInst)
{
    WNDCLASSEXW wcex;

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
    wcex.lpszClassName = L"GameEngineWindowClass";
    wcex.hIconSm = nullptr;

    RegisterClassExW(&wcex);

    hWnd_ = CreateWindowW(L"GameEngineWindowClass", L"SnowBro", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, _hInst, nullptr);

    if (!hWnd_)
    {
        return;
    }
}

void GameEngineWindow::ShowGameWindow()
{
    ShowWindow(hWnd_, SW_SHOW);
    UpdateWindow(hWnd_);
}
