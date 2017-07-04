/* -----
 * Пользовательская библиотека, содержащая описание классов "дерево" и "узел" для решения задачи задачи №3.
 ----- */

#include "iostream"

using namespace std;

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
    friend class tree; // Дружественный класс "дерево"
    
};

/* Класс "дерево" */
class tree {

    node * root;
    char num;           // Счётчик тэгов
    char maxnum;        // Максимальный тэг
    int maxrow;         // Максимальная глубина
    int offset;         // Смещение корня
    char ** SCREEN;     // Матрица для вывода дерева на экран

    tree (const tree &);                    // Фиктивный конструктор копии
    tree operator = (const tree &&) const;  // Оператор присваивания с переносом
    node* makeNode (int depth);             // Создание поддрева
    void outNodes (node * v, int r, int c); // Выдача поддрева
    void clrscr ();     // Очистка матрицы вывода

    public:
        tree (char num, char maxnum, int maxrow);
        ~tree ();
        void makeTree () {        // Генерация дерева
            root = makeNode(0);
        }
        void outTree ();          // Вывод дерева на экран
        bool exist () {           // Проверка дерева на пустоту
            return root != NULL;
        }
        int BFS ();               // Обход дерева "в ширину"

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

/* Функция создания поддрева  */
node * tree :: makeNode (int depth) {

    node * currentNode = NULL;                                  // Создаваемый узел
    bool createNode = (depth < rand() % 6 + 1) && (num <= 'z'); // Случайно создаём или не создаём узел

    if (createNode) {
        currentNode = new node;
        currentNode->left = makeNode(depth + 1);  // Рекурсивно генерируем левое поддрево
        currentNode->tag = num++;                 // Размечаем во внутреннем порядке (симметричном)
        currentNode->right = makeNode(depth + 1); // Рекурсивно генерируем правое поддрево
    }

    return currentNode;

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

/* Функция инициализации (очистки) массива для вывода */
void tree :: clrscr () {

    for (int i = 0; i < maxrow; ++i)
        for (int j = 0; j < 80; ++j)
            SCREEN[i][j]=' ';

}

/* Функция занесения поддрева в матрицу вывода */
void tree :: outNodes (node * currentNode, int row, int column) {

    if (row && column && (column < 80))
        SCREEN[row - 1][column - 1] = currentNode->tag;                       // Вывод метки обрабатываемого узла
    if (row < maxrow) {
        if (currentNode->left)
            outNodes (currentNode->left, row + 1, column - (offset >> row));  // Рекурсивная обработка левого поддрева с учетом сдвига для следующего уровня
        if (currentNode->right)
            outNodes (currentNode->right, row + 1, column + (offset >> row)); // Рекурсивная обработка правого поддрева с учетом сдвига для следующего уровня
    }

}

/* Функция нерекурсивного обхода дерева способом «в ширину» */
int tree :: BFS () {

     const int maxQueueSize = 20;        // Максимальный размер очереди
     int count = 0;

     QUEUE <node *> queue(maxQueueSize); // Создание очереди указателей на узлы
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