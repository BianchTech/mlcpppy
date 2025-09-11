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
#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H
#include <string>
#include <variant>
#include <vector>

class Attribute
{
public:
    using ValueType = std::variant<int, double, float, std::string>;
    Attribute(int v) : value(v) {}
    Attribute(double v) : value(v) {}
    Attribute(const std::string& v) : value(v) {}
    const ValueType& getValue() const { return value; }
    ~Attribute();
private:
    /* data */
    ValueType value;
};

#endif // ATTRIBUTE_H