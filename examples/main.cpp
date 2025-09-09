#include <iostream>
#include "mlcpppy/classifiers/neighbors/kdtree.h"

int main(int argc, char const *argv[])
{
    int x, y, k;
    if (argc < 4) {
        std::cerr << "Uso: " << argv[0] << " <x> <y> <k>\n";
        x = 7;
        y = 4;
        k = 2;
        // return 1;
    } else {
        x = std::atoi(argv[1]);
        y = std::atoi(argv[2]);
        k = std::atoi(argv[3]);
    }

    std::vector<std::vector<int>> points = {
        {1, 2},
        {2, 1},
        {3, 2},
        {7, 4},
        {5, 9},
        {6, 1},
        {0, 3},
        {4, 7},
        {8, 2},
        {3, 5}
    };

    auto tree = new KDTree();
    tree->BuildTree(points);
    tree->PrintInorder();

    std::vector<std::vector<int>> points_knn = tree->KNearestNeighbor({x, y}, k);

    for (size_t i = 0; i < points_knn.size(); ++i) {
        std::cout << "Point " << i << ": ";
        for (size_t j = 0; j < points_knn[i].size(); ++j) {
            std::cout << points_knn[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    tree->Insert({x+1, y-1});
    tree->PrintInorder();

    return 0;
}
