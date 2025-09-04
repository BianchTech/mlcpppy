#include <iostream>
#include "mlcpppy/classifiers/neighbors/kdtree.h"

int main(int argc, char const *argv[])
{
    std::vector<std::vector<int>> points = {
        {1, 2, 3},
        {2, 1, 3},
        {3, 2, 1},
        {7, 4, 0},
        {5, 9, 2},
        {6, 1, 8},
        {0, 3, 5},
        {4, 7, 6},
        {8, 2, 9},
        {3, 5, 7}
    };

    auto tree = new KDTree();
    tree->BuildTree(points);
    tree->PrintInorder();
    return 0;
}
