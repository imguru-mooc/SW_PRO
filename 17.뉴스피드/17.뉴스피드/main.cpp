#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define ADDNEWS (100)
#define ERASENEWS (200)
#define READNEWS (300)
#define CHANGESECTION (400)
#define GETLIST (500)

extern void init();
extern void addNews(int mSection, int mNewsId);
extern void eraseNews(int mNewsId);
extern void readNews(int mUserId, int mNewsId);
extern void changeSection(int mNewsId, int mSection);
extern int getList(int mUserId, int mList[]);

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

static int run()
{
	int N;
	int cmd;
	int mSection, mUserId;
	int mNewsId;
	int res[10];

	init();

	int retVal = 1;

	scanf("%d", &N);
	for (int i = 0; i < N; ++i) {
		scanf("%d", &cmd);
		switch (cmd)
		{
		case ADDNEWS:
			scanf("%d %d", &mSection, &mNewsId);
			addNews(mSection, mNewsId);
			break;
		case ERASENEWS:
			scanf("%d", &mNewsId);
			eraseNews(mNewsId);
			break;
		case READNEWS:
			scanf("%d %d", &mUserId, &mNewsId);
			readNews(mUserId, mNewsId);
			break;
		case CHANGESECTION:
			scanf("%d %d", &mNewsId, &mSection);
			changeSection(mNewsId, mSection);
			break;
		case GETLIST:
			scanf("%d", &mUserId);
			int num = getList(mUserId, res);
			int numans;
			scanf("%d", &numans);
			if (numans != num)
				retVal = 0;

			for (int j = 0; j < numans; j++) {
				int ans;
				scanf("%d", &ans);
				if (ans != res[j])
					retVal = 0;
			}
			break;
		}
	}

	return retVal;
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
	for (int tc = 1; tc <= T; tc++) {
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
	}
	end = clock();
	printf("%lu\n", end - start);

	return 0;
}


#if 1
#define MAX_SECTIONS 10
#define MAX_NEWS_ID 50001
#define MAX_USER_ID 100001

//--------------------------------------------------------------------------------------

typedef struct News
{
	int id;
	int section;
	int read_count;
	int score;
	int heap_idx;
} News;

typedef struct heap
{
	News* data[MAX_NEWS_ID];
	int h_count;
} HEAP;

#define SWAP(a,b)     \
do {                  \
    News *temp;       \
    temp = (a);       \
    (a) = (b);        \
    (b) = temp;       \
}while(0)

void up_heap(HEAP* heap, int cur)
{
	News** a = heap->data;
	int c, r;
		
	for (c = cur; c > 0; c = r)
	{
		r = (c - 1) / 2;
		if ( a[r]->score >= a[c]->score )
			break;
		SWAP(a[c], a[r]);

		a[c]->heap_idx = c;
		a[r]->heap_idx = r;
	}
}

void down_heap(HEAP* heap, int cur)
{
	int r, c;
	News** a = heap->data;
	int n = heap->h_count;

	for (r = cur; r * 2 + 1 < n - 1; r = c)
	{
		c = r * 2 + 1;
		if (c < n - 2 && a[c]->score < a[c + 1]->score)
			c++;
		if ( a[r]->score >= a[c]->score)
			break;

		SWAP(a[c], a[r]);

		a[c]->heap_idx = c;
		a[r]->heap_idx = r;
	}
}

void push(HEAP* heap, News* data)
{
	int cur = heap->h_count;
	heap->data[heap->h_count++] = data;
	((News*)data)->heap_idx = cur;
	up_heap(heap, cur);
}

void pop(HEAP* heap)
{
	News** a = heap->data;
	int n = heap->h_count;

	if (n > 1)
	{
		SWAP(a[0], a[n - 1]);
		a[0]->heap_idx = 0;
		down_heap(heap, 0);
	}
	heap->h_count--;
}

News* top(HEAP* heap)
{
	if (heap->h_count == 0)
		return 0;
	return heap->data[0];
}

void remove(HEAP* heap, int cur)
{
	News** a = heap->data;
	int n = heap->h_count;
	if (cur != n - 1 )
	{
		SWAP(a[cur], a[n - 1]);
		a[cur]->heap_idx = cur;

		if (cur == 0 || (a[cur]->score <= a[(cur - 1) / 2]->score))
			down_heap(heap, cur);
		else
			up_heap(heap, cur);
	}
	heap->h_count--;
}

int section_user[MAX_USER_ID];
News news_pool[MAX_NEWS_ID];
HEAP heap[MAX_SECTIONS];


void init()
{
	int i;
    for (i = 0; i < MAX_USER_ID; ++i)
        section_user[i] = -1;

	for (i = 0; i < MAX_SECTIONS; ++i)
		heap[i].h_count = 0;
}

void addNews(int mSection, int mNewsId) 
{
    News* news = &news_pool[mNewsId];
	news->id = mNewsId;
	news->section = mSection;
	news->read_count = 0;
	news->score = news->read_count * 50000 + mNewsId - 1;

	push( &heap[mSection], news);
}

void eraseNews(int mNewsId) // Max 5000
{
	News* news = &news_pool[mNewsId];
	remove(&heap[news->section], news->heap_idx);
}

void readNews(int mUserId, int mNewsId) // Max 50000
{
    News* news = &news_pool[mNewsId];
	 
	section_user[mUserId] = news->section;
	++news->read_count;
	news->score = news->read_count * 50000 + news->id - 1;

	if (news->heap_idx == 0)
		return;

	up_heap(&heap[news->section], news->heap_idx);
}

void changeSection(int mNewsId, int mSection) // Max 5000
{
    News* news = &news_pool[mNewsId];
	remove(&heap[news->section], news->heap_idx);

    news->section = mSection;
    push(&heap[news->section], news);
}

int getList(int mUserId, int mList[]) // Max 50000
{
	int i, j;
	struct Data
	{
		News* news;
		unsigned score;
	};
	Data candi[10] = { 0, };
	int nNews = 0;

	for (i = 0; i < 10; ++i) {
		candi[i].news = 0;
		for (j = 0; j < MAX_SECTIONS; ++j) {
			if (heap[j].h_count == 0)
				continue;

			int bonus = section_user[mUserId] == j ? 500000 : 0;
			unsigned newScore = top(&heap[j])->score + bonus;
			if (!candi[i].news || newScore > candi[i].score)
			{
				candi[i].news = top(&heap[j]);
				candi[i].score = newScore;
			}
		}
		if (!candi[i].news)
			break;
		pop(&heap[candi[i].news->section]);
		++nNews;
	}

	for (i = 0; i < nNews; ++i) {
		mList[i] = candi[i].news->id;
		push(&heap[candi[i].news->section], candi[i].news);
	}

	return nNews;
}
#endif

