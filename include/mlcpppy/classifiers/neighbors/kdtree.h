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
#include "nearest_neighbor.h"

class KDTree : public NearestNeighbor {
 private:
  class Node;
  Node* root_;
  int K_;
  std::priority_queue<std::pair<double, Node*>> bests_;

  Node* Build(std::vector<std::vector<int>> points, int depth);
  Node* NearestNeighbor(Node* root, std::vector<int>& target, int depth);
  void KNearestNeighbor(Node* root, std::vector<int>& target, int depth);

  Node* Closest(Node* n0, Node* n1, std::vector<int>& target);
  double DistSquared(const std::vector<int>& p0, const std::vector<int>& p1);
  static void Inorder(Node* root);

 public:
  KDTree();
  void Insert(std::vector<int> point) override;
  void BuildTree(std::vector<std::vector<int>> points) override;
  std::vector<std::vector<int>> KNearestNeighbor(std::vector<int> target_points, int k) override;
  void PrintInorder();

  ~KDTree() override;
};
#endif  // KDTREE_H