#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

// API Command
#define CMD_INIT        100
#define CMD_ADDWORD     200
#define CMD_REMOVEWORD  300
#define CMD_SEARCHWORD  400

// User Implement API
extern void init(void);
extern void addWord(char str[]);
extern int  removeWord(char str[]);
extern int  searchWord(char str[]);

#define STRLEN_MAX 6

static int run(int score)
{
    int queryCnt;
    scanf("%d", &queryCnt);

    for (int q = 0; q < queryCnt; ++q)
    {
        int cmd;
        scanf("%d", &cmd);

        if (cmd == CMD_INIT)
        {
            init();
        }
        else if (cmd == CMD_ADDWORD)
        {
            char str[STRLEN_MAX + 1];
            scanf("%s", str);

            addWord(str);
        }
        else if (cmd == CMD_REMOVEWORD)
        {
            char str[STRLEN_MAX + 1];
            scanf("%s", str);

            int userAns = removeWord(str);

            int ans;
            scanf("%d", &ans);

            if (userAns != ans)
            {
                score = 0;
            }
        }
        else if (cmd == CMD_SEARCHWORD)
        {
            char str[STRLEN_MAX + 1];
            scanf("%s", str);

            int userAns = searchWord(str);

            int ans;
            scanf("%d", &ans);

            if (userAns != ans)
            {
                score = 0;
            }
        }
    }
    return score;
}

#include <time.h>
int main(void)
{
    clock_t start, end;
    setbuf(stdout, NULL);

    freopen("sample_input.txt", "r", stdin);

    int TC;
    int targetScore;
    scanf("%d %d", &TC, &targetScore);

    start = clock();
    for (int testcase = 1; testcase <= TC; ++testcase)
    {
        int score = run(targetScore);
        printf("#%d %d\n", testcase, score);
    }
    end = clock();
    printf("%lu\n", end - start);

    return 0;
}

#if 1

#define list_entry(ptr, type, member)     \
((type*)((char*)ptr - (char*)&((type*)0)->member))

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
char* my_strcpy(char* dest, char* src)
{
    char* tmp = dest;

    while ((*dest++ = *src++) != '\0')
        /* nothing */;
    return tmp;
}

size_t my_strlen(const char* s)
{
    const char* sc;

    for (sc = s; *sc != '\0'; ++sc)
        /* nothing */;
    return sc - s;
}
//-----------------------------------------------------------------------

typedef struct
{
    char word[10];
    NODE list;
} WORD;

NODE word_list;
WORD word_pool[50000];
int  word_count;


void init(void)
{
    word_count = 0;
    INIT_LIST_HEAD(&word_list);
}

void addWord(char str[])
{
    WORD* w;

    w = &word_pool[word_count++];
    my_strcpy(w->word, str);
    list_add_tail(&w->list, &word_list);
}

int match(char word[], int w, char str[], int s)
{
    int word_len;
    int str_len;

    word_len = my_strlen(word);
    str_len = my_strlen(str);

    if (w < word_len && s < str_len && word[w] == str[s])
        return match(word, w + 1, str, s + 1);

    if (w == word_len && s == str_len)
        return 1;

    if (str[s] == '*')
        if (match(word, w, str, s + 1) || (w < word_len && match(word, w + 1, str, s)))
            return 1;

    return 0;
}

int removeWord(char str[])
{
    int count = 0;
    NODE * temp, * n;

    WORD* w;

    list_for_each_safe(temp, n, &word_list)
    {
        w = list_entry(temp, WORD, list);
        if (match(w->word, 0, str, 0))
        {
            list_del(temp);
            count++;
        }
    }
    return count;
}


int searchWord(char str[])
{
    int count = 0;
    NODE* temp;

    WORD* w;

    list_for_each(temp, &word_list)
    {
        w = list_entry(temp, WORD, list);
        if (match(w->word, 0, str, 0))
        {
            count++;
        }
    }
    return count;
}
#endif



#if 0
struct Node {
    int cnt;
    int endCnt;
    Node* alphabet[26];
    Node* parent;
};

Node node[600002];

int nodeCnt;
int result;
Node* head;
Node* rhead;

Node* getAlphabet() {
    node[nodeCnt].endCnt = node[nodeCnt].cnt = 0;
    node[nodeCnt].parent = nullptr;
    for (register int i = 0; i < 26; ++i) {
        node[nodeCnt].alphabet[i] = nullptr;
    }
    return &node[nodeCnt++];
}

void reserveStr(char a[], char b[], int len) {
    int j = len;
    for (int i = 0; i < len; i++) {
        a[--j] = b[i];
    }
    a[len] = '\0';
}

int mstrcmp(const char a[], const char b[]);
void mstrcpy(char dest[], const char src[]);
int mstrlen(const char a[]);


void init(void)
{
    nodeCnt = 0;
    head = getAlphabet();
    rhead = getAlphabet();
}

void addWord2Node(Node* tmp, char str[]) {
    if (*str == '\0')
    {
        tmp->endCnt++;
        return;
    }
    tmp->cnt++;
    int index = *str - 'a';
    if (tmp->alphabet[index])
    {
        addWord2Node(tmp->alphabet[index], (str + 1));
    }
    else
    {
        tmp->alphabet[index] = getAlphabet();
        tmp->alphabet[index]->parent = tmp;
        addWord2Node(tmp->alphabet[index], str + 1);
    }
}
void addWord(char str[])
{
    int length = mstrlen(str);
    addWord2Node(head, str);

    char rstr[7];
    reserveStr(rstr, str, length);
    addWord2Node(rhead, rstr);
}

int calculate_searchword(Node* st, const char* str, bool isRemove = false) {
    int res = 0;
    if (*str == '\0')
    {
        res = st->endCnt;
        if (isRemove)
        {
            st->endCnt = 0;
            register Node* tmp = st->parent;
            while (tmp)
            {
                tmp->cnt -= res;
                tmp = tmp->parent;
            }
        }
        return res;
    }

    if (*str != '*')
    {
        int index = *str - 'a';
        if (st->alphabet[index])
        {
            res += calculate_searchword(st->alphabet[index], str + 1, isRemove);
        }
    }
    else
    {
        if (*(str + 1) == '\0')
        {
            res = st->endCnt + st->cnt;
            if (isRemove)
            {
                st->endCnt = 0;
                st->cnt = 0;
                for (register int i = 0; i < 26; i++)
                {
                    st->alphabet[i] = nullptr;
                }
                register Node* tmp = st->parent;
                while (tmp)
                {
                    tmp->cnt -= res;
                    tmp = tmp->parent;
                }
            }
        }
        else
        {
            for (register int i = 0; i < 26; i++)
            {
                if (st->alphabet[i])
                {
                    if (i == *(str + 1) - 'a')
                    {
                        res += calculate_searchword(st->alphabet[i], str + 2, isRemove);
                    }
                    res += calculate_searchword(st->alphabet[i], str, isRemove);
                }
            }
        }
    }
    return res;
}

int removeWord(char str[])
{
    if (str[0] == '*' && str[1] == '\0') {
        int result = head->cnt;
        init();
        return result;
    }
    int isWildCard = -1;
    int length = 0;
    char rstr[7];

    for (int i = 0; str[i]; ++i) {
        if (str[i] == '*') {
            isWildCard = i;
        }
        ++length;
    }
    reserveStr(rstr, str, length);

    calculate_searchword(head, str, true);
    return calculate_searchword(rhead, rstr, true);
}

int searchWord(char str[])
{
    if (str[0] == '*' && str[1] == '\0')
        return head->cnt;
    int wildCard = -1;
    int length = 0;

    for (int i = 0; str[i]; ++i) {
        if (str[i] == '*') {
            wildCard = i;
        }
        ++length;
    }
    char rstr[7];
    reserveStr(rstr, str, length);

    if (wildCard >= length / 2) {
        return calculate_searchword(head, str);
    }
    return calculate_searchword(rhead, rstr);
}


int mstrcmp(const char a[], const char b[])
{
    int i;
    for (i = 0; a[i] != '\0'; ++i) if (a[i] != b[i]) return a[i] - b[i];
    return a[i] - b[i];
}

void mstrcpy(char dest[], const char src[])
{
    int i = 0;
    while (src[i] != '\0') { dest[i] = src[i]; i++; }
    dest[i] = src[i];
}

int mstrlen(const char a[])
{
    int i;
    for (i = 0; a[i] != '\0'; ++i);
    return i;
}

#endif


#if 0
#define rint register int
#define NULL 0
const int ALPHABET_SIZE = 26;
enum SEARCH_OPT { COUNT = 0, REMOVE = 1 };

int mstrlen(const char* str) {
    rint len = 0;
    while (str[len]) {
        ++len;
    }
    return len;
}

int mstrcmp(const char* s1, const char* s2) {
    while (*s1 == *s2 && *s2)
        ++s1, ++s2;
    return (*s1 - *s2);
}

int mstrcpy(char* dst, const char* src) {
    rint i = 0;
    for (; src[i]; ++i) dst[i] = src[i];
    dst[i] = src[i];
    return i;
}
void reverseWord(char* dst, const char* src, int len) {
    for (int i = 0, j = len - 1; i < len; i++, j--) {
        dst[j] = src[i];
    }
    dst[len] = NULL;
}

struct Trie {
    Trie* parent;
    int word;
    int cn;
    int cwds;

    struct Trie* c[ALPHABET_SIZE];
};
Trie pool[50000 * 5];
int pn = 0;

struct Trie* getNode(Trie* parent) {
    struct Trie* p = &pool[pn++];
    p->word = p->cwds = p->cn = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        p->c[i] = NULL;
    p->parent = parent;
    return p;
}

int removeWordInTrie(Trie* p) {
    int cnt_removed = p->word;
    if (cnt_removed > 0) {
        p->word = 0;
        for (p = p->parent; p != NULL; p = p->parent) {
            p->cwds -= cnt_removed;
        }
    }
    return cnt_removed;
}

char postfix[10];
int cmp_len = 0;
int word_cnt = 0;
int depth = 0;

void dfsTrie(Trie* p, const char* cmp_str, int search_opt = COUNT) {
    if (p->word > 0 && depth >= cmp_len) {
        if (cmp_len == 0 || 0 == mstrcmp(cmp_str, &postfix[depth - cmp_len])) {
            if (search_opt == COUNT)
                word_cnt += p->word;
            else
                word_cnt += removeWordInTrie(p);
        }

    }
    if (p->cwds == 0)
        return;
    for (rint i = 0, rem = p->cn; i < ALPHABET_SIZE && rem > 0; ++i) {
        if (p->c[i] != NULL) {
            postfix[depth++] = 'a' + i;
            postfix[depth] = NULL;
            dfsTrie(p->c[i], cmp_str, search_opt);
            postfix[--depth] = NULL;
            --rem;
        }
    }
}

int countOrRemoveTrie(Trie* mid, char* cmp_str, int search_opt = COUNT) {
    if (mid == NULL) {
        return 0;
    }

    if (*cmp_str == NULL) {
        if (search_opt == COUNT) {
            return mid->word;
        }
        else {
            return removeWordInTrie(mid);
        }
    }
    else if (*cmp_str == '*' && *(cmp_str + 1) == NULL && search_opt == COUNT) {
        return mid->word + mid->cwds;
    }
    else {
        ++cmp_str;
        cmp_len = mstrlen(cmp_str);
        postfix[0] = NULL;
        word_cnt = depth = 0;
        dfsTrie(mid, cmp_str, search_opt);
        return word_cnt;
    }
}

void insertTrie(Trie* root, const char* str) {
    register Trie* p = root;

    for (rint i = 0; str[i]; i++) {
        int idx = str[i] - 'a';
        if (p->c[idx] == NULL) {
            p->c[idx] = getNode(p);
            p->cn++;
        }
        p->cwds++;

        p = p->c[idx];
    }
    p->word++;
    int a = 1;
}

Trie* searchTrie(Trie* root, const char* str) {
    register Trie* p = root;
    rint i;
    for (i = 0; str[i] != NULL && str[i] != '*'; i++) {
        int idx = str[i] - 'a';
        if (p->c[idx] == NULL) {
            return NULL;
        }
        p = p->c[idx];
    }
    return p;
}

Trie* head_trie, * tail_trie;

//////////////////////////////////////////////////////////////

void init() {
    pn = 0;
    head_trie = getNode(NULL);
    tail_trie = getNode(NULL);
}

void addWord(char str[]) {
    insertTrie(head_trie, str);
    int len = mstrlen(str);

    char tail_str[10];
    reverseWord(tail_str, str, len);
    insertTrie(tail_trie, tail_str);
    int a = 1;
}

int searchWord(char str[]) {
    int len = mstrlen(str);
    int head_len = 0;

    while (str[head_len] != '*' && str[head_len] != NULL) {
        head_len++;
    }
    int tail_len = len == head_len ? len : len - head_len - 1;

    if (head_len >= tail_len) {
        Trie* p = searchTrie(head_trie, str);
        return countOrRemoveTrie(p, &str[head_len], COUNT);
    }
    else {
        char tail_str[10];
        reverseWord(tail_str, str, len);

        Trie* p = searchTrie(tail_trie, tail_str);
        return countOrRemoveTrie(p, &tail_str[tail_len], COUNT);
    }
}

int removeWord(char str[]) {
    int len = mstrlen(str);
    int head_len = 0;
    while (str[head_len] != '*' && str[head_len] != NULL) head_len++;
    int tail_len = len == head_len ? len : len - head_len - 1;

    Trie* p;
    p = searchTrie(head_trie, str);
    int cnt1 = countOrRemoveTrie(p, &str[head_len], REMOVE);

    char tail_str[10];
    reverseWord(tail_str, str, len);
    p = searchTrie(tail_trie, tail_str);
    int cnt2 = countOrRemoveTrie(p, &tail_str[tail_len], REMOVE);
    return cnt2;
}
#endif