/// \file Turret.cpp
/// \brief Code for the turret object class CTurret.
/// Nathan here. I want to reuse these for visual flare.

#include "Door.h"
#include "ComponentIncludes.h"
#include "ObjectManager.h"
#include "TileManager.h"
#include "Player.h"
#include "Helpers.h"
#include "Particle.h"
#include "ParticleEngine.h"

/// Create and initialize a turret object given its position.
/// \param p Position of turret.

CDoor::CDoor(const Vector2& p) : CObject(eSprite::LockedDoor, p) {
    m_bStatic = true; //turrets are static
    m_isDoor = true;
} //constructor

/// Rotate the turret and fire the gun at at the closest available target if
/// there is one, and rotate the turret at a constant speed otherwise.

void CDoor::Lock() {

}

void CDoor::move() {
    if (m_pPlayer) { //safety
        //const float r = ((CTurret*)m_pPlayer)->m_fRadius; //player radius
        
    } //if

    m_fRoll += 0.2f * m_fRotSpeed * XM_2PI * m_pTimer->GetFrameTime(); //rotate
    NormalizeAngle(m_fRoll); //normalize to [-pi, pi] for accuracy
} //move

/// Response to collision. 
/// \param norm Collision normal.
/// \param d Overlap distance.
/// \param pObj Pointer to object being collided with (defaults to `nullptr`,
/// which means collision with a wall).

//bool CDoor::CanLeave() { return m_isStun; }

void CDoor::CollisionResponse(const Vector2& norm, float d, CObject* pObj) {
    if (m_pPlayer) {
        if (pObj->isPlayer() && m_nSpriteIndex == (UINT)eSprite::OpenDoor) {
            m_isStun = true;
            //m_pAudio->play(eSound::Ricochet);
        }
    }
} //CollisionResponse