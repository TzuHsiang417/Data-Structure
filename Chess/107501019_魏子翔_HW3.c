#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <termios.h> 
#include <unistd.h> 
#include <fcntl.h> 
//#include <windows.h>

#define HOME 1  //遊戲主畫面
#define GAME 2  //進行遊戲
#define MENU 3  //遊戲菜單
#define WINNER 4    //遊戲結束，顯示勝利者
#define RESTART 5   //將遊戲重製
#define RECORD 6    //讀取遊戲紀錄
#define SAVE 7  //遊戲存檔
#define REPLAY 8    //遊戲重播
#define WHITE_TURN 1    //白方回合
#define BLACK_TURN 2    //黑方回合
#define CHESS_POSITION 2    //所選擇棋子的位置
#define CHESS_MOVING 1      //所選擇棋子可移動到的位置
#define CHESS_EATTING 3     //所選擇棋子可以吃掉的位置
#define NO_CHESS 0  //該位置無棋子
#define CAN_MOVE 0  //可以移動的指令
#define CANNOT_MOVE 1   //無法移動的指令
#define WHITE_SQUARE 0  //棋盤中白色方格
#define BLACK_SQUARE 1  //棋盤中黑色方格
#define STACK_SIZE 200  //stack的size
#define QUEUE_SIZE 200  //queue的size
#define STACK_EMPTY -1  //stack是空的
#define LEFTTIME 60 //每回合的時間限制
#define TRUE 1
enum Type { // 1 pawn 2 rook 3 bishop 4 knight 5 queen 6 king
    NONE = 0,
    PAWN,
    ROOK,
    BISHOP,
    KNIGHT,
    QUEEN,
    KING,
};

/*void window()
{
    HWND h;
    int x,y,cx,cy;
    char szConsoleTitle[100];
    GetConsoleTitle(szConsoleTitle, 100) ;
    h=FindWindow(NULL,szConsoleTitle); 
    x=550; y=100; cx=480; cy=600;
    SetWindowPos(h,HWND_TOP,x,y,cx,cy,SWP_SHOWWINDOW);
}*/

int mode = HOME;    //將一開始的模式設為主畫面模式
int currentTurn = WHITE_TURN; //紀錄當前是誰的回合
int board_ptr[8][8];    //二維陣列去存各棋子的位置
const int board[8][8] = {
    {2,4,3,5,6,3,4,2},
    {1,1,1,1,1,1,1,1},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1},
    {2,4,3,5,6,3,4,2}
};
int blackWhite_ptr[8][8];   //二維陣列去存棋盤上黑棋及白棋
const int blackWhite[8][8] = {
    {2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2},
    {1,1,1,2,2,2,2,2},
    {2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2},
    {1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1}
};
char chess_ptr[8][8];   //二維陣列去存棋盤個位置的符號
const char chess[8][8] = {
    {'r','n','b','q','k','b','n','r'},
    {'p','p','p','p','p','p','p','p'},
    {'0','0','0','0','0','0','0','0'},
    {'0','0','0','0','0','0','0','0'},
    {'0','0','0','0','0','0','0','0'},
    {'0','0','0','0','0','0','0','0'},
    {'P','P','P','P','P','P','P','P'},
    {'R','N','B','Q','K','B','N','R'},
};
int moves[8][8];    //二維陣列去存棋子移動時，棋盤所對應的狀態

int kbhit(void)     //模擬windows編譯器才有的kbhit()
{ 
    struct termios oldt, newt; 
    int ch; 
    int oldf; 
    tcgetattr(STDIN_FILENO, &oldt); 
    newt = oldt; 
    newt.c_lflag &= ~(ICANON | ECHO); 
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); 
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0); 
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK); 
    ch = getchar(); 
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); 
    fcntl(STDIN_FILENO, F_SETFL, oldf); 
    if(ch != EOF) 
    { 
        ungetc(ch, stdin); 
        return 1; 
    } 
    return 0; 
} 

int getch(void)     //模擬windows編譯器才有的getch()
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

struct node //紀錄棋局linked list
{
    int board[8][8];
    int blackwhite[8][8];
    char chess[8][8];
    int currentturn;
    struct node *left, *right;
};
typedef struct node NODE;
NODE *list=NULL;
NODE *stack=NULL;
NODE *queue=NULL;

void pushback() //將棋局存進linked list
{
    NODE *tmp;
    tmp = (NODE*)malloc(sizeof(NODE));
    memcpy(tmp->blackwhite, blackWhite_ptr, 256);
    memcpy(tmp->board, board_ptr, 256);
    memcpy(tmp->chess, chess_ptr, 64);
    tmp->currentturn = currentTurn;
    if(list == NULL)
    {
        list=tmp;
        tmp->left=NULL;
    }
    else
    {
        tmp->left = stack;
        stack->right = tmp;
    }
    tmp->right = NULL;
    stack = tmp;
}

void pop()  //悔棋，將棋局拿走，並刪掉
{
    NODE *tmp;
    tmp = stack;
    stack = stack->left;
    if(stack != NULL)
        stack->right = NULL;
    memcpy(board_ptr, stack->board, 256);
    memcpy(blackWhite_ptr, stack->blackwhite, 256);
    memcpy(chess_ptr, stack->chess, 64);
    currentTurn = stack->currentturn;
    free(tmp);
}

void list_replaying()   //將linked list裡的棋局重播
{
    memcpy(board_ptr, queue->board, 256);
    memcpy(blackWhite_ptr, queue->blackwhite, 256);
    memcpy(chess_ptr, queue->chess, 64);
    currentTurn = queue->currentturn;
    queue = queue->right;
}

void FreeAll()  //將整個linked list都釋放
{
    while(stack != NULL)
    {
        NODE *tmp;
        tmp = stack;
        stack = stack->left;
        if(stack != NULL)
            stack->right = NULL;
        free(tmp);
    }
    list = NULL;
}

void towerMoves(int color, int *canMove, int x, int y)  //十字移動Rook
{
    for(int dir = -1; dir < 2; dir+=2)
    {
        int count = 1;
        while(1)
        {
            if(x+(count*dir) <= 7 && x+(count*dir) >= 0)    //限制在棋盤內掃描
            {
                if(board_ptr[y][x+(count*dir)] != NO_CHESS) //如果所掃到的位置有棋子
                {
                    if(blackWhite_ptr[y][x+(count*dir)] != color)   //判斷是不是敵方的棋子
                    {
                        moves[y][x+(count*dir)] = CHESS_EATTING;
                        *canMove = CAN_MOVE;
                    }
                    break;
                }
                else
                {
                    moves[y][x+(count*dir)] = CHESS_MOVING;
                    *canMove = CAN_MOVE;
                }
            }
            else
                break;

            count++;
        }
        count = 1;
        while(1)
        {
            if(y+(count*dir) <= 7 && y+(count*dir) >= 0)    //限制在棋盤內掃描
            {
                if(board_ptr[y+(count*dir)][x] != NO_CHESS) //如果所掃到的位置有棋子
                {
                    if(blackWhite_ptr[y+(count*dir)][x] != color) //判斷是不是敵方的棋子
                    {
                        moves[y+(count*dir)][x] = CHESS_EATTING;
                        *canMove = CAN_MOVE;
                    }
                    break;
                }
                else
                {
                    moves[y+(count*dir)][x] = CHESS_MOVING;
                    *canMove = CAN_MOVE;
                }
            }
            else
                break;
            count++;
        }
    }
}

void runnerMove(int color, int *canMove, int x, int y)  //叉字移動Bishop
{
    for(int xDir = -1; xDir < 2; xDir+=2)   
    {
        for(int yDir = -1; yDir < 2; yDir+=2)
        {
            int count = 1;
            while(1)
            {
                if(x+(count*xDir) <= 7 && x+(count*xDir) >= 0 && y+(count*yDir) <= 7 && y+(count*yDir) >= 0)    //限制在棋盤內掃描
                {
                    if(board_ptr[y+(count*yDir)][x+(count*xDir)] != NO_CHESS)   //如果所掃到的位置有棋子
                    {
                        if(blackWhite_ptr[y+(count*yDir)][x+(count*xDir)] != color) //判斷是否為敵方的棋子
                        {
                            moves[y+(count*yDir)][x+(count*xDir)] = CHESS_EATTING;
                            *canMove = CAN_MOVE;
                        }
                        break;
                    }
                    else
                    {
                        moves[y+(count*yDir)][x+(count*xDir)] = CHESS_MOVING;
                        *canMove = CAN_MOVE;
                    }
                }
                else
                {
                    break;
                }
                count++;
            }
        }
    }
}

int getValidMoves(int x, int y) //判斷棋子是否能移動
{
    int piece = board_ptr[y][x];    //存棋子為何種角色
    int color = blackWhite_ptr[y][x];   //存棋子為何種顏色
    int canMove = CANNOT_MOVE;
    moves[y][x] = CHESS_POSITION;
    if(x > 7 || x < 0 || y > 7 || y < 0)
        return 1;

    switch (piece)  //根據不同的棋子，給予各棋子行走的路線判別
    {
        case NONE:
            return 1;
            break;

        case PAWN:
            if(color == WHITE_TURN) //白方的士兵
            {
                if(y == 6 && board_ptr[y-2][x] == NO_CHESS)
                {
                    moves[y-2][x] = CHESS_MOVING;
                    canMove = CAN_MOVE;
                }
                if(y-1 >= 0)
                {
                    if(board_ptr[y-1][x] == NO_CHESS)
                    {
                        moves[y-1][x] = CHESS_MOVING;
                        canMove = CAN_MOVE;
                    }
                    if(x+1<=7 && blackWhite_ptr[y-1][x+1] == BLACK_TURN && board_ptr[y-1][x+1] != NO_CHESS)
                    {
                        moves[y-1][x+1] = CHESS_EATTING;
                        canMove = CAN_MOVE;
                    }
                    if(x-1>=0 && blackWhite_ptr[y-1][x-1] == BLACK_TURN && board_ptr[y-1][x-1] != 0)
                    {
                        moves[y-1][x-1] = CHESS_EATTING;
                        canMove = CAN_MOVE;
                    }
                }
            }
            else    //黑方的士兵
            {
                if(y == 1 && board_ptr[y+2][x] == NO_CHESS)
                {
                    moves[y+2][x] = CHESS_MOVING;
                    canMove = CAN_MOVE;
                }
                if(y+1 <= 7)
                {
                    if(board_ptr[y+1][x] == NO_CHESS)
                    {
                        moves[y+1][x] = CHESS_MOVING;
                        canMove = CAN_MOVE;
                    }
                    if(x+1<=7 && blackWhite_ptr[y+1][x+1] == WHITE_TURN && board_ptr[y+1][x+1] != NO_CHESS)
                    {
                        moves[y+1][x+1] = CHESS_EATTING;
                        canMove = CAN_MOVE;
                    }
                    if(x-1>=0 && blackWhite_ptr[y+1][x-1] == WHITE_TURN && board_ptr[y+1][x-1] != NO_CHESS)
                    {
                        moves[y+1][x-1] = CHESS_EATTING;
                        canMove = CAN_MOVE;
                    }  
                }
            }
            break;

        case KNIGHT:
            for(int i = -1; i < 2; i+=2)
            {
                //TODO CLEAN THIS UP
                if(x+i <= 7 && x+i >= 0 && y+(2*i) >= 0 && y+(2*i) <= 7)
                {
                    moves[y+(2*i)][x+i] = blackWhite_ptr[y+(2*i)][x+i] == color && board_ptr[y+(2*i)][x+i] != 0 ? 0 : 1;
                    canMove = CAN_MOVE;
                }
                if(y+i <= 7 && y+i >= 0 && x+(2*i) >= 0 && x+(2*i) <= 7)
                {
                    moves[y+i][x+(2*i)] = blackWhite_ptr[y+i][x+(2*i)] == color && board_ptr[y+i][x+(2*i)] != 0 ? 0 : 1;
                    canMove = CAN_MOVE;
                }
                if(x-i <= 7 && x-i >= 0 && y+(2*i) >= 0 && y+(2*i) <= 7)
                {
                    moves[y+(2*i)][x-i] = blackWhite_ptr[y+(2*i)][x-i] == color && board_ptr[y+(2*i)][x-i] != 0 ? 0 : 1;
                    canMove = CAN_MOVE;
                }
                if(y-i <= 7 && y-i >= 0 && x+(2*i) >= 0 && x+(2*i) <= 7)
                {
                    moves[y-i][x+(2*i)] = blackWhite_ptr[y-i][x+(2*i)] == color && board_ptr[y-i][x+(2*i)] != 0 ? 0 : 1;
                    canMove = CAN_MOVE;
                }
            }
            break;

        case BISHOP:
            runnerMove(color, &canMove, x, y);
            break;
        case ROOK:
            towerMoves(color, &canMove, x, y);
            break;
        case QUEEN:
            towerMoves(color, &canMove, x, y);
            runnerMove(color, &canMove, x, y);
            break;
        case KING:
            for(int xDir = -1; xDir < 2; xDir++)
            {
                for(int yDir = -1; yDir < 2; yDir++)
                {
                    if(xDir+x <= 7 && xDir+x >= 0 && y+yDir >= 0 && yDir+y <= 7 && !(xDir == 0 && yDir == 0))
                    {
                        if(board_ptr[yDir+y][xDir+x] != NO_CHESS)
                        {
                            if(blackWhite_ptr[yDir+y][xDir+x] != color)
                                moves[yDir+y][xDir+x] = CHESS_EATTING;
                                canMove = CAN_MOVE;
                        }
                        else
                        {
                            moves[yDir+y][xDir+x] = CHESS_MOVING;
                            canMove = CAN_MOVE;
                        }
                    }
                }
            }
            break;
    }
    
    if(canMove == CANNOT_MOVE)
        moves[y][x]=0;
    return canMove;
}

void drawBoard()    //繪製棋盤
{
    //SetConsoleOutputCP(437);  //擴展ASCII字符，linux無須擴展
    printf("      ");
    for(int y=0; y<8; y++)  //繪製X軸座標
    {
        char c = (char)y;
        printf("%c:    ",y+97);
    }

    printf("\n\n");
    for(int y=0; y<8; y++)  //繪製Y軸座標及棋盤
    {
        for (int z=0; z<3; z++)
        {
            if(z==1)
                printf("%d:  ", y+1);   //印製Y軸座標
            else
                printf("    ");
            for(int x=0; x<8; x++)
            {
                if(z==1 && board_ptr[y][x]!=NO_CHESS)   //如果印製的方格有棋子
                {
                    if((y+x)%2==WHITE_SQUARE)   //印製白方格
                    {
                        if(blackWhite_ptr[y][x]==WHITE_TURN)
                            printf("%c%c\033[4;31;47m%c%d\033[m%c%c", 219, 219, chess_ptr[y][x], blackWhite_ptr[y][x], 219, 219);
                        else
                            printf("%c%c\033[4;34;47m%c%d\033[m%c%c", 219, 219, chess_ptr[y][x], blackWhite_ptr[y][x], 219, 219);
                    }
                    else    //印製黑方格
                    {
                        if(blackWhite_ptr[y][x]==WHITE_TURN)
                            printf("  \033[4;31m%c%d\033[m  ", chess_ptr[y][x], blackWhite_ptr[y][x]);
                        else
                            printf("  \033[4;34m%c%d\033[m  ", chess_ptr[y][x], blackWhite_ptr[y][x]);
                    }
                }
                else    //印製的方格沒棋子
                {
                    if((y+x)%2==WHITE_SQUARE)
                        printf("%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219);
                    else
                        printf("      ");
                }
            }
            printf("\n");
        }
    }

}

void drawMoves()    //繪製移動狀態
{
    //SetConsoleOutputCP(437);  //擴展ASCII字符，linux無須擴展
    printf("      ");
    for(int y=0; y<8; y++)  //繪製X軸座標
    {
        char c = (char)y;
        printf("%c:    ",y+97);
    }

    printf("\n\n");
    for(int y=0; y<8; y++)  //繪製Y軸座標及棋盤
    {
        for (int z=0; z<3; z++)
        {
            if(z==1)
                printf("%d:  ", y+1);
            else
                printf("    ");
            for(int x=0; x<8; x++)
            {
                if(z==1 && board_ptr[y][x]!=NO_CHESS)   //如果印製的方格有棋子
                {
                    if((y+x)%2==WHITE_SQUARE)   //印製白方格
                    {
                        if(blackWhite_ptr[y][x]==WHITE_TURN)
                        {
                            if(moves[y][x]==CHESS_POSITION) //如果印製的位置是我方棋子的位置
                                printf("%c%c\033[4;7;31m%c%d\033[m%c%c", 219, 219, chess_ptr[y][x], blackWhite_ptr[y][x], 219, 219);
                            else if(moves[y][x]==CHESS_EATTING) //如果印製的位置是可以被吃棋子的位置
                                printf("%c%c\033[4;31;43m%c%d\033[m%c%c", 219, 219, chess_ptr[y][x], blackWhite_ptr[y][x], 219, 219);
                            else    //如果印製的位置是棋子可以移動的位置
                                printf("%c%c\033[4;31;47m%c%d\033[m%c%c", 219, 219, chess_ptr[y][x], blackWhite_ptr[y][x], 219, 219);
                        }
                        else
                        {
                            if(moves[y][x]==CHESS_POSITION) //如果印製的位置是我方棋子的位置
                                printf("%c%c\033[4;7;34m%c%d\033[m%c%c", 219, 219, chess_ptr[y][x], blackWhite_ptr[y][x], 219, 219);
                            else if(moves[y][x]==CHESS_EATTING) //如果印製的位置是可以被吃棋子的位置
                                printf("%c%c\033[4;34;43m%c%d\033[m%c%c", 219, 219, chess_ptr[y][x], blackWhite_ptr[y][x], 219, 219);
                            else    //如果印製的位置是棋子可以移動的位置
                                printf("%c%c\033[4;34;47m%c%d\033[m%c%c", 219, 219, chess_ptr[y][x], blackWhite_ptr[y][x], 219, 219);
                        }
                    }
                    else    //印製黑方格
                    {
                        if(blackWhite_ptr[y][x]==WHITE_TURN)
                        {
                            if(moves[y][x]==CHESS_POSITION) //如果印製的位置是我方棋子的位置
                                printf("  \033[4;7;31m%c%d\033[m  ", chess_ptr[y][x], blackWhite_ptr[y][x]);
                            else if(moves[y][x]==CHESS_EATTING) //如果印製的位置是可以被吃棋子的位置
                                printf("  \033[4;31;43m%c%d\033[m  ", chess_ptr[y][x], blackWhite_ptr[y][x]);
                            else    //如果印製的位置是棋子可以移動的位置
                                printf("  \033[4;31m%c%d\033[m  ", chess_ptr[y][x], blackWhite_ptr[y][x]);
                        }
                        else
                        {
                            if(moves[y][x]==CHESS_POSITION) //如果印製的位置是我方棋子的位置
                                printf("  \033[4;7;34m%c%d\033[m  ", chess_ptr[y][x], blackWhite_ptr[y][x]);
                            else if(moves[y][x]==CHESS_EATTING) //如果印製的位置是可以被吃棋子的位置
                                printf("  \033[4;34;43m%c%d\033[m  ", chess_ptr[y][x], blackWhite_ptr[y][x]);
                            else    //如果印製的位置是棋子可以移動的位置
                                printf("  \033[4;34m%c%d\033[m  ", chess_ptr[y][x], blackWhite_ptr[y][x]);
                        }
                    }
                }
                else if(z==1 && moves[y][x]==CHESS_MOVING)  //如果印製的位置沒棋子
                {
                    if((y+x)%2==WHITE_SQUARE)
                        printf("%c%c\033[32m%c%c\033[m%c%c", 219, 219, 219, 219, 219, 219);
                    else
                        printf("  \033[32m%c%c\033[m  ", 219, 219);
                }
                else    //如果印製的位置沒棋子
                {
                    if((y+x)%2==WHITE_SQUARE)
                        printf("%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219);
                    else
                        printf("      ");
                }
            }
            printf("\n");
        }
    }

}

void drawturn() //繪製當前是誰的回合
{
    printf("\n                    ");
    if(currentTurn == WHITE_TURN)
        printf("\033[7m White's turn \033[m\n\n");
    else
        printf("\033[7m Black's turn \033[m\n\n");
}

void drawhome() //繪製主畫面
{
    //SetConsoleOutputCP(437);
    printf("\n\n");
    for(int y=0; y<5; y++)
    {
        printf("\033[7m   \033[m");
        for(int x=0; x<25; x++)
        {
            if((y==1 || y==3) && x==10)
            {
                printf("\033[7m        \033[m");
                x=13;
            }
            else if(y==2 && x==10)
            {
                printf("\033[7m Chess! \033[m");
                x=13;
            }
            else
            {
                if((x+y)%2 == 0)
                    printf("\033[7m%c%c\033[m", 219, 219);
                else
                    printf("\033[7m  \033[m");
            }
        }
        printf("\033[7m   \033[m\n");
    }
    printf("\n                      ");
    printf("1.Restart\n");
    printf("\n                      ");
    printf("2.Record\n");
    printf("\n                      ");
    printf("3.Rules\n");
    printf("\n                      ");
    /*printf("4.Replay\n");
    printf("\n                      ");*/
    printf("4.Exit\n");
    printf("\n                     ");
    printf("Input: ");
}

void home() //主畫面
{
    while(mode == HOME)
    {
        system("@cls||clear");
        drawhome();
        int input;
        scanf("%d", &input);    //在主畫面輸入要做甚麼步驟
        switch(input)
        {
            case 1:
                mode = RESTART;
                break;
            case 3:
                system("@cls||clear");
                printf("-Red indicates white side, blue indicates black side.\n\n");
                printf("-The first word indicates what chess piece it is.\n\n");
                printf("-The second word indicates what color it is.\n\n");
                printf("- 1 indicates white side, 2 indicates black side.\n\n");
                printf("-Each round, please entering the chess's coordinate first.\n\n");
                printf("-Then, entering the position which you want to move.\n\n");
                printf("-\033[33m%c\033[m indicates you can capture.\n\n", 219);
                printf("-\033[32m%c\033[m indicates you can move to.\n\n", 219);
                printf("-\033[41m  \033[m and \033[44m  \033[m indicates your position.\n\n");
                printf("-In the game, you can enter ++ to call the menu.\n\n");
                printf("-In the game, you can enter -- to regret.\n\n");
                printf("-Each round, you have 60 seconds to move.\n\n");
                printf("-P:pawn, R:rook, N:knight, B:bishop, Q:queen, K:king.\n\n");
                getchar();
                getchar();
                break;
            case 2:
                mode = RECORD;
                break;
            case 4:
                mode = 0;
                break;
        }   
    }
}

void restart()  //重新開始，將板面所有東西重置
{
    while(mode == RESTART)
    {
        memcpy(board_ptr, board, 256);  //板面重置
        memcpy(blackWhite_ptr, blackWhite, 256);    //板面黑白棋位置重置
        memcpy(chess_ptr, chess, 64);   //板面棋子位置重置
        currentTurn = WHITE_TURN;
        FreeAll();
        pushback();
        mode = GAME;
    }
}

void record()   //讀取存檔紀錄
{
    while(mode == RECORD)
        {
        FILE *fBoard = fopen("boardfile.txt", "rb");
        FILE *fBlackWhite = fopen("blackwhitefile.txt", "rb");
        FILE *fChess = fopen("chessfile.txt", "rb");
        FILE *fTurn = fopen("turnfile.txt", "rb");
        if(!fBoard || !fBlackWhite || !fChess || !fTurn)
        {
            printf("\n                    No Record!!!\n");
            int i;
            scanf("%d", &i);
            mode = HOME;
            break;
        }

        while(!feof(fBoard))
        {
            fread(&board_ptr, sizeof(int), 64, fBoard);
        }
        while(!feof(fBlackWhite))
        {
            fread(&blackWhite_ptr, sizeof(int), 64, fBlackWhite);
        }
        while(!feof(fChess))
        {
            fread(&chess_ptr, sizeof(char), 64, fChess);
        }
        while(!feof(fTurn))
        {
            fread(&currentTurn, sizeof(int), 1, fTurn);
        }
        fclose(fBoard);
        fclose(fBlackWhite);
        fclose(fChess);
        fclose(fTurn);

        FreeAll();
        pushback();
        mode = GAME;
    }
}

void game()     //遊戲模式
{
    time_t t1, t2;  //時間
    if(mode == GAME)
        t1 = time(NULL);    //以t1為參考時間
    while(mode == GAME) 
    {
        char a = ' ', b = ' ';
        while(TRUE) //倒數計時的迴圈
        {
            system("clear");    //清理畫面
            if(kbhit()) //如果有鍵擊
            {
                if((a<97 || a>104) && a!=43 && a!=45)   //a需界在'a'到'h'，或是a必須等於'+'、'-'
                {
                    a = getch();
                    if((a<97 || a>104) && a!=43 && a!=45)
                        a = ' ';
                }
                else if((b<49 || b>56) && b!=43 && b!=45)   //a需界在'1'到'8'，或是a必須等於'+'、'-'
                {
                    b = getch();
                    if((b<49 || b>56) && b!=43 && b!=45)
                        b = ' ';
                }
            }
            t2 = time(NULL);    //給予當前時間，並與t1參考時間去作相減，得到所經過的時間
            drawturn();     //繪製誰的黑白回合
            drawBoard();    //繪製棋盤
            printf("\nTime left: %ld s\n", LEFTTIME-t2+t1);
            printf("\nChoosing your chess: %c%c\n", a, b);
            if((b>=49 && b<=56) || b=='+' || b=='-')    //跳脫迴圈的依據
                break;
            if(t2-t1 >= LEFTTIME)   //當超過時間，跳出迴圈
                break;
        }

        if(t2-t1 >= LEFTTIME)   //當超過時間，則回合交換
        {
            t1 = time(NULL);
            currentTurn = currentTurn == 1 ? 2 : 1;
            break;
        }
        int input[2];
        
        if(a=='+' && b=='+')    //呼叫菜單menu
        {
            mode = MENU;
            break;
        }
        if(a=='-' && b=='-')    //悔棋regret
        {
            if(stack->left == NULL)
            {
                printf("\n\nYou can not REGRET!!!");
                getchar();
                getchar();
            }
            else
                pop();
            continue;
        }
        input[0] = a-'a';   //將a-h字元轉換成0-7數值
        input[1] = b-'1';   //將1-8字元轉換成0-7數值

        int x = input[0];   //確定X座標
        int y = input[1];   //確定Y座標
        if(board_ptr[y][x] == NO_CHESS) //如果選到的座標沒有棋子，則在重新一次
            continue;
        if(blackWhite_ptr[y][x] != currentTurn) //如果選到的棋子不是己方的棋子，則重新一次
            continue;
        if(getValidMoves(x,y) == CANNOT_MOVE)   //如果選到的棋子無法移動，則重新一次
            continue;

        a = ' '; 
        b = ' ';
        while(TRUE)
        {
            system("clear");
            if(kbhit())
            {
                if(a<97 || a>104)
                {
                    a = getch();
                    if(a<97 || a>104)
                        a = ' ';
                }
                else if(b<49 || b>56)
                {
                    b = getch();
                    if(b<49 || b>56)
                        b = ' ';
                }
            }
            t2 = time(NULL);
            drawturn();     //繪製誰的黑白回合
            drawMoves();    //繪製棋盤
            printf("\nTime left: %ld s", LEFTTIME-t2+t1);
            printf("\n\nChoosing your chess: %c%c", x+'a', y+'1');
            printf("\n\nMoving your chess to: %c%c", a, b);
            printf("\n\n");
            if(b>=49 && b<=56)
                break;
            if(t2-t1 >= LEFTTIME)
                break;
        }
        if(t2-t1 >= LEFTTIME)
        {
            t1 = time(NULL);
            currentTurn = currentTurn == 1 ? 2 : 1;
            break;
        }

        input[0] = a-'a';
        input[1] = b-'1';

        if(moves[input[1]][input[0]] == CHESS_MOVING || moves[input[1]][input[0]] == CHESS_EATTING)     //移動、吃掉的判別
        {
            if(board_ptr[input[1]][input[0]] == KING)   //如果國王被吃掉，則將模式變為顯示勝利者模式
                mode = WINNER;
            blackWhite_ptr[input[1]][input[0]] = blackWhite_ptr[y][x];
            board_ptr[input[1]][input[0]] = board_ptr[y][x];
            board_ptr[y][x] = 0;
            chess_ptr[input[1]][input[0]] = chess_ptr[y][x];
            chess_ptr[y][x] = '0';
            currentTurn = currentTurn == 1 ? 2 : 1;
            pushback();
            t1 = time(NULL);
        }
        for(int x_ = 0; x_ < 8; x_++)
        {
            for(int y_ = 0; y_ < 8; y_++)
                moves[x_][y_] = 0;
        }
    }
}

void menu() //菜單模式
{
    while(mode == MENU)
    {
        printf("\n");
        printf("Menu: 1.Continue 2.Save 3.Replaly 4.Exit\n");
        printf("Input: ");
        int input;
        scanf("%d", &input);
        switch (input)
        {
            case 1:
                mode = GAME;
                break;
            case 2:
                mode = SAVE;
                break;
            case 3:
                mode = REPLAY;
                break;
            case 4:
                mode = HOME;
                break;
            default:
                break;
        }
    }
}

void save() //儲存
{
    while(mode == SAVE)
    {
        FILE *fBoard;
        FILE *fBlackWhite;
        FILE *fChess;
        FILE *fTurn;
        fBoard = fopen("boardfile.txt", "wb");
        fBlackWhite = fopen("blackwhitefile.txt", "wb");
        fChess = fopen("chessfile.txt", "wb");
        fTurn = fopen("turnfile.txt", "wb");
        if(!fBoard || !fBlackWhite || !fChess || !fTurn)
        {
            printf("\nFile can be saved!!!");
            int i;
            scanf("\n%d", &i);
            mode = HOME;
            break;
        }
        fwrite(board_ptr, sizeof(int), 64, fBoard);
        fwrite(blackWhite_ptr, sizeof(int), 64, fBlackWhite);
        fwrite(chess_ptr, sizeof(char), 64, fChess);
        fwrite(&currentTurn, sizeof(int), 1, fTurn);
        fclose(fBoard);
        fclose(fBlackWhite);
        fclose(fChess);
        fclose(fTurn);
        printf("\nFile is saved successfully!!! (Press Enter to continue.)");
        getchar();
        getchar();
        mode = GAME;
    }
}

void winner()   //某方獲勝遊戲結束
{
    while(mode == WINNER)
    {
        system("clear");
        printf("\n\n\n");
        drawBoard();
        printf("\n                     ");
        if(currentTurn == BLACK_TURN)
            printf("White wins!!!\n\n");
        else
            printf("Black wins!!!\n\n");
        mode = HOME;
        int i;
        scanf("%d", &i);
    }
}

void replaying()    //重播
{
    if(mode == REPLAY)
    {
        queue = list;
        list_replaying();
    }
    while(mode == REPLAY)
    {
        system("clear");
        drawturn();
        drawBoard();    //繪製棋盤
        printf("\nInput ++ to go to next turn or -- to exit. ");
        printf("\n\nInput: ");

        char in[3];
        scanf("%s", &in[0], &in[1]);
        if(in[0]=='+' && in[1]=='+')
        {
            if(queue == NULL)
            {
                printf("\n\nThere is no round to REPLAY!!!");
                getchar();
                getchar();
            }
            else
                list_replaying();
        }
        else if(in[0]=='-' && in[1]=='-')
        {
            memcpy(board_ptr, stack->board, 256);
            memcpy(blackWhite_ptr, stack->blackwhite, 256);
            memcpy(chess_ptr, stack->chess, 64);
            currentTurn = stack->currentturn;
            mode = GAME;
        }
    }
}

void execution()    //將所有模式執行
{
    do
    {
        home();
        restart();
        record();       
        game();        
        menu();        
        save();        
        winner();
        replaying();
    } while (mode != 0);
}

int main()
{   
    execution();
    return 0;
}