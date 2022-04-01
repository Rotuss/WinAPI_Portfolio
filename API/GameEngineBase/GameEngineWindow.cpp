#include "GameEngineWindow.h"
#include "GameEngineDebug.h"
// GameEngineBase가 exe 파일 만들 필요X. => 라이브러리 프로젝트
// GameEngineBase -> 속성 -> 일반 -> 구성 형식(정적 라이브러리)

// HWND hWnd    : 어떤 윈도우에 무슨 일이 생겼는지 그 윈도우의 핸들
// UINT message : 그 메시지의 종류가 무엇인지
// WPARAM wParam
// LPARAM lParam
// 전역 함수
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        GameEngineWindow::GetInst().Off();
        return DefWindowProc(hWnd, message, wParam, lParam);
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    default:
        break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

GameEngineWindow* GameEngineWindow::Inst_ = new GameEngineWindow();


GameEngineWindow::GameEngineWindow()
    : hInst_(nullptr)
    , hWnd_(nullptr)
    , WindowOn_(true)
    , HDC_(nullptr)
{
}

GameEngineWindow::~GameEngineWindow()
{
    // 직접 만들어 준 것이 아니면 모두 삭제
    if (nullptr != HDC_)
    {
        ReleaseDC(hWnd_, HDC_);
        HDC_ = nullptr;
    }

    if (nullptr != hWnd_)
    {
        DestroyWindow(hWnd_);
        hWnd_ = nullptr;
    }
}

void GameEngineWindow::Off()
{
    WindowOn_ = false;
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
    // 클래스 등록은 한 번만!
    hInst_ = _hInst;
    RegClass(_hInst);

    hWnd_ = CreateWindowExA(0L, "GameEngineWindowClass", "SnowBro", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, _hInst, nullptr);

    // HDC : 화면에 무언가를 그리기 위한 핸들
    HDC_ = GetDC(hWnd_);

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

void GameEngineWindow::MessageLoop(void(* _InitFunction)(), void(*_LoopFunction)())
{
    // _InitFunction() : 루프를 돌기 전에 뭔가 준비할게 있다면 준비함수를 실행
    if (nullptr != _InitFunction)
    {
        _InitFunction();
    }

    MSG msg;

    while (WindowOn_)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            DispatchMessage(&msg);
        }

        // 게임 루프
        if (nullptr == _LoopFunction)
        {
            continue;
        }
        _LoopFunction();
    } 
}

void GameEngineWindow::SetWindowScaleAndPosition(float4 _Pos, float4 _Scale)
{
    RECT Rc = { 0,0,_Scale.ix(),_Scale.iy() };
    // 1280 + 메뉴바
    AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, FALSE);
    
    Scale_ = _Scale;

    SetWindowPos(hWnd_, nullptr, _Pos.ix(), _Pos.iy(), Rc.right - Rc.left, Rc.bottom - Rc.top, SWP_NOZORDER);
}
