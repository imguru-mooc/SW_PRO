#if 0
#include <iostream>
using namespace std;
char* xstrchr(char* s, char c)
{
	while (*s != c && *s != 0) ++s;
	return *s != c ? NULL : s;
}
int main()
{
	char s[] = "abcdefg";
	char* p = xstrchr(s, 'z');
	if (p == NULL)
		cout << "찾을 수 없습니다." << endl;
	else 
		cout << p << endl;
}
#endif

#if 0
#include <iostream>
using namespace std;
char* xstrchr(char* first, char* last, char value)
{
	while (*first != value && first != last) ++first;
	return *first != value ? NULL : first;
}
int main()
{
	char s[] = "abcdefg";
	char* p = xstrchr(s, s+2 , 'c'); // "abc"에서 검색
	if (p == NULL) cout << "찾을수 없습니다." << endl;
	else cout << *p << endl;
}
#endif

#if 0
#include <iostream>
using namespace std;
template<typename T> T* xstrchr(T* first, T* last, T value)
{
	while (*first != value && first != last)
		++first;
	return *first != value ? NULL : first;
}
int main()
{
	double d[] = { 1,2,3,4,5,6,7,8,9,10 };
	double* p = xstrchr(d, d + 4, 5.0); // { 1,2,3,4,5 } 에서 검색
	cout << *p << endl;
	//double* p1 = xstrchr(d, d + 4, 5);
}
#endif

#if 0
#include <iostream>
using namespace std;
template<typename T1, typename T2>
T1 xfind(T1 first, T1 last, T2 value)
{
	while (*first != value && first != last) ++first;
	return *first != value ? NULL : first;
}
int main()
{
	double d[] = { 1,2,3,4,5,6,7,8,9,10 };
	double* p = xfind(d, d + 4, 5);
	cout << *p << endl;
}
#endif


#if 0
#include <iostream>
using namespace std;
template<typename T1, typename T2>
T1 xfind(T1 first, T1 last, T2 value)
{
	while (first != last && *first != value)
		++first;
	return first;
}
int main()
{
	double d[] = { 1,2,3,4,5,6,7,8,9,10 };
	double* p = xfind(d, d + 10, 10); // d+10, 즉 10은 검색에 포함되지 않음
	if (p == d + 10) cout << "찾을 수 없습니다." << endl;
	else cout << *p << endl;
}
#endif

#if 0
#include <iostream>
using namespace std;
template<typename T> struct Node
{
	T data;
	Node* next;
	Node(T a, Node* n) : data(a), next(n) {}
};
template<typename T> class slist
{
	Node<T>* head;
public:
	slist() : head(0) {}
	void push_front(const T& a) { head = new Node<T>(a, head); }
};
int main()
{
	slist<int> s;
	s.push_front(10);
	s.push_front(20);
	s.push_front(30);
	s.push_front(40);
	s.push_front(50);
}
#endif


#if 0
#include <iostream>
using namespace std;

template<typename T1, typename T2>
T1 xfind(T1 first, T1 last, T2 value)
{
	while (first != last && *first != value)
		++first;
	return first;
}

template<typename T> struct Node
{
	T data;
	Node* next;
	Node(T a, Node* n) : data(a), next(n) {}
};

template<typename T> class slist_iterator
{
	Node<T>* current;
public:
	slist_iterator(Node<T>*p = 0) : current(p) {}
	
	inline slist_iterator& operator++()
	{
		current = current->next;
		return *this;
	}
	inline T& operator*() { return current->data; }
	inline bool operator==(const slist_iterator& p)
	{
		return current == p.current;
	}
	inline bool operator!=(const slist_iterator& p)
	{
		return current != p.current;
	}
};

template<typename T> class slist
{
	Node<T>* head;
public:
	typedef slist_iterator<T> iterator;
	slist() : head(0) {}
	void push_front(const T& a) { head = new Node<T>(a, head); }
	iterator begin() { return iterator(head); }
	iterator end() { return iterator(0); }
};

int main()
{
	slist<int> s;
	s.push_front(10);
	s.push_front(20);
	s.push_front(30);
	slist<int>::iterator p1 = xfind(s.begin(), s.end(), 20);
	cout << *p1 << endl;
	
	slist<int>::iterator p2 = s.begin();
	while (p2 != s.end())
	{
		cout << *p2 << endl;
		++p2;
	}
}
#endif

#if 0
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
int main()
{
	string s = "hello";
	string::iterator p = s.begin();
	++p;
	cout << *p << endl; // 'e'
	reverse(s.begin(), s.end()); cout << s << endl; // "olleh"
	sort(s.begin(), s.end()); cout << s << endl; // ""
	list<int> st;
	st.push_front(10);
	st.push_front(20);
	st.push_front(30);
	reverse(st.begin(), st.end());
	list<int>::iterator p2 = st.begin();
	while (p2 != st.end())
	{
		cout << *p2 << endl;
		++p2;
	}
}
#endif

#if 0
#include <iostream>
#include <vector>
using namespace std;
int main()
{
	vector<int> v(5, 0);
	vector<int>::iterator p = v.begin();
	cout << *p << endl; 
}
#endif

#if 0
#include <iostream>
#include <vector>
using namespace std;
void main()
{
	vector<int> v(5, 0);
	vector<int>::iterator p = v.begin();
	cout << *p << endl;
	v.resize(10);
	p = v.begin();
	cout << *p << endl; // 오류. 무효화된 반복자
}
#endif

#if 0
#include <iostream>
#include <algorithm>
using namespace std;
void show(int n)
{
	cout << n << endl;
}
int main()
{
	int x[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	for_each(x, x + 10, show);
}

#endif

#if 0
#include <iostream>
#include <algorithm>
using namespace std;

template <typename T, typename F>
void my_for_each(T first, T last, F func)
{
	while (first != last)
	{
		func(*first);
		++first;
	}
}

void show(int n)
{
	cout << n << endl;
}
int main()
{
	int x[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	my_for_each(x, x + 10, show);
}

#endif


#if 0
#include <iostream>
#include <algorithm>
using namespace std;
int absolutePlus(int a, int b)
{
	return abs(a) + abs(b);
}
int main()
{
	int x[5] = { 1, 2, 3, 4, 5 };
	int y[5] = { -1, -2, -3, -4, -5 };
	int z[5];
	transform(x, x + 5, y, z, absolutePlus);
	copy(z, z + 5, ostream_iterator<int>(cout, " "));
}
#endif

#if 0
#include <iostream>
#include <algorithm>
using namespace std;
int absolutePlus(int a, int b)
{
	return abs(a) + abs(b);
}
int main()
{
	int x[5] = { 1, 2, 3, 4, 5 };
	int y[5] = { -1, -2, -3, -4, -5 };
	int z[5];
	transform(x, x + 5, y, z, absolutePlus);
	copy(z, z + 5, ostream_iterator<int>(cout, " "));
	//for (int i = 0; i < 5; i++)
	//	cout << z[i] << " ";
}
#endif

#if 0
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
template< typename T> struct Show
{
	ostream& out;
	string separator;
public:
	Show(ostream& os = cout, string sep = "\n") : out(os), separator(sep)
	{}
	void operator()(T n) const
	{
		out << n << separator;
    }
};
int main()
{
	int x[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	//Show<int> s;
	//s(1);
	ofstream f("a.txt");
	for_each(x, x + 10, Show<int>(f));
	ostringstream oss;
	for_each(x, x + 10, Show<int>(oss, " "));
	string s = oss.str();
	cout << s << endl;
}
#endif

#if 0
#include <iostream>
#include <functional>
#include <algorithm>
using namespace std;
int main()
{
	int x[5] = { 1, 2, 3, 4, 5 };
	int y[5] = { 6, 7, 8, 9, 10 };
	int s1[5], s2[5];
	transform(x, x + 5, y, s1, plus<int>());
	transform(x, x + 5, y, s2, minus<int>());
	copy(s1, s1 + 5, ostream_iterator<int>(cout, " "));
	cout << endl;
	copy(s2, s2 + 5, ostream_iterator<int>(cout, " "));
	cout << endl;
}
#endif

#if 0
#include <iostream>
#include <algorithm>
using namespace std;
struct IsOdd
{
public:
	bool operator()(int n) const
	{
		return ((n % 2) != 0);
	}
};
void main()
{
	int x[10] = { 1, 2, 3, 4, 3, 8, 3, 2, 5, 7 };
	int y[10] = { 1, 2, 3, 4, 3, 8, 3, 2, 5, 7 };
	int* px = remove(x, x + 10, 3); 
	int* py = remove_if(y, y + 10, IsOdd()); 
	copy(x, px, ostream_iterator<int>(cout, " "));
	cout << endl;
	copy(y, py, ostream_iterator<int>(cout, " "));
	cout << endl;
};
#endif

#if 1
#include <list>
#include <stack>
#include <queue>
#include <iostream>
using namespace std;

struct AbsGreater
{
	bool operator()(int a, int b)
	{
		return abs(a) < abs(b);
	}
};

int main()
{
	priority_queue<int, vector<int>, AbsGreater > pq;
	pq.push(10);
	pq.push(-5);
	pq.push(20);
	pq.push(30);
	pq.push(15);
	cout << pq.top() << endl;
	pq.pop();
	cout << pq.top() << endl;
}

#endif
















#if 0
#include <list>
#include <stack>
#include <queue>
#include <iostream>
using namespace std;

struct Greater
{
	bool operator()(int a, int b)
	{
		return a > b;
	}
};

#include <time.h>
int main()
{
	int i, j;
	clock_t start, end;

	priority_queue<int, vector<int>, Greater > pq;

	start = clock();
	for (i = 0; i < 1000; i++)
	{
		for (j = 0; j < 1000; j++)
			pq.push(i + 1);

		for (j = 0; j < 1000; j++)
			pq.pop();
	}
	end = clock();
	printf("%lu\n", end - start);
}

#endif


#if 0
#include <stdio.h>
typedef struct heap
{
	void* data[10000];
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

int my_compare(void* a, void* b)
{
	int ret = 0;
	int* x = (int*)a;
	int* y = (int*)b;

	ret = *x - *y;

	return ret;
}

int data[1000];

#include <time.h>
int main()
{
	int i, j;
	clock_t start, end;
	
	HEAP heap;
	heap.h_count = 0;

	start = clock();
	for (i = 0; i < 1000; i++)
	{
		for (j = 0; j < 1000; j++)
		{
			data[j] = i + 1;
			push(&heap, data + j, my_compare);
		}

		for (j = 0; j < 1000; j++)
			pop(&heap, my_compare);
	}
	end = clock();
	printf("%lu\n", end - start);
}

#endif