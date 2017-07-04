/* -----
 * Пользовательская библиотека, содержащая описание классов "дерево" и "узел дерева" для решения задачи задачи №3.
 ----- */

#include "cstdlib"
#include "iostream"
#include "ctime"
#include <string.h>
//#include "queue"
//#include "stack"

using namespace std;

//Класс «узел дерева»
class Node{ char d;	 //тегузла
Node * lft;	// левый сын
Node  * mdl;	//средний сын (если нужно)
Node * rgt;	// правыйсын
public:
    Node() { lft = nullptr; mdl = nullptr; rgt = nullptr; } // конструкторузла
    ~Node() {
        if (lft) delete lft; // деструктор (уничтожаетподдерево)
        if (mdl) delete mdl;
        if (rgt) delete rgt;
    }
    friend class Tree;	// дружественныйкласс «дерево»
};

// Класс «дерево в целом»
class Tree
{ Node * root;	// указатель на корень дерева
char num, maxnum;		//счётчик тегов и максимальный тег
int maxrow, offset;		//максимальная глубина, смещение корня
char ** SCREEN;	// память для выдачи на экран
void clrscr();	// очистка рабочей памяти
Node* MakeNode(int depth);	// создание поддерева
void OutNodes(Node * v, int r, int c); // выдача поддерева
Tree(const Tree &);	// фиктивный конструктор копии
Tree operator = (const Tree &) const;	// фиктивное присваивание
 
public:
    Tree(char num, char maxnum, int maxrow);//конструктор пустого дерева
    ~Tree();
    
    void MakeTree() {root = MakeNode(0);}// ввод — генерация дерева
    
    bool exist() { return root != NULL; } // проверка «дерево не пусто»
    
    int DFS();	// обходы дерева
    
    int BFS();
    
    void OutTree();	// выдача на экран
};

Tree :: Tree(char nm, char mnm, int mxr) : num(nm), maxnum(mnm), maxrow(mxr), offset(40), root(NULL)
{
    SCREEN = new char *[maxrow];
    for (int i = 0; i<maxrow; i++) SCREEN[i] = new char[80];
}

Tree :: ~Tree() {
    for (int i = 0; i<maxrow; i++) delete[]SCREEN[i];
    delete[]SCREEN; delete root;
}

Node * Tree::MakeNode(int depth)
{
    Node * v = NULL;
    int Y = (depth < rand() % 6 + 1) && (num <= 'z');
    //int Y;
     //cout << "Node (" <<num<< "," << depth << ")  1/0: " ; cin>> Y;
    if (Y) {	// создание узла, если Y = 1
        v = new Node;
        v->d = num++;	 // разметка в прямом порядке (= «в глубину»)
        v->lft = MakeNode(depth + 1);
                 //v->d = num++;          //вариант — во внутреннем
        v->mdl = MakeNode(depth + 1);
        v->rgt = MakeNode(depth + 1);
                 //v->d = num++;		// вариант — в обратном
    }
    return v;
}

void Tree::OutTree()
{
    clrscr();
    OutNodes(root, 1, offset);
    for (int i = 0; i<maxrow; i++)
    {
        SCREEN[i][79] = 0;
        cout << "\n"<< SCREEN[i];
    }
    cout << "\n";
}

void Tree::clrscr()
{
    for (int i = 0; i<maxrow; i++)
        memset(SCREEN[i], '.', 80);
}

void Tree::OutNodes(Node * v, int r, int c)
{
    if (r && c && (c<80)) SCREEN[r - 1][c - 1] = v->d; // выводметки
    if (r <maxrow) {
        if (v->lft) OutNodes(v->lft, r + 1, c -(offset >> r)); //левыйсын
        if (v->mdl) OutNodes(v->mdl, r+1, c);	//— средний сын (если нужно)
        if (v->rgt) OutNodes(v->rgt, r + 1, c + (offset >> r)); //правыйсын
    }
}

template<class Item> class STACK
{
    Item * S; int t;
public:
    STACK(int maxt)
    {
        S = new Item[maxt]; t = 0;
    }
    int empty() const { return t == 0; }
    void push(Item item) { S[t++] = item; }
    Item pop() { return (t ? S[--t] : 0); }
};

 int Tree:: DFS()
{
    const int MaxS = 20; //максимальныйразмерстека
    int count = 0;
    STACK <Node *> S(MaxS);  //создание стека указателей на узлы
    S.push(root); // QUEUE <- v
    while (!S.empty()) //Пока стек не пуст…
    {
        Node * v = S.pop(); // поднять узел из стека
        cout << v->d << '_'; count++;       // выдать тег, счёт узлов
        if (v->rgt) S.push(v->rgt); // STACK <- (правыйсын)
        if (v->mdl) S.push(v->mdl);
        if (v->lft) S.push(v->lft); // STACK <- (левыйсын)
    }
    return count;
}

 template <class Item> class QUEUE
 {
     Item * Q; int h, t, N;
 public:
     QUEUE(int maxQ) : h(0), t(0), N(maxQ) { Q = new Item[maxQ + 1]; }
     int empty()const { return (h % N) == t; }
     void put(Item item) { Q[t++] = item; t %= N; }
     Item get() { h %= N; return Q[h++]; }
 };

 int Tree::BFS()
 {
     const int MaxQ = 20; //максимальный размер очереди
     int count = 0;
     QUEUE <Node *> Q(MaxQ);  //создание очереди указателей на узлы
     Q.put(root); // QUEUE <- root поместить в очередь корень дерева 
     while (!Q.empty()) //пока очередь не пуста
     {
         Node * v = Q.get();// взять из очереди,
         cout << v->d << '_'; count++; // выдать тег, счёт узлов 
         if (v->lft) Q.put(v->lft); // QUEUE <- (левыйсын)
         if (v->mdl) Q.put(v->mdl);
         if (v->rgt) Q.put(v->rgt); // QUEUE <- (правыйсын)
     }
     return count;
 }
