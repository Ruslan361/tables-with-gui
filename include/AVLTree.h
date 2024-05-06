#ifndef AVLTREE_H
#define AVLTREE_H
#include "tpair.h"
#include <iostream>
#include "tsinglelinkedlist.h"
#include "ttable.h"

template <typename TKey, typename TValue>
class AVLTree : public TContainer<TKey, TValue> {
private:
    struct Node {
        TKey key;
        TValue value;
        Node* left;
        Node* right;
        int height;

        Node(const TKey& k, const TValue& v) : key(k), value(v), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    // Вспомогательные методы
    int height(Node* node);
    int balanceFactor(Node* node);
    void updateHeight(Node* node);
    Node* rotateRight(Node* node);
    Node* rotateLeft(Node* node);
    Node* balance(Node* node);
    Node* insert(Node* node, const TKey& key, const TValue& value);
    Node* findMin(Node* node);
    Node* removeMin(Node* node);
    Node* remove(Node* node, const TKey& key);
    void destroy(Node* node);
    void getKeys(Node* node, TSingleLinkedList<TKey>& keys);

public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() { destroy(root); }

    // Методы из TTable
    void Add(const TKey& key, const TValue& value) override { root = insert(root, key, value); }
    void Add(const TPair<TKey, TValue>& pair) override { Add(pair.key, pair.value); }
    void Remove(const TKey& key) override { root = remove(root, key); }
    bool Search(const TKey& key, TValue& value) const override;
    TSingleLinkedList<TKey> GetKeys() override;
    TSingleLinkedList<TValue> GetValues(const TKey& key) override;
};

template<typename TKey, typename TValue>
int AVLTree<TKey, TValue>::height(Node* node) {
    return node ? node->height : 0;
}

template<typename TKey, typename TValue>
int AVLTree<TKey, TValue>::balanceFactor(Node* node) {
    return height(node->right) - height(node->left);
}

template<typename TKey, typename TValue>
void AVLTree<TKey, TValue>::updateHeight(Node* node) {
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

template<typename TKey, typename TValue>
typename AVLTree<TKey, TValue>::Node* AVLTree<TKey, TValue>::rotateRight(Node* node) {
    Node* leftChild = node->left;
    node->left = leftChild->right;
    leftChild->right = node;
    updateHeight(node);
    updateHeight(leftChild);
    return leftChild;
}

template<typename TKey, typename TValue>
typename AVLTree<TKey, TValue>::Node* AVLTree<TKey, TValue>::rotateLeft(Node* node) {
    Node* rightChild = node->right;
    node->right = rightChild->left;
    rightChild->left = node;
    updateHeight(node);
    updateHeight(rightChild);
    return rightChild;
}

template<typename TKey, typename TValue>
typename AVLTree<TKey, TValue>::Node* AVLTree<TKey, TValue>::balance(Node* node) {
    updateHeight(node);
    if (balanceFactor(node) == 2) {
        if (balanceFactor(node->right) < 0)
            node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    if (balanceFactor(node) == -2) {
        if (balanceFactor(node->left) > 0)
            node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    return node;
}

template<typename TKey, typename TValue>
typename AVLTree<TKey, TValue>::Node* AVLTree<TKey, TValue>::insert(Node* node, const TKey& key, const TValue& value) {
    if (!node) return new Node(key, value);
    if (key < node->key)
        node->left = insert(node->left, key, value);
    else if (key > node->key)
        node->right = insert(node->right, key, value);
    else
        node->value = value;
    return balance(node);
}

template<typename TKey, typename TValue>
typename AVLTree<TKey, TValue>::Node* AVLTree<TKey, TValue>::findMin(Node* node) {
    return node->left ? findMin(node->left) : node;
}

template<typename TKey, typename TValue>
typename AVLTree<TKey, TValue>::Node* AVLTree<TKey, TValue>::removeMin(Node* node) {
    if (!node->left)
        return node->right;
    node->left = removeMin(node->left);
    return balance(node);
}

template<typename TKey, typename TValue>
typename AVLTree<TKey, TValue>::Node* AVLTree<TKey, TValue>::remove(Node* node, const TKey& key) {
    if (!node) return nullptr;
    if (key < node->key)
        node->left = remove(node->left, key);
    else if (key > node->key)
        node->right = remove(node->right, key);
    else {
        Node* leftChild = node->left;
        Node* rightChild = node->right;
        delete node;
        if (!rightChild) return leftChild;
        Node* minNode = findMin(rightChild);
        minNode->right = removeMin(rightChild);
        minNode->left = leftChild;
        return balance(minNode);
    }
    return balance(node);
}

template<typename TKey, typename TValue>
void AVLTree<TKey, TValue>::destroy(Node* node) {
    if (!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

template<typename TKey, typename TValue>
bool AVLTree<TKey, TValue>::Search(const TKey& key, TValue& value) const {
    Node* current = root;
    while (current) {
        if (key < current->key)
            current = current->left;
        else if (key > current->key)
            current = current->right;
        else {
            value = current->value;
            return true;
        }
    }
    return false;
}

template<typename TKey, typename TValue>
void AVLTree<TKey, TValue>::getKeys(Node* node, TSingleLinkedList<TKey>& keys) {
    if (!node) return;
    getKeys(node->left, keys);
    keys.Add(node->key);
    getKeys(node->right, keys);
}

template<typename TKey, typename TValue>
TSingleLinkedList<TKey> AVLTree<TKey, TValue>::GetKeys() {
    TSingleLinkedList<TKey> keys;
    getKeys(root, keys);
    return keys;
}

template<typename TKey, typename TValue>
TSingleLinkedList<TValue> AVLTree<TKey, TValue>::GetValues(const TKey& key) {
    TSingleLinkedList<TValue> values;
    TValue value;
    if (Search(key, value))
        values.Add(value);
    return values;
}
#endif // AVLTREE_H
