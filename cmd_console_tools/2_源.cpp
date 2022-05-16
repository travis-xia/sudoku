#include <conio.h>
#include<windows.h>
#include <graphics.h>
#include <time.h>
#include<stdio.h>
#include<stdlib.h>
#include <string.h>//加的
#define MAP_COL 9
#define MAP_ROW 9

using namespace std;
/* xutao 需要用到的接口：
go(int) //1简单 2一般 3困难 - 生成xutao::tans(真正问题的答案)和xutao::ans(生成的问题)，在外部直接调用即可
*/
namespace xutao
{
	int mat[10][10];
	int ans[10][10];//生成的问题
	int tans[10][10]; //真正问题的答案
	int cnt;
	int row[10][10], line[10][10], block[10][10];
	int flag;
	int t1;
	int count_block(int x, int y);
	void mod(int x, int y, int num);
	void del(int x, int y, int num);
	int check_single(int x, int y, int num);//		x为行坐标  y为列坐标  num为填入数值
	int check_delete(int x, int y, int num);
	void initialization();
	void print();
	void dfs(int x, int y);
	void dig();
	void print_anss();
	void printANS();
	void go(int);
	void backup();
	void dig()
	{
		//printf("cnt = %d\n",cnt);
		int i = 1, j, k, l = (81 - cnt) / 9;
		while (i < 10)
		{
			k = l;
			while (k) {
				j = rand() % 9 + 1;
				while (ans[i][j] == 0)
				{
					j %= 9;
					j++;
				}
				ans[i][j] = 0;
				k--;
			}
			i++;
		}
	}
	//1简单 2一般 3困难 - 生成xutao::tans和xutao::ans，在外部直接调用即可
	void go(int ch)
	{
		srand((unsigned int)time(NULL));//改了，防warning
		switch (ch)
		{
		case 0:cnt = 72;//测试程序取最简单情况
			break;
		case 1:cnt = rand() % 10 + 56;
			break;
		case 2:cnt = rand() % 10 + 37;
			break;
		case 3:cnt = rand() % 10 + 16;
			break;
		default:printf("error.\n");
			exit(0);
		}
		while (flag == 0)
			initialization();
		backup();
		dig();
	}

	void backup()
	{
		for (int i = 1; i <= 9; i++)
		{
			for (int j = 1; j <= 9; j++)
			{
				tans[i][j] = ans[i][j];
			}
		}
	}

	int count_block(int x, int y)
	{
		if (1 <= x && x <= 3)
		{
			if (1 <= y && y <= 3)
				return 1;
			if (4 <= y && y <= 6)
				return 2;
			if (7 <= y && y <= 9)
				return 3;
		}
		else if (4 <= x && x <= 6)
		{
			if (1 <= y && y <= 3)
				return 4;
			if (4 <= y && y <= 6)
				return 5;
			if (7 <= y && y <= 9)
				return 6;
		}
		else if (7 <= x && x <= 9)
		{
			if (1 <= y && y <= 3)
				return 7;
			if (4 <= y && y <= 6)
				return 8;
			if (7 <= y && y <= 9)
				return 9;
		}
		return 1;//防warning，任意返回一个值
	}

	void mod(int x, int y, int num)
	{
		row[x][num]++;
		line[y][num]++;
		block[count_block(x, y)][num]++;
		mat[x][y] = num;
	}

	void del(int x, int y, int num)
	{
		row[x][num]--;
		line[y][num]--;
		block[count_block(x, y)][num]--;
		mat[x][y] = 0;
	}

	int check_single(int x, int y, int num)
	{
		if (row[x][num] == 0 && line[y][num] == 0 && block[count_block(x, y)][num] == 0)
			return 1;
		else return 0;
	}
	int check_delete(int x, int y, int num)
	{
		if (row[x][num] > 1 || line[y][num] > 1 || block[count_block(x, y)][num] > 1)
			return 1;
		else return 0;
	}

	void initialization()
	{

		memset(row, 0, sizeof(row));
		memset(line, 0, sizeof(line));
		memset(block, 0, sizeof(block));
		memset(mat, 0, sizeof(mat));
		t1 = clock();
		int i, j;
		for (i = 1; i <= 9; i++) {
			for (j = 1; j <= 9; j++) {
				int num = rand() % 9 + 1;
				mod(i, j, num);
			}
		}
		for (i = 9; i >= 1; i--) {
			for (j = 9; j >= 1; j--) {
				if (check_delete(i, j, mat[i][j]))
				{
					del(i, j, mat[i][j]);
				}
			}
		}
		dfs(1, 1);
	}

	void print()
	{
		int i, j;
		for (i = 1; i <= 9; i++) {
			for (j = 1; j <= 9; j++) {
				printf("%2d", tans[i][j]);
			}
			printf("\n");
		}
	}

	void printANS()
	{
		int i, j;
		for (i = 1; i <= 9; i++) {
			for (j = 1; j <= 9; j++) {
				printf("%2d", ans[i][j]);
			}
			printf("\n");
		}
	}


	void dfs(int x, int y)
	{
		if (flag > 0)
		{
			return;
		}
		if ((float)(clock() - t1) > 1000)
			return;
		int i, j;
		if (mat[x][y] == 0) {
			for (i = 1; i <= 9; i++)
				if (check_single(x, y, i)) {
					mod(x, y, i);
					dfs(x, y);
					del(x, y, i);
				}
		}
		if (mat[x][y] != 0) {
			if (x == 9 && y == 9)
			{
				flag++;
				for (i = 1; i <= 9; i++)
					for (j = 1; j <= 9; j++)
						ans[i][j] = mat[i][j];
			}
			else if (y == 9)
				dfs(x + 1, 1);
			else
				dfs(x, y + 1);
		}
	}
}

COORD currentPos = { 0,0 }, numPos = { 10,0 }, coord, waitPos, highlightpos;
struct {
	int i = 0;
	int j = 0;
	int flag = 0;
}highlightset;
MOUSEMSG msg;
int mx, my;//鼠标坐标
int mouseclickcount = 0;
int num = 1;
int deleteflag = 0;

int map[9][9];//改的
int map_cpy[9][9];//改的
int answer[9][9];//改的
/*int map[9][9] = { {9,8,2,5,3,6,1,7,4},
		{4,3,6,7,1,9,5,8,2},
		{1,5,0,4,8,2,3,6,9},
		{8,4,5,6,2,7,9,3,1},
		{2,6,3,1,0,5,7,4,8},
		{7,1,0,8,4,3,2,5,6},
		{3,2,4,9,5,8,0,1,7},
		{6,9,1,3,7,4,8,2,5},
		{5,7,8,2,6,1,4,9,3} };
int map_cpy[9][9] = { {9,8,2,5,3,6,1,7,4},
		{4,3,6,7,1,9,5,8,2},
		{1,5,0,4,8,2,3,6,9},
		{8,4,5,6,2,7,9,3,1},
		{2,6,3,1,0,5,7,4,8},
		{7,1,0,8,4,3,2,5,6},
		{3,2,4,9,5,8,0,1,7},
		{6,9,1,3,7,4,8,2,5},
		{5,7,8,2,6,1,4,9,3} };
int answer[9][9] = { {9,8,2,5,3,6,1,7,4},
		{4,3,6,7,1,9,5,8,2},
		{1,5,7,4,8,2,3,6,9},
		{8,4,5,6,2,7,9,3,1},
		{2,6,3,1,9,5,7,4,8},
		{7,1,9,8,4,3,2,5,6},
		{3,2,4,9,5,8,6,1,7},
		{6,9,1,3,7,4,8,2,5},
		{5,7,8,2,6,1,4,9,3} };*/
int map1[3][3] = { 1,2,3,4,5,6,7,8,9 };
void init();
void firstpage();
void draw();
void showdata();
bool isWIN(int,int,int);//改了
void hightlight();
void mousechoose();
void secondPage();//加的
#define MAXN 81 //最大要填的空格数
struct block
{
	int x, y, trueanswer;
} blo[MAXN];//加的
int correct;//加的
int total;//加的

int main() {
	initgraph(900, 660);
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, _T("数独游戏"));
	
	init();

	firstpage();
	secondPage();//加的

	draw();
	showdata();
	bool win = false;//加的
	MessageBox(GetHWnd(),L"操作指南：\n填入数字的方法：\n"
		L"先点击左上角的数字以选定，再点击空格处填入数字。\n也可以鼠标放到空格处后按下键盘对应数字填入。\n删除数字的方法：\n"
		L"先点击delete按钮后点击空格处进行一次删除。\n也可以鼠标放到空格处后按下数字0键删除对应格。", L"提示", 0);//加的
	while (1) {
		while (MouseHit()) {
			msg = GetMouseMsg();
			int x = msg.x;
			int y = msg.y;
			bool donej = false;
			switch (msg.uMsg) {
			case WM_LBUTTONDOWN:     //鼠标左键

				if (msg.x < 500 && msg.x>50 && msg.y < 500 && msg.y>50) {
					int i = (msg.x - 50) / 50;
					int j = (msg.y - 50) / 50;
					if (deleteflag == 1 && map_cpy[j][i] == 0) {
						isWIN(x, y, 1);//删除必然不会导致胜利，win布尔值无需更新
						map[j][i] = num;
						donej = true;//下面不用判了
						deleteflag = 0;
					}
					if (map_cpy[j][i] == 0) {//改过，改成了可以用替代的方式填格子;顺序也调了
						win = isWIN(x, y, 0);
						map[j][i] = num;
					}
					if (deleteflag == 1 && map_cpy[j][i] != 0) {
						//MessageBox(GetHWnd(), L"这个不可以", L"错误！", 0); //没必要显示
					}
					init(); draw(); showdata();
				}
				if (msg.x < 730 && msg.x>580 && msg.y < 230 && msg.y>80) {
					numPos.X = (x - 580) / 50;
					numPos.Y = (y - 80) / 50;
					num = 3 * numPos.Y + numPos.X + 1;
					//MessageBox(GetHWnd(), L"准备好填数字了", L"恭喜你", 0);//没必要显示
					init(); draw(); showdata();
				}
				if (msg.x < 730 && msg.x>580 && msg.y < 350 && msg.y >300) {
					num = 0; deleteflag = 1;
					//MessageBox(GetHWnd(), L"准备删除", L"注意", 0);//没必要显示
					init(); draw(); showdata();
				}
				break;
			case WM_LBUTTONUP:
				break;
			case WM_MOUSEMOVE:   //鼠标移动
				if (msg.x < 500 && msg.x>50 && msg.y < 500 && msg.y>50) {
					highlightset.flag = 1;
					if (highlightset.i != (msg.x - 50) / 50 || highlightset.j != (msg.y - 50) / 50)
					{
						highlightset.i = (msg.x - 50) / 50;
						highlightset.j = (msg.y - 50) / 50;
						cleardevice();
						BeginBatchDraw();
						init(); draw(); showdata();
						EndBatchDraw();
						Sleep(10);
					}

				}
				else {
					highlightset.flag = 0;
				}
				break;
			default:break;
			}
			msg.uMsg = WM_MBUTTONUP;
		}/*
		init();
		drawline();*/
		if (_kbhit())
		{
			char ch = _getch();
			int x, y, i, j, nnum;
			switch (ch)
			{
			case '0':
				x = msg.x;
				y = msg.y;
				i = (msg.x - 50) / 50;
				j = (msg.y - 50) / 50;
				if (i < 0 || j < 0 || i>9 || j>9)
				{
					break;
				}

				if (map_cpy[j][i] == 0)
				{
					isWIN(x, y, 1);
					map[j][i] = 0;
					init(); draw(); showdata();
				}
				break;
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				nnum = ch - '0';
				x = msg.x;
				y = msg.y;
				i = (msg.x - 50) / 50;
				j = (msg.y - 50) / 50;
				if (i < 0 || j < 0 || i>9 || j>9)
				{
					break;
				}

				if (map_cpy[j][i] == 0)
				{
					num = nnum;
					win = isWIN(x, y, 0);
					map[j][i] = nnum;
					init(); draw(); showdata();
				}
				break;
			default:break;
			}
		}

		if (win) {
			MessageBox(GetHWnd(), L"恭喜你，你保研了！", L"注意", 0);
			break;
		}
	}


	(void)_getch();//防warning而改动
	closegraph();
	return 0;
}
void init()
{
	//游戏界面初始化

	setbkcolor(WHITE);
	setbkmode(1);
	cleardevice();
	//添加背景图片
	IMAGE back;
	IMAGE funny;//可能的插图
	IMAGE mask(80, 80);//掩码
	loadimage(&back, _T("D:\\_lr580\\program\\C\\outpack\\2\\a.jpg"), 900, 660, 1);//图片地址记得改
	/*int width = back.getwidth();
	int height = back.getheight();
	initgraph(width, height);*/
	putimage(0, 0, &back);
}
void draw() {
	int i = 0;
	BeginBatchDraw();
	//IMAGE maskbitmap(900, 900);
	//DWORD* pmemmaskbitmap = GetImageBuffer(&maskbitmap);

	//画出大九宫格
	setlinecolor(BLACK);
	for (i = 0; i < 10; i++) {
		if (i % 3 == 0) {
			setlinestyle(PS_SOLID, 3);
		}
		else {
			setlinestyle(PS_DASH, 1);
		}
		line(50, 50 + i * 50, 50 + 450, 50 + i * 50);
	}
	for (i = 0; i < 10; i++) {
		if (i % 3 == 0) {
			setlinestyle(PS_SOLID, 3);
		}
		else {
			setlinestyle(PS_DASH, 1);
		}
		line(50 + i * 50, 50, 50 + i * 50, 50 + 450);
		
	}
	//setfillcolor(WHITE);
	//solidrectangle(550, 50, 750, 500);
	{
		//画出小九宫格
		int i = 0;
		for (i = 0; i < 4; i++) {
			if (i % 3 == 0) {
				setlinestyle(PS_SOLID, 3);
			}
			else {
				setlinestyle(PS_DASH, 1);
			}
			line(580, 80 + i * 50, 730, 80 + i * 50);
		}
		for (i = 0; i < 4; i++) {
			if (i % 3 == 0) {
				setlinestyle(PS_SOLID, 3);
			}
			else {
				setlinestyle(PS_DASH, 1);
			}
			line(580 + i * 50, 80, 580 + i * 50, 230);
		}
	}

	//画出delete
	setfillcolor(LIGHTCYAN);
	solidrectangle(580, 300, 730, 350);
	//画出高亮块
	if (highlightset.flag) {
		setfillcolor(RGB(180, 180, 180));
		for (int a = 0; a < 9; a++)
			solidrectangle(50 + 50 * a, 50 + 50 * highlightset.j, 100 + 50 * a, 100 + 50 * highlightset.j);
		for (int a = 0; a < 9; a++)
			solidrectangle(50 + 50 * highlightset.i, 50 + 50 * a, 100 + 50 * highlightset.i, 100 + 50 * a);
		showdata();
	}
	EndBatchDraw();
}
void showdata() {
	BeginBatchDraw();
	TCHAR str[10];

	LOGFONT f;
	gettextstyle(&f);                     // 获取当前字体设置
	f.lfHeight = 40;                      // 设置字体高度为 40
	wcscpy_s(f.lfFaceName, _T("宋体"));   // 设置字体为“楷体”(高版本 VC 推荐使用 _tcscpy_s 函数)
	f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	settextstyle(&f);


	for (int row = 0; row < MAP_ROW; row++)
	{
		for (int col = 0; col < MAP_COL; col++)
		{
			//数字0就不需要显示了
			if (map[row][col])
			{
				settextcolor(LIGHTRED);
				_stprintf_s(str, _T("%d"), map[row][col]);
				if (map[row][col] != map_cpy[row][col]) settextcolor(GREEN);
				outtextxy((col + 1) * 50 + 15, (row + 1) * 50 + 10, str);
			}
		}
	}
	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			//if (map1[row][col] != 0) {
			settextcolor(GREEN);
			_stprintf_s(str, _T("%d"), map1[row][col]);
			outtextxy((col) * 50 + 580 + 15, (row) * 50 + 80 + 10, str);
			//}
		}
	}
	settextcolor(DARKGRAY);
	outtextxy(595, 300, _T("delete"));

	EndBatchDraw();
}
bool isWIN(int x, int y, int type) {//改了,type=0添加，type=1删除
	int by = (x - 50) / 50;
	int bx = (y - 50) / 50;
	if (bx < 0 || by < 0 || bx>9 || by>9) return false;
	int nnum = num;
	if (!num)
	{
		type = 1;
	}
	if (type == 1)
	{
		nnum = map[bx][by];
	}
	else nnum = num;
 
	for (int i = 0; i < total; i++)
	{
		if (bx == blo[i].x && by == blo[i].y)
		{
			if (nnum == blo[i].trueanswer)
			{
				if (type) correct--;
				else correct++;
			}
			if (map_cpy[bx][by] == 0 && map[bx][by] == blo[i].trueanswer && nnum != blo[i].trueanswer)
			{
				correct--;
			}
			break;
		}
	}
	/*TCHAR tt[20];
	_stprintf_s(tt, _T("%d %d"), correct, total);
	MessageBox(GetHWnd(), tt, L"注意", 0);*/
	return correct==total;
}
void firstpage() {//改过

	int unselect = 1;
	while (unselect)
	{
		BeginBatchDraw();
		setfillcolor(WHITE);
		solidrectangle(350, 260, 550, 300);//位置微调了
		settextcolor(BLACK);
		LOGFONT f;
		gettextstyle(&f);                     // 获取当前字体设置
		f.lfHeight = 40;                      // 设置字体高度为 40
		wcscpy_s(f.lfFaceName, _T("宋体"));   // 设置字体为“楷体”(高版本 VC 推荐使用 _tcscpy_s 函数)
		f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
		settextstyle(&f);
		outtextxy(370, 260, L"开始游戏");
		EndBatchDraw();
		while (MouseHit())
		{
			msg = GetMouseMsg();
			int x = msg.x;
			int y = msg.y;
			switch (msg.uMsg) {
			case WM_LBUTTONDOWN:     //鼠标左键
				if (msg.x < 550 && msg.x > 350 && msg.y < 3000 && msg.y > 260)
				{
					unselect = 0;
				}

				break;
			default:break;
			}
			msg.uMsg = WM_MBUTTONUP;
		}
	}
}

void secondPage()//加的
{
	int unselect = 1;
	int levelType = 0;
	while (unselect)
	{
		BeginBatchDraw();
		
		solidrectangle(350, 60, 550, 100);
		outtextxy(370, 60, L"选择难度");

		solidrectangle(350, 160, 550, 200);
		outtextxy(370, 160, L"简单模式");

		solidrectangle(350, 260, 550, 300);
		outtextxy(370, 260, L"普通模式");

		solidrectangle(350, 360, 550, 400);
		outtextxy(370, 360, L"困难模式");

		EndBatchDraw();
		while (MouseHit()) 
		{
			msg = GetMouseMsg();
			int x = msg.x;
			int y = msg.y;
			switch (msg.uMsg) {
			case WM_LBUTTONDOWN:     //鼠标左键

				if (msg.x < 550 && msg.x > 350 && msg.y < 200 && msg.y > 160) 
				{
					unselect = 0;
					levelType = 1;
				}
				if (msg.x < 550 && msg.x > 350 && msg.y < 300 && msg.y > 260)
				{
					unselect = 0;
					levelType = 2;
				}
				if(msg.x < 550 && msg.x > 350 && msg.y < 400 && msg.y > 360)
				{
					unselect = 0;
					levelType = 3;
				}
				break;
			default:break;
			}
			msg.uMsg = WM_MBUTTONUP;
		}
	}

	cleardevice();
	BeginBatchDraw();
	init(); draw(); showdata();
	EndBatchDraw();

	total = 0;
	correct = 0;
	xutao::go(levelType);
	for (int i = 1; i <= 9; ++i)
	{
		for (int j = 1; j <= 9; ++j)
		{
			map[i - 1][j - 1] = map_cpy[i - 1][j - 1] = xutao::ans[i][j];
			answer[i - 1][j - 1] = xutao::tans[i][j];
			if (map[i - 1][j - 1] != answer[i - 1][j - 1])
			{
				blo[total].x = i-1;
				blo[total].y = j-1;
				blo[total].trueanswer = answer[i - 1][j - 1];
				total++;
			}
		}
	}
}

void hightlight() {
	while (MouseHit()) {
		msg = GetMouseMsg();
		switch (msg.uMsg) {
		case WM_MOUSEMOVE:
			if (msg.x < 500 && msg.x>50 && msg.y < 500 && msg.y>50) {
				highlightpos.X = msg.x;
				highlightpos.Y = msg.y;
				int i = (msg.x - 50) / 50;
				int j = (msg.y - 50) / 50;
				setfillcolor(RGB(174, 174, 174));
				for (int a = 0; a < 9; a++)
					solidrectangle(50 + 50 * a, 50 + 50 * j, 100 + 50 * a, 100 + 50 * j);
				for (int a = 0; a < 9; a++)
					solidrectangle(50 + 50 * i, 50 + 50 * a, 100 + 50 * i, 100 + 50 * a);
			}
			break;
		default: break;
		}
		msg.uMsg = WM_MBUTTONUP;
	}
}
void mousechoose() {
	if (MouseHit()) msg = GetMouseMsg(); FlushMouseMsgBuffer();
	mx = msg.x;
	my = msg.y;
	switch (msg.uMsg) {
	case WM_MOUSEMOVE:
		mx = msg.x;
		my = msg.y;
		break;
	case WM_LBUTTONDOWN:
		if (mx < 500 && mx>50 && my < 500 && my>50) {
			int i = (mx - 50) / 50;
			int j = (my - 50) / 50;
			if (map[i][j] == 0) {
				MessageBox(GetHWnd(), L"开始选择", L"注意", 0);
			}

		}
		break;
	default:
		break;
	}
}


//初始界面 1背景 2开始游戏 3退出（我不玩了） 4音效 5鼠标预选择
//游戏界面 1主阵 2鼠标选择 3修改操作 4计时器 5暂停 6结束游戏
//结束评判 显示
//我们遇到了显示背景时很难避免的屏闪问题
//BeginBatchDraw消除闪烁
//sleep参数的调节也起到了重要作用
//highlight时候我们也遇到了强烈的频闪。我们学到的办法是强化模块性，让画画一次解决，每次mousemove只修改数组
//另外，我自己想到的办法是，尽量避免在大while无限循环的时候画画，那样非常容易闪屏，而是在每次鼠标操作产生影响的时候重绘一次
