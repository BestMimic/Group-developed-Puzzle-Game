/// \file Knight.h

#ifndef __L4RC_GAME_KNIGHT_H__
#define __L4RC_GAME_KNIGHT_H__

#include "Object.h"

class CKnight : public CObject {
protected:
    const UINT m_nMaxHealth = 8; ///< Maximum health.
    UINT m_nHealth = m_nMaxHealth; ///< Current health.
    LEventTimer* m_pFrameEvent = nullptr; ///< Frame event timer.
    void RotateTowards(const Vector2&); ///< Swivel towards position.
    virtual void CollisionResponse(const Vector2&, float, CObject* = nullptr); ///< Collision response.
    virtual void DeathFX(); ///< Death special effects.

    float stuntime;

    void UpdateFramenumber(); ///< Update frame number.

public:
    CKnight(eSprite t, const Vector2& p); ///< Constructor.
    virtual void move(); ///< Move knight.

    virtual ~CKnight(); ///< Destructor.

    void WalkLeft(); ///< Start walking left.
    void WalkRight(); ///< Start walking right.
    void WalkDown(); ///< Start walking Down.
    void WalkUp(); ///< Start walking up.
    void Stop(); ///< Stop walking.

    void Stun(); ///< Become stunned
    void Wake(); //< Wake from stun

    const Vector2& GetPos() const; ///< Get position.
}; //CTurret

#endif //__L4RC_GAME_KNIGHT_H__