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
struct BinarySearchTree
{
        struct Node;

        typedef Node* NodePtr;

        struct Node
        {
                NodePtr prev;
                NodePtr left;
                NodePtr right;
                unsigned int key;
                ValType value;
                bool unknown;
                bool isEnd;
        };

        void TraverseTree(std::function<void(std::pair<uint, ValType> val)> func)
        {
            if (headNode->isEnd)
            {
                TraverseTree(nextNode, nullptr, func);
            }
            else
            {
                TraverseTree(headNode, nullptr, func);
            }
        }

        unsigned int size() { return _size; };

    private:
        bool TraverseTree(NodePtr node, const NodePtr previousNode, std::function<void(std::pair<uint, ValType> val)> func)
        {
            if (node->value == 0 && previousNode != nullptr)
            {
                func({ previousNode->key, previousNode->value });
                return false;
            }

            if (const NodePtr nextNode = node->left == previousNode ? node->prev : node->left; !TraverseTree(nextNode, node, func))
            {
                return TraverseTree(node->right, node, func);
            }

            return true;
        }

        NodePtr nextNode;
        NodePtr headNode; // headnode stores min/max in left/right and upmost node in parent
        NodePtr endNode;
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

class Transform
{
    public:
        Transform() = default;

        Vector pos;
        Matrix orient;
};

#endif // _FLCOREDEFS_H_
