#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define	MAXL			5
#define MAXF			10

extern void init(int N);
extern void add(int id, int F, int ids[MAXF]);
extern void del(int id1, int id2);
extern int  recommend(int id, int list[MAXL]);

#define INIT			1
#define ADD				2
#define DEL				3
#define RECOMMEND		4

static int N, M;

static bool run()
{
    int cmd;
    int id, F, ids[MAXF];
    int id1, id2;
    int len, len_a;
    int list[MAXL], list_a[MAXL];

    bool okay;

    okay = false;

    scanf("%d", &M);

    for (int k = 0; k < M; ++k)
    {
        scanf("%d", &cmd);
        switch (cmd)
        {
        case INIT:
            scanf("%d", &N);
            init(N);
            okay = true;
            break;
        case ADD:
            scanf("%d %d", &id, &F);
            for (int i = 0; i < F; ++i)
                scanf("%d", &ids[i]);
            if (okay)
                add(id, F, ids);
            break;
        case DEL:
            scanf("%d %d", &id1, &id2);
            if (okay)
                del(id1, id2);
            break;
        case RECOMMEND:
            scanf("%d %d", &id, &len_a);
            for (int i = 0; i < len_a; ++i)
                scanf("%d", &list_a[i]);
            if (okay)
            {
                len = recommend(id, list);
                if (len != len_a)
                    okay = false;

                for (int i = 0; okay && i < len_a; ++i)
                    if (list[i] != list_a[i])
                        okay = false;
            }
            break;
        }
    }

    return okay;
}

#include <time.h>
int main()
{
    int TC, MARK;
    clock_t start, end;

    start = clock();
    freopen("sample_input.txt", "r", stdin);

    setbuf(stdout, NULL);
    scanf("%d %d", &TC, &MARK);

    for (int testcase = 1; testcase <= TC; ++testcase)
    {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", testcase, score);
    }
    end = clock();
    printf("%lu\n", end - start);

    return 0;
}

#if 0
#define MAX_USER 10000

int friend_table[MAX_USER][MAX_USER];
int user_count;

void init(int N)
{
    int i, j;
    user_count = N;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
            friend_table[i][j] = 0;
    }
}

void add(int id, int F, int ids[])
{
    int i;

    for (i = 0; i < F; i++)
    {
        friend_table[id - 1][ids[i] - 1] = 1;
        friend_table[ids[i] - 1][id - 1] = 1;
    }
}

void del(int id1, int id2)
{
    friend_table[id1 - 1][id2 - 1] = 0;
    friend_table[id2 - 1][id1 - 1] = 0;
}

int recommend(int id, int list[])
{
    int i, j, k;
    int f_temp[MAX_USER] = { 0, };
    int max;
    int index=0;
    int count = 0;

    for (i = 0; i < user_count; i++)
    {
        if (friend_table[id - 1][i] == 0)
            continue;

        for (j = 0; j < user_count; j++)
        {
            if (friend_table[i][j] == 0)
                continue;

            if (friend_table[id-1][j] == 0)
                f_temp[j]++;
        }
    }

    f_temp[id - 1] = 0;

    for (i = 0; i < 5; i++) 
    {
        max = 0;
        for (int j = 0; j < user_count; j++) 
        {
            if (max < f_temp[j]) 
            {
                max = f_temp[j];
                index = j;
            }
        }
        if (max > 0) 
        {
            f_temp[index] = 0;
            list[count++] = index+1;
        }
        else
            break;
    }

    return count;
}
#endif



#if 1

//-------------------------------------------------------------------------------
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
//-------------------------------------------------------------------------------

#define MAX_USER 10000
#define MAX_POOL 500000

typedef struct
{
    int uid;
    NODE list;
} USER;

NODE users[MAX_USER];
USER user_pool[MAX_POOL];

int pool_count;
int user_count;

void init(int N)
{
    int i;
    user_count = N;
    pool_count = 0;

    for (i = 0; i < N; i++)
        INIT_LIST_HEAD(&users[i]);
}

void add(int id, int F, int ids[])
{
    int i;
    USER *p;

    for (i = 0; i < F; i++)
    {
        p = &user_pool[pool_count++];
        p->uid = ids[i]-1;
        list_add_tail(&p->list, &users[id-1]);

        p = &user_pool[pool_count++];
        p->uid = id-1;
        list_add_tail(&p->list, &users[ids[i]-1]);
    }
}

void del(int id1, int id2)
{
    NODE* temp;
    USER* p;

    list_for_each(temp, &users[id1-1])
    {
        p = list_entry(temp, USER, list);
        if (p->uid == id2 - 1)
        {
            list_del(temp);
            break;
        }
    }
    list_for_each(temp, &users[id2-1])
    {
        p = list_entry(temp, USER, list);
        if (p->uid == id1 - 1)
        {
            list_del(temp);
            break;
        }
    }
}

int recommend(int id, int list[])
{
    int i, j;
    int f_temp[MAX_USER] = { 0, };
    int friends[MAX_USER] = { 0 };
    int max;
    int index = 0;
    int count = 0;
    NODE* temp;
    USER* p;

    list_for_each(temp, &users[id-1])
    {
        p = list_entry(temp, USER, list);
        friends[p->uid]++;
    }

    for (i = 0; i < user_count; i++)
    {
        if (friends[i] == 0)
            continue;

        list_for_each(temp, &users[i])
        {
            p = list_entry(temp, USER, list);
            if (friends[p->uid] == 1)
                continue;

            f_temp[p->uid]++;
        }
    }

    f_temp[id - 1] = 0;

    for (i = 0; i < 5; i++)
    {
        max = 0;
        for (j = 0; j < user_count; j++)
        {
            if (max < f_temp[j])
            {
                max = f_temp[j];
                index = j;
            }
        }
        if (max > 0)
        {
            f_temp[index] = 0;
            list[count++] = index + 1;
        }
        else
            break;
    }

    return count;
}

#endif

