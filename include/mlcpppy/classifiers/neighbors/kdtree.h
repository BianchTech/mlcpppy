/*
 * Copyright (C) 2025  Pedro Bianchini de Quadros
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#ifndef KDTREE_H
#define KDTREE_H

#include <queue>
#include <vector>

#include "nearest_neighbor.h"

template <typename T = double, size_t N = 3>
class KDTree : public NearestNeighbor<T, N> {
       private:
        using PointType = typename NearestNeighbor<T, N>::PointType;
        class Node;
        Node *root_;
        int K_;
        std::priority_queue<std::pair<double, Node *>> bests_;

        Node *Build(std::vector<PointType> points, int depth);
        Node *NearestNeighbor(Node *root, const PointType &target, int depth);
        void KNearestNeighbor(Node *root, const PointType &target, int depth);

        Node *Closest(Node *n0, Node *n1, const PointType &target);
        double DistSquared(const PointType &p0, const PointType &p1);
        static void Inorder(Node *root);

       public:
        KDTree();
        void Insert(const PointType &point) override;
        void BuildTree(const std::vector<PointType> &points) override;
        std::vector<PointType> KNearestNeighbor(const PointType &target_points,
                                                int k) override;
        void PrintInorder();

        ~KDTree() override;
};
#endif  // KDTREE_H