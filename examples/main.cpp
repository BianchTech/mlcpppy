#include <iostream>

#include "mlcpppy/classifiers/neighbors/kdtree.h"

int main(int argc, char const *argv[]) {
        double x, y;
        int k;
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

        std::vector<Point<double, 2>> points = {
            {1.0, 2.0}, {2.0, 1.0}, {3.0, 2.0}, {7.0, 4.0}, {5.0, 9.0},
            {6.0, 1.0}, {0.0, 3.0}, {4.0, 7.0}, {8.0, 2.0}, {3.0, 5.0}};

        auto tree = new KDTree<double, 2>();
        tree->BuildTree(points);
        tree->PrintInorder();

        std::vector<Point<double, 2>> points_knn =
            tree->KNearestNeighbor(Point<double, 2>({x, y}), k);

        for (size_t i = 0; i < points_knn.size(); ++i) {
                std::cout << "Point " << i << ": ";
                for (size_t j = 0; j < points_knn[i].size(); ++j) {
                        std::cout << points_knn[i].data().at(j) << " ";
                }
                std::cout << std::endl;
        }

        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;

        tree->Insert({x + 1, y - 1});
        tree->PrintInorder();

        return 0;
}
