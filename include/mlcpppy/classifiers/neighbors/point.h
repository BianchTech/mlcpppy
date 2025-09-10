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
#ifndef POINT_H
#define POINT_H

#include <array>
#include <initializer_list>
#include <stdexcept>
#include <type_traits>

template <typename T = double, int N = 3,
          typename =
              typename std::enable_if<std::is_floating_point<T>::value>::type>
class Point {
       private:
        std::array<T, N> data_;

       public:
        explicit Point() : data_{} {}
        explicit Point(const std::array<T, N> &data) : data_(data) {}
        inline Point(std::initializer_list<T> list) {
                if (list.size() != N) {
                        throw std::invalid_argument(
                            "Initializer list size must match Point dimension");
                }
                std::copy(list.begin(), list.end(), data_.begin());
        }
        const std::array<T, N> &data() const { return data_; }
        const size_t size() const {
                return data_.size();
        }
};

#endif // POINT_H