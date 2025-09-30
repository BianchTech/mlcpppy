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

#include "../types.h"

/**
 * @brief Represents a single attribute that can hold multiple types of values.
 *
 * @note This class is still under development. Future features may include
 *       better type introspection, validation, and integration with Instances
 * and ARFF loading.
 */
class Attribute {
       public:
        /**
         * @brief Constructs an Attribute with an int value.
         * @param v The integer value to store.
         */
        Attribute(const ValueType& v) : value(v) {}

        /**
         * @brief Returns a constant reference to the stored value.
         * @return The stored value as a ValueType.
         */
        const ValueType& GetValue() const { return value; }

        /**
         * @brief Overloads the stream insertion operator to print the attribute
         * value and type.
         * @param os Output stream.
         * @param a The Attribute object to print.
         * @return Reference to the output stream.
         */
        friend std::ostream& operator<<(std::ostream& os, const Attribute& a) {
                std::visit(
                    [&os](auto&& arg) {
                            os << arg << "(" << typeid(arg).name() << ")";
                    },
                    a.GetValue());
                return os;
        }

        /**
         * @brief Default destructor.
         */
        ~Attribute() = default;

       private:
        ValueType value;  ///< Internal storage for the attribute's value
};

#endif  // ATTRIBUTE_H