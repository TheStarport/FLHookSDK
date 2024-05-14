#pragma once

#include "Common/Damage.hpp"
#include "Common/Enums.hpp"
#include "Common/EquipDesc.hpp"
#include "Common/Fuse.hpp"
#include "Common/Goods.hpp"
#include "Common/INI_Reader.hpp"
#include "Common/MiscStructs.hpp"
#include "Common/NewChar.hpp"
#include "Common/Reputation.hpp"
#include "Common/Strings.hpp"
#include "Common/SubObjectID.hpp"
#include "Common/AI/AIEnums.hpp"
#include "Common/AI/BaseOp.hpp"
#include "Common/AI/ContentCallback.hpp"
#include "Common/AI/Ops.hpp"
#include "Common/AI/Personality.hpp"
#include "Common/AI/StateGraph.hpp"
#include "Common/Archetype/Root.hpp"
#include "Common/Archetype/MotorData.hpp"
#include "Common/Archetype/Explosion.hpp"
#include "Common/Archetype/Effect.hpp"
#include "Common/Archetype/DamageObjInfo.hpp"
#include "Common/Archetype/CollisionGroup.hpp"
#include "Common/Archetype/ArchetypeMethods.hpp"
#include "Common/Archetype/Root/Asteroid.hpp"
#include "Common/Archetype/Root/EqObj.hpp"
#include "Common/Archetype/Root/Equipment.hpp"
#include "Common/Archetype/Root/DynamicAsteroid.hpp"
#include "Common/Archetype/Root/AttachedFXEquip.hpp"
#include "Common/Archetype/Root/Equipment/Armor.hpp"
#include "Common/Archetype/Root/Equipment/AttachedEquipment.hpp"
#include "Common/Archetype/Root/Equipment/Commodity.hpp"
#include "Common/Archetype/Root/Equipment/Engine.hpp"
#include "Common/Archetype/Root/Equipment/InternalFXEquip.hpp"
#include "Common/Archetype/Root/Equipment/Light.hpp"
#include "Common/Archetype/Root/Equipment/LootCrate.hpp"
#include "Common/Archetype/Root/Equipment/Power.hpp"
#include "Common/Archetype/Root/Equipment/Projectile.hpp"
#include "Common/Archetype/Root/Equipment/Regens.hpp"
#include "Common/Archetype/Root/Equipment/Scanner.hpp"
#include "Common/Archetype/Root/Equipment/Shield.hpp"
#include "Common/Archetype/Root/Equipment/Tractor.hpp"
#include "Common/Archetype/Root/Equipment/TradeLaneEquip.hpp"
#include "Common/Archetype/Root/Equipment/AttachedEquipment/Launcher.hpp"
#include "Common/Archetype/Root/Equipment/AttachedEquipment/CargoPod.hpp"
#include "Common/Archetype/Root/Equipment/AttachedEquipment/CloakingDevice.hpp"
#include "Common/Archetype/Root/Equipment/AttachedEquipment/ShieldGenerator.hpp"
#include "Common/Archetype/Root/Equipment/AttachedEquipment/Thruster.hpp"
#include "Common/Archetype/Root/Equipment/Launcher/Gun.hpp"
#include "Common/Archetype/Root/Equipment/Launcher/MineDropper.hpp"
#include "Common/Archetype/Root/Equipment/Launcher/CounterMeasureDropper.hpp"
#include "Common/Archetype/Root/Equipment/Projectile/Munition.hpp"
#include "Common/Archetype/Root/Equipment/Projectile/Mine.hpp"
#include "Common/Archetype/Root/Equipment/Projectile/CounterMeasure.hpp"
#include "Common/Archetype/Root/EqObj/Ship.hpp"
#include "Common/Archetype/Root/EqObj/Solar.hpp"
#include "Common/CmnAsteroid/LootableZone.hpp"
#include "Common/CmnAsteroid/CAsteroidCube.hpp"
#include "Common/CmnAsteroid/CAsteroidField.hpp"
#include "Common/CmnAsteroid/CAsteroidSystem.hpp"
#include "Common/CmnAsteroid/CmnAsteroidMethods.hpp"
#include "Common/CObjects/EngineObject.hpp"
#include "Common/CObjects/CObject.hpp"
#include "Common/CObjects/CSimple.hpp"
#include "Common/CObjects/CDynamicAsteroid.hpp"
#include "Common/CEquip/CEquip.hpp"
#include "Common/CEquip/CAttachedEquip.hpp"
#include "Common/CEquip/CEArmor.hpp"
#include "Common/CEquip/CEPower.hpp"
#include "Common/CEquip/CEquipManager.hpp"
#include "Common/CEquip/CExternalEquip.hpp"
#include "Common/CEquip/CELightEquip.hpp"
#include "Common/CEquip/CEInternalFX.hpp"
#include "Common/CEquip/CERepairDroid.hpp"
#include "Common/CEquip/CInternalEquip.hpp"
#include "Common/CEquip/CInternalEquip/CECargo.hpp"
#include "Common/CEquip/CInternalEquip/CEEngine.hpp"
#include "Common/CEquip/CInternalEquip/CEScanner.hpp"
#include "Common/CEquip/CInternalEquip/CETractor.hpp"
#include "Common/CEquip/CInternalEquip/CETradeLaneEquip.hpp"
#include "Common/CEquip/CExternalEquip/CECloakingDevice.hpp"
#include "Common/CEquip/CExternalEquip/CEAttachedFX.hpp"
#include "Common/CEquip/CAttachedEquip/CELauncher.hpp"
#include "Common/CEquip/CAttachedEquip/CEShield.hpp"
#include "Common/CEquip/CAttachedEquip/CEThruster.hpp"
#include "Common/CEquip/CAttachedEquip/CECargoPod.hpp"
#include "Common/CEquip/CAttachedEquip/CEShieldGenerator.hpp"
#include "Common/CEquip/CAttachedEquip/CELauncher/CEGun.hpp"
#include "Common/CEquip/CAttachedEquip/CELauncher/CEMineDropper.hpp"
#include "Common/CEquip/CAttachedEquip/CELauncher/CECounterMeasureDropper.hpp"
#include "Common/CObjects/CSimple/CAsteroid.hpp"
#include "Common/CObjects/CSimple/CLoot.hpp"
#include "Common/CObjects/CSimple/CProjectile.hpp"
#include "Common/CObjects/CSimple/CProjectile/CMunition.hpp"
#include "Common/CObjects/CSimple/CProjectile/CBeam.hpp"
#include "Common/CObjects/CSimple/CProjectile/CMine.hpp"
#include "Common/CObjects/CSimple/CProjectile/CCounterMeasure.hpp"
#include "Common/CObjects/CSimple/CProjectile/CBeam.hpp"
#include "Common/CObjects/CSimple/CProjectile/CGuided.hpp"
#include "Common/CObjects/CSimple/CEqObj/CEqObj.hpp"
#include "Common/CObjects/CSimple/CEqObj/CShip.hpp"
#include "Common/CObjects/CSimple/CEqObj/CSolar.hpp"
#include "Common/PhySys/Controller.hpp"
#include "Common/PhySys/CollisionEvent.hpp"
#include "Common/PhySys/RayHit.hpp"
#include "Common/PhySys/PhySysMethods.hpp"
#include "Common/PhySys/PhyCollisionStateManager.hpp"
#include "Common/PhySys/Controller/CSteering.hpp"
#include "Common/PhySys/Controller/CNudgeEngine.hpp"
#include "Common/PhySys/Controller/CPhysAttachment.hpp"
#include "Common/PhySys/Controller/CPhysControllerEquip.hpp"
#include "Common/PhySys/Controller/CStrafeEngine.hpp"
#include "Common/Universe/IBase.hpp"
#include "Common/Universe/IZone.hpp"
#include "Common/Universe/ISystem.hpp"
#include "Common/Universe/UniverseMethods.hpp"
#include "Common/CArchGroup.hpp"
#include "Common/XML.hpp"
#include "Common/Watchable.hpp"
#include "Common/FmtStr.hpp"
#include "Common/Unknown.hpp"
#include "Common/CommonMethods.hpp"

#include "Common/BinarySearchTree.hpp"
#include "Common/CArchGroup.hpp"