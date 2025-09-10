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
#ifndef NEAREST_NEIGHBOR_H
#define NEAREST_NEIGHBOR_H
#include <vector>
#include "point.h"

template<typename T, int N>
class NearestNeighbor {
 public:
  virtual ~NearestNeighbor() = default;
  virtual std::vector<Point<T, N>> KNearestNeighbor(Point<T, N>, int) = 0;
  virtual void Insert(Point<T, N>) = 0;
  virtual void BuildTree(std::vector<Point<T, N>>) = 0;
  virtual void Delete(Point<T, N>){};
};
#endif  // NEAREST_NEIGHBOR_H