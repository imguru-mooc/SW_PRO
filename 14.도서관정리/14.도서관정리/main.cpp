#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CMD_INIT		100
#define CMD_ADD			200
#define CMD_MOVETYPE	300
#define CMD_MOVENAME	400
#define CMD_DELETENAME	500
#define CMD_COUNTBOOK	600

#define MAX_N			5

#define MAX_NAME_LEN	7
#define MAX_TAG_LEN		4

extern void init(int M);
extern void add(char mName[MAX_NAME_LEN], int mTypeNum, char mTypes[MAX_N][MAX_TAG_LEN], int mSection);
extern int  moveType(char mType[MAX_TAG_LEN], int mFrom, int mTo);
extern void moveName(char mName[MAX_NAME_LEN], int mSection);
extern void deleteName(char mName[MAX_NAME_LEN]);
extern int  countBook(int mTypeNum, char mTypes[MAX_N][MAX_TAG_LEN], int mSection);

static bool run()
{
	int  Q;
	int  cmd, M, mTypeNum, mSection, mFrom, mTo;
	char mName[MAX_NAME_LEN], mType[MAX_TAG_LEN], mTypes[MAX_N][MAX_TAG_LEN];

	int  ret, ans;

	scanf("%d", &Q);

	bool okay = false;

	for (int q = 0; q <= Q; ++q)
	{
		scanf("%d", &cmd);

		switch (cmd)
		{
		case CMD_INIT:
			scanf("%d", &M);
			init(M);
			okay = true;
			break;
		case CMD_ADD:
			scanf("%s %d", mName, &mTypeNum);
			for (int i = 0; i < mTypeNum; ++i)
				scanf("%s", mTypes[i]);
			scanf("%d", &mSection);
			if (okay)
				add(mName, mTypeNum, mTypes, mSection);
			break;
		case CMD_MOVETYPE:
			scanf("%s %d %d", mType, &mFrom, &mTo);
			if (okay)
				ret = moveType(mType, mFrom, mTo);
			scanf("%d", &ans);
			if (ret != ans)
				okay = false;
			break;
		case CMD_MOVENAME:
			scanf("%s %d", mName, &mSection);
			if (okay)
				moveName(mName, mSection);
			break;
		case CMD_DELETENAME:
			scanf("%s", mName);
			if (okay)
				deleteName(mName);
			break;
		case CMD_COUNTBOOK:
			scanf("%d", &mTypeNum);
			for (int i = 0; i < mTypeNum; ++i)
				scanf("%s", mTypes[i]);
			scanf("%d", &mSection);
			if (okay)
				ret = countBook(mTypeNum, mTypes, mSection);
			scanf("%d", &ans);
			if (ret != ans)
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
	printf("%u\n", end - start);

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

#define MAX_TYPE  5
#define MAX_BOOK  50000
#define MAX_BOOK_HASH 4096
#define MAX_TYPE_HASH 8192
#define MAX_TAG_LEN 4

typedef unsigned long long u64;

struct book;

typedef struct
{
	u64 tid;
	struct book* book;
	NODE hash_list;
} TYPE;

typedef struct book
{
	int index;
	u64 bid;
	TYPE type_array[MAX_TYPE];
	int type_count;
	int section;
	NODE list;
} BOOK;

BOOK book_pool[MAX_BOOK];
int book_count;
NODE type_hash[MAX_TYPE_HASH];
NODE book_hash[MAX_BOOK_HASH];

#define  hash_str(str)                          \
do{                                             \
	int idx;                                    \
    hx = 0;                                     \
	for (idx = 0; (str)[idx]; ++idx)            \
		hx = (hx<<6) + (str)[idx] - 'A' + 1;    \
}while(0)

void init(int m)
{
	int i, j;
	book_count = 0;
	for (i = 0; i < MAX_TYPE_HASH; i++)
		INIT_LIST_HEAD(&type_hash[i]);

	for (i = 0; i < MAX_BOOK_HASH; i++)
		INIT_LIST_HEAD(&book_hash[i]);
}

void add(char mName[MAX_NAME_LEN], int mTypeNum, char mTypes[][MAX_TAG_LEN], int mSection)
{
	BOOK* book;
	int i;
	u64 hx=0;

	book = &book_pool[book_count++];
	book->index = book_count - 1;
	hash_str(mName);
	book->bid = hx;
	book->type_count = mTypeNum;
	book->section = mSection - 1;
	list_add_tail(&book->list, &book_hash[book->bid % MAX_BOOK_HASH]);

	for (i = 0; i < mTypeNum; i++)
	{
		hash_str(mTypes[i]);
		book->type_array[i].tid = hx;
		book->type_array[i].book = book;
		list_add_tail(&book->type_array[i].hash_list, &type_hash[hx%MAX_TYPE_HASH]);
	}
}

int moveType(char mType[MAX_TAG_LEN], int mFrom, int mTo)
{
	int count = 0;
	u64 hx=0;
	NODE* temp, *head;
	BOOK* book = 0;
	TYPE* type;

	hash_str(mType);

	head = &type_hash[hx%MAX_TYPE_HASH];
	list_for_each(temp, head)
	{
		type = list_entry(temp, TYPE, hash_list);

		book = type->book;
		if (type->tid == hx)
		{
			if (book->section == mFrom - 1)
			{
				book->section = mTo - 1;
				count++;
  		    }
		}
	}
	return count;
}

void moveName(char mName[MAX_NAME_LEN], int mSection)
{
	NODE* temp, *head;
	BOOK* book = 0;
	u64 hx=0;

	hash_str(mName);
	head = &book_hash[hx % MAX_BOOK_HASH];
	list_for_each(temp, head)
	{
		book = list_entry(temp, BOOK, list);

		if (book->bid == hx)
		{
			book->section = mSection - 1;
			break;
		}
	}
}

void deleteName(char mName[MAX_NAME_LEN])
{
	int i;
	NODE* temp, *head;
	BOOK* book = 0;
	u64 hx=0;

	hash_str(mName);

	head = &book_hash[hx%MAX_BOOK_HASH];
	list_for_each(temp, head)
	{
		book = list_entry(temp, BOOK, list);
		if (book->bid == hx)
		{
			list_del(&book->list);
			for (i = 0; i < book->type_count; i++)
				list_del(&book->type_array[i].hash_list);
			break;
		}
	}
}

int countBook(int mTypeNum, char mTypes[][MAX_TAG_LEN], int mSection)
{
	int count = 0;
	int i;
	NODE* temp, *head;
	BOOK* book = 0;
	TYPE* type = 0;
	u64 hx=0;
	int is_visit[MAX_BOOK] = { 0, };
	int index;

	for (i = 0; i < mTypeNum; i++)
	{
		hash_str(mTypes[i]);
		head = &type_hash[hx%MAX_TYPE_HASH];
		list_for_each(temp, head)
		{
			type = list_entry(temp, TYPE, hash_list);
			book = type->book;
			index = book->index;
			if (is_visit[index] == 1)
				continue;
			if (book->section == mSection - 1)
			{
				if (type->tid == hx)
				{
					count++;
					is_visit[index] = 1;
				}
			}
		}
	}
	return count;
}
#endif
