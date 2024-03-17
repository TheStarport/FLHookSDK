#pragma once
#include "FLCore/FLCoreDefs.hpp"

ArchetypeBstInsertError(Archetype::Asteroid*, "common.dll", 0x9BEB0);
ArchetypeBstInsertError(Archetype::DynamicAsteroid*, "common.dll", 0x9BEB0);
ArchetypeBstInsertError(Archetype::Equipment*, "common.dll", 0x9BBE0);
ArchetypeBstInsertError(Archetype::Ship*, "common.dll", 0x9BEB0);
ArchetypeBstInsertError(Archetype::Solar*, "common.dll", 0x9BEB0);
ArchetypeBstInsert(Archetype::Explosion*, "common.dll", 0xAC1F0);
ArchetypeBstInsert(Archetype::MotorData*, "common.dll", 0xC22F0);
ArchetypeBstInsert(Archetype::Root*, "common.dll", 0x9BAD0);

namespace Trees
{
    #define BST(type, module, addr) (BinarySearchTree<type>*)(DWORD(GetModuleHandleA(module)) + addr)
    static BinarySearchTree<Archetype::Asteroid*>* asteroids = BST(Archetype::Asteroid*, "common.dll", 0x19CA98);
    static BinarySearchTree<Archetype::DynamicAsteroid*>* dynamicAsteroids = BST(Archetype::DynamicAsteroid*, "common.dll", 0x19CA84);
    static BinarySearchTree<Archetype::Equipment*>* equipment = BST(Archetype::Equipment*, "common.dll", 0x19CAD4);
    static BinarySearchTree<Archetype::Explosion*>* explosions = BST(Archetype::Explosion*, "common.dll", 0x19CF3C);
    static BinarySearchTree<Archetype::MotorData*>* motors = BST(Archetype::MotorData*, "common.dll", 0x19CA70);
    static BinarySearchTree<Archetype::Ship*>* ships = BST(Archetype::Ship*, "common.dll", 0x19CAC0);
    static BinarySearchTree<Archetype::Root*>* allArchetypes = BST(Archetype::Root*, "common.dll", 0x19CAE8);
    static BinarySearchTree<Archetype::Solar*>* solar = BST(Archetype::Solar*, "common.dll", 0x19CAAC);
    #undef BST
} // namespace Trees

#endif //_FLCORECOMMON_H_
