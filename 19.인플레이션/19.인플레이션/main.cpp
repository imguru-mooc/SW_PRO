#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

extern void init(int, char[][20], char[][100], int[]);
extern void priceChange(char[], char[]);
extern int daySurvivable(char[]);

static int run()
{
    int ret_val = 1;
    int N, Q, mDuration[50] = {};
    char mName[50][20] = {}, mPrice[50][100] = {};
    scanf("%d %d", &N, &Q);

    for (int i = 0; i < N; ++i) {
        scanf("%s %s %d", mName[i], mPrice[i], &mDuration[i]);
    }

    init(N, mName, mPrice, mDuration);

    for (int i = 0; i < Q; ++i) {
        int type;
        scanf("%d", &type);
        if (type == 1) {
            char name[20] = {}, price[100] = {};

            scanf("%s %s", name, price);
            priceChange(name, price);
        }
        else if (type == 2) {
            char money[100] = {};

            scanf("%s", money);

            int user, answer;
            user = daySurvivable(money);
            scanf("%d", &answer);

            if (user != answer) {
                ret_val = 0;
            }
        }
    }

    return ret_val;
}

#include <time.h>
int main()
{
    clock_t start, end;
    setbuf(stdout, NULL);
    freopen("sample_input.txt", "r", stdin);

    int T, score;
    scanf("%d%d", &T, &score);
    
    start = clock();
    for (int tc = 1; tc <= T; tc++) {
        if (run() == 1)
            printf("#%d %d\n", tc, score);
        else
            printf("#%d 0\n", tc);
    }
    end = clock();
    printf("%lu\n", end - start);

    return 0;
}


#if 1
//-------------------------------------------------------------------------------

typedef  long long int  ll;

void generic_swap(void* a, void* b, int size)
{
    char t;
    char* x = (char*)a;
    char* y = (char*)b;
    do {
        t = *x;
        *x++ = *y;
        *y++ = t;
    } while (--size > 0);
}

void sort(void* a, int num, int size, ll (*cmp_func)( void*,  void*))
{
    char* base = (char*)a;
    int i = (num / 2 - 1) * size, n = num * size, c, r;

    for (; i >= 0; i -= size) {
        for (r = i; r * 2 + size < n; r = c) {
            c = r * 2 + size;
            if (c < n - size &&
                cmp_func(base + c, base + c + size) < 0)
                c += size;
            if (cmp_func(base + r, base + c) >= 0)
                break;
            generic_swap(base + r, base + c, size);
        }
    }

    for (i = n - size; i > 0; i -= size) {
        generic_swap(base, base + i, size);
        for (r = 0; r * 2 + size < i; r = c) {
            c = r * 2 + size;
            if (c < i - size &&
                cmp_func(base + c, base + c + size) < 0)
                c += size;
            if (cmp_func(base + r, base + c) >= 0)
                break;
            generic_swap(base + r, base + c, size);
        }
    }
}
//-------------------------------------------------------------------------------


#define BND  1e14
#define BIGINTPOW 14
#define BIGINTLEN  8
#define HMAX  1007

typedef struct
{
    ll val[BIGINTLEN];
    int cnt;
} BIGINT;

typedef struct
{
    BIGINT price;
    ll name_id;
    int du;
} ITEM;

ITEM item[HMAX];
int index_count;
ITEM* index_arr[50];


void set_val( BIGINT *big, char* in) 
{
    int i = 0;
    while (in[i]) 
        i++; 
    i--;
    big->cnt = i / BIGINTPOW + 1;
    for (int p = 0; p < BIGINTLEN; p++) 
    {
        big->val[p] = 0;
        ll mul = 1;
        for (int j = 0; j < BIGINTPOW && i>=0; j++, i--, mul *= 10)
            big->val[p] += mul * (in[i] - '0');
    }
}

int is_minus(BIGINT* big) 
{
    if (big->val[BIGINTLEN - 1] < 0)
        return 1;
    return 0;
}

void normalize(BIGINT* big)
{
    int bound = BIGINTLEN - 1;
    for (int i = 0; i < bound; i++) 
    {
        if (big->val[i] < 0) 
        {
            big->val[i] *= -1;
            ll borrow = (ll)((big->val[i] + BND - 1) / BND);
            big->val[i] = (ll)(borrow * BND - big->val[i]);
            big->val[i + 1] -= borrow;
        }
    }
}

void sub(BIGINT* a, BIGINT* b, int multiple) 
{
    int bound = b->cnt;
    for (int i = 0; i < bound; i++)
        a->val[i] -= b->val[i] * multiple;
}

void set_price(ITEM* item, char* iPrice)
{
    set_val(&item->price, iPrice);
}

ll my_compare(void *a, void *b) 
{
    ITEM* x = *(ITEM**)a;
    ITEM* y = *(ITEM**)b;

    for (int i = BIGINTLEN - 1; i>=0; i--) 
    {
        ll l = x->price.val[i] / x->du;
        ll r = y->price.val[i] / y->du;
        if (l != r)
            return r - l;
    }
    return 0;
}

ll name_hash(char* name) 
{
    ll ret = 0;
    int i = 0;
    for (int i = 0; name[i]; i++)
        ret = ret * 27 + name[i] - 'a' + 1;
    return ret;
}

void init(int N, char mName[50][20], char mPrice[50][100], int mDuration[50]) 
{
    ITEM* p;
    index_count = 0;

    for (int i = 0; i < N; i++) 
    {
        p = &item[i];
        p->du = mDuration[i];
        p->name_id = name_hash(mName[i]);
        set_price(p, mPrice[i]);
        index_arr[index_count++] = &item[i];
    }
    sort(index_arr, index_count, sizeof(int) ,my_compare);
}

int find_item(char* name) 
{
    int i;
    ll h = name_hash(name);
    for (i = 0; i < index_count; i++)
        if (h == item[i].name_id)
            break;

    return i;
}

void priceChange(char mName[20], char mPrice[100]) 
{
    int idx = find_item(mName);
    set_price(&item[idx], mPrice);
    sort(index_arr, index_count, sizeof(int), my_compare);
}

int survivable(int day, BIGINT money) 
{
    ITEM* p;
    for(int i = 0; i < index_count; i++) 
    {
        p = index_arr[i];
        int q = (day + p->du - 1) / p->du;
        sub(&money, &p->price, q);
        if (i % 10 == 0) 
        {
            normalize(&money);
            if (money.val[BIGINTLEN - 1] < 0) 
                return 0;
        }
    }
    normalize(&money);
    return money.val[BIGINTLEN - 1] >= 0;
}

int daySurvivable(char mMoney[100]) 
{
    BIGINT total;
    set_val(&total, mMoney);
    int min = 0, max = 3000, mid;
    while (min < max) 
    {
        mid = (min + max + 1) >> 1;
        if (survivable(mid, total))
            min = mid;
        else
            max = mid - 1;
    }
    return min;
}
#endif