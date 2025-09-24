#include "mlcpppy/data_structures/binary_tree.h"

int main(int argc, char const* argv[]) {
        BinaryTree<int>* binary_tree = new BinaryTree<int>();
        // Isso deixa desbalanceado
        // 20, 8, 22, 4, 12, 10, 14

        binary_tree->Insert(20);
        binary_tree->Insert(8);
        binary_tree->Insert(22);
        binary_tree->Insert(4);
        binary_tree->Insert(12);
        binary_tree->Insert(10);
        binary_tree->Insert(14);

        binary_tree->TreeSuccessor();

        binary_tree->Inorder();

        BinaryTree<int>::Node* busca = binary_tree->Search(8);
        if (busca) {
                binary_tree->Delete(busca);
        }

        binary_tree->Inorder();

        return 0;
}
