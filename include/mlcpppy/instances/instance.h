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
#ifndef INSTANCE_H
#define INSTANCE_H

#include <iostream>
#include <vector>

#include "attribute.h"

/**
 * @brief Represents a single instance consisting of multiple Attribute objects.
 *
 * @note This class is still under development. Future features may include
 *       schema validation, type checking, and integration with ARFF datasets.
 */
class Instance {
       private:
        std::vector<Attribute>
            values_instance_;  ///< Container for the attributes of this
                               ///< instance

       public:
        Instance() {}


        /**
         * @brief Constructs an Instance with a variable number of Attribute
         * arguments.
         *
         * @tparam Args Variadic template parameter representing Attribute
         * types.
         * @param args Attributes to include in this instance.
         */
        template <typename... Args>
        Instance(Args... args) {
                values_instance_ = {args...};
        }

        /**
         * @brief Overloads the stream insertion operator to print all
         * attributes in the instance.
         * @param os Output stream.
         * @param inst The Instance object to print.
         * @return Reference to the output stream.
         */
        friend std::ostream& operator<<(std::ostream& os,
                                        const Instance& inst) {
                os << "[";
                for (size_t i = 0; i < inst.values_instance_.size(); ++i) {
                        os << inst.values_instance_[i];
                        if (i != inst.values_instance_.size() - 1)
                                os << ", ";  // Comma between elements
                }
                os << "]";
                return os;
        }
};

#endif  // INSTANCE_H