#include<windows.h>
//一 设计窗口类
//二 注册窗口类
//三 创建窗口
//四 显示窗口
//五 更新窗口
//六 消息循环

//窗口处理函数 
LRESULT CALLBACK WindowProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);








int WINAPI WinMain (HINSTANCE hInstance,HINSTANCE hPreinstance,LPSTR lpCmdLine,int nCmdShow){
   // MessageBox(NULL,TEXT("hhhhhhh"),TEXT("hello"),MB_OK);

    //一 设计窗口类
    TCHAR szAppClassName[] = TEXT("wodeEDU");//不会显示这个类型名，是隐藏的

    WNDCLASS wc={0};
    wc.hbrBackground=CreateSolidBrush(RGB(255,255,255));//0:dark
    wc.hCursor      = LoadCursor(NULL,IDC_ARROW);//加载光标
    wc.lpfnWndProc  = WindowProc;   //窗口处理函数

    // wc.hIcon        = LoadIcon(hInstance,MAKEINRESOURSE(IDI_ICON1));//加载图标

    wc.hInstance    = hInstance;//当前应用程序实例句柄
    wc.style        = CS_HREDRAW | CS_VREDRAW;//窗口类的类的风格
    wc.lpszClassName= szAppClassName;//窗口的类型名

    //二 注册窗口类
    RegisterClass(&wc);

    //三 创建窗口

    HWND hWnd = CreateWindow(
        szAppClassName,                                    //窗口类型名
        L"我的窗口",                                        //标题
        WS_BORDER|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX,    //窗口风格
        200,100,                                           //左上角坐标
        500,630,
        NULL,                                              //父窗口句柄
        NULL,                                              //菜单句柄
        hInstance,                                         //应用程序实例句柄
        NULL                                               //附加信息
        );
//句柄就是一个ID,好比人的身份证,指针类型

    //四 显示窗口
    ShowWindow(hWnd,SW_SHOW);
 
    //五 更新窗口
    UpdateWindow(hWnd);


    //六 消息循环
    MSG msg;

    while(GetMessage(&msg,NULL,0,0)){
        //将虚拟键消息转化为字符消息
        TranslateMessage(&msg);
        //将消息分发给窗口处理函数
        DispatchMessage(&msg);


    }

    return 0;//程序结束
}

LRESULT CALLBACK WindowProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
    switch(uMsg){
        case WM_CLOSE://窗口关闭消息
            destroyWindow(hWnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
    }


    return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

