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

extern bool swap(int dir);

int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };

/**
* board: 현재 상태
* pattern: 정답 패턴
* Y0: 현재 빈칸 위치 (Y좌표)
* X0: 현재 빈칸 위치 (X좌표)
*/
int board[5][5], pattern[3][3], Y0, X0;


void mySwap(int dir) {
    board[Y0][X0] = board[Y0 + dy[dir]][X0 + dx[dir]];
    board[Y0 + dy[dir]][X0 + dx[dir]] = 0;

    Y0 += dy[dir]; X0 += dx[dir];
    swap(dir);
}
/**
* fixed: 정답 맞춘 위치는 1 나머진 -1
* Visited:
* marked:
*
*/
int fixed[5][5], Visited[5][5];
bool marked[5][5];

struct Point
{
    int y, x;
};
Point queue[555]; int front, end;
int Movement[555], moveCnt;

void trace(int ys, int xs, int ye, int xe, int mark) {
    int ws = moveCnt;
    while (!(ys == ye && xs == xe)) {
        marked[ye][xe] = mark;
        int dir = Visited[ye][xe];
        Movement[moveCnt++] = dir;
        ye -= dy[dir]; xe -= dx[dir];
    }

    // 이 아래는 그냥 reverse 해주는 과정. 다르게 처리해도 될듯..
    int we = moveCnt;
    for (int i = 0; i < (we - ws) / 2; i++) {
        int t = Movement[ws + i];
        Movement[ws + i] = Movement[we - i - 1];
        Movement[we - i - 1] = t;
    }
}

void move(int ys, int xs, int ye, int xe) {
    front = end = 0;
    queue[0].y = ys;
    queue[0].x = xs;

    //[ys][xs]로 부터 모든 위치까지 이동 방향을 Visited[][] 배열에 저장.
    while (front <= end) {
        Point p = queue[front++];
        for (int i = 0; i < 4; i++) {
            int ny = p.y + dy[i];
            int nx = p.x + dx[i];

            // 맵 밖으로 나가는지 체크
            if (!(0 <= ny && ny < 5 && 0 <= nx && nx < 5)) continue;

            // 이미 정답처리된 위치(fixed)거나 방문한 위치인지 체크
            if (fixed[ny][nx] || Visited[ny][nx] != -1) continue;

            ++end;
            queue[end].y = ny;
            queue[end].x = nx;

            Visited[ny][nx] = i;
            if (ny == ye && nx == xe)break;
        }
    }
    trace(ys, xs, ye, xe, 0);
}

void calc(int y, int x, int c) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++)
            Visited[i][j] = -1;
    }

    //////////////////////////////////////////////////////////////////////////////////////////
    // 내가 원하는 위치에 빈칸을 이동 시킴
    Visited[Y0][X0] = 0;
    moveCnt = 0;
    move(Y0, X0, y, x); // 이동 경로 찾기
    for (int i = 0; i < moveCnt; i++)
        mySwap(Movement[i]);
    //////////////////////////////////////////////////////////////////////////////////////////


    //////////////////////////////////////////////////////////////////////////////////////////
    // 가장 가까운 target 색칸 찾기
    int Yt = -1, Xt = -1;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            Visited[i][j] = -1;
            marked[i][j] = 0;
        }
    }
    Visited[Y0][X0] = 0;

    front = end = 0;
    queue[0].y = Y0;
    queue[0].x = X0;

    while (front <= end && Yt == -1 && Xt == -1) {
        Point p = queue[front++];
        int y = p.y, x = p.x;
        for (int i = 0; i < 4; i++) {
            int ny = y + dy[i];
            int nx = x + dx[i];
            if (!(0 <= ny && ny < 5 && 0 <= nx && nx < 5)) continue;
            if (fixed[ny][nx] || Visited[ny][nx] >= 0) continue;

            ++end;
            queue[end].y = ny;
            queue[end].x = nx;
            Visited[ny][nx] = i;

            if (board[ny][nx] == c) {
                Yt = ny, Xt = nx;
                break;
            }
        }
    }
    //////////////////////////////////////////////////////////////////////////////////////////
    moveCnt = 0;
    trace(Y0, X0, Yt, Xt, 1);

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) Visited[i][j] = marked[i][j] ? 9 : -1;
    }
    Visited[Yt][Xt] = 0;
    move(Yt, Xt, Y0, X0);

    for (int i = 0; ; i = (i + 1) % moveCnt) {
        mySwap(Movement[i]);
        if (board[y][x] == c) return;
    }
}

void solve(int orgBoard[5][5], int orgPattern[3][3], int callCntLimit) {
    // board 초기화, 
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            marked[i][j] = fixed[i][j] = 0;
            board[i][j] = orgBoard[i][j];

            // 빈 칸 위치를 기억함.
            if (board[i][j] == 0) Y0 = i, X0 = j;
        }
    }
    //pattern 초기화
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            pattern[i][j] = orgPattern[i][j];
        }
    }

    // pattern의 우상단(1,1) 부터 순서대로 완성해나감
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // (i+1, i+1) 위치를 정답색으로 만든다.
            calc(i + 1, j + 1, pattern[i][j]);

            // fix 된 위치, 5x5 맵에 정답 완성된 위치를 fixed 표시함
            // 이후 bfs 탐색에서 요 위치는 방문하지 않도록 처리한다.
            fixed[i + 1][j + 1] = 1;
        }
    }
}
#endif 

#if 0

#undef  offsetof
#define offsetof(TYPE, MEMBER)	((unsigned int)&((TYPE *)0)->MEMBER)

#define container_of(ptr, type, member) 			\
		((type *)( (char *)ptr - offsetof(type,member) ))

#define list_entry(ptr, type, member) \
	container_of(ptr, type, member)

#define list_first_entry(ptr, type, member) \
	list_entry((ptr)->next, type, member)

#define list_for_each(pos, head) \
	for (pos = (head)->next; pos != (head); pos = pos->next)

#define list_for_each_entry(pos, head, member)				\
	for (pos = list_first_entry(head, typeof(*pos), member);	\
			&pos->member != (head);					\
			pos = list_next_entry(pos, member))

#define list_for_each_safe(pos, n, head) \
	for (pos = (head)->next, n = pos->next; pos != (head); \
		pos = n, n = pos->next)

typedef struct node
{
    struct node* next, * prev;
} NODE;

void __list_add(NODE* temp,
    NODE* prev,
    NODE* next)
{
    next->prev = temp;
    temp->next = next;
    temp->prev = prev;
    prev->next = temp;
}

void list_add(NODE* temp, NODE* head)
{
    __list_add(temp, head, head->next);
}

void list_add_tail(NODE* temp, NODE* head)
{
    __list_add(temp, head->prev, head);
}

void __list_del(NODE* prev, NODE* next)
{
    next->prev = prev;
    prev->next = next;
}

void list_del(NODE* entry)
{
    __list_del(entry->prev, entry->next);
}

int list_empty(const NODE* head)
{
    return head->next == head;
}

void INIT_LIST_HEAD(NODE* list)
{
    list->next = list;
    list->prev = list;
}

#define SIZE  5

typedef struct
{
    int   f;
    int   fx;
    int   move_count;
    int   pre;
    int   map[SIZE][SIZE];
    NODE list;
} DATA;

DATA data_pool[10000];
int data_pool_count;

NODE queue;
NODE close;

int queue_empty(void)
{
    return list_empty(&queue);
}

int calc_heuristic(int board[SIZE][SIZE], int pattern[3][3])
{
    int i, j;
    int cnt = 0;

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (board[i + 1][j + 1] == pattern[i][j])
            {
                cnt++;
            }
        }
    }

    cnt = 9 - cnt;

    return cnt;
}

DATA* dequeue(void)
{
    NODE* temp;
    DATA* data;

    data = list_first_entry(&queue, DATA, list);
    list_del(&data->list);
    return data;
}

void my_swap(int board[SIZE][SIZE], int x, int y, int nx, int ny)
{
    int temp;

    temp = board[y][x];
    board[y][x] = board[ny][nx];
    board[ny][nx] = temp;
}

void enqueue(int board[SIZE][SIZE], int pattern[3][3], int pre, int move)
{
    int i, j;
    DATA* data, * p;
    NODE* temp;

    list_for_each(temp, &close)
    {
        int flag = 0;
        p = list_entry(temp, DATA, list);
        for (i = 0; i < SIZE; i++)
        {
            for (j = 0; j < SIZE; j++)
            {
                if (p->map[i][j] != board[i][j])
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 1)
                break;
        }
        if (flag == 0)
            return;
    }

    data = &data_pool[data_pool_count++];
    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
            data->map[i][j] = board[i][j];

    data->move_count = move;
    data->pre = pre;
    data->fx = calc_heuristic(board, pattern);
    data->f = data->move_count + data->fx;

    if (list_empty(&queue))
        list_add_tail(&data->list, &queue);
    else
    {
        list_for_each(temp, &queue)
        {
            p = list_entry(temp, DATA, list);
            if (data->f <= p->f)
            {
                break;
            }
        }
        list_add_tail(&data->list, temp);
    }
}

int astar(int board[SIZE][SIZE], int pattern[3][3], int callCntLimit)
{
    int sx = 0, sy = 0;
    int i, j, result;
    DATA* data;
    int count = 0;

    result = 0;

    enqueue(board, pattern, -1, 0);

    while (!queue_empty())
    {
        data = dequeue();
        
        count++;
        if (count > callCntLimit)
        {
            break;
        }

        if (data->fx == 0)
        {
            result = data->move_count;
            for (i = 0; i < SIZE; i++)
                for (j = 0; j < SIZE; j++)
                    orgBoard[i][j] = data->map[i][j];
            break;
        }

        for (i = 0; i < SIZE; i++)
        {
            for (j = 0; j < SIZE; j++)
            {
                if (data->map[i][j] == 0)
                {
                    sx = j;
                    sy = i;
                    break;
                }
            }
        }

        data->move_count++;

        if (sy - 1 >= 0 && data->pre != DOWN)
        {
            my_swap(data->map, sx, sy, sx, sy - 1);
            enqueue(data->map, pattern, UP, data->move_count);
            my_swap(data->map, sx, sy, sx, sy - 1);
        }

        if (sy + 1 < SIZE && data->pre != UP)
        {
            my_swap(data->map, sx, sy, sx, sy + 1);
            enqueue(data->map, pattern, DOWN, data->move_count);
            my_swap(data->map, sx, sy, sx, sy + 1);
        }

        if (sx + 1 < SIZE && data->pre != LEFT)
        {
            my_swap(data->map, sx + 1, sy, sx, sy);
            enqueue(data->map, pattern, RIGHT, data->move_count);
            my_swap(data->map, sx + 1, sy, sx, sy);
        }

        if (sx - 1 >= 0 && data->pre != RIGHT)
        {
            my_swap(data->map, sx - 1, sy, sx, sy);
            enqueue(data->map, pattern, LEFT, data->move_count);
            my_swap(data->map, sx - 1, sy, sx, sy);
        }
        list_add_tail(&data->list, &close);
    }

    return result;
}

void solve(int board[SIZE][SIZE], int pattern[3][3], int callCntLimit)
{
    int result;
    data_pool_count = 0;
    INIT_LIST_HEAD(&queue);
    INIT_LIST_HEAD(&close);
    result = astar(board, pattern, callCntLimit);
}
#endif


#if 0
struct Point
{
    int y, x;
};
Point queue[200]; int front, end;
int move[200], moveCnt;
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };

//Y0, X0 empty space (0) 
int board[5][5], pattern[3][3], Y0, X0, Yt, Xt;
//fixed for target
int fixed[5][5], Visited[5][5];
bool marked[5][5];

extern bool swap(int dir);

void mySwap(int dir) {
    board[Y0][X0] = board[Y0 + dy[dir]][X0 + dx[dir]];
    board[Y0 + dy[dir]][X0 + dx[dir]] = 0;

    Y0 += dy[dir]; X0 += dx[dir];
    swap(dir);
}

void backtrace(int ys, int xs, int ye, int xe, int mark) {
    int ws = moveCnt;
    while (!(ys == ye && xs == xe)) {
        marked[ye][xe] = mark;
        int dir = Visited[ye][xe];
        move[moveCnt++] = dir;
        ye -= dy[dir]; xe -= dx[dir];
    }

    //find the right way in the reverse way
    int we = moveCnt;
    for (int i = 0; i < (we - ws) / 2; i++) {
        int t = move[ws + i];
        move[ws + i] = move[we - i - 1];
        move[we - i - 1] = t;
    }
}

void realMove(int ys, int xs, int ye, int xe) {

    //set up start point
    front = end = 0;
    queue[0].y = ys;
    queue[0].x = xs;

    //check visited
    while (front <= end) {
        Point p = queue[front++];
        for (int i = 0; i < 4; i++) {
            int ny = p.y + dy[i];
            int nx = p.x + dx[i];

            if (0 <= ny && ny < 5 && 0 <= nx && nx < 5) { //range check
                if (fixed[ny][nx] == 0 && Visited[ny][nx] == -1) {//fixed not && visited not

                    ++end;
                    queue[end].y = ny;
                    queue[end].x = nx;
                    Visited[ny][nx] = i; //direction

                    if (ny == ye && nx == xe)
                        break;
                }
            }

        }
    }

    backtrace(ys, xs, ye, xe, 0);
}


void findTarget(int ys, int xs, int ye, int xe, int c) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            Visited[i][j] = -1;
            marked[i][j] = 0;
        }
    }

    Visited[ys][xs] = 0;

    front = end = 0;
    queue[0].y = ys;
    queue[0].x = xs;

    while (front <= end && Yt == -1 && Xt == -1) {
        Point p = queue[front++];
        int y = p.y, x = p.x;
        for (int i = 0; i < 4; i++) {
            int ny = y + dy[i];
            int nx = x + dx[i];

            if (0 <= ny && ny < 5 && 0 <= nx && nx < 5) { //range change
                if (fixed[ny][nx] == 0 && Visited[ny][nx] == -1) {//fixed not && visited not

                    ++end;
                    queue[end].y = ny;
                    queue[end].x = nx;
                    Visited[ny][nx] = i; //direction

                    if (board[ny][nx] == c) {
                        Yt = ny, Xt = nx;
                        break;
                    }
                }
            }
        }
    }

    moveCnt = 0;
    backtrace(ys, xs, Yt, Xt, 1);
}

void puzzle(int y, int x, int c) {

    //initialize vistied matrix
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++)
            Visited[i][j] = -1;
    }

    //////////////////////////////////////////////////////////////////////////////////////////
    //move an empty space to pattern 
    Visited[Y0][X0] = 0;
    moveCnt = 0;
    realMove(Y0, X0, y, x); // 이동 경로 찾기: 빈칸<->타켓
    for (int i = 0; i < moveCnt; i++)
        mySwap(move[i]);

    //////////////////////////////////////////////////////////////////////////////////////////
    //find the closest target
    Yt = -1, Xt = -1;
    findTarget(Y0, X0, Yt, Yt, c);

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++)
            Visited[i][j] = marked[i][j] ? 1 : -1;
    }
    Visited[Yt][Xt] = 0;
    //moveCnt = 0; do not need to intialize
    realMove(Yt, Xt, Y0, X0);

    //cycle
    for (int i = 0; ; i = (i + 1) % moveCnt) {
        mySwap(move[i]);
        if (board[y][x] == c) return;
    }
}

void solve(int orgBoard[5][5], int orgPattern[3][3], int callCntLimit) {
    //initialize board 
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            marked[i][j] = fixed[i][j] = 0;
            board[i][j] = orgBoard[i][j];

            //remember an empty space
            if (board[i][j] == 0) Y0 = i, X0 = j;
        }
    }
    //initialize pattern
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            pattern[i][j] = orgPattern[i][j];
        }
    }

    //start from pattern (1,1)
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {

            puzzle(i + 1, j + 1, pattern[i][j]);

            fixed[i + 1][j + 1] = 1;
        }
    }
}
#endif