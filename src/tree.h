/* -----
 * Пользовательская библиотека, содержащая описание классов "дерево" и "узел дерева" для решения задачи задачи №3.
 ----- */

#include "cstdlib"
#include "iostream"
#include "ctime"
#include <string.h>

using namespace std;

/* Класс "узел" */
class node {

    char tag;
    node * left;
    node * right;
    public:
        node () : left (nullptr), right (nullptr) {
        }
        
        ~node () {
            if (left) delete left;
            if (right) delete right;
        }
    friend class tree;
    
};

/* Класс "дерево" */
class tree {

    node * root;
    char num, maxnum;
    int maxrow, offset;
    char ** SCREEN;

    tree (const tree &);
    tree operator = (const tree &) const;
    node* makeNode (int depth);
    void outNodes (node * v, int r, int c);
    void clrscr ();

    public:
        tree (char num, char maxnum, int maxrow);
        ~tree ();
        void makeTree () {
            root = makeNode(0);
        }
        void outTree ();
        bool exist () {
            return root != NULL;
        }
        int DFS ();
        int BFS ();

};

/* Конструктор дерева */
tree :: tree (char nm, char mnm, int mxr) : num(nm), maxnum(mnm), maxrow(mxr), offset(40), root(NULL) {

    SCREEN = new char *[maxrow];

    for (int i = 0; i < maxrow; ++i)
        SCREEN[i] = new char[80];

}

/* Деструктор дерева */
tree :: ~tree () {

    for (int i = 0; i < maxrow; ++i)
        delete[] SCREEN[i];

    delete[] SCREEN;
    delete root;

}

/* Функция создания  */
node * tree :: makeNode (int depth) {

    node * v = NULL;
    int Y = (depth < rand() % 6 + 1) && (num <= 'z');
    //int Y;
     //cout << "node (" <<num<< "," << depth << ")  1/0: " ; cin>> Y;
    if (Y) {	// создание узла, если Y = 1
        v = new node;
        v->left = makeNode(depth + 1);
        v->tag = num++;	 // Разметка во внутреннем порядке симметричном
        v->right = makeNode(depth + 1);
                 //v->d = num++;		// вариант — в обратном
    }

    return v;

}

/* Функция вывода дерева на экран */
void tree :: outTree () {

    clrscr ();
    outNodes (root, 1, offset);
    for (int i = 0; i < maxrow; ++i) {
        SCREEN[i][79] = 0;
        cout << "\n"<< SCREEN[i];
    }
    cout << "\n";

}

/* Функция инициализации точками массива для вывода */
void tree :: clrscr () {

    for (int i = 0; i < maxrow; ++i)
        memset (SCREEN[i], '.', 80);

}

/* Функция вывода узлов до заданной глубины */
void tree :: outNodes (node * v, int r, int c) {

    if (r && c && (c<80))
        SCREEN[r - 1][c - 1] = v->tag; // выводметки
    if (r < maxrow) {
        if (v->left)
            outNodes (v->left, r + 1, c - (offset >> r)); //левыйсын
        if (v->right)
            outNodes (v->right, r + 1, c + (offset >> r)); //правыйсын
    }

}

/* Шаблон для класса "стек" */
template <class item> class STACK {

    item * stack; 
    int size;

    public:
        STACK (int maxSize) {
            stack = new item[maxSize];
            size = 0;
        }
        int empty () const {
            return size == 0;
        }
        void push (item thing) {
            stack[size++] = thing;
        }
        item pop () {
            return (size ? stack[--size] : 0);
        }

};

/* Шаблон для класса "очередь" */
template <class item> class QUEUE {

    item * queue; 
    int location, size, maxSize;

    public:
        QUEUE (int maxSize) : location(0), size(0), maxSize(maxSize) {
            queue = new item[maxSize + 1];
        }
        int empty () const {
            return (location % maxSize) == size;
        }
        void put (item thing) {
            queue[size++] = thing;
            size %= maxSize;
        }
        item get () {
            location %= maxSize;
            return queue[location++];
        }

};

/* Функция нерекурсивного обхода дерева способом «в глубину» */
int tree :: DFS () {

    const int maxStackSize = 20;        // Максимальный размер стека
    int count = 0;

    STACK <node *> stack(maxStackSize); // Создание стека указателей на узлы
    stack.push (root);                  // Добавляем корень в стек

    while ( !stack.empty() ) {            // Пока стек не пуст
        node * currentNode = stack.pop(); // Подннимаем узел из стека
        cout << currentNode->tag << '_';  // Выдаём тег
        count++;                          // Считаем этот узел
        if (currentNode->right)
            stack.push(currentNode->right); // Добавляем в стек правого сына
        if (currentNode->left)
            stack.push(currentNode->left);  // Добавляем в стек левого сына
    }

    return count;

}

/* Функция нерекурсивного обхода дерева способом «в ширину» */
int tree :: BFS () {

     const int maxQueueSize = 20;        // Максимальный размер очереди
     int count = 0;

     QUEUE <node *> queue(maxQueueSize); // создание очереди указателей на узлы
     queue.put(root);                    // Добавляем корень в очередь

     while ( !queue.empty() ) {             // Пока очередь не пуста
         node * currentNode = queue.get();  // Берём узел из очереди
         cout << currentNode->tag << '_';   // Выдаём тег
         count++;                           // Считаем этот узел
         if (currentNode->left)
             queue.put(currentNode->left);  // Добавляем в очередь левого сына
         if (currentNode->right)
             queue.put(currentNode->right); // Добавляем в очередь правого сына
     }

     return count;

}