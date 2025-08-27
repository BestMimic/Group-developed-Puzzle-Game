/// \file Pulse.cpp
/// \brief Code for the bullet object class CPulse.

#include "Pulse.h"
#include "ComponentIncludes.h"
#include "TileManager.h"
#include "Particle.h"
#include "ParticleEngine.h"
#include "Helpers.h"

/// Create and initialize a bullet object given its initial position.
/// \param t Sprite type of bullet.
/// \param p Initial position of bullet.

CPulse::CPulse(eSprite t, const Vector2& p) : CObject(t, p) {
    m_bIsBullet = false;
    //m_bStatic = true;
    m_bIsTarget = false;
    m_isPulse = true;
    start = m_pTimer->GetTime();
} //constructor

void CPulse::move()
{
    CObject::move();
    expand();
    checkForDeath();
}

void CPulse::expand()
{
    if (!m_bDead && m_bStatic && m_isPulse)
    {
        /*m_fXScale += 141.75f * m_pTimer->GetFrameTime();
        m_fYScale += 141.75f * m_pTimer->GetFrameTime();
        m_fRadius += 2268.0f * m_pTimer->GetFrameTime();*/

        m_fXScale += 70.875f * m_pTimer->GetFrameTime();
        m_fYScale += 70.875f * m_pTimer->GetFrameTime();
        m_fRadius += 1134.0f * m_pTimer->GetFrameTime();
    }
}

void CPulse::DelayDeath() {m_isStun = true;}

void CPulse::checkForDeath()
{
    if ((m_pTimer->GetTime() - start) >= 1.0f)
        m_isStun = false;
}

/// Response to collision, which for a bullet means playing a sound and a
/// particle effect, and then dying. 
/// \param norm Collision normal.
/// \param d Overlap distance.
/// \param pObj Pointer to object being collided with (defaults to nullptr).

void CPulse::CollisionResponse(const Vector2& norm, float d, CObject* pObj) {
    if (pObj == nullptr) //collide with edge of world
    {
        m_pAudio->play(eSound::Ricochet);
        m_pTileManager->ReactToPulse();
        if (count != 1)
        {
            m_pAudio->play(eSound::Bump);
            count = 1;
        }
    }
    //if (pObj->isDoor() || pObj->isSwitch() || pObj ->isKnight()) //Ignores Knight, Switches, and Doors
     

    //bullets die on collision

    if (!m_bDead)
    {
        //DelayDeath();
        if (pObj == nullptr)
        {
            m_bDead = true; //mark object for deletion
            DeathFX();
        }
    } //if
} //CollisionResponse

/// Create a smoke particle effect to mark the death of the bullet.

void CPulse::DeathFX() {
    LParticleDesc2D d; //particle descriptor

    d.m_nSpriteIndex = (UINT)eSprite::Smoke;
    d.m_vPos = m_vPos;
    d.m_fLifeSpan = 0.5f;
    d.m_fMaxScale = 0.5f;
    d.m_fScaleInFrac = 0.2f; 
    d.m_fFadeOutFrac = 0.8f;
    d.m_fScaleOutFrac = d.m_fFadeOutFrac;

    m_pParticleEngine->create(d); //create particle
} //DeathFX