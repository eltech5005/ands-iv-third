/* -----
 * Вариант: 5
 * Вид дерева: Двоичное
 * Разметка: Симметричная
 * Способ обхода: В ширину
 * Задание: Количество вершин, имеющих не более одного потомка.
 ----- */

#include <iostream>
#include <time.h>
#include <stdlib.h>

#include <src/tree.h>

using namespace std;

int main(int argc, char **argv) {

    int n = 0;
    Tree Tr('a', 'z', 8);
    srand(time(NULL));
    setlocale(LC_ALL, "Russian");
    Tr.MakeTree();
    if (Tr.exist()) {
        Tr.OutTree();
        cout << "\n" << "Deep walk: ";
        n = Tr.DFS();
        cout << " Nodes passed = " << n;
        cout << "\n" << "Weight walk: ";
        n = Tr.BFS();
        cout << " Nodes passed = " << n;
    }
        else 
        cout << "Tree is empty!";
        cout << "\n" << "=== END ===";
        
    return 0;
}
