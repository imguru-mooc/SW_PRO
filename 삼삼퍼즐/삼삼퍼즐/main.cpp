#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include<stdio.h>

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3


extern void solve(int board[5][5], int pattern[3][3], int callCntLimit);

static int orgBoard[5][5];
static int orgPattern[3][3];
static int emptyY, emptyX;
static int callCnt;

bool swap(int dir) {
    int dy[4] = { -1, 0, 1, 0 };
    int dx[4] = { 0, 1, 0, -1 };

    ++callCnt;

    if (dir < UP || dir > LEFT) {
        return false;
    }

    int newY = emptyY + dy[dir];
    int newX = emptyX + dx[dir];

    if (newY < 0 || newY >= 5 || newX < 0 || newX >= 5) {
        return false;
    }

    orgBoard[emptyY][emptyX] = orgBoard[newY][newX];
    orgBoard[newY][newX] = 0;
    emptyY = newY;
    emptyX = newX;

    return true;
}

static bool run() {

    int board[5][5];
    int pattern[3][3];
    int callCntLimit;

    scanf("%d", &callCntLimit);

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            scanf("%d", &board[i][j]);

            orgBoard[i][j] = board[i][j];

            if (board[i][j] == 0) {
                emptyY = i;
                emptyX = j;
            }
        }
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            scanf("%d", &pattern[i][j]);

            orgPattern[i][j] = pattern[i][j];
        }
    }

    callCnt = 0;

    solve(board, pattern, callCntLimit);

    bool isCorrect = (callCnt <= callCntLimit);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (orgBoard[i + 1][j + 1] != orgPattern[i][j]) {
                isCorrect = false;
            }
        }
    }

    return isCorrect;
}

#include <time.h>
int main(void) {
    clock_t start, end;
    setbuf(stdout, NULL);
    freopen("sample_input.txt", "r", stdin);

    int T;
    scanf("%d", &T);

    start = clock();
    for (int tc = 1; tc <= T; ++tc) {
        printf("#%d %d\n", tc, run() ? 100 : 0);
    }
    end = clock();
    printf("%lu\n", end - start);
    printf("callCnt=%d\n", callCnt);

    return 0;
}

#if 1
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

#define  FIXED   8
#define  MARKED  9

#define MAX 1024


extern bool swap(int dir);

int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };

int(*board)[5];
int(*pattern)[3];
int empty_y, empty_x;


void my_swap(int dir) 
{
    int new_y; 
    int new_x; 

    new_y = empty_y + dy[dir];
    new_x = empty_x + dx[dir];

    board[empty_y][empty_x] = board[new_y][new_x];
    board[new_y][new_x] = 0;

    empty_y = new_y;
    empty_x = new_x;

    swap(dir);
}

int visited[5][5];

typedef struct 
{
    int y;
    int x;
} Point;

typedef struct
{
    Point data[MAX];
    int rear;
    int front;
    int size;
} Queue;

Queue queue; 
int movement[MAX];
int move_count;

void init_queue(Queue* q)
{
    q->front = 0;
    q->rear = 0;
    q->size = 0;
}

int is_queue_empty(Queue* q)
{
    return q->size == 0;
}

void enqueue(Queue* q, int y, int x)
{
    q->data[q->rear].y = y;
    q->data[q->rear].x = x;
    q->rear = (q->rear + 1) % MAX;
    q->size++;
}

Point dequeue(Queue* q)
{
    Point temp;
    temp = q->data[q->front];
    q->front = (q->front + 1) % MAX;
    q->size--;
    return temp;
}

void trace(int ys, int xs, int ye, int xe, int mark) 
{
    int dir;
    int ws = move_count;
    int we;
    int i, t;

    while (!(ys == ye && xs == xe)) 
    {
        dir = visited[ye][xe];
        visited[ye][xe] = mark;
        movement[move_count++] = dir;
        ye -= dy[dir]; 
        xe -= dx[dir];
    }

    we = move_count;
    for (i = 0; i < (we - ws) / 2; i++) 
    {
        t = movement[ws + i];
        movement[ws + i] = movement[we - i - 1];
        movement[we - i - 1] = t;
    }
}

void move(int ys, int xs, int ye, int xe, int marked, int color, int* target_y, int* target_x) 
{
    int i;
    int ny=0;
    int nx=0;
    int flag = 0;
    init_queue(&queue);



    enqueue(&queue, ys, xs);

    while (!is_queue_empty(&queue))
    {
        Point p;
        p = dequeue(&queue);
        for (i = 0; i < 4; i++) 
        {
            ny = p.y + dy[i];
            nx = p.x + dx[i];

            if (!(0 <= ny && ny < 5 && 0 <= nx && nx < 5)) 
                continue;

            if (visited[ny][nx] != -1) 
                continue;

            enqueue(&queue, ny, nx);
            visited[ny][nx] = i;

            if (marked == 0)
            {
                if (ny == ye && nx == xe)
                {
                    flag = 1;
                    break;
                }
            }
            else
            {
                if (board[ny][nx] == color)
                {
                    *target_y = ny;
                    *target_x = nx;
                    flag = 1;
                    break;
                }
            }
        }
        if (flag == 1)
            break;
    }

    trace(ys, xs, ny, nx, marked);
}

void calc(int y, int x, int c) 
{
    int i, j;
    int target_y, target_x;

    if (y != empty_y || x != empty_x)
    {
        for (i = 0; i < 5; i++)
            for (j = 0; j < 5; j++)
                if (visited[i][j] != FIXED)
                    visited[i][j] = -1;

        visited[empty_y][empty_x] = 0;
        move_count = 0;
        move(empty_y, empty_x, y, x, 0, 0, 0, 0);
        for (i = 0; i < move_count; i++)
            my_swap(movement[i]);
    }

    for (i = 0; i < 5; i++) 
    {
        for (j = 0; j < 5; j++) 
        {
            if (visited[i][j] != FIXED)
                visited[i][j] = -1;
        }
    }

    visited[empty_y][empty_x] = 0;
    move_count = 0;
    move(empty_y, empty_x, y, x, MARKED, c, &target_y, &target_x);

    for (i = 0; i < 5; i++)
        for (j = 0; j < 5; j++)
            if(visited[i][j] != MARKED && visited[i][j] != FIXED)
                visited[i][j] = -1;

    visited[target_y][target_x] = 0;
    move(target_y, target_x, empty_y, empty_x,0,0,0,0);

    for (i = 0; ; i = (i + 1) % move_count) 
    {
        my_swap(movement[i]);
        if (board[y][x] == c) 
            return;
    }
}

void solve(int orgBoard[5][5], int orgPattern[3][3], int callCntLimit) 
{
    int i, j;

    board = orgBoard;
    for (i = 0; i < 5; i++) 
    {
        for (j = 0; j < 5; j++) 
        {
            if (board[i][j] == 0)
            {
                empty_y = i;
                empty_x = j;
            }
            visited[i][j] = -1;
        }
    }
    
    pattern = orgPattern;

    for (i = 0; i < 3; i++) 
    {
        for (j = 0; j < 3; j++) 
        {
            if( board[i+1][j+1]!=pattern[i][j])
                calc(i + 1, j + 1, pattern[i][j]);

            visited[i + 1][j + 1] = FIXED;
        }
    }
}
#endif 