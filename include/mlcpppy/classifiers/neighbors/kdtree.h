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

#include <vector>
#include <queue>
#include <algorithm>
#include "nearest_neighbor.h"

template <typename T, int N>
class KDTree : public NearestNeighbor<T, N> {
private:
    class Node {
    public:
        Node* left_;
        Node* right_;
        Point<T, N> point_;
        int depth_;

        explicit Node() {}
        explicit Node(Point<T, N> point, Node* left, Node* right) : point_(point), left_(left), right_(right) {}
        explicit Node(Point<T, N> point, Node* left, Node* right, int depth) : point_(point), left_(left), right_(right), depth_(depth) {}
        explicit Node(Point<T, N> point) : point_(point) {
            this->left_ = nullptr;
            this->right_ = nullptr;
        }
        explicit Node(Point<T, N> point, int depth) : point_(point), depth_(depth) {
            this->left_ = nullptr;
            this->right_ = nullptr;
        }

        ~Node() {
            delete left_;
            delete right_;
        }
    };
    
    Node* root_;
    int K_;
    std::priority_queue<std::pair<double, Node*>> bests_;

    Node* Build(std::vector<Point<T, N>> points, int depth) {
        if (points.empty()) {
            return nullptr;
        }
        int k = points.at(0).data().size();
        int axis = depth % k;

        std::sort(points.begin(), points.end(), [axis](const Point<T, N>& a, const Point<T, N>& b) {
            return a.data()[axis] < b.data()[axis];
        });

        int median = points.size() / 2;
        std::vector<Point<T, N>> points_left(points.begin(), points.begin() + median);
        std::vector<Point<T, N>> points_right(points.begin() + median + 1, points.end());


        return new Node(
            points.at(median),
            Build(points_left, depth + 1),
            Build(points_right, depth + 1),
            depth
        );
    }


    Node* NearestNeighbor(Node* root, Point<T, N>& target, int depth) {
        if (root == nullptr) return nullptr;

        Node* next_branch;
        Node* other_branch;

        int axis = depth % root->point_.size();

        if (target.data().at(axis) < root->point_.data().at(axis))
        {
            next_branch = root->left_;
            other_branch = root->right_;
        } else {
            next_branch = root->right_;
            other_branch = root->left_;
        }

        Node* temp = NearestNeighbor(next_branch, target, depth + 1);
        Node* best = Closest(temp, root, target);
        double radius_squared = DistSquared(target, best->point_);

        double dist = target.data().at(axis) - root->point_.data().at(axis);

        if (radius_squared >= dist * dist)
        {
            temp = NearestNeighbor(other_branch, target, depth + 1);
            best = Closest(temp, best, target);
        }

        return best;

    }

    void KNearestNeighbor(Node* root, Point<T, N>& target, int depth) {
        if (root == nullptr) return;

        Node* next_branch;
        Node* other_branch;

        int axis = depth % root->point_.size();

        if (target.data().at(axis) < root->point_.data().at(axis))
        {
            next_branch = root->left_;
            other_branch = root->right_;
        } else {
            next_branch = root->right_;
            other_branch = root->left_;
        }

        KNearestNeighbor(next_branch, target, depth + 1);
        double dist = DistSquared(target, root->point_);

        if (this->bests_.size() < this->K_)
        {
            this->bests_.push({dist, root});
        }
        else if (dist < this->bests_.top().first)
        {
            bests_.pop();
            this->bests_.push({dist, root});
        }

        double diff = target.data().at(axis) - root->point_.data().at(axis);

        if (this->bests_.size() < this->K_ || diff * diff < this->bests_.top().first) {
            KNearestNeighbor(other_branch, target, depth + 1);
        }
    }
  

    Node* Closest(Node* n0, Node* n1, Point<T, N>& target) {
        if (n0 == nullptr) return n1;
        if (n1 == nullptr) return n0;

        long d1 = DistSquared(n0->point_, target);
        long d2 = DistSquared(n1->point_, target);

        if (d1 < d2)
            return n0;
        else
            return n1;
    }

    double DistSquared(const Point<T, N>& p0, const Point<T, N>& p1) {
        long total = 0;
        size_t numDims = p0.size();

        for (size_t i = 0; i < numDims; ++i) {
            int diff = std::abs(p0.data()[i] - p1.data()[i]);
            total += static_cast<double>(diff) * diff; // mais eficiente que pow para int
        }

        return total;
    }

    static void Inorder(Node* root) {
        if (!root) return;

        Inorder(root->left_);

        if (root->left_) {
            std::cout << "    \"";
            for (size_t i = 0; i < root->point_.size(); i++)
                std::cout << root->point_.data()[i] << (i + 1 == root->point_.size() ? "" : ",");
            std::cout << "\" -> \"";
            for (size_t i = 0; i < root->left_->point_.size(); i++)
                std::cout << root->left_->point_.data()[i] << (i + 1 == root->left_->point_.size() ? "" : ",");
            std::cout << "\" [label=\"esq\"];\n";
        }

        if (root->right_) {
            std::cout << "    \"";
            for (size_t i = 0; i < root->point_.size(); i++)
                std::cout << root->point_.data()[i] << (i + 1 == root->point_.size() ? "" : ",");
            std::cout << "\" -> \"";
            for (size_t i = 0; i < root->right_->point_.size(); i++)
                std::cout << root->right_->point_.data()[i] << (i + 1 == root->right_->point_.size() ? "" : ",");
            std::cout << "\" [label=\"dir\"];\n";
        }

        Inorder(root->right_);
    }

public:
    KDTree() : root_(nullptr) {}
    void Insert(Point<T, N> point) override {
        Node* p = this->root_;
        Node* prev = nullptr;

        int depth = 0;
        int n_dims = point.size();

        while (p != nullptr)
        {
            prev = p;
            if (point.data().at(depth) < p->point_.data().at(depth))
                p = p->left_;
            else
                p= p->right_;
            depth = (depth + 1) % n_dims;
        }

        if (this->root_ == nullptr)
            this->root_ = new Node(point);
        else if((point.data().at((depth - 1) % n_dims)) < (prev->point_.data().at((depth - 1) % n_dims)))
            prev->left_ = new Node(point, depth);
        else
            prev->right_ = new Node(point, depth);
    }

    void BuildTree(std::vector<Point<T, N>> points) override {
    if (points.empty())
        {
            return;
        }

        int initial_size = points.at(0).size();

        for (auto &point : points)
        {
            if (point.data().empty())
            {
                return;
            }

            if (point.size() != initial_size)
            {
                return;
            }


        }

        this->root_ = Build(points, 0);
    }
    
    
    std::vector<Point<T, N>> KNearestNeighbor(Point<T, N> target_points, int k) override {
        if (k)
            this->K_ = k;

        if (k == 1){
            Node* result = NearestNeighbor(this->root_, target_points, 0);
            std::vector<Point<T, N>> points;
            if (result)
            {
                points.push_back(result->point_);
            }
            return points;
        }

        KNearestNeighbor(this->root_, target_points, 0);
        std::vector<Point<T, N>> tmp;
        while (!this->bests_.empty())
        {
            tmp.push_back(this->bests_.top().second->point_);
            this->bests_.pop();
        }

        return tmp;
    }

  void PrintInorder() {
    // TODO: A ideia é isso gerar um arquivo para o graphiz gerar o grafo
    std::cout << "digraph G {\n";
    Inorder(this->root_);
    std::cout << "}\n";
  }

  ~KDTree() override {
    delete root_;
  }
};
#endif  // KDTREE_H