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

#include <iostream>

template <typename N>
class BinaryTree {
       public:
        class Node {
               public:
                N key;
                Node* left;
                Node* right;
                Node* p;  // -> Refere-se ao pai

                Node(N key) : key(key){};
        };

        BinaryTree() { this->root = nullptr; };

        void Insert(N new_key) {
                Node* y = nullptr;
                Node* x = this->root;
                Node* z = new Node(new_key);

                while (x) {
                        y = x;
                        if (z->key < x->key)
                                x = x->left;
                        else
                                x = x->right;
                }

                // Ponteiro para o pai
                z->p = y;

                if (y == nullptr)
                        this->root = z;
                else if (z->key < y->key)
                        y->left = z;
                else
                        y->right = z;
        }

        void Delete(Node* z) {
                if (z->left == nullptr)
                        this->Transplant(z, z->right);
                else if (z->right == nullptr)
                        this->Transplant(z, z->left);
                else {
                        Node* y = Minimum(z->right);
                        if (y->p != z) {
                                this->Transplant(y, y->right);
                                y->right = z->right;
                                y->right->p = y;
                        }

                        this->Transplant(z, y);
                        y->left = z->left;
                        y->left->p = y;
                }
        }

        void Inorder() const {
                InorderRecursive(this->root);
                std::cout << std::endl;
        }

        Node* Search(N key) { return this->TreeSearch(this->root, key); }

        Node* Minimum(Node* x) const {
                while (x->left != nullptr) x = x->left;
                return x;
        }

        Node* Maximum(Node* x) const {
                while (x->right != nullptr) x = x->right;
                return x;
        }

        Node* TreeSuccessor(Node* x) const {
                if (x->right) return Minimum(x->right);

                // O y vai receber o pai do x
                Node* y = x->p;
                while (y && x == y->right) {
                        x = y;
                        y = y->p;
                }

                return y;
        }

        Node* TreePredecessor(Node* x) const {
                if (x->left) return Maximum(x->left);

                // O y vai receber o pai do x
                Node* y = x->p;
                while (y && x == y->left) {
                        x = y;
                        y = y->p;
                }

                return y;
        }

        Node* TreeSuccessor() { return TreeSuccessor(this->root); }

        ~BinaryTree() = default;

       private:
        Node* root;

        void InorderRecursive(Node* root) const {
                if (root) {
                        InorderRecursive(root->left);
                        std::cout << root->key << std::endl;
                        std::cout << "Pai: ";
                        if (root->p) {
                                std::cout << root->p->key << std::endl;
                        } else {
                                std::cout << "Sem pai" << std::endl;
                        }
                        InorderRecursive(root->right);
                }
        }

        Node* TreeSearch(Node* root, N k) {
                if (root == nullptr || k == root->key) {
                        return root;
                }

                if (k < root->key) return TreeSearch(root->left, k);
                return TreeSearch(root->right, k);
        }

        void Transplant(Node* u, Node* v) {
                if (u->p == nullptr)
                        this->root = v;
                else if (u == u->p->left)
                        u->p->left = v;
                else
                        u->p->right = v;

                if (v) v->p = u->p;
        }
};