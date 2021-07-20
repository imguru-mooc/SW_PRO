#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CMD_INIT			1
#define CMD_OPENACCOUNT		2
#define CMD_CLOSEACCOUNT	3
#define CMD_SENDBYNUMBER	4
#define CMD_SENDBYNAME		5
#define CMD_SENDBONUS		6

#define MAX_NAME_LEN (4+1)


extern void init();
extern void openAccount(int mTime, char mName[MAX_NAME_LEN], char mGroup[MAX_NAME_LEN], int mNumber, int mAsset);
extern int closeAccount(int mTime, int mNumber);
extern int sendByNumber(int mTime, int mNumber, int mReceiveNumber, int mValue);
extern int sendByName(int mTime, int mNumber, char mReceiveName[MAX_NAME_LEN], int mValue);
extern void sendBonus(int mTime, char mGroup[MAX_NAME_LEN], int mValue);

static bool run()
{
    int Q;
    int cmd, mNumber, mAsset, mReceiveNumber, mValue;
    char mName[MAX_NAME_LEN], mReceiveName[MAX_NAME_LEN], mGroup[MAX_NAME_LEN];

    int ret = 0;
    int ans = 0;
    scanf("%d", &Q);
    bool okay = false;

    for (int mTime = 0; mTime < Q; ++mTime)
    {
        scanf("%d", &cmd);

        switch (cmd)
        {
        case CMD_INIT:
            init();
            okay = true;
            break;
        case CMD_OPENACCOUNT:
            scanf("%s %s %d %d", mName, mGroup, &mNumber, &mAsset);
            if (okay)
                openAccount(mTime, mName, mGroup, mNumber, mAsset);
            break;
        case CMD_CLOSEACCOUNT:
            scanf("%d", &mNumber);
            if (okay)
                ret = closeAccount(mTime, mNumber);
            scanf("%d", &ans);
            if (ret != ans)
                okay = false;
            break;
        case CMD_SENDBYNUMBER:
            scanf("%d %d %d", &mNumber, &mReceiveNumber, &mValue);
            if (okay)
                ret = sendByNumber(mTime, mNumber, mReceiveNumber, mValue);
            scanf("%d", &ans);
            if (ret != ans)
                okay = false;
            break;
        case CMD_SENDBYNAME:
            scanf("%d %s %d", &mNumber, mReceiveName, &mValue);
            if (okay)
                ret = sendByName(mTime, mNumber, mReceiveName, mValue);
            scanf("%d", &ans);
            if (ret != ans)
                okay = false;
            break;
        case CMD_SENDBONUS:
            scanf("%s %d", mGroup, &mValue);
            if (okay)
                sendBonus(mTime, mGroup, mValue);
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

typedef unsigned long long u64;

u64  hash_str(char *str)                          
{            
    u64 hx=0;
	int idx;                                                                        
	for (idx = 0; str[idx]; ++idx)           
		hx = (hx*27) + str[idx] - 'a' + 1; 

    return hx;
}


#define MAX_NAME_LEN    (4+1)

#define MAX_ACCOUNT_VALUE   100000
#define MAX_ACCOUNT_COUNT   30000
#define MAX_GROUP           20

#define NUM_ALPHA           26
#define MAX_HASHED_VALUE    531441      // (26+1)^4

#define NULL            0

struct Customer;

typedef struct Account
{
    Customer* customer;
    int groupIdx;
    int num;
    int asset;
    NODE clist;
    NODE glist;
}Account;

typedef struct Customer
{
    NODE account_head;
    NODE group_heads[MAX_GROUP + 1];
}Customer;

int group_hash[MAX_HASHED_VALUE];     // 531441
int group_count;

Customer customer_pool[MAX_ACCOUNT_COUNT];       // 30000
int customer_count;

Customer* customer_hash[MAX_HASHED_VALUE];      // 531441

Account account_pool[MAX_ACCOUNT_COUNT];         // 30000
int account_count;
Account* account_hash[MAX_ACCOUNT_VALUE + 1];   // 100000

void init() 
{
    int i;
    group_count = 0;
    customer_count = 0;
    account_count = 0;

    for ( i = 0; i < MAX_HASHED_VALUE; ++i)
    {
        group_hash[i] = 0;
        customer_hash[i] = 0;
    }

    for ( i = 1; i <= MAX_ACCOUNT_VALUE; ++i)
    {
        account_hash[i] = 0;
    }
}

void openAccount(int mTime, char mName[MAX_NAME_LEN], char mGroup[MAX_NAME_LEN], int mNumber, int mAsset) 
{
    int i;
    u64 n_hash = hash_str(mName);
    u64 g_hash = hash_str(mGroup);
    Customer* customer;
    int group_index;

    if (group_hash[g_hash] == 0)
    {
        group_hash[g_hash] = ++group_count;
    }

    group_index = group_hash[g_hash];


    account_hash[mNumber] = &account_pool[account_count++];

    Account* temp = account_hash[mNumber];

    customer = customer_hash[n_hash];
    if (!customer)
    {
        customer_hash[n_hash] = &customer_pool[customer_count++];
        customer = customer_hash[n_hash];
        INIT_LIST_HEAD(&customer->account_head);
        

        for (i = 1; i <= MAX_GROUP; ++i)
        {
            INIT_LIST_HEAD(&customer->group_heads[i]);
        }
    }

    temp->customer = customer;
    temp->groupIdx = group_index;
    temp->num = mNumber;
    temp->asset = mAsset;

    list_add(&temp->clist, &customer->account_head);
    list_add(&temp->glist, &customer->group_heads[group_index]);
}

int closeAccount(int mTime, int mNumber) {
    Account* temp = account_hash[mNumber];

    list_del(&temp->clist);
    list_del(&temp->glist);
    account_hash[mNumber] = 0;

    return temp->asset;
}

int sendByNumber(int mTime, int mNumber, int mReceiveNumber, int mValue) {
    Account* from_acc;
    Account* to_acc;

    if ((from_acc = account_hash[mNumber]) == 0)
        return -1;

    if ((to_acc = account_hash[mReceiveNumber]) == 0)
        return -1;

    if (from_acc->asset < mValue)
        return -1;

    from_acc->asset -= mValue;
    if (from_acc->customer->account_head.next != &from_acc->clist)
    {
        list_del(&from_acc->clist);
        list_add(&from_acc->clist, &from_acc->customer->account_head);
    }

    if (from_acc->customer->group_heads[from_acc->groupIdx].next != &from_acc->glist)
    {
        list_del(&from_acc->glist);
        list_add(&from_acc->glist, &from_acc->customer->group_heads[from_acc->groupIdx]);
    }

    to_acc->asset += mValue;
    if (to_acc->customer->account_head.next != &to_acc->clist)
    {
        list_del(&to_acc->clist);
        list_add(&to_acc->clist, &to_acc->customer->account_head);
    }

    if (to_acc->customer->group_heads[to_acc->groupIdx].next != &to_acc->glist)
    {
        list_del(&to_acc->glist);
        list_add(&to_acc->glist, &to_acc->customer->group_heads[to_acc->groupIdx]);
    }

    return to_acc->asset;
}

int sendByName(int mTime, int mNumber, char mReceiveName[MAX_NAME_LEN], int mValue) {
    NODE* temp;
    Account* account;
    u64 n_hash = hash_str(mReceiveName);

    if (!customer_hash[n_hash])
        return -1;

    temp = customer_hash[n_hash]->account_head.next;
    account = list_entry(temp, Account, clist);
    return sendByNumber(mTime, mNumber, account->num, mValue);
}

void sendBonus(int mTime, char mGroup[MAX_NAME_LEN], int mValue) 
{
    int i;
    Account* account;
    NODE* temp;
    u64 g_hash = hash_str(mGroup);
    int group_index = group_hash[g_hash];

    for (i = 0; i < customer_count; ++i)
    {
        if (list_empty(&customer_pool[i].group_heads[group_index]))
            continue;

        temp = customer_pool[i].group_heads[group_index].next;
        if (temp)
        {
            account = list_entry(temp, Account, glist);
            account->asset += mValue;

            if (account->customer->account_head.next != &account->clist)
            {
                list_del(&account->clist);
                list_add(&account->clist, &account->customer->account_head);
            }
        }
    }
}

#endif


