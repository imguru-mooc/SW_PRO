#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CMD_INIT 100
#define CMD_GETRECT 200
#define CMD_MERGE 300
#define CMD_SPLIT 400
#define CMD_UNDO 500
#define CMD_CHKRECT 600

#define MAX_SELECT 15

extern void init(int R, int C);
extern void getRect(int r, int c, int rect[]);
extern int mergeCells(int cnt, int rs[], int cs[], int rect[]);
extern int splitCell(int r, int c, int rect[]);
extern void undo();
extern int checkRectangle(int r1, int c1, int r2, int c2);

static bool run()
{

	int Q, cmd;
	int R, C;
	int r, c, cnt, rs[MAX_SELECT], cs[MAX_SELECT];
	int r1, c1, r2, c2;
	int ans_rect[4];
	int rect[4];

	int ret = 0;
	int ans = 0;
	scanf("%d", &Q);
	bool okay = false;

	for (int order = 0; order < Q; ++order)
	{
		scanf("%d", &cmd);
		switch (cmd)
		{
		case CMD_INIT:
			scanf("%d %d", &R, &C);
			init(R, C);
			okay = true;
			break;
		case CMD_GETRECT:
			scanf("%d %d", &r, &c);
			getRect(r, c, rect);
			for (int i = 0; i < 4; i++)
			{
				scanf("%d", &ans_rect[i]);
				if (ans_rect[i] != rect[i])
					okay = false;
			}
			break;
		case CMD_MERGE:
			scanf("%d", &cnt);
			for (int i = 0; i < cnt; i++)
				scanf("%d", &rs[i]);
			for (int i = 0; i < cnt; i++)
				scanf("%d", &cs[i]);
			ret = mergeCells(cnt, rs, cs, rect);
			scanf("%d", &ans);
			if (ans != ret)
				okay = false;
			if (ans == 0)
				break;
			for (int i = 0; i < 4; i++)
			{
				scanf("%d", &ans_rect[i]);
				if (ans_rect[i] != rect[i])
					okay = false;
			}
			break;
		case CMD_SPLIT:
			scanf("%d %d", &r, &c);
			ret = splitCell(r, c, rect);
			scanf("%d", &ans);
			if (ans != ret)
				okay = false;
			if (ans == 0)
				break;
			for (int i = 0; i < 4; i++)
			{
				scanf("%d", &ans_rect[i]);
				if (ans_rect[i] != rect[i])
					okay = false;
			}
			break;
		case CMD_UNDO:
			undo();
			break;
		case CMD_CHKRECT:
			scanf("%d %d %d %d", &r1, &c1, &r2, &c2);
			ret = checkRectangle(r1, c1, r2, c2);
			scanf("%d", &ans);
			if (ans != ret)
				okay = false;
			break;
		}
	}
	return okay;
}

#include <time.h>
int main()
{
	clock_t start, end;
	setbuf(stdout, NULL);
	freopen("sample_input.txt", "r", stdin);

	int T, MARK;
	scanf("%d %d", &T, &MARK);

	start = clock();
	for (int tc = 1; tc <= T; tc++)
	{
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
	}
	end = clock();
	printf("%lu\n", end - start);
	return 0;
}

#if 1

//-----------------------------------------------------------------------

#define list_entry(ptr, type, member)     \
((type*)((char*)ptr - (unsigned long)&((type*)0)->member))

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
}NODE;

#define __list_add(temp, p, n)     \
do{                                \
    NODE *prev = (p);              \
    NODE *next = (n);              \
	(temp)->next = next;           \
	prev->next = (temp);           \
	(temp)->prev = prev;           \
	next->prev = (temp);           \
}while(0)


#define list_add(temp, head)    \
	__list_add((temp), (head), (head)->next)

#define list_add_tail(temp, head)    \
	__list_add((temp), (head)->prev, (head))


#define  __list_del(p, n)     \
do{                           \
	(n)->prev = (p);          \
	(p)->next = (n);          \
}while(0)

#define list_del(entry)       \
	__list_del((entry)->prev, (entry)->next)

#define INIT_LIST_HEAD(list)  \
do{                           \
	(list)->next = (list);    \
	(list)->prev = (list);    \
}while(0)

int list_empty(NODE* head)
{
    return head->next == head;
}

#define MAX_R 1000
#define MAX_C 1000
#define MAX_N 2002

#define MAX(x,y)  (((x) > (y)) ? (x) : (y))
#define MIN(x,y)  (((x) < (y)) ? (x) : (y))
#define POINT_IN_RECT(rect, r, c)  ((rect)->sr <= (r) && (r) <= (rect)->er && (rect)->sc <= (c) && (c) <= (rect)->ec)

typedef struct rect
{
    int sr, sc, er, ec;
    int size;
    NODE list;
} RECT;

NODE rect_list_head;

RECT node[MAX_N];
RECT *backup[MAX_N];
RECT* undo_backup[MAX_N];
int idx;
int backup_idx;
int undo_idx;

typedef enum { INIT=1000, MERGE, SPLIT, UNDO } TYPE;

TYPE status, undo_prev;

void init(int R, int C)
{
    int i;
    status = INIT;
    INIT_LIST_HEAD(&rect_list_head);

    for (i = 0; i < MAX_N; i++)
        node[i].size = 0;
    
    idx = 0;
    backup_idx = 0;
    undo_idx = 0;
}

void copy(int sr, int sc, int er, int ec, int rect[]) 
{
    rect[0] = sr; rect[1] = sc; rect[2] = er; rect[3] = ec;
}


void getRect(int r, int c, int rect[])
{
    NODE* temp;
    RECT* t_rect=0;
    int flag=0;

    list_for_each(temp, &rect_list_head)
    {
        t_rect = list_entry(temp, RECT, list);
        if (POINT_IN_RECT(t_rect, r, c))
        {
            flag = 1;
            break;
        }
    }

    if (flag==0) 
        copy(r, c, r, c, rect);
    else 
        copy(t_rect->sr, t_rect->sc, t_rect->er, t_rect->ec, rect);
}
int mergeCells(int cnt, int rs[], int cs[], int rect[])
{
    NODE* temp;
    RECT* t_rect=0;
    RECT* mlist[MAX_N] = { 0, };

    int sr = MAX_R, sc = MAX_C, er = 0, ec = 0;
    int size = 0, t = 0, flag=0,j;
    int i;

    for (i = 0; i < cnt; i++) 
    {
        int r = rs[i]; 
        int c = cs[i];

        flag = 0;
        list_for_each(temp, &rect_list_head)
        {
            t_rect = list_entry(temp, RECT, list);
            if (POINT_IN_RECT(t_rect, r, c))
            {
                flag = 1;
                break;
            }
        }

        if (flag==0) 
        {
            sr = MIN(sr, r);
            sc = MIN(sc, c);
            er = MAX(er, r);
            ec = MAX(ec, c);
            size++;
            continue;
        }
        sr = MIN(sr, t_rect->sr);
        sc = MIN(sc, t_rect->sc);
        er = MAX(er, t_rect->er);
        ec = MAX(ec, t_rect->ec);

        for (j = 0; j < t; j++)
        {
            if (mlist[j] == t_rect)
                return 0;
        }

        mlist[t++] = t_rect;
        size += t_rect->size;
    }

    int mergesize = (er - sr + 1) * (ec - sc + 1);
    if (mergesize != size) 
        return 0;

    node[idx].sr = sr;
    node[idx].sc = sc;
    node[idx].er = er;
    node[idx].ec = ec;
    node[idx].size = size;

    list_add_tail(&node[idx].list, &rect_list_head);
    idx++;

    undo_idx = 0;
    backup_idx = 0;
    for (i = 0; i < t; i++)
    {
        list_del(&mlist[i]->list);
        backup[backup_idx++] = mlist[i];
    }

    copy(sr, sc, er, ec, rect);
    status = MERGE;
    return 1;
}

int splitCell(int r, int c, int rect[])
{
    NODE* temp;
    RECT* t_rect=0;
    int flag = 0;
    list_for_each(temp, &rect_list_head)
    {
        t_rect = list_entry(temp, RECT, list);
        if (POINT_IN_RECT(t_rect, r, c))
        {
            flag = 1;
            break;
        }
    }
    if (flag == 0) 
        return 0;

    undo_idx = 0;
    backup_idx = 0;
    backup[backup_idx] = t_rect;
    status = SPLIT;
    list_del(&t_rect->list);
    copy(t_rect->sr, t_rect->sc, t_rect->er, t_rect->ec, rect);
    return 1;
}

void undo()
{
    RECT* p=0;
    int i;
    if (status == INIT)
        return;

    if (status == MERGE)
    {
        p = list_entry(rect_list_head.prev, RECT, list);
        list_del(&p->list);

        undo_idx = 0;
        for (i = 0; i < backup_idx; i++)
        {
            list_add_tail(&backup[i]->list, &rect_list_head);
            undo_backup[undo_idx++] = backup[i];
        }
        backup_idx = 0;
        backup[backup_idx++] = p;
    }
    else if (status == SPLIT)
    {
        list_add_tail(&backup[0]->list, &rect_list_head);
        undo_idx = 0;
        undo_backup[undo_idx++] = backup[0];
        backup_idx = 0;
    }
    else if (status == UNDO)
    {
        RECT* temp[MAX_N];
        int t;
        for (i = 0; i < undo_idx; i++)
        {
            list_del(&undo_backup[i]->list);
            temp[i] = undo_backup[i];
        }

        for (i = 0; i < backup_idx; i++)
        {
            list_add_tail(&backup[i]->list, &rect_list_head);
            undo_backup[i] = backup[i];
        }

        for (i = 0; i < undo_idx; i++)
            backup[i] = temp[i];

        t = undo_idx;
        undo_idx = backup_idx;
        backup_idx = t;
    }
    status = UNDO;
}

int check(int sr, int sc, int er, int ec, RECT *p) 
{
    if (sr > p->er || p->sr > er || sc > p->ec || p->sc > ec)
        return 0;

    if (sr <= p->sr && p->er <= er && sc <= p->sc && p->ec <= ec)
        return 0;

    if (p->sr <= sr && er <= p->er && p->sc <= sc && ec <= p->ec)
        return 0;

    return 1;
}

int checkRectangle(int sr, int sc, int er, int ec)
{
    NODE* temp;
    RECT* t_rect=0;
    int ret = 0;
    list_for_each(temp, &rect_list_head)
    {
        t_rect = list_entry(temp, RECT, list);

        ret = check(sr, sc, er, ec, t_rect);
        if (ret == 1)
            return 1;
    }
    return 0;
}

#endif