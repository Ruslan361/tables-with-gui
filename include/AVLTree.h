#ifndef AVLTREE_H
#define AVLTREE_H
#include "tpair.h"
#include <iostream>
#include "tsinglelinkedlist.h"
#include "ttable.h"

template <typename TKey, typename TValue>
class AVLTreeNode 
{
public:
    AVLTreeNode* left;
    AVLTreeNode* right;
    int heigh; 
    TKey key;
    TValue value;
    AVLTreeNode(const TKey& key, const TValue& value, AVLTreeNode* left, AVLTreeNode* right, int heigh)
    {
        this->left = left;
        this->right = right;
        this->heigh = heigh;
        this->key = key;
        this->value = value;
    }
    AVLTreeNode(const TKey& key, const TValue& value) : AVLTreeNode(key, value, nullptr, nullptr, 1) {}
    void CalculateHeight()
    {
        int left_height = 0;
        if (left != nullptr)
        {
            left_height = left->heigh;
        }
        int right_height = 0;
        if (right != nullptr)
        {
            right_height = right->heigh;
        }
        int max_height = left_height > right_height ? left_height : right_height;
        heigh = max_height + 1;
    }
};

template<typename TKey, typename TValue>
void GetKeysNode(AVLTreeNode<TKey, TValue>* node, TSingleLinkedList<TKey>& list)
{
    if (node == nullptr) return;
    if (node->left) GetKeysNode(node->left, list);
    list.Add(node->key);
    if (node->right) GetKeysNode(node->right, list);

    return;
}

template<typename TKey, typename TValue>
void DeleteNodes(AVLTreeNode<TKey, TValue>* node)
{
    if (node == nullptr) return;
    if (node->left) DeleteNodes(node->left);
    if (node->right) DeleteNodes(node->right);
    delete node;
    return;
}

template<typename TKey, typename TValue>
AVLTreeNode<TKey, TValue>* RightRotate(AVLTreeNode<TKey, TValue>* y) {
    AVLTreeNode<TKey, TValue>* x = y->left;
    AVLTreeNode<TKey, TValue>* T2 = x->right;

    x->right = y;
    y->left = T2;

    x->CalculateHeight();
    y->CalculateHeight();

    // y->height = max(height(y->left), height(y->right)) + 1;
    // x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}
template<typename TKey, typename TValue>
AVLTreeNode<TKey, TValue>* LeftRotate(AVLTreeNode<TKey, TValue>* x) {
    AVLTreeNode<TKey, TValue>* y = x->right;
    AVLTreeNode<TKey, TValue>* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->CalculateHeight();
    y->CalculateHeight();
    //x->height = max(height(x->left), height(x->right)) + 1;
    //y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}
template<typename TKey, typename TValue>
void PrintGraph(AVLTreeNode<TKey, TValue>* root)
{

    if (root == nullptr)
        return;
    if (root->left != nullptr)
    {
        std::cout << root->key << "-" << root->left->key << std::endl;
        PrintGraph(root->left);
        
    }

    if (root->right != nullptr)
    {
        std::cout << root->key << "-" << root->right->key << std::endl;
        PrintGraph(root->right);
        
    }
    
}
template<typename TKey, typename TValue>
int GetHeight(AVLTreeNode<TKey, TValue>* node)
{
    if (node == nullptr)
        return 0;
    else
        return node->heigh;
}
template<typename TKey, typename TValue>
AVLTreeNode<TKey, TValue>* Insert(AVLTreeNode<TKey, TValue>* node, const TKey& key, const TValue& value)
{
    if (node == nullptr)
    {
        AVLTreeNode<TKey, TValue>* ptr = new AVLTreeNode<TKey, TValue>(key, value);
        return ptr;
    }
    if (node->key > key)
        node->left = Insert(node->left, key, value);
    else if (node->key < key)
        node->right = Insert(node->right, key, value);
    else
        throw std::invalid_argument("key is exist");

    int balance = GetHeight(node->right) - GetHeight(node->left);
    if (balance < -1)
    {
        return RightRotate<TKey, TValue>(node);
    }
    if (balance > 1)
    {
        return LeftRotate<TKey, TValue>(node);
    }
    node->CalculateHeight();
    return node;
    //node->CalculateHeight();
}

template<typename TKey, typename TValue>
AVLTreeNode<TKey, TValue>* SearchNode(const AVLTreeNode<TKey, TValue>* root, const TKey& key)
{
    if (root == nullptr)
        {
            return nullptr;
        }
        AVLTreeNode<TKey, TValue>* current = root;
        do
        {
            if (key == current->key)
            {
                return current;
            }
            else if (key > current->key)
            {
                current = current->right;
            }
            else
            {
                current = current->left;
            }
        } while (current != nullptr);
        return nullptr;
}
template<typename TKey, typename TValue>
AVLTreeNode<TKey, TValue>* SearchNearestBigger(const AVLTreeNode<TKey, TValue>* root)
{
    if (root == nullptr) return nullptr;
    if (root->right == nullptr) return nullptr;
    AVLTreeNode<TKey, TValue>* current = root->right;
    while (current->left != nullptr)
    {
        current = current->left;
    }
    return current;
}

template<typename TKey, typename TValue>
AVLTreeNode<TKey, TValue>* DeleteNode(AVLTreeNode<TKey, TValue>* root, const TKey& key)
{
    if (root == nullptr) return nullptr;
    if ((root->left == nullptr) && (root->right == nullptr))
    {
        if (key == root->key)
        {
            delete root;
            root = nullptr;
        }
        
    }
    else if (root->right == nullptr)
    {
        if (root->left->key == key)
        {
            delete root->left;
            root->left = nullptr;
            // root->heigh = 1;
            // return root;
        }
    }
    else if (root->left == nullptr)
    {
        if (root->right->key == key)
        {
            delete root->right;
            root->left = nullptr;
            // root->heigh = 1;
            // return root;
        }

    }
    else{
    if (key < root->key)
    {
        root->left = DeleteNode(root->left, key);

    }
    else if (key > root->key)
    {
        root->right = DeleteNode(root->right, key);

    }
    else
    {
        AVLTreeNode<TKey, TValue>* nearest = SearchNearestBigger(root);
        TKey n_key = nearest->key;
        TValue n_value = nearest->value;
        root->right = DeleteNode(root->right, n_key);
        root->value = n_value;
        root->key = n_key;

    }
    int balance = GetHeight(root->right) - GetHeight(root->left);
    if (balance < -1)
    {
        return RightRotate<TKey, TValue>(root);
    }
    if (balance > 1)
    {
        return LeftRotate<TKey, TValue>(root);
    }
    root->CalculateHeight();
    }
    return root;
}

 template <typename TKey, typename TValue>
 class AVLTree : public TTable<TKey, TValue>
 {
    AVLTreeNode<TKey, TValue>* parent;
public:
    AVLTree()
    {
        parent = nullptr;
    }
    void Add(const TKey& key, const TValue& value)
    {
        parent = Insert(parent, key, value);

    }
    void Add(const TPair<TKey, TValue>& pair)
    {
        Add(pair.key, pair.value);
    }
    bool Search(const TKey& key, TValue& value) const
    {
        if (parent == nullptr)
        {
            return false;
        }
        AVLTreeNode<TKey, TValue>* current = parent;
        do
        {
            if (key == current->key)
            {
                value = current->value;
                return true;
            }
            else if (key > current->key)
            {
                current = current->right;
            }
            else
            {
                current = current->left;
            }
        } while (current != nullptr);
        return false;
    }

    void Remove(const TKey& key)
    {
        parent = DeleteNode(parent, key);
        //std::cout << std::endl << "new tree" << std::endl;
        //PrintGraph(parent);
    }
    TSingleLinkedList<TKey> GetKeys()
    {
        TSingleLinkedList<TKey> keys;
        GetKeysNode(parent, keys);
        return keys;
    }
    ~AVLTree()
    {
        DeleteNodes(parent);
    }
    TSingleLinkedList<TValue> GetValues(const TKey& key)
    {
        TSingleLinkedList<TValue> values;
        TValue value;
        if (Search(key, value))
        {
            values.Add(value);
        }
        return values;
    }
// //    void Add(const TPair<TKey, TValue>& pair);
// //    void Remove(const TKey& key);
// //    bool Search(const TKey& key, TValue& value) const;
// //    TSingleLinkedList<TKey> GetKeys();
// //    TSingleLinkedList<TValue> GetValues(const TKey& key);
 };

#endif // AVLTREE_H
