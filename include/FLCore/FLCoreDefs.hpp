#ifndef _FLCOREDEFS_H_
#define _FLCOREDEFS_H_

#ifdef USE_GLM
    #include "glm/glm.hpp"
    #include "glm/gtc/quaternion.hpp"

#endif

#include "../Typedefs.hpp"
#include "st6.h"

#pragma warning(disable : 4251 4002 4099 4302)

#ifndef IMPORT
    #define IMPORT __declspec(dllimport)
#endif
#ifndef EXPORT
    #define EXPORT __declspec(dllexport)
#endif

#define OBJECT_DATA_SIZE 2048

template <typename T>
struct BinarySearchTree;

template <typename T>
struct Node
{
        Node* left;
        Node* head;
        Node* right;
        uint key;
        T value;
        bool unknown;
        bool isEnd;

        class Iterator
        {
                friend BinarySearchTree<T>;
                Node* node;
                explicit Iterator(Node* node) { this->node = node; }

            public:
                Iterator& operator++()
                {
                    node = node->Traverse();
                    return *this;
                }

                Node* operator->() const { return node; }
                Node* operator*() const { return node; }

                friend bool operator==(const Iterator& a, const Iterator& b) { return a.node == b.node; }
                friend bool operator!=(const Iterator& a, const Iterator& b) { return a.node != b.node; }
        };

    private:
        Node* Traverse()
        {
            Node* node = this;
            Node** nodeRef = &node;

            Node* v1 = (*nodeRef)->right;
            Node* result;

            if (v1->isEnd)
            {
                for (result = (*nodeRef)->head; (*nodeRef) == result->right; result = result->head)
                {
                    (*nodeRef) = result;
                }

                if ((*nodeRef)->right != result)
                {
                    (*nodeRef) = result;
                }
            }
            else
            {
                for (result = v1->left; !result->isEnd; result = result->left)
                {
                    v1 = result;
                }

                (*nodeRef) = v1;
            }

            return *nodeRef;
        }
};

template <typename ValType>
struct BinarySearchTree
{
        using Iter = typename Node<ValType>::Iterator;
        unsigned int size() { return _size; }
        Iter begin() { return Iter(headNode->head); }
        Iter end() { return Iter(headNode); }

        // Specialize for different types!
        void Insert(uint key, ValType val);
        Iter Find(uint& key)
        {
            Iter bstIterator = begin();
            Iter endIterator = Iter(endNode);
            while (bstIterator != endIterator)
            {
                if (bstIterator->key == key)
                {
                    return bstIterator;
                }
                if (bstIterator->key > key)
                {
                    bstIterator = Iter(bstIterator->left);
                }
                else
                {
                    bstIterator = Iter(bstIterator->right);
                }
            }
            return end();
        }

    private:
        Node<ValType>* nextNode = nullptr;
        Node<ValType>* headNode = nullptr; // headnode stores min/max in left/right and upmost node in parent
        Node<ValType>* endNode = nullptr;
        void* dunno2 = nullptr;
        // ReSharper disable once CppInconsistentNaming
        unsigned int _size = 0u;
};

// Not quite a BST, through very similar.
template <typename KeyType, typename ValType>
class FlMap
{

    public:
        struct Node;

        typedef Node* NodePtr;

        struct Node
        {
                NodePtr left;
                NodePtr parent;
                NodePtr right;
                KeyType key;
                ValType data;
        };

        class Iterator
        {
                void Inc()
                {
                    if (!classObj->IsNil(currentNode->right))
                    {
                        currentNode = classObj->Min(currentNode->right);
                    }
                    else if (!classObj->IsNil(currentNode))
                    { // climb looking for right subtree
                        NodePtr node;
                        while (!classObj->IsNil(node = currentNode->parent) && currentNode == node->right)
                        {
                            currentNode = node; // ==> parent while right subtree
                        }
                        currentNode = node; // ==> parent (head if end())
                    }

                    // set to end node if we are at nil (so we can compare against end-iterator)
                    if (classObj->IsNil(currentNode))
                    {
                        currentNode = classObj->end().currentNode;
                    }
                }

            public:
                Iterator(NodePtr currentNode, const FlMap* classPtr)
                {
                    this->currentNode = currentNode;
                    classObj = classPtr;
                }

                Iterator()
                {
                    currentNode = 0;
                    classObj = 0;
                }

                NodePtr operator*() { return currentNode; }
                Iterator& operator++()
                {
                    Inc();
                    return *this;
                }
                bool operator==(const Iterator& right) const { return currentNode == right.currentNode; }

                unsigned int key() { return currentNode->key; }

                ValType* value() { return &currentNode->data; }
                operator bool() { return currentNode && currentNode->left && currentNode->parent && currentNode->right; }

            private:
                NodePtr currentNode;
                const FlMap* classObj;
        };

        unsigned int size() const { return _size; };

        Iterator begin() { return Iterator(headNode->left, this); }
        Iterator end() { return Iterator(headNode, this); }
        Iterator begin() const { return Iterator(headNode->left, this); }
        Iterator end() const { return Iterator(headNode, this); }

        Iterator find(KeyType key) const
        {
            NodePtr searchNode = headNode->parent; // parent of headnode is first legit (upmost) node

            while (!IsNil(searchNode))
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

            return Iterator{ searchNode, this };
        }

    protected:
        NodePtr Min(NodePtr node) const
        {
            // go to leftmost child
            while (IsNil(node->left) == false)
            {
                node = node->left;
            }

            return node;
        }

        bool IsNil(NodePtr node) const { return (node == endNode || node == headNode); }

    private:
        void* dunno = nullptr;
        NodePtr headNode = nullptr; // headnode stores min/max in left/right and upmost node in parent
        NodePtr endNode = nullptr;
        void* dunno2 = nullptr;
        unsigned int _size = 0; // NOLINT
};

template <int size>
struct TString
{
        int len;
        char data[size + 1];

        TString() : len(0) { data[0] = 0; }
};

#ifdef USE_GLM

class Vector : public glm::vec<3, float, glm::packed_highp>
{
    public:
        Vector() = default;
        Vector(const float a, const float b, const float c) : glm::vec3(a, b, c) {}
        Vector(glm::vec<3, float, glm::packed_highp> v) : glm::vec3(v.x, v.y, v.z) {}

        bool InRadius(const Vector& v, float radius) const { return std::abs(glm::distance<3, float, glm::packed_highp>(*this, v)) < radius; }
};

class Matrix : public glm::mat3
{
    public:
        Matrix() = default;
        Matrix(const glm::vec3 a, const glm::vec3 b, const glm::vec3 c) : glm::mat3(a, b, c) {}
        static Matrix Identity() { return Matrix({ 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }); }

        [[nodiscard]]
        Vector ToEuler(const bool inDegrees) const
        {
            float heading = 0.0f;
            float bank = 0.0f;
            float attitude = 0.0f;

            const float mathDunno = sqrtf(operator[](0)[0] * operator[](0)[0] + operator[](1)[0] * operator[](1)[0]);

            // singularity at south or north pole
            if (mathDunno <= 0.0000019f)
            {
                heading = atan2(-operator[](1)[2], operator[](1)[1]);
                bank = atan2(-operator[](2)[0], mathDunno);
                attitude = 0.0f;
            }
            else
            {
                heading = atan2(operator[](2)[1], operator[](2)[2]);
                bank = atan2(-operator[](2)[0], mathDunno);
                attitude = atan2(operator[](1)[0], operator[](0)[0]);
            }

            if (inDegrees)
            {
                constexpr float mod = 57.295776f;
                return { heading * mod, bank * mod, attitude * mod };
            }
            return { heading, bank, attitude };
        }
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
        explicit Quaternion(const Matrix& rotation)
        {
            w = sqrt(std::max(0.0f, 1 + rotation[0][0] + rotation[1][1] + rotation[2][2])) / 2;
            x = sqrt(std::max(0.0f, 1 + rotation[0][0] - rotation[1][1] - rotation[2][2])) / 2;
            y = sqrt(std::max(0.0f, 1 - rotation[0][0] + rotation[1][1] - rotation[2][2])) / 2;
            z = sqrt(std::max(0.0f, 1 - rotation[0][0] - rotation[1][1] + rotation[2][2])) / 2;
            x = static_cast<float>(_copysign(x, rotation[2][1] - rotation[1][2]));
            y = static_cast<float>(_copysign(y, rotation[0][2] - rotation[2][0]));
            z = static_cast<float>(_copysign(z, rotation[1][0] - rotation[0][1]));
        }
};

#else

struct Vector
{
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;

        bool InRadius(const Vector& v, const float radius) const
        {
            const Vector n = { x - v.x, y - v.y, z - v.z };
            return std::sqrtf(n.x * n.x + n.y * n.y + n.z * n.z) < radius;
        }
};

union Matrix {
        struct
        {
                Vector a;
                Vector b;
                Vector c;
        };
        float data[3][3]{};

        Matrix()
        {
            a = { 1.0f, 0.0f, 0.0f };
            b = { 0.0f, 1.0f, 0.0f };
            c = { 0.0f, 0.0f, 1.0f };
        }

        const float (&operator[](const size_t i) const)[3] { return data[i]; }

        [[nodiscard]]
        Vector ToEuler(const bool inDegrees) const
        {
            float heading = 0.0f;
            float bank = 0.0f;
            float attitude = 0.0f;

            const float mathDunno = sqrtf(data[0][0] * data[0][0] + data[1][0] * data[1][0]);

            // singularity at south or north pole
            if (data[0][0] <= 0.0000019f)
            {
                heading = atan2(-data[1][2], data[1][1]);
                bank = atan2(-data[2][0], mathDunno);
                attitude = 0.0f;
            }
            else
            {
                heading = atan2(data[2][1], data[2][2]);
                bank = atan2(-data[2][0], mathDunno);
                attitude = atan2(data[1][0], data[0][0]);
            }

            if (inDegrees)
            {
                constexpr float mod = 57.295776f;
                return { heading * mod, bank * mod, attitude * mod };
            }
            return { heading, bank, attitude };
        }
};

struct Quaternion
{
        float w = 0.0f;
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
        explicit Quaternion(const Matrix& rotation)
        {
            w = sqrtf(std::max(0.0f, 1 + rotation[0][0] + rotation[1][1] + rotation[2][2])) / 2;
            x = sqrtf(std::max(0.0f, 1 + rotation[0][0] - rotation[1][1] - rotation[2][2])) / 2;
            y = sqrtf(std::max(0.0f, 1 - rotation[0][0] + rotation[1][1] - rotation[2][2])) / 2;
            z = sqrtf(std::max(0.0f, 1 - rotation[0][0] - rotation[1][1] + rotation[2][2])) / 2;
            x = static_cast<float>(_copysign(x, rotation[2][1] - rotation[1][2]));
            y = static_cast<float>(_copysign(y, rotation[0][2] - rotation[2][0]));
            z = static_cast<float>(_copysign(z, rotation[1][0] - rotation[0][1]));
        }
};

#endif

class Transform
{
    public:
        Transform() = default;

        Vector pos;
        Matrix orient;
};

// We need to specialize the BST insert function for each type and then proxy it to the original function

#define ArchetypeBstInsertError(type, module, insertAddr)                                              \
    template <>                                                                                        \
    inline void BinarySearchTree<type>::Insert(uint key, type value)                                   \
    {                                                                                                  \
        static DWORD mod = DWORD(GetModuleHandleA(module));                                            \
        using InsertFuncType = int(__thiscall*)(BinarySearchTree * ptr, type, uint*, char* errorName); \
        static auto insertFunc = reinterpret_cast<InsertFuncType>(mod + insertAddr);                   \
                                                                                                       \
        insertFunc(this, value, &key, nullptr);                                                        \
    }

#define ArchetypeBstInsert(type, module, insertAddr)                                  \
    template <>                                                                       \
    inline void BinarySearchTree<type>::Insert(uint key, type value)                  \
    {                                                                                 \
        static DWORD mod = DWORD(GetModuleHandleA(module));                           \
        using InsertFuncType = int(__thiscall*)(BinarySearchTree * ptr, type, uint*); \
        static auto insertFunc = reinterpret_cast<InsertFuncType>(mod + insertAddr);  \
                                                                                      \
        insertFunc(this, value, &key);                                                \
    }

#endif // _FLCOREDEFS_H_
