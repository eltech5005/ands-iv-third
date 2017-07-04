/* -----
 * Вариант: 5
 * Вид дерева: Двоичное
 * Разметка: Симметричная
 * Способ обхода: В ширину
 * Задание: Количество вершин, имеющих не более одного потомка.
 ----- */

#define SCREEN_WIDTH 80
#define SCREEN_OFFSET 40

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <src/tree.h>

using namespace std;

int main (int argc, char **argv) {

    srand(time(NULL));

    /* Переменная для посчёта количества узлов */
    int nodesCount = 0;

    /* Генерируем дерево с тегами узлов от 'a' до 'z'
     * максимальной высоты 8 */
    tree processTree ('a', 'z', 8);
    processTree.makeTree();

    for (int i=0; i < SCREEN_OFFSET-10; ++i) cout << " "; cout << "Generated tree:\n";
    for (int i=0; i < SCREEN_WIDTH; ++i) cout << "-"; cout << endl;

    if ( processTree.exist() ) {

        processTree.outTree();
        for (int i=0; i < SCREEN_WIDTH; ++i) cout << "-"; cout << endl;
        
        cout << " \"Width\" walk: "; nodesCount = processTree.BFS();
        cout << "\n Target nodes = " << nodesCount << endl;

    } else {
        cout << "\n\n\n";
        for (int i=0; i < SCREEN_OFFSET-10; ++i) cout << " "; cout << "Tree is empty! \n";
    }

    for (int i=0; i < SCREEN_WIDTH/2 - 5; ++i) cout << "-";
    cout << " End ";
    for (int i=0; i < SCREEN_WIDTH/2; ++i) cout << "-";

    return 0;
}
