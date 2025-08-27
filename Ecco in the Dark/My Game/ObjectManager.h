/// \file ObjectManager.h
/// \brief Interface for the object manager CObjectManager.

#ifndef __L4RC_GAME_OBJECTMANAGER_H__
#define __L4RC_GAME_OBJECTMANAGER_H__

#include "BaseObjectManager.h"
#include "Object.h"
#include "Common.h"

/// \brief The object manager.
///
/// A collection of all of the game objects.

class CObjectManager: 
  public LBaseObjectManager<CObject>,
  public CCommon
{
  private:
    //LParticleDesc2D pulse;
    void BroadPhase(); ///< Broad phase collision detection and response.
    void NarrowPhase(CObject*, CObject*); ///< Narrow phase collision detection and response.

  public:
      CObject* create(eSprite, const Vector2&); ///< Create new object.
    
    virtual void draw(); ///< Draw all objects.

    void FireGun(CObject*, eSprite); ///< Fire object's gun.
    void ShowPulse(CObject*, eSprite);
    double pointer(CObject*, eSprite);
    const size_t GetNumTurrets() const; ///< Get number of turrets in object list.
    const bool GetNumOffSwitch() const; ///< Get number of unlit switches
    const bool GetNumOnSwitch() const; ///< Get number of lit switches
    const bool GetNumButtonUp() const; ///< Get number of buttons that are not being pressed
    void PlayerPressButton();
    void KnightPressButton();
    void UnlockDoor();
    const bool GetDoorEnter(/*CObject* pObj, eSprite OpenDoor*/) const; ///< tell us if the player is touching the door
    const size_t GetNumKnights() const; ///< Get number of knights in object list.
}; //CObjectManager

#endif //__L4RC_GAME_OBJECTMANAGER_H__
