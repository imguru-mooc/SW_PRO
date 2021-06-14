
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif


#include <stdio.h>

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
#define MALE   0
#define FEMALE 1

#define INIT         0
#define ADDMEMBER    1
#define GETDISTANCE  2
#define COUNTMEMBER  3

#define COUPLE  0
#define PARENT  1
#define CHILD   2

#define NAME_LEN_MAX 19

////////////////////////////////////////////////////////////////////////////////

extern void init(char initialMemberName[], int initialMemberSex);
extern bool addMember(char newMemberName[], int newMemberSex, int relationship, char existingMemberName[]);
extern int  getDistance(char nameA[], char nameB[]);
extern int  countMember(char name[], int dist);

////////////////////////////////////////////////////////////////////////////////

static int score = 0;

static void cmd_init()
{
    char initialMemberName[NAME_LEN_MAX + 1];
    int initialMemberSex;

    scanf("%s %d", initialMemberName, &initialMemberSex);

    init(initialMemberName, initialMemberSex);
}

static void cmd_addMember()
{
    char newMemberName[NAME_LEN_MAX + 1];
    int newMemberSex;
    int relationship;
    char existingMemberName[NAME_LEN_MAX + 1];

    scanf("%s %d %d %s", newMemberName, &newMemberSex, &relationship, existingMemberName);

    bool userAns = addMember(newMemberName, newMemberSex, relationship, existingMemberName);

    int ans;
    scanf("%d", &ans);
    bool ansbool = ans == 1 ? true : false;

    if (ansbool != userAns)
    {
        score = 0;
    }
}

static void cmd_getDistance()
{
    char nameA[NAME_LEN_MAX + 1];
    char nameB[NAME_LEN_MAX + 1];

    scanf("%s %s", nameA, nameB);

    int userAns = getDistance(nameA, nameB);

    int ans;
    scanf("%d", &ans);

    if (ans != userAns)
    {
        score = 0;
    }
}

static void cmd_countMember()
{
    char name[NAME_LEN_MAX + 1];
    int dist;

    scanf("%s %d", name, &dist);

    int userAns = countMember(name, dist);

    int ans;
    scanf("%d", &ans);

    if (ans != userAns)
    {
        score = 0;
    }
}

#include <time.h>
int main()
{
	clock_t start, end;

    setbuf(stdout, NULL);

    freopen("sample_input.txt", "r", stdin);

    int T, scoreIdx;
    scanf("%d %d", &T, &scoreIdx);

	start = clock();
    for (int TC = 1; TC <= T; TC++)
    {
        score = scoreIdx;

        int cmdL;
        scanf("%d", &cmdL);

        for (int cmdIdx = 0; cmdIdx < cmdL; ++cmdIdx)
        {
            int c_num;
            scanf("%d", &c_num);

            switch (c_num)
            {
            case INIT:
                cmd_init();
                break;

            case ADDMEMBER:
				
                cmd_addMember();
				
                break;

            case GETDISTANCE:
				
                cmd_getDistance();

                break;

            case COUNTMEMBER:
                cmd_countMember();
				end = clock();
                break;

            default:
                break;
            }
        }

        printf("#%d %d\n", TC, score == scoreIdx ? scoreIdx : 0);
    }
	printf("%lu\n", end - start);
	
    return 0;
}

#if 0

#define uint unsigned int
#define rint register int
#define MU 200
#define MH 500

struct NODE {
	int sex, parent, couple;
} NODEs[MU];
int NodeCount;

int Map[MU][MU], DisMap[MU][MU];

uint NameCode[MH];
int NameID[MH];

#define getCode(code,str)   for (rint i=0; str[i]; i++) code = (code << 5) + str[i] - 96;

void init(char name[], int sex) {
	NodeCount = 0;
	rint i, j;
	for (i = 0; i < MH; i++) {
		NameCode[i] = 0;
	}
	for (i = 0; i < MU; i++) {
		for (j = 0; j < MU; j++)
			Map[i][j] = -1;
	}
	for (i = 0; i < MU; i++) {
		for (j = 0; j < MU; j++)
			DisMap[i][j] = 0;
	}

	NODEs[NodeCount] = { sex, -1, -1 };

	register uint code = 0;
	getCode(code, name)
		NameCode[code % MH] = code;
	NameID[code % MH] = NodeCount++;
}

void update(int idN, int idE, int relation) {
	rint i;
	for (i = 0; i < idE; i++) {
		Map[idN][i] = Map[idE][i] + relation;
		DisMap[idN][Map[idN][i]]++;
		DisMap[i][Map[idN][i]]++;
	}
	Map[idN][idE] = relation;
	DisMap[idN][relation]++;
	DisMap[idE][relation]++;
	for (i = idE + 1; i < idN; i++) {
		Map[idN][i] = Map[i][idE] + relation;
		DisMap[idN][Map[idN][i]]++;
		DisMap[i][Map[idN][i]]++;
	}
}

bool addMember(char name[], int sex, int relationship, char existingName[]) {
	register uint codeE = 0;
	getCode(codeE, existingName)
		rint h = codeE % MH;
	while (NameCode[h] != codeE)
		h = (h + 1) % MH;
	int idE = NameID[h];

	NODE* nodeE = &NODEs[idE];

	if (relationship == 0) {
		if ((nodeE->sex == sex) || (nodeE->couple != -1))
			return 0;

		NODEs[NodeCount] = { sex, -1, idE };
		nodeE->couple = NodeCount;
		update(NodeCount, idE, 0);
	}
	else if (relationship == 1) {
		int idP = nodeE->parent;
		if (idP == -1) {
			NODEs[NodeCount] = { sex, -1, -1 };
			nodeE->parent = NodeCount;
			update(NodeCount, idE, 1);
		}
		else {
			NODE* nodeP = &NODEs[idP];
			if ((nodeP->sex == sex) || (nodeP->couple != -1))
				return 0;

			NODEs[NodeCount] = { sex, -1, idP };
			nodeP->couple = NodeCount;
			update(NodeCount, idP, 0);
		}
	}
	else {
		NODEs[NodeCount] = { sex, idE, -1 };
		update(NodeCount, idE, 1);
	}

	register uint code = 0;
	getCode(code, name)
		h = code % MH;
	while (NameCode[h])
		h = (h + 1) % MH;
	NameCode[h] = code;
	NameID[h] = NodeCount++;

	return 1;
}

int  getDistance(char nameA[], char nameB[]) {
	register uint code = 0;
	getCode(code, nameA)

		rint h = code % MH;
	while (NameCode[h] != code)
		h = (h + 1) % MH;
	int idA = NameID[h];

	code = 0;
	getCode(code, nameB)

		h = code % MH;
	while (NameCode[h] != code)
		h = (h + 1) % MH;
	int idB = NameID[h];

	return (idA > idB) ? Map[idA][idB] : Map[idB][idA];
}

int  countMember(char name[], int dist) {
	register uint code = 0;
	getCode(code, name)

		rint h = code % MH;
	while (NameCode[h] != code)
		h = (h + 1) % MH;

	return DisMap[NameID[h]][dist];
}

#endif


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

//--------------------------------------------------------------------------------------
char* my_strcpy(char* dest, char* src)
{
	char* tmp = dest;

	while ((*dest++ = *src++) != '\0')
		/* nothing */;
	return tmp;
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
//-----------------------------------------------------------------------

typedef  unsigned long long u64;
#define  MAX_POOL 200 
#define  MAX_HASH 32

u64 str_hash(const char* str)
{
	u64 res = 0ULL;
	int i;

	for (i = 0; *str; i++)
	{
		res = (res << 2) + (*str - 'a' + 1);
		str++;
	}

	return res;
}

typedef struct member
{
	int id;
	u64 name_id;
	char name[20];
	int  sex;
	struct member* parent;
	struct member* couple;
	NODE name_hash_list;
} MEMBER;

MEMBER  member_pool[MAX_POOL];
int member_count;

NODE name_hash_heads[MAX_HASH];

int map[MAX_POOL][MAX_POOL];
int dist_map[MAX_POOL][MAX_POOL];

MEMBER* alloc_member(char name[], int sex)
{
	MEMBER* p;
	p = &member_pool[member_count];
	p->id = member_count++;
	p->name_id = str_hash(name);
	my_strcpy(p->name, name);
	p->sex = sex;
	p->parent = 0;
	p->couple = 0;
	
	list_add_tail(&p->name_hash_list, &name_hash_heads[p->name_id % MAX_HASH]);
	return p;
}

void init(char name[], int sex)
{
	int i,j;
	MEMBER* p;

	member_count = 0;

	for (i = 0; i < MAX_HASH; i++)
		INIT_LIST_HEAD(&name_hash_heads[i]);

	p = alloc_member(name, sex);

	for (i = 0; i < MAX_POOL; i++)
	{
		for (j = 0; j < MAX_POOL; j++)
		{
			map[i][j] = -1;
			dist_map[i][j] = 0;
		}
	}
}

MEMBER* findMemberByName(char name[])
{
	NODE* temp;
	MEMBER* p;
	u64 name_id;

	name_id = str_hash(name);
	list_for_each(temp, &name_hash_heads[name_id % MAX_HASH])
	{
		p = list_entry(temp, MEMBER, name_hash_list);
		if (p->name_id == name_id)
		{
			if( my_strcmp( p->name, name) == 0 )
				return p;
		}
	}
	return 0;
}

void update(int id_new, int id_exist, int relation) {
	int i;
	for (i = 0; i < id_exist; i++) {
		map[id_new][i] = map[id_exist][i] + relation;
		dist_map[id_new][map[id_new][i]]++;
		dist_map[i][map[id_new][i]]++;
	}

	map[id_new][id_exist] = relation;
	dist_map[id_new][relation]++;
	dist_map[id_exist][relation]++;

	for (i = id_exist + 1; i < id_new; i++) {
		map[id_new][i] = map[i][id_exist] + relation;
		dist_map[id_new][map[id_new][i]]++;
		dist_map[i][map[id_new][i]]++;
	}
}

bool addMember(char newMemberName[], int newMemberSex, int relationship, char existingMemberName[])
{
	MEMBER* p;
	MEMBER* newMember;

	p = findMemberByName(existingMemberName);

	if (relationship == 0)
	{
		if (p->sex == newMemberSex || p->couple)
			return 0;

  	    newMember = alloc_member(newMemberName, newMemberSex);
		newMember->couple = p;
		p->couple = newMember;
		update(newMember->id, p->id, 0);
	}
	else if (relationship == 1)
	{
		if (p->parent == 0)
		{
			newMember = alloc_member(newMemberName, newMemberSex);
			p->parent = newMember;
			update(newMember->id, p->id, 1);
		}
		else 
		{
			if (p->parent->sex == newMemberSex || p->parent->couple)
				return 0;

			newMember = alloc_member(newMemberName, newMemberSex);
			p->parent->couple = newMember;
			newMember->couple = p->parent;
			update(newMember->id, p->parent->id, 0);
		}
	}
	else 
	{
		newMember = alloc_member(newMemberName, newMemberSex);
		newMember->parent = p;
		update(newMember->id, p->id, 1);
	}
	return 1;
}

int getDistance(char start[], char end[])
{
	int ret;
	int s_id, e_id;

	s_id = findMemberByName(start)->id;
	e_id = findMemberByName(end)->id;
	ret = (s_id > e_id) ? map[s_id][e_id] : map[e_id][s_id];
	return ret;
}

int countMember(char name[], int n)
{
	int ret;
	int id;

	id = findMemberByName(name)->id;
	ret = dist_map[id][n];
	return ret;
}

#endif

