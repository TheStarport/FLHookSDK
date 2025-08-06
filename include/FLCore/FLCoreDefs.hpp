#ifndef _FLCOREDEFS_H_
#define _FLCOREDEFS_H_

#ifndef SERVER

using Id = unsigned int;
using SystemId = unsigned int;
using BaseId = unsigned int;
using ShipId = unsigned int;
using ObjectId = unsigned int;
using EquipmentId = unsigned int;
using ClientId = unsigned int;
using RepId = int;
struct GoodInfo;
using GoodId = GoodInfo*;

#endif

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

template <int size>
struct TString
{
        int len;
        char data[size + 1];

        TString() : len(0) { data[0] = 0; }
};

#ifdef USE_GLM

class Matrix;
class Vector : public glm::vec<3, float, glm::packed_highp>
{
    public:
        Vector() = default;
        Vector(const float a, const float b, const float c) : glm::vec3(a, b, c) {}
        Vector(glm::vec<3, float, glm::packed_highp> v) : glm::vec3(v.x, v.y, v.z) {}

        bool InRadius(const Vector& v, float radius) const { return std::abs(glm::distance<3, float, glm::packed_highp>(*this, v)) < radius; }
        void TranslateX(const Matrix& rot, float length);
        void TranslateY(const Matrix& rot, float length);
        void TranslateZ(const Matrix& rot, float length);
        float Magnitude();
        void Resize(float targetLength);

        static float Distance(const Vector& v1, const Vector& v2) { return glm::length<3, float, glm::packed_highp>(v1 - v2); }
};

Matrix EulerMatrix(const Vector&);

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

        static Matrix FromEuler(Vector rot) { return EulerMatrix(rot); }
};

inline void Vector::TranslateX(const Matrix& rot, float length)
{
    this->x += length * rot[0][0];
    this->y += length * rot[1][0];
    this->z += length * rot[2][0];
}
inline void Vector::TranslateY(const Matrix& rot, float length)
{
    this->x += length * rot[0][1];
    this->y += length * rot[1][1];
    this->z += length * rot[2][1];
}
inline void Vector::TranslateZ(const Matrix& rot, float length)
{
    this->x += length * rot[0][2];
    this->y += length * rot[1][2];
    this->z += length * rot[2][2];
}

inline float Vector::Magnitude() { return sqrtf(x * x + y * y + z * z); }

inline void Vector::Resize(float targetLength)
{
    float ratio = targetLength / Magnitude();

    x *= ratio;
    y *= ratio;
    z *= ratio;
}

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

        static Matrix FromEuler(Vector rot) { return EulerMatrix(rot); }
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
