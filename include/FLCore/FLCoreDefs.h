#ifndef _FLCOREDEFS_H_
#define _FLCOREDEFS_H_

#include "../Typedefs.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "st6.h"

#pragma warning(disable : 4251 4002 4099 4302)

#ifndef IMPORT
    #define IMPORT __declspec(dllimport)
#endif
#ifndef EXPORT
    #define EXPORT __declspec(dllexport)
#endif

#define OBJECT_DATA_SIZE 2048

template <typename ValType>
class BinarySearchTree
{
    public:
        struct Node;

        typedef Node* NodePtr;

        struct Node
        {
                NodePtr left;
                NodePtr parent;
                NodePtr right;
                unsigned int key;
                ValType data;
        };

        class Iterator
        {
            public:
                Iterator(NodePtr currentNode, BinarySearchTree<ValType>* classPtr)
                {
                    _currentNode = currentNode;
                    _classObj = classPtr;
                }

                Iterator()
                {
                    _currentNode = 0;
                    _classObj = 0;
                }

                void Inc()
                {
                    if (_classObj->IsNil(_currentNode) == true)
                        ;
                    else if (_classObj->IsNil(_currentNode->right) == false)
                    {
                        _currentNode = _classObj->Min(_currentNode->right);
                    }
                    else
                    { // climb looking for right subtree
                        NodePtr node;
                        while (_classObj->IsNil(node = _currentNode->parent) == false && _currentNode == node->right)
                        {
                            _currentNode = node; // ==> parent while right subtree
                        }
                        _currentNode = node; // ==> parent (head if end())
                    }

                    // set to end node if we are at nil (so we can compare against end-iterator)
                    if (_classObj->IsNil(_currentNode))
                    {
                        _currentNode = _classObj->end()._currentNode;
                    }
                }

                Iterator& operator++()
                {
                    Inc();
                    return *this;
                }

                Iterator operator++(int)
                {
                    Iterator tmp(*this); // copy
                    operator++();        // pre-increment
                    return tmp;          // return old value
                }

                bool operator==(const Iterator& _Right) const
                { // test for iterator equality
                    return (_currentNode == _Right._currentNode);
                }

                bool operator!=(const Iterator& _Right) const
                { // test for iterator inequality
                    return (!(*this == _Right));
                }

                unsigned int* key() { return &_currentNode->key; }

                ValType* value() { return &_currentNode->data; }

            private:
                NodePtr _currentNode;
                BinarySearchTree<ValType>* _classObj;
        };

    public:
        unsigned int size() { return _size; };

        Iterator begin() { return Iterator(_headNode->left, this); }

        Iterator end() { return Iterator(_endNode, this); }

        Iterator find(unsigned int key)
        {
            NodePtr searchNode = _headNode->parent; // parent of headnode is first legit (upmost) node

            while (IsNil(searchNode) == false)
            {
                if (searchNode->key == key)
                {
                    break;
                }

                if (key < searchNode->key)
                {
                    searchNode = searchNode->left;
                }
                else
                {
                    searchNode = searchNode->right;
                }
            }

            return Iterator(searchNode, this);
        }

    protected:
        NodePtr Min(NodePtr node)
        {
            // go to leftmost child
            while (IsNil(node->left) == false)
            {
                node = node->left;
            }

            return node;
        }

        bool IsNil(NodePtr node) { return (node == _endNode || node == _headNode); }

    private:
        void* dunno;
        NodePtr _headNode; // headnode stores min/max in left/right and upmost node in parent
        NodePtr _endNode;
        void* dunno2;
        unsigned int _size;
};

template <int size>
struct TString
{
        int len;
        char data[size + 1];

        TString() : len(0) { data[0] = 0; }
};

class Vector : public glm::vec<3, float, glm::packed_highp>
{
    public:
        Vector() = default;
        Vector(const float a, const float b, const float c) : glm::vec3(a, b, c) {}
        Vector(glm::vec<3, float, glm::packed_highp> v) : glm::vec3(v.x, v.y, v.z) {}
};

class Matrix : public glm::mat3
{
    public:
        Matrix() = default;
        Matrix(const glm::vec3 a, const glm::vec3 b, const glm::vec3 c) : glm::mat3(a, b, c) {}
        static Matrix Identity() { return Matrix({ 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }); }
};

class Quaternion : public glm::qua<float, glm::packed_highp>
{
    public:
        Quaternion() = default;
        Quaternion(const float a, const float b, const float c, const float d) : glm::qua<float, glm::packed_highp>(a, b, c, d) {}
        explicit Quaternion(const glm::quat& quat)
        {
            w = quat.w;
            x = quat.x;
            y = quat.y;
            z = quat.z;
        }
};

class Transform
{
    public:
        Transform() = default;

        Vector pos;
        Matrix orient;
};

#endif // _FLCOREDEFS_H_
