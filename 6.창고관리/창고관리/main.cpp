#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <string.h>

#define ADD_ITEM                100
#define REMOVE_ITEM_BY_NAME     200
#define REMOVE_ITEM_BY_TAG      300
#define GET_ITEM                400
#define GET_AREA                500

extern void init(int R, int C);
extern int addItem(char name[], char tag[], int height, int width,
    int mode, int r, int c);
extern int removeItemByName(char name[]);
extern int removeItemByTag(char tag[]);
extern int getItem(int r, int c, char name[], char tag[]);
extern int getArea(char tag[]);
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

static int run(int Result) {
    int N, R, C;

    scanf("%d %d %d", &N, &R, &C);

    init(R, C);

    for (int i = 0; i < N; ++i) {
        int cmd = 0;
        char name[11];
        char tag[11];
        char userName[11];
        char userTag[11];
        int height, width, mode, r, c;
        int ans, res;

        scanf("%d", &cmd);

        switch (cmd) {
        case ADD_ITEM:
            scanf("%s %s", name, tag);
            scanf("%d %d %d %d %d", &height, &width, &mode, &r, &c);

            res = addItem(name, tag, height, width, mode, r, c);

            scanf("%d", &ans);
            if (res != ans) 
                Result = 0;
            break;

        case REMOVE_ITEM_BY_NAME:
            scanf("%s", name);

            res = removeItemByName(name);

            scanf("%d", &ans);
            if (res != ans) 
                Result = 0;
            break;

        case REMOVE_ITEM_BY_TAG:
            scanf("%s", tag);

            res = removeItemByTag(tag);

            scanf("%d", &ans);
            if (res != ans) 
                Result = 0;
            break;

        case GET_ITEM:
            scanf("%d %d", &r, &c);

            res = getItem(r, c, userName, userTag);

            scanf("%d", &ans);
            if (res != ans) Result = 0;
            if (ans == 1) {
                scanf("%s %s", name, tag);
                if (strcmp(name, userName) != 0) 
                    Result = 0;
                if (strcmp(tag, userTag) != 0) 
                    Result = 0;
            }
            break;

        case GET_AREA:
            scanf("%s", tag);

            res = getArea(tag);

            scanf("%d", &ans);
            if (res != ans) 
                Result = 0;
            break;

        default:
            Result = 0;
            break;
        }
    }

    return Result;
}

#include <time.h>
int main() {

    setbuf(stdout, NULL);

    freopen("sample_input.txt", "r", stdin);

    int T, Result;
    scanf("%d %d", &T, &Result);

    clock_t start, end;

    start = clock();
    for (int tc = 1; tc <= T; tc++) {
        printf("#%d %d\n", tc, run(Result));
    }
    end = clock();
    printf("%lu\n", end - start);

    return 0;
}

#if 1
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

//-----------------------------------------------------------------------

#define MAX_ITEM 300
#define MAX_HASH 32
typedef  unsigned long long u64;

u64 strToNum(const char* str)
{
    u64 res = 0LL;

    while (*str) {
        res = (res << 5) + (*str - 'a' + 1);
        str++;
    }

    return res;
}

void my_strcpy(char* dst, char* src)
{
    while (*dst++ = *src++)
        ;
}

typedef struct
{
    char name[11];
    u64 name_id;
    char tag[11];
    u64 tag_id;
    int r;
    int c;
    int height;
    int width;
    NODE tag_hash_list;
    NODE name_hash_list;
} RECT;

NODE tag_hash_heads[MAX_HASH];
NODE name_hash_heads[MAX_HASH];

RECT rect_pool[MAX_ITEM * 10];
int rect_pool_count;
RECT* map[MAX_ITEM][MAX_ITEM];

int max_r;
int max_c;

void init(int R, int C)
{
    int i, j;
    rect_pool_count = 0;
    max_r = R;
    max_c = C;

    for (i = 0; i < MAX_HASH; i++)
    {
        INIT_LIST_HEAD(&tag_hash_heads[i]);
        INIT_LIST_HEAD(&name_hash_heads[i]);
    }

    for (i = 0; i < max_r; i++)
        for (j = 0; j < max_c; j++)
            map[i][j] = 0;
}

RECT* is_intersect(int height, int width, int r, int c)
{
    RECT* p;
    NODE* temp;
    int i, j;

    for (i = 0; i < MAX_HASH; i++)
    {
        list_for_each(temp, &tag_hash_heads[i])
        {
            p = list_entry(temp, RECT, tag_hash_list);
            if (p->c + p->width > c &&
                c + width > p->c &&
                p->r + p->height > r &&
                r + height > p->r)
                return p;
        }
    }

    return 0;
}

int addItem(char name[], char tag[], int height, int width, int mode, int r, int c)
{
    int ret = 0;
    int i, j;
    int flag = 0;
    RECT* p, * rect;

    r--;
    c--;
    if (mode == 0)
    {
        if ((max_r - r - height < 0) || (max_c - c - width < 0))
            return 0;

        p = is_intersect(height, width, r, c);
        if (p != 0)
            return 0;
    }
    else
    {
        for (j = 0; j < max_c - width + 1; j++)
        {
            c = j;
            for (i = 0; i < max_r - height + 1; i++)
            {
                r = i;
                p = is_intersect(height, width, r, c);
                if (p != 0)
                {
                    i += p->height - 1 - (r - p->r);
                    continue;
                }
                flag = 1;
                break;
            }
            if (flag == 1)
                break;
        }
        if (flag == 0)
            return 0;
    }

    rect = &rect_pool[rect_pool_count++];
    my_strcpy(rect->name, name);
    rect->name_id = strToNum(name);
    my_strcpy(rect->tag, tag);
    rect->tag_id = strToNum(tag);
    rect->r = r;
    rect->c = c;
    rect->height = height;
    rect->width = width;

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
            map[i + r][j + c] = rect;
    }

    list_add_tail(&rect->name_hash_list, &name_hash_heads[rect->name_id % MAX_HASH]);
    list_add_tail(&rect->tag_hash_list, &tag_hash_heads[rect->tag_id % MAX_HASH]);
    return 1;
}

int getItem(int r, int c, char name[], char tag[])
{
    RECT* p;

    p = map[r - 1][c - 1];
    if (p != 0)
    {
        my_strcpy(name, p->name);
        my_strcpy(tag, p->tag);
        return 1;
    }
    return 0;
}

int getArea(char tag[])
{
    int area = 0;
    u64 id;
    NODE* temp;
    RECT* p;
    id = strToNum(tag);
    list_for_each(temp, &tag_hash_heads[id % MAX_HASH])
    {
        p = list_entry(temp, RECT, tag_hash_list);
        if (id == p->tag_id)
        {
            area += p->height * p->width;
        }
    }
    return area;
}

int removeItemByName(char name[])
{
    u64 id;
    int count = 0, i, j;
    NODE* temp, * n;
    RECT* p;

    id = strToNum(name);
    list_for_each_safe(temp, n, &name_hash_heads[id % MAX_HASH])
    {
        p = list_entry(temp, RECT, name_hash_list);
        if (id == p->name_id)
        {
            list_del(&p->name_hash_list);
            list_del(&p->tag_hash_list);

            for (i = 0; i < p->height; i++)
            {
                for (j = 0; j < p->width; j++)
                    map[i + p->r][j + p->c] = 0;
            }
            count++;
        }
    }
    return count;
}

int removeItemByTag(char tag[])
{
    u64 id;
    int count = 0, i, j;
    NODE* temp, * n;
    RECT* p;

    id = strToNum(tag);
    list_for_each_safe(temp, n, &tag_hash_heads[id % MAX_HASH])
    {
        p = list_entry(temp, RECT, tag_hash_list);
        if (id == p->tag_id)
        {
            list_del(&p->name_hash_list);
            list_del(&p->tag_hash_list);

            for (i = 0; i < p->height; i++)
            {
                for (j = 0; j < p->width; j++)
                    map[i + p->r][j + p->c] = 0;
            }

            count++;
        }
    }
    return count;
}

#endif

