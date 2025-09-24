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

template <typename T>
class RBTree {
       private:
        class Node {
               public:
                Node* left;
                Node* right;
                Node* parent;
                N value;
                int color;

                explict Node(N value) : value(value) {
                        this->left = nullptr;
                        this->right = nullptr;
                        this->parent = nullptr;
                }
        }

        Node* root;
        constexpr int BLACK = 0;
        constexpr int RED = 1;

       public:
        void Insert() {}

        void Remove() {}

        Node Search() const {}

        int Color(Node* node) {
                if (node != nullptr) {
                        return this->BLACK;
                } else {
                        return node->color;
                }
        }

        void ChangeColor(Node* node) {
                node->color = !node->color;
                if (node->left) node->left->color = !node->left->color;

                if (node->right) node->right->color = !node->right->color;
        }

        Node* RotateLeft(Node* A) {
                Node* B = A->right;
                A->right = B->left;
                B->left = A;
                B->color = A->color;
                A->color = this->RED;
                return B;
        }

        Node* RotateRight(Node* A) {
                Node* B = A->left;
                A->left = B->right;
                B->right = A;
                B->color = A->color;
                A->color = this->RED;
                return B;
        }

        Node* MoveToLeftRed(Node* node) {
                this->ChangeColor(node);
                if (this->Color(node->right->left) == this->RED) {
                        node->right = this->RotateRight(node->right);
                        node = this->RotateLeft(node);
                        this->ChangeColor(node);
                }
        }

        Node* MoveToRightRed(Node* node) {
                this->ChangeColor(node);
                if (this->Color(node->left->left) == this->RED) {
                        node = this->RotateRight(node);
                        this->ChangeColor(node);
                }
        }

        Node* BalanceTree(Node* node) {
                if (this->Color(node->right) == this->RED)
                        node = this->RotateLeft(node);

                if (node->left != nullptr &&
                    this->Color(node->right) == this->RED &&
                    this->Color(node->left->left) == this->RED)
                        node = this->RotateLeft(node);

                if (this->Color(node->left) == this->RED &&
                    this->Color(node->right) == this->RED)
                        this->ChangeColor(node);

                return node;
        }
};
