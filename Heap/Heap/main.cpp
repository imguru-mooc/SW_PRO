#if 0
#include <stdio.h>
// ver 0.1
int heap[1000];
int h_count;

void swap(int* a, int* b)
{
    int t;
    t = *a; 
    *a = *b;
    *b = t;
}

void up_heap(int* a, int n)
{
    int c, r;

    for (c = n - 1; c > 0; c = r)
    {
        r = (c - 1) / 2;
        if (a[r] <= a[c])
            break;
        swap(&a[r], &a[c]);
    }
}

void down_heap(int* a, int n)
{
    int r, c;
    swap(a, a + n);
    for (r = 0; r * 2 + 1 < n; r = c)
    {
        c = r * 2 + 1;
        if (c<n - 1 && a[c] > a[c + 1])
            c++;
        if (a[r] <= a[c])
            break;
        swap(a + r, a + c);
    }
}

int main()
{
    int a[] = { 4,3,2,5,6,1,7 };
    int i;

    for (i = 0; i < 7; i++)
    {
        heap[h_count++] = a[i];
        up_heap(heap, h_count);
    }

    for (i = 0; i < 7; i++)
        printf("%4d", heap[i]);
    printf("\n");

    for (i = 0; i < 7; i++)
    {
        printf("%4d", heap[0]);
        h_count--;
        down_heap(heap, h_count);
    }
	return 0;
}
#endif

#if 0
#include <stdio.h>
// ver 0.2

void swap(int* a, int* b)
{
    int t;
    t = *a;
    *a = *b;
    *b = t;
}

void up_heap(int* a, int n)
{
    int c, r;

    for (c = n - 1; c > 0; c = r)
    {
        r = (c - 1) / 2;
        if (a[r] <= a[c])
            break;
        swap(&a[r], &a[c]);
    }
}

void down_heap(int* a, int n)
{
    int r, c;
    swap(a, a+n-1);
    for (r = 0; r * 2 + 1 < n-1; r = c)
    {
        c = r * 2 + 1;
        if (c<n - 2 && a[c] > a[c + 1])
            c++;
        if (a[r] <= a[c])
            break;
        swap(a + r, a + c);
    }
}

int heap[1000];
int h_count;

void push(int data)
{
    heap[h_count++] = data;
    up_heap(heap, h_count);
}

void pop(void)
{
    down_heap(heap, h_count--);
}

int top()
{
    if (h_count == 0)
        return 0;
    return heap[0];
}

void display()
{
    int i;
    for (i = 0; i < 7; i++)
        printf("%4d", heap[i]);
    printf("\n");
}
//-------------------------------------------------
int main()
{
    int a[] = { 4,3,2,5,6,1,7 };
    int i;

    for (i = 0; i < 7; i++)
        push(a[i]);

    display();

    for (i = 0; i < 7; i++)
    {
        printf("%4d", top());
        pop();
    }
    return 0;
}
#endif

#if 0
#include <stdio.h>
// ver 0.3

#define HEAP_MAX 10000

typedef struct heap
{
    int data[HEAP_MAX];
    int h_count;
} HEAP;

void swap(int* a, int* b)
{
    int t;
    t = *a;
    *a = *b;
    *b = t;
}

void up_heap(HEAP *heap)
{
    int* a = heap->data;
    int n = heap->h_count;
    int c, r;

    for (c = n - 1; c > 0; c = r)
    {
        r = (c - 1) / 2;
        if (a[r] <= a[c])
            break;
        swap(&a[r], &a[c]);
    }
}

void down_heap(HEAP* heap)
{
    int r, c;
    int* a = heap->data;
    int n = heap->h_count;
    swap(a, a + n - 1);
    for (r = 0; r * 2 + 1 < n - 1; r = c)
    {
        c = r * 2 + 1;
        if (c<n - 2 && a[c] > a[c + 1])
            c++;
        if (a[r] <= a[c])
            break;
        swap(a + r, a + c);
    }
}

HEAP heap;

void push(HEAP* heap, int data)
{
    heap->data[heap->h_count++] = data;
    up_heap(heap);
}

void pop(HEAP* heap)
{
    down_heap(heap);
    heap->h_count--;
}

int top(HEAP* heap)
{
    if (heap->h_count == 0)
        return 0;
    return heap->data[0];
}

void display(HEAP *heap)
{
    int i;
    for (i = 0; i < 7; i++)
        printf("%4d", heap->data[i]);
    printf("\n");
}

void init(void)
{
    heap.h_count = 0;
}
//-------------------------------------------------
int main()
{
    int a[] = { 4,3,2,5,6,1,7 };
    int i;

    for (i = 0; i < 7; i++)
        push(&heap, a[i]);

    display(&heap);

    for (i = 0; i < 7; i++)
    {
        printf("%4d", top(&heap));
        pop(&heap);
    }
    return 0;
}
#endif

#if 0
#include <stdio.h>
// ver 0.4

#define HEAP_MAX 10000

typedef struct
{
    int sid;
}SAWON;

typedef struct heap
{
    SAWON data[HEAP_MAX];
    int h_count;
} HEAP;

void swap(SAWON* a, SAWON* b)
{
    SAWON t;
    t = *a;
    *a = *b;
    *b = t;
}

void up_heap(HEAP* heap)
{
    SAWON* a = heap->data;
    int n = heap->h_count;
    int c, r;

    for (c = n - 1; c > 0; c = r)
    {
        r = (c - 1) / 2;
        if (a[r].sid <= a[c].sid)
            break;
        swap(&a[r], &a[c]);
    }
}

void down_heap(HEAP* heap)
{
    int r, c;
    SAWON* a = heap->data;
    int n = heap->h_count;
    swap(a, a + n - 1);
    for (r = 0; r * 2 + 1 < n - 1; r = c)
    {
        c = r * 2 + 1;
        if (c<n - 2 && a[c].sid > a[c + 1].sid)
            c++;
        if (a[r].sid <= a[c].sid)
            break;
        swap(a + r, a + c);
    }
}

HEAP heap;

void push(HEAP* heap, SAWON *data)
{
    heap->data[heap->h_count++] = *data;
    up_heap(heap);
}

void pop(HEAP* heap)
{
    down_heap(heap);
    heap->h_count--;
}

SAWON* top(HEAP* heap)
{
    if (heap->h_count == 0)
        return 0;
    return &heap->data[0];
}

void display(HEAP* heap)
{
    int i;
    for (i = 0; i < 7; i++)
        printf("%4d", heap->data[i].sid);
    printf("\n");
}

//-------------------------------------------------

SAWON sawon[1000];
int sawon_count;

void init(void)
{
    heap.h_count = 0;
    sawon_count = 0;
}

int main()
{
    int a[] = { 4,3,2,5,6,1,7 };
    int i;
    SAWON* s;

    for (i = 0; i < 7; i++)
    {
        s = &sawon[sawon_count++];
        s->sid = a[i];
        push(&heap, s);
    }

    display(&heap);

    for (i = 0; i < 7; i++)
    {
        printf("%4d", top(&heap)->sid);
        pop(&heap);
    }
    return 0;
}
#endif


#if 0
#include <stdio.h>
// ver 0.5

#define HEAP_MAX 10000

typedef struct
{
    int sid;
}SAWON;

typedef struct heap
{
    SAWON data[HEAP_MAX];
    int h_count;
} HEAP;

void swap(SAWON* a, SAWON* b)
{
    SAWON t;
    t = *a;
    *a = *b;
    *b = t;
}

void up_heap(HEAP* heap, int(*cmp)(int*, int*))
{
    SAWON* a = heap->data;
    int n = heap->h_count;
    int c, r;

    for (c = n - 1; c > 0; c = r)
    {
        r = (c - 1) / 2;
        if ( cmp(&a[r].sid , &a[c].sid) <= 0 )
            break;
        swap(&a[r], &a[c]);
    }
}

void down_heap(HEAP* heap, int(*cmp)(int*, int*))
{
    int r, c;
    SAWON* a = heap->data;
    int n = heap->h_count;
    swap(a, a + n - 1);
    for (r = 0; r * 2 + 1 < n - 1; r = c)
    {
        c = r * 2 + 1;
        if (c<n - 2 && cmp(&a[c].sid, &a[c + 1].sid) > 0 )
            c++;
        if (cmp( &a[r].sid , &a[c].sid ) <= 0)
            break;
        swap(a + r, a + c);
    }
}

HEAP heap;

void push(HEAP* heap, SAWON* data, int(*cmp)(int*, int*))
{
    heap->data[heap->h_count++] = *data;
    up_heap(heap, cmp);
}

void pop(HEAP* heap, int(*cmp)(int*, int*))
{
    down_heap(heap,cmp);
    heap->h_count--;
}

SAWON* top(HEAP* heap)
{
    if (heap->h_count == 0)
        return 0;
    return &heap->data[0];
}

void display(HEAP* heap)
{
    int i;
    for (i = 0; i < 7; i++)
        printf("%4d", heap->data[i].sid);
    printf("\n");
}

//-------------------------------------------------

SAWON sawon[1000];
int sawon_count;

void init(void)
{
    heap.h_count = 0;
    sawon_count = 0;
}

int min_cmp(int* a, int* b)
{
    return *a - *b;
}

int max_cmp(int* a, int* b)
{
    return *b - *a;
}

int main()
{
    int a[] = { 4,3,2,5,6,1,7 };
    int i;
    SAWON* s;

    for (i = 0; i < 7; i++)
    {
        s = &sawon[sawon_count++];
        s->sid = a[i];
        push(&heap, s, max_cmp );
    }

    display(&heap);

    for (i = 0; i < 7; i++)
    {
        printf("%4d", top(&heap)->sid);
        pop(&heap, max_cmp);
    }
    return 0;
}
#endif


#if 1
#include <stdio.h>
// ver 0.6

#define HEAP_MAX 10000

typedef struct
{
    int sid;
}SAWON;

typedef struct heap
{
    void* data[HEAP_MAX];
    int h_count;
} HEAP;

void swap(void** a, void** b)
{
    void* t;
    t = *a;
    *a = *b;
    *b = t;
}

void up_heap(HEAP* heap, int(*cmp)(void*, void*))
{
    void** a = heap->data;
    int n = heap->h_count;
    int c, r;

    for (c = n - 1; c > 0; c = r)
    {
        r = (c - 1) / 2;
        if (cmp(a[r], a[c]) <= 0)
            break;
        swap(&a[r], &a[c]);
    }
}

void down_heap(HEAP* heap, int(*cmp)(void*, void*))
{
    int r, c;
    void** a = heap->data;
    int n = heap->h_count;
    swap(a, a + n - 1);
    for (r = 0; r * 2 + 1 < n - 1; r = c)
    {
        c = r * 2 + 1;
        if (c < n - 2 && cmp(a[c], a[c + 1]) > 0)
            c++;
        if (cmp(a[r], a[c]) <= 0)
            break;
        swap(a + r, a + c);
    }
}

HEAP heap;

void push(HEAP* heap, void* data, int(*cmp)(void*, void*))
{
    heap->data[heap->h_count++] = data;
    up_heap(heap, cmp);
}

void pop(HEAP* heap, int(*cmp)(void*, void*))
{
    down_heap(heap, cmp);
    heap->h_count--;
}

void* top(HEAP* heap)
{
    if (heap->h_count == 0)
        return 0;
    return heap->data[0];
}



//-------------------------------------------------
void display(HEAP* heap)
{
    int i;
    SAWON* s;
    for (i = 0; i < 7; i++)
    {
        s = (SAWON*)heap->data[i];
        printf("%4d", s->sid);
    }
    printf("\n");
}


SAWON sawon[1000];
int sawon_count;

void init(void)
{
    heap.h_count = 0;
    sawon_count = 0;
}

int min_cmp(void* a, void* b)
{
    SAWON* x = (SAWON*)a;
    SAWON* y = (SAWON*)b;
    return x->sid - y->sid;
}

int max_cmp(void* a, void* b)
{
    SAWON* x = (SAWON*)a;
    SAWON* y = (SAWON*)b;
    return y->sid - x->sid;
}

int main()
{
    int a[] = { 4,3,2,5,6,1,7 };
    int i;
    SAWON* s;

    for (i = 0; i < 7; i++)
    {
        s = &sawon[sawon_count++];
        s->sid = a[i];
        push(&heap, s, min_cmp);
    }

    display(&heap);

    for (i = 0; i < 7; i++)
    {
        s = (SAWON*)top(&heap);
        printf("%4d", s->sid);
        pop(&heap, min_cmp);
    }
    return 0;
}
#endif