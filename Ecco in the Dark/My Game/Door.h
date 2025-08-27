/// \file Door.h
/// \brief Interface for the Door object class CTurret.

#ifndef __L4RC_GAME_DOOR_H__
#define __L4RC_GAME_DOOR_H__

#include "Object.h"

/// \brief The door object. 
///
/// CDoor is the abstract representation of a door object.

class CDoor : public CObject {
protected:
    bool locked = true; ///< whether the door can be used to progress yet
    //bool leave = false; ///< whether the player can leave
    void Lock();
    //bool CanLeave();
    virtual void CollisionResponse(const Vector2&, float, CObject* = nullptr); ///< Collision response.

public:
    CDoor(const Vector2& p); ///< Constructor.
    virtual void move(); ///< Move turret.
}; //CDoor

#endif //__L4RC_GAME_TURRET_H__
