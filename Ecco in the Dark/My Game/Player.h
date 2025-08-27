/// \file Player.h
/// \brief Interface for the player object class CPlayer.

#ifndef __L4RC_GAME_PLAYER_H__
#define __L4RC_GAME_PLAYER_H__

#include "Object.h"
#include "EventTimer.h"

/// \brief The player object. 
///
/// The abstract representation of the player object. The player differs from
/// the other objects in the game in that it moves in respond to device inputs.

class CPlayer: public CObject{
  protected:  
    const UINT m_nMaxHealth = 12; ///< Maximum health.
    UINT m_nHealth = m_nMaxHealth; ///< Current health.
    LEventTimer* m_pFrameEvent = nullptr; ///< Frame event timer.
    virtual void CollisionResponse(const Vector2&, float, CObject* = nullptr); ///< Collision response.
    virtual void DeathFX(); ///< Death special effects.

    void UpdateFramenumber(); ///< Update frame number.

  public:
    CPlayer(eSprite t, const Vector2& p); ///< Constructor.
    virtual ~CPlayer(); ///< Destructor.

    virtual void move(); ///< Move player object.
    
    void WalkRightUp();
    void WalkRightDown();
    void WalkLeftDown();
    void WalkLeftUp();
    void WalkLeft(); ///< Start walking left.
    void WalkRight(); ///< Start walking right.
    void WalkDown(); ///< Start walking Down.
    void WalkUp(); ///< Start walking up.
    void Stop(); ///< Stop walking.
   

    const Vector2& GetPos() const; ///< Get position.
}; //CPlayer




#endif //__L4RC_GAME_PLAYER_H__

