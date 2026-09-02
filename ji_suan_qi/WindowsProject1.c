// WindowsProject1.c : 计算器应用程序入口点（纯 C 语言实现）
//

#include "framework.h"
#include "WindowsProject1.h"
#include <stdio.h>
#include <math.h>
#include <strsafe.h>

#define MAX_LOADSTRING 100

// 计算器控件 ID
#define IDC_DISPLAY     2000
#define IDC_BTN_0       2001
#define IDC_BTN_1       2002
#define IDC_BTN_2       2003
#define IDC_BTN_3       2004
#define IDC_BTN_4       2005
#define IDC_BTN_5       2006
#define IDC_BTN_6       2007
#define IDC_BTN_7       2008
#define IDC_BTN_8       2009
#define IDC_BTN_9       2010
#define IDC_BTN_DOT     2011
#define IDC_BTN_ADD     2012
#define IDC_BTN_SUB     2013
#define IDC_BTN_MUL     2014
#define IDC_BTN_DIV     2015
#define IDC_BTN_EQ      2016
#define IDC_BTN_CLR     2017
#define IDC_BTN_SQRT    2018
#define IDC_BTN_PCT     2019
#define IDC_BTN_DERIV   2020
#define IDC_BTN_INTEG   2021

// 全局变量
HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

// 计算器状态
typedef struct {
    double currentValue;      // 当前显示的值
    double storedValue;       // 存储的值（用于二元运算）
    int    pendingOp;         // 待执行的运算: 0=无, 1=+, 2=-, 3=*, 4=/
    int    waitingForOperand; // 是否等待新操作数输入
    int    hasDecimal;        // 当前输入是否已有小数点
    int    decimalPlaces;     // 当前小数位数
} CalcState;

static CalcState g_calc = { 0.0, 0.0, 0, 1, 0, 0 };
static HWND g_hDisplay = NULL;
static HFONT g_hDisplayFont = NULL;
static HFONT g_hBtnFont = NULL;

// 数值微分的被导函数 f(x) = x^2
static double derivFunc(double x) {
    return x * x;
}

// 数值积分的被积函数 f(t) = t^2
static double integFunc(double t) {
    return t * t;
}

// 数值微分：中心差分法计算 f'(x)，f(x)=x^2，结果为 2x
static double numericalDerivative(double x) {
    double h = 1e-5;
    return (derivFunc(x + h) - derivFunc(x - h)) / (2.0 * h);
}

// 数值积分：Simpson 法计算 ∫₀ˣ t^2 dt，结果为 x^3/3
static double numericalIntegral(double x) {
    int n = 1000;            // 区间数（偶数）
    double a = 0.0;
    double b = x;
    double h = (b - a) / (double)n;
    double sum = integFunc(a) + integFunc(b);
    int i;
    for (i = 1; i < n; i++) {
        double t = a + (double)i * h;
        if (i % 2 == 0) {
            sum += 2.0 * integFunc(t);
        } else {
            sum += 4.0 * integFunc(t);
        }
    }
    return sum * h / 3.0;
}

// 格式化显示：保留 4 位小数以内，去除末尾多余的 0
static void FormatDisplay(WCHAR *buffer, int bufSize, double value) {
    int len;
    WCHAR *dot;

    if (!isfinite(value)) {
        StringCchCopyW(buffer, bufSize, L"Error");
        return;
    }
    // 保留 4 位小数
    StringCchPrintfW(buffer, bufSize, L"%.4f", value);
    // 去除末尾多余的 0
    len = (int)wcslen(buffer);
    dot = wcschr(buffer, L'.');
    if (dot) {
        int dotPos = (int)(dot - buffer);
        while (len > dotPos + 1 && buffer[len - 1] == L'0') {
            buffer[len - 1] = L'\0';
            len--;
        }
        // 小数点后无数字则去掉小数点
        if (len == dotPos + 1) {
            buffer[len - 1] = L'\0';
        }
    }
}

// 更新显示
static void UpdateDisplay(void) {
    WCHAR buf[64];
    FormatDisplay(buf, 64, g_calc.currentValue);
    SetWindowTextW(g_hDisplay, buf);
}

// 输入数字
static void InputDigit(int digit) {
    if (g_calc.waitingForOperand) {
        g_calc.currentValue = 0.0;
        g_calc.hasDecimal = 0;
        g_calc.decimalPlaces = 0;
        g_calc.waitingForOperand = 0;
    }
    if (g_calc.hasDecimal) {
        g_calc.decimalPlaces++;
        g_calc.currentValue += (double)digit * pow(10.0, -(double)g_calc.decimalPlaces);
    } else {
        g_calc.currentValue = g_calc.currentValue * 10.0 + (double)digit;
    }
    UpdateDisplay();
}

// 输入小数点
static void InputDecimal(void) {
    if (g_calc.waitingForOperand) {
        g_calc.currentValue = 0.0;
        g_calc.waitingForOperand = 0;
    }
    if (!g_calc.hasDecimal) {
        g_calc.hasDecimal = 1;
        g_calc.decimalPlaces = 0;
    }
    UpdateDisplay();
}

// 执行二元运算
static double CalculateBinary(double a, double b, int op) {
    switch (op) {
        case 1: return a + b;
        case 2: return a - b;
        case 3: return a * b;
        case 4:
            if (b == 0.0) return NAN;
            return a / b;
        default: return b;
    }
}

// 设置运算符
static void SetOperator(int op) {
    if (g_calc.pendingOp != 0 && !g_calc.waitingForOperand) {
        g_calc.storedValue = CalculateBinary(g_calc.storedValue, g_calc.currentValue, g_calc.pendingOp);
        g_calc.currentValue = g_calc.storedValue;
        UpdateDisplay();
    } else {
        g_calc.storedValue = g_calc.currentValue;
    }
    g_calc.pendingOp = op;
    g_calc.waitingForOperand = 1;
}

// 等号
static void OnEquals(void) {
    if (g_calc.pendingOp != 0) {
        g_calc.currentValue = CalculateBinary(g_calc.storedValue, g_calc.currentValue, g_calc.pendingOp);
        g_calc.pendingOp = 0;
        g_calc.waitingForOperand = 1;
        UpdateDisplay();
    }
}

// 清除
static void OnClear(void) {
    g_calc.currentValue = 0.0;
    g_calc.storedValue = 0.0;
    g_calc.pendingOp = 0;
    g_calc.waitingForOperand = 1;
    g_calc.hasDecimal = 0;
    g_calc.decimalPlaces = 0;
    UpdateDisplay();
}

// 平方根
static void OnSqrt(void) {
    if (g_calc.currentValue < 0.0) {
        g_calc.currentValue = NAN;
    } else {
        g_calc.currentValue = sqrt(g_calc.currentValue);
    }
    g_calc.waitingForOperand = 1;
    UpdateDisplay();
}

// 百分比
static void OnPercent(void) {
    g_calc.currentValue = g_calc.currentValue / 100.0;
    g_calc.waitingForOperand = 1;
    UpdateDisplay();
}

// 求导：对 f(x)=x^2 在当前值处求数值导数
static void OnDerivative(void) {
    g_calc.currentValue = numericalDerivative(g_calc.currentValue);
    g_calc.waitingForOperand = 1;
    UpdateDisplay();
}

// 积分：对 f(t)=t^2 从 0 到当前值进行数值积分
static void OnIntegral(void) {
    g_calc.currentValue = numericalIntegral(g_calc.currentValue);
    g_calc.waitingForOperand = 1;
    UpdateDisplay();
}

// 前向声明
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// 创建按钮辅助函数
static HWND CreateBtn(HWND parent, const WCHAR *text, int id, int x, int y, int w, int h) {
    return CreateWindowW(L"BUTTON", text, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                         x, y, w, h, parent, (HMENU)(LONG_PTR)id, hInst, NULL);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance(hInstance, nCmdShow)) {
        return FALSE;
    }

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance) {
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = CreateSolidBrush(RGB(240, 240, 240)); // 浅色背景
    wcex.lpszMenuName = NULL;  // 无菜单
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
    RECT rc;
    hInst = hInstance;
    // 客户区大小: 宽 335, 高 410
    rc.left = 0;
    rc.top = 0;
    rc.right = 335;
    rc.bottom = 410;
    AdjustWindowRectEx(&rc, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, FALSE, 0);
    HWND hWnd = CreateWindowW(szWindowClass, szTitle,
                               WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
                               CW_USEDEFAULT, 0,
                               rc.right - rc.left, rc.bottom - rc.top,
                               NULL, NULL, hInstance, NULL);
    if (!hWnd) return FALSE;
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_CREATE: {
        int btnW = 75, btnH = 50;
        int gap = 5;
        int startX = 10, startY = 60;
        int col, row;
        int ids[] = {IDC_BTN_0, IDC_BTN_1, IDC_BTN_2, IDC_BTN_3, IDC_BTN_4,
                     IDC_BTN_5, IDC_BTN_6, IDC_BTN_7, IDC_BTN_8, IDC_BTN_9,
                     IDC_BTN_DOT, IDC_BTN_ADD, IDC_BTN_SUB, IDC_BTN_MUL, IDC_BTN_DIV,
                     IDC_BTN_EQ, IDC_BTN_CLR, IDC_BTN_SQRT, IDC_BTN_PCT,
                     IDC_BTN_DERIV, IDC_BTN_INTEG};
        int nIds = (int)(sizeof(ids) / sizeof(ids[0]));
        int i;

        // 创建显示框
        g_hDisplay = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", L"0",
                                      WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_READONLY | ES_AUTOHSCROLL,
                                      10, 10, 315, 40, hWnd, (HMENU)IDC_DISPLAY, hInst, NULL);
        g_hDisplayFont = CreateFontW(28, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                                      DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                                      CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                                      DEFAULT_PITCH | FF_DONTCARE, L"Consolas");
        SendMessageW(g_hDisplay, WM_SETFONT, (WPARAM)g_hDisplayFont, TRUE);

        // 第 1 行: 7, 8, 9, /
        col = 0; row = 0;
        CreateBtn(hWnd, L"7", IDC_BTN_7, startX + 0*(btnW+gap), startY + 0*(btnH+gap), btnW, btnH);
        CreateBtn(hWnd, L"8", IDC_BTN_8, startX + 1*(btnW+gap), startY + 0*(btnH+gap), btnW, btnH);
        CreateBtn(hWnd, L"9", IDC_BTN_9, startX + 2*(btnW+gap), startY + 0*(btnH+gap), btnW, btnH);
        CreateBtn(hWnd, L"/", IDC_BTN_DIV, startX + 3*(btnW+gap), startY + 0*(btnH+gap), btnW, btnH);
        // 第 2 行: 4, 5, 6, *
        CreateBtn(hWnd, L"4", IDC_BTN_4, startX + 0*(btnW+gap), startY + 1*(btnH+gap), btnW, btnH);
        CreateBtn(hWnd, L"5", IDC_BTN_5, startX + 1*(btnW+gap), startY + 1*(btnH+gap), btnW, btnH);
        CreateBtn(hWnd, L"6", IDC_BTN_6, startX + 2*(btnW+gap), startY + 1*(btnH+gap), btnW, btnH);
        CreateBtn(hWnd, L"*", IDC_BTN_MUL, startX + 3*(btnW+gap), startY + 1*(btnH+gap), btnW, btnH);
        // 第 3 行: 1, 2, 3, -
        CreateBtn(hWnd, L"1", IDC_BTN_1, startX + 0*(btnW+gap), startY + 2*(btnH+gap), btnW, btnH);
        CreateBtn(hWnd, L"2", IDC_BTN_2, startX + 1*(btnW+gap), startY + 2*(btnH+gap), btnW, btnH);
        CreateBtn(hWnd, L"3", IDC_BTN_3, startX + 2*(btnW+gap), startY + 2*(btnH+gap), btnW, btnH);
        CreateBtn(hWnd, L"-", IDC_BTN_SUB, startX + 3*(btnW+gap), startY + 2*(btnH+gap), btnW, btnH);
        // 第 4 行: 0, ., =, +
        CreateBtn(hWnd, L"0", IDC_BTN_0, startX + 0*(btnW+gap), startY + 3*(btnH+gap), btnW, btnH);
        CreateBtn(hWnd, L".", IDC_BTN_DOT, startX + 1*(btnW+gap), startY + 3*(btnH+gap), btnW, btnH);
        CreateBtn(hWnd, L"=", IDC_BTN_EQ, startX + 2*(btnW+gap), startY + 3*(btnH+gap), btnW, btnH);
        CreateBtn(hWnd, L"+", IDC_BTN_ADD, startX + 3*(btnW+gap), startY + 3*(btnH+gap), btnW, btnH);
        // 第 5 行: C, √, %, d/dx
        CreateBtn(hWnd, L"C", IDC_BTN_CLR, startX + 0*(btnW+gap), startY + 4*(btnH+gap), btnW, btnH);
        CreateBtn(hWnd, L"√", IDC_BTN_SQRT, startX + 1*(btnW+gap), startY + 4*(btnH+gap), btnW, btnH);
        CreateBtn(hWnd, L"%", IDC_BTN_PCT, startX + 2*(btnW+gap), startY + 4*(btnH+gap), btnW, btnH);
        CreateBtn(hWnd, L"d/dx", IDC_BTN_DERIV, startX + 3*(btnW+gap), startY + 4*(btnH+gap), btnW, btnH);
        // 第 6 行: ∫ (跨 4 列)
        CreateBtn(hWnd, L"∫", IDC_BTN_INTEG, startX, startY + 5*(btnH+gap),
                  btnW * 4 + gap * 3, btnH);

        // 设置按钮字体
        g_hBtnFont = CreateFontW(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                                  DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                                  CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                                  DEFAULT_PITCH | FF_DONTCARE, L"Segoe UI");
        for (i = 0; i < nIds; i++) {
            HWND hBtn = GetDlgItem(hWnd, ids[i]);
            if (hBtn) SendMessageW(hBtn, WM_SETFONT, (WPARAM)g_hBtnFont, TRUE);
        }

        UpdateDisplay();
        return 0;
    }
    case WM_COMMAND: {
        int wmId = LOWORD(wParam);
        switch (wmId) {
            case IDC_BTN_0: InputDigit(0); break;
            case IDC_BTN_1: InputDigit(1); break;
            case IDC_BTN_2: InputDigit(2); break;
            case IDC_BTN_3: InputDigit(3); break;
            case IDC_BTN_4: InputDigit(4); break;
            case IDC_BTN_5: InputDigit(5); break;
            case IDC_BTN_6: InputDigit(6); break;
            case IDC_BTN_7: InputDigit(7); break;
            case IDC_BTN_8: InputDigit(8); break;
            case IDC_BTN_9: InputDigit(9); break;
            case IDC_BTN_DOT: InputDecimal(); break;
            case IDC_BTN_ADD: SetOperator(1); break;
            case IDC_BTN_SUB: SetOperator(2); break;
            case IDC_BTN_MUL: SetOperator(3); break;
            case IDC_BTN_DIV: SetOperator(4); break;
            case IDC_BTN_EQ: OnEquals(); break;
            case IDC_BTN_CLR: OnClear(); break;
            case IDC_BTN_SQRT: OnSqrt(); break;
            case IDC_BTN_PCT: OnPercent(); break;
            case IDC_BTN_DERIV: OnDerivative(); break;
            case IDC_BTN_INTEG: OnIntegral(); break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
        }
        return 0;
    }
    case WM_CTLCOLORSTATIC: {
        // 显示框（只读 EDIT）背景设为浅色
        HDC hdc = (HDC)wParam;
        SetBkColor(hdc, RGB(255, 255, 255));
        SetTextColor(hdc, RGB(0, 0, 0));
        static HBRUSH hDispBrush = NULL;
        if (!hDispBrush) hDispBrush = CreateSolidBrush(RGB(255, 255, 255));
        return (INT_PTR)hDispBrush;
    }
    case WM_DESTROY:
        if (g_hDisplayFont) DeleteObject(g_hDisplayFont);
        if (g_hBtnFont) DeleteObject(g_hBtnFont);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
