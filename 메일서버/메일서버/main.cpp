#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define INIT         0
#define SENDMAIL     1
#define GETCOUNT     2
#define DELETEMAIL   3
#define SEARCHMAIL   4

extern void init(int N, int K);
extern void sendMail(char subject[], int uID, int cnt, int rIDs[]);
extern int getCount(int uID);
extern int deleteMail(int uID, char subject[]);
extern int searchMail(int uID, char text[]);

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

#define MAX_WORD 10000
static char Word[MAX_WORD][11];

static int N, W, minR, maxR, SW;

static int mSeed;
static int pseudo_rand(void)
{
	mSeed = mSeed * 214013 + 2531011;
	return (mSeed >> 16) & 0x7FFF;
}

static void make_string(int seed)
{
	mSeed = seed;

	for (int i = 0; i < W; ++i) {
		int length = 5 + pseudo_rand() % 6;
		for (int k = 0; k < length; ++k) {
			Word[i][k] = 'a' + pseudo_rand() % 26;
		}
		Word[i][length] = '\0';
	}
}

static void send_mail(int seed)
{
	char str[200];
	int pos = 0;

	mSeed = seed;

	int wcnt = 1 + pseudo_rand() % SW;
	for (int i = 0; i < wcnt; ++i) {
		int widx = pseudo_rand() % W;
		for (int k = 0; k < 10; ++k) {
			if (Word[widx][k] == '\0') break;
			str[pos++] = Word[widx][k];
		}
		str[pos++] = ' ';
	}
	str[pos - 1] = '\0';

	int uid = pseudo_rand() % N;
	int rcnt = minR + pseudo_rand() % (maxR - minR + 1);
	int rids[50];
	for (int i = 0; i < rcnt; ++i) {
		rids[i] = pseudo_rand() % N;
	}

	sendMail(str, uid, rcnt, rids);
}

static int delete_mail(int uid, int seed)
{
	char str[200];
	int pos = 0;

	mSeed = seed;

	int wcnt = 1 + pseudo_rand() % SW;
	for (int i = 0; i < wcnt; ++i) {
		int widx = pseudo_rand() % W;
		for (int k = 0; k < 10; ++k) {
			if (Word[widx][k] == '\0') break;
			str[pos++] = Word[widx][k];
		}
		str[pos++] = ' ';
	}
	str[pos - 1] = '\0';

	return deleteMail(uid, str);
}

static int run(int answer)
{
	int Q, K, cmd, sample, seed, param1, param2, ret;
	char str[30];

	scanf("%d %d %d %d", &Q, &sample, &N, &K);
	if (sample == 0) {
		scanf("%d %d %d %d %d", &W, &minR, &maxR, &SW, &seed);
		make_string(seed);
	}

	init(N, K);

	for (int i = 1; i < Q; ++i) {
		scanf("%d", &cmd);
		switch (cmd) {
		case SENDMAIL:
			if (sample == 1) {
				int uid, rcnt;
				int rids[10];
				scanf("%s %d %d", str, &uid, &rcnt);
				for (int k = 0; k < rcnt; ++k) scanf("%d", &rids[k]);
				for (int k = 0; k < 30; ++k) {
					if (str[k] == '\0') break;
					if (str[k] == '_') str[k] = ' ';
				}
				sendMail(str, uid, rcnt, rids);
			}
			else {
				scanf("%d", &seed);
				send_mail(seed);
			}
			break;
		case GETCOUNT:
			scanf("%d %d", &param1, &param2);
			ret = getCount(param1);
			if (ret != param2)
				answer = 0;
			break;
		case DELETEMAIL:
			if (sample == 1) {
				int uid;
				scanf("%d %s %d", &param1, str, &param2);
				for (int k = 0; k < 30; ++k) {
					if (str[k] == '\0') break;
					if (str[k] == '_') str[k] = ' ';
				}
				ret = deleteMail(param1, str);
				if (ret != param2)
					answer = 0;
			}
			else {
				scanf("%d %d %d", &param1, &seed, &param2);
				ret = delete_mail(param1, seed);
				if (ret != param2)
					answer = 0;
			}
			break;
		case SEARCHMAIL:
			scanf("%d %s %d", &param1, str, &param2);
			ret = searchMail(param1, str);
			if (ret != param2)
				answer = 0;
			break;
		default:
			break;
		}
	}

	return answer;
}

#include <time.h>
int main()
{
	setbuf(stdout, NULL);
	freopen("sample_input.txt", "r", stdin);

	int T, Mark;
	scanf("%d %d", &T, &Mark);

	clock_t start, end;
	start = clock();
	for (int tc = 1; tc <= T; tc++) {
		printf("#%d %d\n", tc, run(Mark));
	}
	end = clock();
	printf("%lu\n", end - start);
	return 0;
}
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
	(temp)->next = (n);            \
	(p)->next = (temp);            \
	(temp)->prev = (p);            \
	(n)->prev = (temp);            \
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

#if 1
#define MAXM 10000
#define MAXU 1000

typedef unsigned long long u64;

typedef struct
{
	int word_cnt;
	u64 word[11];
} MAIL;

typedef struct
{
	MAIL* p;
	NODE list;
} MAIL_P;

typedef struct
{
	int count;
	NODE mail_list_head;
	MAIL_P  mail_p[600];
	int mail_pool_count;
} USER;

USER user_pool[MAXU];
MAIL mail_pool[MAXM];
int mail_pool_count;

int mail_max_count;

void init(int N, int K)
{
	int i;

	mail_max_count = K;
	mail_pool_count = 0;

	for (i = 0; i < N; i++)
	{
		user_pool[i].count = 0;
		user_pool[i].mail_pool_count = 0;
		INIT_LIST_HEAD(&user_pool[i].mail_list_head);
	}
}

#define STR_HASH(result,ch) ((result) = ((result) << 5) + ((ch) - 'a' + 1))

void sendMail(char subject[], int uID, int cnt, int rIDs[])
{
	int i;
	MAIL* mp;

	mp = &mail_pool[mail_pool_count++];
    mp->word_cnt = 0;
    mp->word[mp->word_cnt] = 0;

	while (*subject) {
		if (*subject == ' ')
		{
			mp->word_cnt++;
			mp->word[mp->word_cnt] = 0;
		}
		else {
			STR_HASH(mp->word[mp->word_cnt], *subject);
		}
		subject++;
	}
	mp->word_cnt++;

	for (i = 0; i < cnt; i++)
	{
		USER* up = &user_pool[rIDs[i]];
		MAIL_P* p = &up->mail_p[up->mail_pool_count++];
		p->p = mp;
		if (up->count == mail_max_count)
		{
			list_del(up->mail_list_head.next);
			up->count--;
		}
		list_add_tail(&p->list, &up->mail_list_head);
		up->count++;
	}
}

int getCount(int uID)
{
	return user_pool[uID].count;
}

int deleteMail(int uID, char subject[])
{
	NODE* temp, * n;
	MAIL_P* p;
	int remove_count = 0;
	USER* up = &user_pool[uID];

	int scnt = 0;
	u64 word[10] = { 0, };
	int i;

	while (*subject) {
		if (*subject == ' ')
			scnt++;
		else
			STR_HASH(word[scnt], *subject);
		subject++;
	}
	scnt++;

	list_for_each_safe(temp, n, &up->mail_list_head)
	{
		p = list_entry(temp, MAIL_P, list);
		if (scnt != p->p->word_cnt)
			continue;
		for (i = 0; i < scnt; i++)
		{
			if (word[i] != p->p->word[i])
				break;
		}
		if (i == scnt)
		{
			list_del(temp);
			up->count--;
			remove_count++;
		}
	}
	return remove_count;
}

int searchMail(int uID, char text[])
{
	NODE* temp;
	MAIL_P* p;
	USER* up = &user_pool[uID];

	int search_count = 0;
	u64 word = { 0 };
	int i;

	while (*text)
		STR_HASH(word, *text++);

	list_for_each(temp, &up->mail_list_head)
	{
		p = list_entry(temp, MAIL_P, list);

		for (i = 0; i < p->p->word_cnt; i++)
		{
			if (p->p->word[i] == word)
			{
				search_count++;
				break;
			}
		}
	}

	return search_count;
}
#endif
















//-----------------------------------------------------------------------
#if 0
#define MAXM 10000
#define MAXU 1000
#define HASH_MAX 64

typedef unsigned long long u64;

typedef struct
{
	int word_cnt;
	u64 word[11];
} MAIL;

typedef struct
{
	MAIL* p;
	u64 hash_id;
	NODE list;
	NODE hash_list;
} MAIL_P;

typedef struct
{
	int count;
	NODE mail_list_head;
	NODE mail_hash_heads[HASH_MAX];
	MAIL_P  mail_p[600];
	int mail_pool_count;
} USER;

USER user_pool[MAXU];
MAIL mail_pool[MAXM];
int mail_pool_count;

int mail_max_count;

void init(int N, int K)
{
	int i, j;

	mail_max_count = K;
	mail_pool_count = 0;

	for (i = 0; i < N; i++)
	{
		user_pool[i].count = 0;
		user_pool[i].mail_pool_count = 0;
		INIT_LIST_HEAD(&user_pool[i].mail_list_head);
		for(j=0; j<HASH_MAX; j++)
			INIT_LIST_HEAD(&user_pool[i].mail_hash_heads[j]);
	}
}

#define STR_HASH(result,ch) ((result) = ((result) << 5) + ((ch) - 'a' + 1))

void sendMail(char subject[], int uID, int cnt, int rIDs[])
{
	int i;
	MAIL* mp;
	u64 hash_id = 0;

	mp = &mail_pool[mail_pool_count++];
	mp->word_cnt = 0;
	mp->word[mp->word_cnt] = 0;
	while (*subject) {
		if (*subject == ' ')
		{
			hash_id += mp->word[mp->word_cnt];
			hash_id %= HASH_MAX;
			mp->word_cnt++;
			mp->word[mp->word_cnt] = 0;
		}
		else {
			STR_HASH(mp->word[mp->word_cnt], *subject);
		}
		subject++;
	}
	mp->word_cnt++;

	for (i = 0; i < cnt; i++)
	{
		USER* up = &user_pool[rIDs[i]];
		MAIL_P* p = &up->mail_p[up->mail_pool_count++];
		p->p = mp;
		p->hash_id = hash_id;
		if (up->count == mail_max_count)
		{
			list_del(up->mail_list_head.next);
			list_del(up->mail_hash_heads[hash_id % HASH_MAX].next);
			up->count--;
		}
		list_add_tail(&p->list, &up->mail_list_head);
		list_add_tail(&p->hash_list, &up->mail_hash_heads[hash_id %HASH_MAX]);
		up->count++;
	}
}

int getCount(int uID)
{
	return user_pool[uID].count;
}

int deleteMail(int uID, char subject[])
{
	NODE* temp, * n;
	MAIL_P* p;
	int remove_count = 0;
	USER* up = &user_pool[uID];

	int scnt = 0;
	u64 word[10] = { 0, }, hash_id=0;
	int i;

	while (*subject) {
		if (*subject == ' ')
		{
			hash_id += word[scnt];
			hash_id %= HASH_MAX;
			scnt++;
		}
		else
			STR_HASH(word[scnt], *subject);
		subject++;
	}
	scnt++;

	list_for_each_safe(temp, n, &up->mail_hash_heads[hash_id %HASH_MAX])
	{
		p = list_entry(temp, MAIL_P, hash_list);
		if (scnt != p->p->word_cnt)
			continue;
		for (i = 0; i < scnt; i++)
		{
			if (word[i] != p->p->word[i])
				break;
		}
		if (i == scnt)
		{
			list_del(&p->list);
			list_del(&p->hash_list);
			up->count--;
			remove_count++;
		}
	}
	return remove_count;
}

int searchMail(int uID, char text[])
{
	NODE* temp;
	MAIL_P* p;
	USER* up = &user_pool[uID];

	int search_count = 0;
	u64 word = { 0 };
	int i;

	while (*text)
		STR_HASH(word, *text++);

	list_for_each(temp, &up->mail_list_head)
	{
		p = list_entry(temp, MAIL_P, list);

		for (i = 0; i < p->p->word_cnt; i++)
		{
			if (p->p->word[i] == word)
			{
				search_count++;
				break;
			}
		}
	}

	return search_count;
}
#endif


