#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

typedef enum {
    INIT,
    ADD,
    DELETE,
    CHANGE,
    GETCOUNT
} COMMAND;

extern void init();
extern void addEvent(int uid, char ename[], int groupid);
extern int deleteEvent(int uid, char ename[]);
extern int changeEvent(int uid, char ename[], char cname[]);
extern int getCount(int uid);

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

static int mSeed;
static int pseudo_rand(void)
{
    mSeed = mSeed * 431345 + 2531999;
    return mSeed & 0x7FFFFFFF;
}

static void make_string(char str[], int seed)
{
    mSeed = seed;
    int length = 5 + pseudo_rand() % 10;
    for (int i = 0; i < length; ++i) {
        str[i] = 'a' + pseudo_rand() % 26;
    }
    str[length] = 0;
}

static int run()
{
    int answer = 100;

    int cmd, p1, p2, p3, p4;
    char str1[15], str2[15];

    int N, ret, flag;
    scanf("%d %d %d", &cmd, &N, &flag);

    init();

    for (int i = 1; i < N; ++i) {
        scanf("%d", &cmd);
        switch (cmd) {
        case ADD:
            if (flag == 1) {
                scanf("%d %s %d", &p1, str1, &p3);
            }
            else {
                scanf("%d %d %d", &p1, &p2, &p3);
                make_string(str1, p2);
            }
            addEvent(p1, str1, p3);
            break;

        case DELETE:
            if (flag == 1) {
                scanf("%d %s %d", &p1, str1, &p3);
            }
            else {
                scanf("%d %d %d", &p1, &p2, &p3);
                make_string(str1, p2);
            }
            ret = deleteEvent(p1, str1);
            if (ret != p3)
                answer = 0;
            break;

        case CHANGE:
            if (flag == 1) {
                scanf("%d %s %s %d", &p1, str1, str2, &p4);
            }
            else {
                scanf("%d %d %d %d", &p1, &p2, &p3, &p4);
                make_string(str1, p2);
                make_string(str2, p3);
            }
            ret = changeEvent(p1, str1, str2);
            if (ret != p4)
                answer = 0;
            break;

        case GETCOUNT:
            scanf("%d %d", &p1, &p2);
            ret = getCount(p1);
            if (ret != p2)
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
    clock_t start, end;
    setbuf(stdout, NULL);
    freopen("sample_input.txt", "r", stdin);

    int T;
    scanf("%d", &T);

    start = clock();
    for (int tc = 1; tc <= T; tc++) {
        printf("#%d %d\n", tc, run());
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

void my_strcpy(char* dst, char* src)
{
    while (*dst++ = *src++)
        ;
}

int my_strcmp(const char* cs, const char* ct)
{
    unsigned char c1, c2;

    while (1) {
        c1 = *cs++;
        c2 = *ct++;
        if (c1 != c2)
            return c1 < c2 ? -1 : 1;
        if (!c1)
            break;
    }
    return 0;
}

//-------------------------------------------------------------------------------

#define MAX_USER 1000
#define MAX_GROUP 100
#define MAX_BUF 50000
#define MAX_HASH 1024

typedef struct
{
    int gid;
    NODE master_list_head;
} GROUP;

typedef struct
{
    int uid;
    int gid;
    int key;
    char ename[20];
    int is_master;
    NODE member_list_head;
    NODE list;
    NODE hash_list;
} EVENT;

NODE  hash_table[MAX_HASH];
GROUP group_pool[MAX_GROUP];
EVENT event_pool[MAX_BUF];

int event_pool_count;
int num_event_of_user[MAX_USER];

int hash_str(const char* str)
{
    int i;
    int hx = 0;

    for (i = 0; str[i]; ++i) 
    {
        hx = (hx << 1) + str[i] - 'a' + 1;
    }
    return hx;
}


void init()
{
    int i;

    event_pool_count = 0;

    for (i = 0; i < MAX_GROUP; i++)
    {
        INIT_LIST_HEAD(&group_pool[i].master_list_head);
    }

    for (i = 0; i < MAX_HASH; i++)
    {
        INIT_LIST_HEAD(&hash_table[i]);
    }

    for (i = 0; i < MAX_USER; i++)
    {
        num_event_of_user[i] = 0;
    }
}

void addEvent(int uid, char ename[], int groupid)
{
    NODE* temp1;
    NODE* temp2;
    EVENT* event = 0, * master = 0;
    int flag = 0;

    event = &event_pool[event_pool_count++];
    event->uid = uid;
    event->gid = groupid;
    event->key = hash_str(ename);
    my_strcpy(event->ename, ename);
    INIT_LIST_HEAD(&event->member_list_head);
    list_add_tail(&event->hash_list, &hash_table[event->key%MAX_HASH]);

    list_for_each(temp1, &group_pool[groupid].master_list_head)
    {
        master = list_entry(temp1, EVENT, list);
        if (event->key == master->key && 
            !my_strcmp(event->ename, master->ename))
        {
            flag = 1;
            break;
        }
    }

    if (flag == 1)
    {
        list_add_tail(&event->list, &master->member_list_head);
        event->is_master = 0;
    }
    else
    {
        list_add_tail(&event->list, &group_pool[groupid].master_list_head);
        event->is_master = 1;
    }
    num_event_of_user[uid]++;
}

int getCount(int uid)
{
    return num_event_of_user[uid];
}

EVENT* find_event(int uid, int key, char ename[])
{
    NODE* temp;
    EVENT* event;

    list_for_each(temp, &hash_table[key%MAX_HASH])
    {
        event = list_entry(temp, EVENT, hash_list);
        if (event->uid == uid && event->key == key &&
            !my_strcmp(event->ename, ename))
            return event;
    }
    return 0;
}

int deleteEvent(int uid, char ename[])
{
    int count = 0;
    NODE* temp;
    NODE* n;
    EVENT* member;
    EVENT* event;
    int key;

    key = hash_str(ename);
    while (1)
    {
        event = find_event(uid, key, ename);
        if (event == 0)
            break;

        if (event->is_master == 1)
        {
            list_for_each_safe(temp, n, &event->member_list_head)
            {
                count++;
                member = list_entry(temp, EVENT, list);
                list_del(&member->list);
                list_del(&member->hash_list);
                num_event_of_user[member->uid]--;
            }
        }
        count++;
        list_del(&event->list);
        list_del(&event->hash_list);
        num_event_of_user[event->uid]--;
    }

    return count;
}

int changeEvent(int uid, char ename[], char cname[])
{
    int count = 0;
    NODE* temp;
    NODE* n;
    EVENT* member;
    int e_key, c_key;
    EVENT* event;

    c_key = hash_str(cname);
    e_key = hash_str(ename);

    while (1)
    {
        event = find_event(uid, e_key, ename);
        if (event == 0)
            break;

        if (event->is_master == 1)
        {
            list_for_each_safe(temp, n, &event->member_list_head)
            {
                count++;
                member = list_entry(temp, EVENT, list);
                
                my_strcpy(member->ename, cname);
                member->key = c_key;
                list_del(&member->hash_list);
                list_add_tail(&member->hash_list, &hash_table[c_key % MAX_HASH]);
            }
            count++;
            my_strcpy(event->ename, cname);
            event->key = c_key;
            list_del(&event->hash_list);
            list_add_tail(&event->hash_list, &hash_table[c_key % MAX_HASH]);
        }
        else
        {
            count++;
            my_strcpy(event->ename, cname);
            event->key = c_key;
            list_del(&event->hash_list);
            list_add_tail(&event->hash_list, &hash_table[c_key % MAX_HASH]);
            event->is_master = 1;
            list_del(&event->list);
            list_add_tail(&event->list, &group_pool[event->gid].master_list_head);
        }
    }

    return count;
}
#endif

