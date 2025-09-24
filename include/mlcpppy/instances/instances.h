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
#ifndef INSTANCES_H
#define INSTANCES_H

#include <vector>

#include "instance.h"

/**
 * @brief Represents a collection of Instance objects, similar to a dataset in
 * ARFF format.
 *
 * @note This class is still under development. Future features may include
 *       schema validation, type checking, and ARFF file loading.
 */
class Instances {
       private:
        std::vector<Instance>
            instances_data_;  ///< Container for all Instance objects

       public:
        /**
         * @brief Constructor that initializes the Instances collection.
         * @param instances Vector of Instance objects to initialize the
         * collection.
         */
        Instances(std::vector<Instance> instances)
            : instances_data_(instances) {}

        /**
         * @brief Overloads the stream insertion operator to print all
         * instances.
         * @param os Output stream.
         * @param instances The Instances object to print.
         * @return Reference to the output stream.
         */
        friend std::ostream& operator<<(std::ostream& os,
                                        const Instances& instances) {
                os << "[";
                for (size_t i = 0; i < instances.instances_data_.size(); ++i) {
                        os << instances.instances_data_[i];
                        if (i != instances.instances_data_.size() - 1)
                                os << ", \n";  // Comma between elements
                }
                os << "]";
                return os;
        }

        /**
         * @brief Default destructor.
         */
        ~Instances() = default;
};

#endif  // INSTANCES_H