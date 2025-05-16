#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#define W 84
#define H 84
#define red_s coordTemp.Y = coord.Y;coordTemp.X = coord.X;WriteConsoleOutputAttribute(hOutBuf, red, 6, coordTemp, &bytes);WriteConsoleOutputAttribute(hOutput, red, 6, coordTemp, &bytes);
#define blue_s coordTemp.Y = coord.Y;coordTemp.X = coord.X;WriteConsoleOutputAttribute(hOutBuf, blue, 6, coordTemp, &bytes);WriteConsoleOutputAttribute(hOutput, blue, 6, coordTemp, &bytes);
#define yellow_s coordTemp.Y = coord.Y;coordTemp.X = coord.X;WriteConsoleOutputAttribute(hOutBuf, yellow, 6, coordTemp, &bytes);WriteConsoleOutputAttribute(hOutput, yellow, 6, coordTemp, &bytes);
#define green_s coordTemp.Y = coord.Y;coordTemp.X = coord.X;WriteConsoleOutputAttribute(hOutBuf, green, 6, coordTemp, &bytes);WriteConsoleOutputAttribute(hOutput, green, 6, coordTemp, &bytes);
#define white_s coordTemp.Y = coord.Y;coordTemp.X = coord.X;WriteConsoleOutputAttribute(hOutBuf, white, 6, coordTemp, &bytes);WriteConsoleOutputAttribute(hOutput, white, 6, coordTemp, &bytes);
#define pink_s coordTemp.Y = coord.Y;coordTemp.X = coord.X;WriteConsoleOutputAttribute(hOutBuf, pink, 6, coordTemp, &bytes);WriteConsoleOutputAttribute(hOutput, pink, 6, coordTemp, &bytes);
#define deepred_s coordTemp.Y = coord.Y;coordTemp.X = coord.X;WriteConsoleOutputAttribute(hOutBuf, deep_red, 6, coordTemp, &bytes);WriteConsoleOutputAttribute(hOutput, deep_red, 6, coordTemp, &bytes);
#define BEGIN 1
#define GAME 2
#define EXIT 3
#define RULE 4
#define Choose_Map 5
#define GAMEOVER 6
#define FLAMETIME 150

using namespace std;

HANDLE hOutput, hOutBuf;//控制檯屏幕緩衝區句柄
HANDLE *houtpoint;//顯示指針
COORD coord = {0, 0}, coordTemp = {0, 0};//雙緩衝處理顯示
DWORD bytes = 0;
bool showCircle = false;//判斷顯示哪個緩衝區

const int M = 1e3 + 5;
/*int wall[15][15] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},{0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1},{0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},{0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1},{0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},{0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1},{0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1},{0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},{0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1},{0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},{0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1},{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
int block[15][15] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0},{0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0},{0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0},{0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0},{0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0},{0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0},{0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0},{0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
*/
int wall[15][15];
int block[15][15];
int wall_1[15][15] =  
{
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1},
	{0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1},
	{0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1},
	{0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1},
	{0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1},
	{0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1},
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};
int block_1[15][15] = 
{
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0},
	{0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0},
	{0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0},
	{0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0},
	{0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0},
	{0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0},
	{0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0},
	{0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};
int wall_2[15][15] =  
{
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1},
	{0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1},
	{0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1},
	{0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1},
	{0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1},
	{0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1},
	{0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
	{0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1},
	{0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1},
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};
int block_2[15][15] = 
{
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0},
	{0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
	{0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0},
	{0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
	{0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0},
	{0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
	{0, 0, 1, 1, 1 ,0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
	{0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
	{0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int wall_3[15][15] = 
{
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //0
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},//1
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},//2
    {0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1},//3
    {0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1},//4
    {0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1},//5
    {0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1},//6
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},//7
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},//8
    {0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1},//9
    {0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1},//10
    {0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1},//11
    {0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1},//12
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},//13
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}//14
};

int block_3[15][15] = 
	{
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//0
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//1
    {0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0},//2
    {0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0},//3
    {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0},//4
    {0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0},//5
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},//6
    {0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0},//7
    {0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0},//8
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},//9
    {0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0},//10
    {0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0},//11
    {0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0},//12
    {0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0},//13
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}//14
	};

bool flame[15][15] = 
{
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //0
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//1
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//2
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

int thing[M][M];
int num, start, flame_start;
int mode;

void window()
{
    HWND h;
    int x,y,cx,cy;
    char szConsoleTitle[100];
    GetConsoleTitle(szConsoleTitle, 100) ;
    h=FindWindow(NULL,szConsoleTitle); 
    x=420; y=0; cx=705; cy=800;
    SetWindowPos(h,HWND_TOP,x,y,cx,cy,SWP_SHOWWINDOW);
}

void stop() {
	while(true) {
		system("pause");
	}
}

struct player{
	int x, y;
	int bown;
	int nom_bown;
	int time;
	int life;
	int fire;
}a[M];

struct bown{
	int x, y;
	int time;
	int from;
	int flame_time;
}b[M];

bool bow(int x, int y) {
	for(int i = start; i <= num && num != 0; i ++) {
		if(b[i].x == x && b[i].y == y) return true;
	}
	return false;
}

void clean_screen()
{
	char outmap[100];
	showCircle = !showCircle;
	if (showCircle)
		houtpoint = &hOutput;
	else
		houtpoint = &hOutBuf;

	WORD white_c[100];
	memset(outmap, 32, sizeof(outmap));//將地圖清零
	memset(white_c, 0x0f, sizeof(white_c));
	coord.X = 0;
	coord.Y = 0;
	for(int i=0; i<47; i++)
	{
		WriteConsoleOutputCharacterA(*houtpoint, outmap, 84, coord, &bytes);
		WriteConsoleOutputAttribute(*houtpoint, white_c, 84, coord, &bytes);
		coord.Y++;
	}
	SetConsoleActiveScreenBuffer(*houtpoint);

	showCircle = !showCircle;
	if (showCircle)
		houtpoint = &hOutput;
	else
		houtpoint = &hOutBuf;

	memset(outmap, 32, sizeof(outmap));//將地圖清零
	coord.X = 0;
	coord.Y = 0;
	for(int i=0; i<47; i++)
	{
		WriteConsoleOutputCharacterA(*houtpoint, outmap, 84, coord, &bytes);
		WriteConsoleOutputAttribute(*houtpoint, white_c, 84, coord, &bytes);
		coord.Y++;
	}
	SetConsoleActiveScreenBuffer(*houtpoint);
}

void drawmap()
{
	WORD red[6] = {0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c};
	WORD blue[6] = {0x09, 0x09, 0x09, 0x09, 0x09, 0x09};
	WORD green[6] = {0x02, 0x02, 0x02, 0x02, 0x02, 0x02};
	WORD yellow[6] = {0x06, 0x06, 0x06, 0x06, 0x06, 0x06};
	WORD white[6] = {0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f};
	WORD pink[6] = {0x0d, 0x0d, 0x0d, 0x0d, 0x0d, 0x0d};
	WORD deep_red[6] = {0x04, 0x04, 0x04, 0x04, 0x04, 0x04};

	showCircle = !showCircle;
	if (showCircle)
		houtpoint = &hOutput;
	else
		houtpoint = &hOutBuf;

	coord.Y = 0;
	for(int i = 1; i <= 14; i ++) 
	{
		for(int z = 0; z < 3 ; z++)
		{
			coord.X = 0;
			char outmap[100];
			int pos = 0;			
			for(int j = 1; j <= 14; j ++) 
			{
				if(wall[i][j] == 1 && i>1 && i<14)
				{
					white_s
					outmap[pos] = outmap[pos+1] = outmap[pos+2] = 219;
					pos+=3;
				}
				else if(wall[i][j] == 1)
				{
					white_s
					outmap[pos] = outmap[pos+1] = outmap[pos+2] = 219;
					pos+=3;
				}
				else if(flame[i][j] == 1)
				{
					deepred_s
					outmap[pos] = outmap[pos+1] = outmap[pos+2] = 219;
					pos+=3;
				}
				else if(block[i][j] == 1) 
				{
					yellow_s
					outmap[pos] = outmap[pos+1] = outmap[pos+2] = 178;
					pos+=3;
				}
				else if(a[1].x == i && a[1].y == j)
				{
					white_s
					if(z == 1)
					{
						outmap[pos] = outmap[pos+1] = outmap[pos+3] = outmap[pos+4] = outmap[pos+5] = ' ';
						outmap[pos+2] = '1';
					}
					else
						outmap[pos] = outmap[pos+1] = outmap[pos+2] = outmap[pos+3] = outmap[pos+4] = outmap[pos+5] = ' ';
					pos+=6;
				}
				else if(a[2].x == i && a[2].y == j) 
				{
					white_s
					if(z == 1)
					{
						outmap[pos] = outmap[pos+1] = outmap[pos+3] = outmap[pos+4] = outmap[pos+5] = ' ';
						outmap[pos+2] = '2';
					}
					else
						outmap[pos] = outmap[pos+1] = outmap[pos+2] = outmap[pos+3] = outmap[pos+4] = outmap[pos+5] = ' ';
					pos+=6;
				}
				else if(bow(i, j)) 
				{
					red_s
					if(z == 1)
					{
						outmap[pos] = outmap[pos+1] = outmap[pos+3] = outmap[pos+4] = ' ';
						outmap[pos+2] = 233;
					pos+=5;
					}
					else
					{
						outmap[pos] = outmap[pos+1] = outmap[pos+2] = outmap[pos+3] = outmap[pos+4] = outmap[pos+5] = ' ';
						pos+=6;
					}
				}
				else if(thing[i][j] == 1) 
				{
					blue_s
					if(z == 1)
					{
						outmap[pos] = outmap[pos+1] = outmap[pos+3] = outmap[pos+4] = outmap[pos+5] = ' ';
						outmap[pos+2] = 'O';
					}
					else
						outmap[pos] = outmap[pos+1] = outmap[pos+2] = outmap[pos+3] = outmap[pos+4] = outmap[pos+5] = ' ';
					pos+=6;
				}
				else if(thing[i][j] == 2) 
				{
					red_s
					if(z == 1)
					{
						outmap[pos] = outmap[pos+1] = outmap[pos+3] = outmap[pos+4] = outmap[pos+5] = ' ';
						outmap[pos+2] = 143;
					}
					else
						outmap[pos] = outmap[pos+1] = outmap[pos+2] = outmap[pos+3] = outmap[pos+4] = outmap[pos+5] = ' ';
					pos+=6;
				}
				else if(thing[i][j] == 3) 
				{
					green_s
					if(z == 1)
					{
						outmap[pos] = outmap[pos+1] = outmap[pos+3] = outmap[pos+4] = outmap[pos+5] = ' ';
						outmap[pos+2] = 'X';
					}
					else
						outmap[pos] = outmap[pos+1] = outmap[pos+2] = outmap[pos+3] = outmap[pos+4] = outmap[pos+5] = ' ';
					pos+=6;
				}  
				else if(thing[i][j] == 4) 
				{
					pink_s
					if(z == 1)
					{
						outmap[pos] = outmap[pos+1] = outmap[pos+4] = outmap[pos+5] = ' ';
						outmap[pos+2] = 'H';
						outmap[pos+3] = 'P';
					}
					else
						outmap[pos] = outmap[pos+1] = outmap[pos+2] = outmap[pos+3] = outmap[pos+4] = outmap[pos+5] = ' ';
					pos+=6;
				}
				else 
				{
					white_s
					outmap[pos] = outmap[pos+1] = outmap[pos+2] = outmap[pos+3] = outmap[pos+4] = outmap[pos+5] = ' ';
					pos+=6;
				}
				coord.X+=6;
			}
			coord.X = 0;
			WriteConsoleOutputCharacterA(*houtpoint, outmap, pos, coord, &bytes);
			coord.Y++;
		}
	}
	char outmap[100];
	coord.Y++;
	coord.X = 13;
	sprintf(outmap, "-Player1 Life: %d  Amount: %d  Fire: %d  Bomb Time: %d ms\n", a[1].life, a[1].bown - a[1].nom_bown, a[1].fire, a[1].time);
	WriteConsoleOutputCharacterA(*houtpoint, outmap, strlen(outmap), coord, &bytes);
	coord.Y+=2;
	coord.X = 13;
	sprintf(outmap, "-Player2 Life: %d  Amount: %d  Fire: %d  Bomb Time: %d ms\n", a[2].life, a[2].bown - a[2].nom_bown, a[2].fire, a[2].time);
	WriteConsoleOutputCharacterA(*houtpoint, outmap, strlen(outmap), coord, &bytes);
	SetConsoleActiveScreenBuffer(*houtpoint);
}

void gameover() //控制遊戲結束
{
	char outmap[100];
	showCircle = !showCircle;
	if (showCircle)
		houtpoint = &hOutput;
	else
		houtpoint = &hOutBuf;

	memset(outmap, 255, sizeof(outmap));//將地圖清零
	//打印"Game Over!"
	coord.X = 34;
	coord.Y = 22;
	//WriteConsoleOutputCharacterA(*houtpoint, "GAME OVER", 9, coord, &bytes);
	//設置新的緩衝區爲活動顯示緩衝
	if(a[1].life<=0 && a[2].life<=0)
		WriteConsoleOutputCharacterA(*houtpoint, "Both Died", 9, coord, &bytes);
	else if(a[2].life<=0)
		WriteConsoleOutputCharacterA(*houtpoint, "Winner : Player 1", 17, coord, &bytes);
	else if(a[1].life<=0)
		WriteConsoleOutputCharacterA(*houtpoint, "Winner : Player 2", 17, coord, &bytes);

	SetConsoleActiveScreenBuffer(*houtpoint);

	if(kbhit())
	{	
		char c;
		c= getch();
		if(c==' ')
			mode = BEGIN;
		
	}
}

void set_move()
{
	if(kbhit())
	{
			char c = getch();
			if(c == -32) 
			{
				c = getch();
				if(c == 72 && block[a[1].x - 1][a[1].y] == 0 && wall[a[1].x - 1][a[1].y] == 0 && bow(a[1].x - 1, a[1].y) == false) {
					-- a[1].x;
				}
				if(c == 80 && block[a[1].x + 1][a[1].y] == 0 && wall[a[1].x + 1][a[1].y] == 0 && bow(a[1].x + 1, a[1].y) == false) {
					++ a[1].x;
				}
				if(c == 75 && block[a[1].x][a[1].y - 1] == 0 && wall[a[1].x][a[1].y - 1] == 0 && bow(a[1].x, a[1].y - 1) == false) {
					-- a[1].y;
				}
				if(c == 77 && block[a[1].x][a[1].y + 1] == 0 && wall[a[1].x][a[1].y + 1] == 0 && bow(a[1].x, a[1].y + 1) == false) {
					++ a[1].y;
				}
			}
			if(c == 'w' && block[a[2].x - 1][a[2].y] == 0 && wall[a[2].x - 1][a[2].y] == 0 && bow(a[2].x - 1, a[2].y) == false) {
				-- a[2].x;
			}
			if(c == 's' && block[a[2].x + 1][a[2].y] == 0 && wall[a[2].x + 1][a[2].y] == 0 && bow(a[2].x, a[2].y + 1) == false) {
				++ a[2].x;
			}
			if(c == 'a' && block[a[2].x][a[2].y - 1] == 0 && wall[a[2].x][a[2].y - 1] == 0 && bow(a[2].x, a[2].y - 1) == false) {
				-- a[2].y;
			}
			if(c == 'd' && block[a[2].x][a[2].y + 1] == 0 && wall[a[2].x][a[2].y + 1] == 0 && bow(a[2].x, a[2].y + 1) == false) {
				++ a[2].y;
			}
			if(c == 13 && a[1].nom_bown < a[1].bown) {
				++ num;
				b[num].x = a[1].x;
				b[num].y = a[1].y;
				b[num].time = clock() + a[1].time;
				b[num].flame_time = clock() + FLAMETIME + a[1].time;
				b[num].from = 1;
				++ a[1].nom_bown;
			}
			if(c == ' ' && a[2].nom_bown < a[2].bown) {
				++ num;
				b[num].x = a[2].x;
				b[num].y = a[2].y;
				b[num].time = clock() + a[2].time;
				b[num].flame_time = clock() + FLAMETIME + a[2].time;
				b[num].from = 2;
				++ a[2].nom_bown;
			}
			if(a[1].nom_bown>a[1].bown)
				a[1].nom_bown=a[1].bown;
			if(a[2].nom_bown>a[2].bown)
				a[2].nom_bown=a[2].bown;
	}
	for(int i = start; i <= num; i ++) 
		{
			if(clock() >= b[i].time) 
			{
				++ start;
				-- a[b[i].from].nom_bown;
				for(int j = b[i].x; j <= b[i].x + a[b[i].from].fire; j ++)
				{
					thing[j][b[i].y] = 0;
					if(wall[j][b[i].y] == true) 
						break;
					flame[j][b[i].y] = 1;
					if(block[j][b[i].y] == true) 
					{
						block[j][b[i].y] = false;
						thing[j][b[i].y] = rand() % 8;
						break;
					}
					if(a[1].x == j && a[1].y == b[i].y) a[1].life -=1;//a[1].life -= a[b[i].from].fire;
					if(a[2].x == j && a[2].y == b[i].y) a[2].life -=1;//a[2].life -= a[b[i].from].fire;
				}
				for(int j = b[i].x-1; j >= b[i].x - a[b[i].from].fire; j --)
				{
					thing[j][b[i].y] = 0;
					if(wall[j][b[i].y] == true) 
						break;
					flame[j][b[i].y] = 1;
					if(block[j][b[i].y] == true) 
					{
						block[j][b[i].y] = false;
						thing[j][b[i].y] = rand() % 8;
						break;
					}
					if(a[1].x == j && a[1].y == b[i].y) a[1].life -=1;//a[1].life -= a[b[i].from].fire;
					if(a[2].x == j && a[2].y == b[i].y) a[2].life -=1;//a[2].life -= a[b[i].from].fire;
				}
				for(int j = b[i].y+1; j <= b[i].y + a[b[i].from].fire; j ++)
				{
					thing[b[i].x][j] = 0;
					if(wall[b[i].x][j] == true) 
						break;
					flame[b[i].x][j] = 1;
					if(block[b[i].x][j] == true) 
					{
						block[b[i].x][j] = false;
						thing[b[i].x][j] = rand() % 8;
						break;
					}
					if(a[1].x == b[i].x && a[1].y == j) a[1].life -=1;//a[1].life -= a[b[i].from].fire;
					if(a[2].x == b[i].x && a[2].y == j) a[2].life -=1;//a[2].life -= a[b[i].from].fire;
				}
				for(int j = b[i].y-1; j >= b[i].y - a[b[i].from].fire; j --)
				{
					thing[b[i].x][j] = 0;
					if(wall[b[i].x][j] == true) 
						break;
					flame[b[i].x][j] = 1;
					if(block[b[i].x][j] == true) 
					{
						block[b[i].x][j] = false;
						thing[b[i].x][j] = rand() % 8;
						break;
					}
					if(a[1].x == b[i].x && a[1].y == j) a[1].life -=1;//a[1].life -= a[b[i].from].fire;
					if(a[2].x == b[i].x && a[2].y == j) a[2].life -=1;//a[2].life -= a[b[i].from].fire;
				}
			}
		}

		for(int i = flame_start; i <= num; i ++) 
		{
			if(clock() >= b[i].flame_time) 
			{
				flame_start++;
				for(int j = b[i].x; j <= b[i].x + a[b[i].from].fire; j ++)
				{
					if(wall[j][b[i].y] == true) 
						break;
					flame[j][b[i].y] = 0;
					if(block[j][b[i].y] == true) 
					{
						break;
					}
				}
				for(int j = b[i].x; j >= b[i].x - a[b[i].from].fire; j --)
				{
					if(wall[j][b[i].y] == true) 
						break;
					flame[j][b[i].y] = 0;
					if(block[j][b[i].y] == true) 
					{
						break;
					}
				}
				for(int j = b[i].y; j <= b[i].y + a[b[i].from].fire; j ++)
				{
					if(wall[b[i].x][j] == true) 
						break;
					flame[b[i].x][j] = 0;
					if(block[b[i].x][j] == true) 
					{
						break;
					}
				}
				for(int j = b[i].y; j >= b[i].y - a[b[i].from].fire; j --)
				{
					if(wall[b[i].x][j] == true) 
						break;
					flame[b[i].x][j] = 0;
					if(block[b[i].x][j] == true) 
					{
						break;
					}
				}
			}
		}

		if(thing[a[1].x][a[1].y] == 1) {
			thing[a[1].x][a[1].y] = 0;
			++ a[1].bown;
		}
		if(thing[a[1].x][a[1].y] == 2) {
			thing[a[1].x][a[1].y] = 0;
			++ a[1].fire;
		}
		if(thing[a[2].x][a[2].y] == 1) {
			thing[a[2].x][a[2].y] = 0;
			++ a[2].bown;
		}
		if(thing[a[2].x][a[2].y] == 2) {
			thing[a[2].x][a[2].y] = 0;
			++ a[2].fire;
		}
		if(thing[a[1].x][a[1].y] == 3) {
			thing[a[1].x][a[1].y] = 0;
			a[1].time -= a[1].time >= 500 ? 150 : 0;
		}
		if(thing[a[2].x][a[2].y] == 3) {
			thing[a[2].x][a[2].y] = 0;
			a[2].time -= a[2].time >= 500 ? 150 : 0;
		}
		if(thing[a[1].x][a[1].y] == 4) {
			thing[a[1].x][a[1].y] = 0;
			a[1].life += 1;
		}
		if(thing[a[2].x][a[2].y] == 4) {
			thing[a[2].x][a[2].y] = 0;
			a[2].life += 1;
		}
}

void beginning(int begin_goto)
{
	showCircle = !showCircle;
	if (showCircle)
		houtpoint = &hOutput;
	else
		houtpoint = &hOutBuf;
	
	char outmap[100];
	coord.X = 7;
	coord.Y = 3;
	sprintf(outmap, "%c%c%c%c      %c%c%c    %c      %c  %c%c%c%c    %c%c%c%c%c  %c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
	WriteConsoleOutputCharacterA(*houtpoint, outmap, strlen(outmap), coord, &bytes);
	coord.Y++;
	sprintf(outmap, "%c      %c  %c      %c  %c%c  %c%c  %c      %c  %c          %c      %c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
	WriteConsoleOutputCharacterA(*houtpoint, outmap, strlen(outmap), coord, &bytes);
	coord.Y++;
	sprintf(outmap, "%c      %c  %c      %c  %c  %c  %c  %c      %c  %c          %c      %c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
	WriteConsoleOutputCharacterA(*houtpoint, outmap, strlen(outmap), coord, &bytes);
	coord.Y++;
	sprintf(outmap, "%c%c%c%c    %c      %c  %c      %c  %c%c%c%c    %c%c%c%c%c  %c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
	WriteConsoleOutputCharacterA(*houtpoint, outmap, strlen(outmap), coord, &bytes);
	coord.Y++;
	sprintf(outmap, "%c      %c  %c      %c  %c      %c  %c      %c  %c          %c  %c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
	WriteConsoleOutputCharacterA(*houtpoint, outmap, strlen(outmap), coord, &bytes);
	coord.Y++;
	sprintf(outmap, "%c      %c  %c      %c  %c      %c  %c      %c  %c          %c    %c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
	WriteConsoleOutputCharacterA(*houtpoint, outmap, strlen(outmap), coord, &bytes);
	coord.Y++;
	sprintf(outmap, "%c%c%c%c      %c%c%c    %c      %c  %c%c%c%c    %c%c%c%c%c  %c      %c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
	WriteConsoleOutputCharacterA(*houtpoint, outmap, strlen(outmap), coord, &bytes);

	WORD Red[84];
	for(int i=0; i<84; i++)
		Red[i] = 0x0c;
	coord.X = 25;
	coord.Y+=2;
	sprintf(outmap, "%c      %c      %c      %c      %c", 219, 219, 219, 219, 219);
	WriteConsoleOutputAttribute(*houtpoint, Red, 34, coord, &bytes);
	WriteConsoleOutputCharacterA(*houtpoint, outmap, strlen(outmap), coord, &bytes);
	coord.Y++;
	sprintf(outmap, "%c%c  %c%c    %c  %c    %c%c    %c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
	WriteConsoleOutputAttribute(*houtpoint, Red, 34, coord, &bytes);
	WriteConsoleOutputCharacterA(*houtpoint, outmap, strlen(outmap), coord, &bytes);
	coord.Y++;
	sprintf(outmap, "%c  %c  %c  %c      %c  %c  %c  %c", 219, 219, 219, 219, 219, 219, 219, 219);
	WriteConsoleOutputAttribute(*houtpoint, Red, 34, coord, &bytes);
	WriteConsoleOutputCharacterA(*houtpoint, outmap, strlen(outmap), coord, &bytes);
	coord.Y++;
	sprintf(outmap, "%c      %c  %c      %c  %c  %c  %c", 219, 219, 219, 219, 219, 219, 219);
	WriteConsoleOutputAttribute(*houtpoint, Red, 34, coord, &bytes);
	WriteConsoleOutputCharacterA(*houtpoint, outmap, strlen(outmap), coord, &bytes);
	coord.Y++;
	sprintf(outmap, "%c      %c  %c%c%c%c%c  %c  %c  %c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
	WriteConsoleOutputAttribute(*houtpoint, Red, 34, coord, &bytes);
	WriteConsoleOutputCharacterA(*houtpoint, outmap, strlen(outmap), coord, &bytes);
	coord.Y++;
	sprintf(outmap, "%c      %c  %c      %c  %c    %c%c", 219, 219, 219, 219, 219, 219, 219);
	WriteConsoleOutputAttribute(*houtpoint, Red, 34, coord, &bytes);
	WriteConsoleOutputCharacterA(*houtpoint, outmap, strlen(outmap), coord, &bytes);
	coord.Y++;
	sprintf(outmap, "%c      %c  %c      %c  %c      %c", 219, 219, 219, 219, 219, 219);
	WriteConsoleOutputAttribute(*houtpoint, Red, 34, coord, &bytes);
	WriteConsoleOutputCharacterA(*houtpoint, outmap, strlen(outmap), coord, &bytes);
	//_getch();

	
	coord.X = 33;
	coord.Y +=5;
	sprintf(outmap, "    Start Game");
	WriteConsoleOutputCharacterA(*houtpoint, outmap, strlen(outmap), coord, &bytes);
	coord.Y +=2;
	sprintf(outmap, "    Game Rule");
	WriteConsoleOutputCharacterA(*houtpoint, outmap, strlen(outmap), coord, &bytes);
	coord.Y +=2;
	sprintf(outmap, "    Exit Game");
	WriteConsoleOutputCharacterA(*houtpoint, outmap, strlen(outmap), coord, &bytes);

	coord.X = 34;
	coord.Y = coord.Y - 4 + 2*begin_goto;

	if((clock()/500)%2 == 0)
		sprintf(outmap, ">>");
	else
		sprintf(outmap, "--");
	WriteConsoleOutputCharacterA(*houtpoint, outmap, strlen(outmap), coord, &bytes);

	SetConsoleActiveScreenBuffer(*houtpoint);
}

void begin_set(int *begin_goto)
{
	if(kbhit())
	{
		char c = getch();
		if(c == -32) 
		{
			c = getch();
			if(c == 80 && (*begin_goto == 0 || *begin_goto == 1))
				(*begin_goto)++;
			if(c == 72 && (*begin_goto ==1  || *begin_goto == 2))
				(*begin_goto)--;
		}

		if(c == 13)
		{
			if(*begin_goto == 0)
				mode = Choose_Map;
			else if(*begin_goto == 2)
				mode = EXIT;
			else if(*begin_goto == 1)
				mode = RULE;

		}
	}
}
void map_select(int begin_goto)
{
	char outmap[1000];
	showCircle = !showCircle;
	if (showCircle)
	{
		houtpoint = &hOutput;
	}
	else
	{
		houtpoint = &hOutBuf;
	}
	memset(outmap, 255, sizeof(outmap));//將地圖清零6
	coord.X = 30;
	coord.Y = 18;
	sprintf(outmap, "    Choose Map");
	WriteConsoleOutputCharacterA(*houtpoint, outmap, strlen(outmap), coord, &bytes);
	coord.Y +=2;
	sprintf(outmap, "    Forbidden Temple");
	WriteConsoleOutputCharacterA(*houtpoint, outmap, strlen(outmap), coord, &bytes);
	coord.Y +=2;
	sprintf(outmap, "    Battle Field");
	WriteConsoleOutputCharacterA(*houtpoint, outmap, strlen(outmap), coord, &bytes);
	coord.Y +=2;
	sprintf(outmap, "    Territory of God");
	WriteConsoleOutputCharacterA(*houtpoint, outmap, strlen(outmap), coord, &bytes);

	coord.X = 30;
	coord.Y = coord.Y - 4 + 2*begin_goto;

	if((clock()/500)%2 == 0)
		sprintf(outmap, ">>");
	else
		sprintf(outmap, "--");
	WriteConsoleOutputCharacterA(*houtpoint, outmap, strlen(outmap), coord, &bytes);

	SetConsoleActiveScreenBuffer(*houtpoint);

	return;
}

void get_map(int *begin_goto)
{
	if(kbhit())
	{
		char c = getch();
		if(c == -32) 
		{
			c = getch();
			if(c == 80 && (*begin_goto == 0 || *begin_goto == 1))
				(*begin_goto)++;
			if(c == 72 && (*begin_goto ==1  || *begin_goto == 2))
				(*begin_goto)--;
		}

		if(c == 13)
		{
			if(*begin_goto == 0)
			{
				memcpy(wall, wall_1,sizeof(wall));
				memcpy(block,block_1,sizeof(block));
			}
			else if(*begin_goto == 2)
			{
				memcpy(wall, wall_3,sizeof(wall));
				memcpy(block,block_3,sizeof(block));
			}
			else if(*begin_goto == 1)
			{
				memcpy(wall, wall_2,sizeof(wall));
				memcpy(block,block_2,sizeof(block));
			}
			mode=GAME;
		}

	}
}

void rule()
{
	char outmap[100];
	showCircle = !showCircle;
	if (showCircle)
	{
		houtpoint = &hOutput;
	}
	else
	{
		houtpoint = &hOutBuf;
	}
	coord.X = 12;
	coord.Y = 17;
	sprintf(outmap, "                 ^");
	WriteConsoleOutputCharacterA(*houtpoint, outmap, strlen(outmap), coord, &bytes);
	coord.Y++;
	sprintf(outmap, "-Player1: push < v > to move character");
	WriteConsoleOutputCharacterA(*houtpoint, outmap, strlen(outmap), coord, &bytes);
	coord.Y+=2;
	sprintf(outmap, "                 w");
	WriteConsoleOutputCharacterA(*houtpoint, outmap, strlen(outmap), coord, &bytes);
	coord.Y++;
	sprintf(outmap, "-Player2: push a s d to move character");
	WriteConsoleOutputCharacterA(*houtpoint, outmap, strlen(outmap), coord, &bytes);
	coord.Y+=2;
	sprintf(outmap, "-When character get O, character's number of bomb will rise.");
	WriteConsoleOutputCharacterA(*houtpoint, outmap, strlen(outmap), coord, &bytes);
	coord.Y+=2;
	sprintf(outmap, "-When character get %c, bomb's fire will rise.", 143);
	WriteConsoleOutputCharacterA(*houtpoint, outmap, strlen(outmap), coord, &bytes);
	coord.Y+=2;
	sprintf(outmap, "-When character get X, character will get bomb's time penalty.", 143);
	WriteConsoleOutputCharacterA(*houtpoint, outmap, strlen(outmap), coord, &bytes);
	coord.Y+=2;
	sprintf(outmap, "-When character get HP, character's life will recover.", 143);
	WriteConsoleOutputCharacterA(*houtpoint, outmap, strlen(outmap), coord, &bytes);

	SetConsoleActiveScreenBuffer(*houtpoint);

	if(kbhit())
	{	
		char c;
		c= getch();
		if(c==' ')
			mode = BEGIN;
		
	}
}

void initial()
{
	a[1].life = 3;
	a[2].life = 3;
	a[1].fire = 1;
	a[2].fire = 1;
	a[1].bown = 1;
	a[2].bown = 1;
	a[1].x = 13;
	a[1].y = 2;
	a[2].x = 2;
	a[2].y = 13;
	a[1].time = 2000;
	a[2].time = 2000;
}

int main() {
	SetConsoleOutputCP(437);
	window();
	srand((unsigned)time(0));
	//創建新的控制檯緩衝區
	hOutBuf = CreateConsoleScreenBuffer(
		GENERIC_WRITE,//定義進程可以往緩衝區寫數據
		FILE_SHARE_WRITE,//定義緩衝區可共享寫權限
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL
	);
	hOutput = CreateConsoleScreenBuffer(
		GENERIC_WRITE,//定義進程可以往緩衝區寫數據
		FILE_SHARE_WRITE,//定義緩衝區可共享寫權限
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL
	);
	//隱藏兩個緩衝區的光標
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = 0;
	cci.dwSize = 1;
	SetConsoleCursorInfo(hOutput, &cci);
	SetConsoleCursorInfo(hOutBuf, &cci);
	
	/*a[1].life = 3;
	a[2].life = 3;
	a[1].fire = 1;
	a[2].fire = 1;
	a[1].bown = 1;
	a[2].bown = 1;
	a[1].x = 13;
	a[1].y = 2;
	a[2].x = 2;
	a[2].y = 13;
	a[1].time = 2000;
	a[2].time = 2000;*/
	mode = BEGIN;

	int begin_goto = 0;
	while(mode != EXIT)
	{
		clean_screen();
		initial();
		begin_goto = 0;
		while(mode == BEGIN)
		{
			beginning(begin_goto);
			begin_set(&begin_goto);
		}
		begin_goto = 0;
		clean_screen();
		while(mode == Choose_Map)
		{
			map_select(begin_goto);
			get_map(&begin_goto);
		}
		while(mode == RULE)
			rule();
		while(a[1].life > 0 && a[2].life > 0 && mode == GAME) 
		{
			drawmap();
			set_move();
			Sleep(5);
			if(a[1].life <= 0 || a[2].life <= 0)
				mode = GAMEOVER;
		}
		clean_screen();
		while(mode == GAMEOVER)
			gameover();
	}
	return 0;
}