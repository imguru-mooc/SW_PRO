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
	char* p = xstrchr(s, 'c');
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
	char* p = xstrchr(s, s + 2, 'c'); // "abc"에서 검색
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
	double* p = xfind(d, d + 9, 10); // d+9, 즉 10은 검색에 포함
	// 되지 않음
	if (p == d + 9) cout << "찾을 수 없습니다." << endl;
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
	vector<int>::iterator p = v.end();
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
		return abs(a) > abs(b);
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
