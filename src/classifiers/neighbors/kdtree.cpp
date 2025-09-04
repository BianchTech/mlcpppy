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

#include "mlcpppy/classifiers/neighbors/kdtree.h"
#include <algorithm>
#include <iostream>

class KDTree::Node {
public:
    Node* left_;
    Node* right_;
    std::vector<int> point_;

    explicit Node() {}
    explicit Node(std::vector<int> point, Node* left, Node* right) : point_(point), left_(left), right_(right) {}
    ~Node() {
        delete left_;
        delete right_;
    }
};

KDTree::Node* KDTree::Build(std::vector<std::vector<int>> points, int depth) {
    
    if (points.empty()) {
        return nullptr;
    }
    int k = points.at(0).size();
    int axis = depth % k;

    std::sort(points.begin(), points.end(), [axis](const std::vector<int>& a, const std::vector<int>& b) {
        return a[axis] < b[axis];
    });

    int median = points.size() / 2;
    std::vector<std::vector<int>> points_left(points.begin(), points.begin() + median);
    std::vector<std::vector<int>> points_right(points.begin() + median + 1, points.end());
    

    return new Node(
        points.at(median), 
        Build(points_left, depth + 1),
        Build(points_right, depth + 1)
    );
}

KDTree::KDTree() : root(nullptr) {}

void KDTree::Insert(std::vector<int> point) {}

void KDTree::BuildTree(std::vector<std::vector<int>> points) {
    if (points.empty())
    {
        return;
    }
    
    int k = 0;
    int initial_size = points.at(0).size();

    for (auto &point : points)
    {
        if (point.empty())
        {
            return;
        }
        
        if (point.size() != initial_size)
        {
            return;
        }
        
        
    }
    
    this->root = Build(points, 0);
}



std::vector<std::vector<int>> KDTree::KNearestNeighbor(std::vector<int> target_points, int k) {
    return std::vector<std::vector<int>>();
}

void KDTree::Inorder(Node* root) {
    if (!root) return;

    // chama o filho esquerdo
    Inorder(root->left_);

    // imprime as conexões do nó atual
    if (root->left_) {
        std::cout << "    \"";
        for (size_t i = 0; i < root->point_.size(); i++)
            std::cout << root->point_[i] << (i + 1 == root->point_.size() ? "" : ",");
        std::cout << "\" -> \"";
        for (size_t i = 0; i < root->left_->point_.size(); i++)
            std::cout << root->left_->point_[i] << (i + 1 == root->left_->point_.size() ? "" : ",");
        std::cout << "\";\n";
    }

    if (root->right_) {
        std::cout << "    \"";
        for (size_t i = 0; i < root->point_.size(); i++)
            std::cout << root->point_[i] << (i + 1 == root->point_.size() ? "" : ",");
        std::cout << "\" -> \"";
        for (size_t i = 0; i < root->right_->point_.size(); i++)
            std::cout << root->right_->point_[i] << (i + 1 == root->right_->point_.size() ? "" : ",");
        std::cout << "\";\n";
    }

    // chama o filho direito
    Inorder(root->right_);
}

void KDTree::PrintInorder() {
    std::cout << "digraph G {\n";
    Inorder(this->root);
    std::cout << "}\n";
}


KDTree::~KDTree() { delete root; }
