//////////////////////////////////////////////////////////////////////
//	Project FLCoreSDK v1.1, modified for use in FLHook Plugin version
//--------------------------
//
//	File:			FLCoreDefs.h
//	Module:
//	Description:	Common declarations
//
//	Web: www.skif.be/flcoresdk.php
//
//
//////////////////////////////////////////////////////////////////////
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

template<typename T>
struct Node
{
	Node* prev;
	Node* childLeft;
	Node* childRight;
	uint key;
	T value;
	bool unknown;
	bool isEnd;

	Node<T>* Traverse()
	{
		Node<T>* node = this;
        Node<T>** nodeRef = &node;

        Node<T>* v1 = (*nodeRef)->childRight;
        Node<T>* result;

        if (v1->isEnd)
        {
            for (result = (*nodeRef)->childLeft; (*nodeRef) == result->childRight; result = result->childLeft)
            {
                (*nodeRef) = result;
            }

            if ((*nodeRef)->childRight != result)
            {
                (*nodeRef) = result;
            }
        }
        else
        {
            for (result = v1->prev; !result->isEnd; result = result->prev)
            {
                v1 = result;
            }

            (*nodeRef) = v1;
        }

        return *nodeRef;
	}
};

template <typename T>
struct BinarySearchTree
{
    Node<T>* unknown;
	Node<T>* root;
	Node<T>* unk;
	Node<T>* unk2;
    uint size;

	void TraverseTree(std::function<void(std::pair<uint, T> val)> func)
	{
        if (root->isEnd)
        {
            TraverseTree(unknown, nullptr, func);
        }
        else
        {
            TraverseTree(root, nullptr, func);
        }
	}
private:
	bool TraverseTree(Node<T>* node, const Node<T>* previousNode, std::function<void(std::pair<uint, T> val)> func)
	{
		if (node->value == 0 && previousNode != nullptr)
		{
			func({ previousNode->key, previousNode->value });
			return false;
		}

		Node<T>* nextNode = node->childLeft == previousNode ? node->prev : node->childLeft;
		if (!TraverseTree(nextNode, node, func))
		{
			return TraverseTree(node->childRight, node, func);
		}

		return true;
	}
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
