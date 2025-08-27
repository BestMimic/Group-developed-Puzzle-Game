/// \file Knight.cpp

#include "Knight.h"
#include "ComponentIncludes.h"
#include "ObjectManager.h"
#include "TileManager.h"
#include "Player.h"
//#include "Pulse.h"
#include "Helpers.h"
#include "Particle.h"
#include "ParticleEngine.h"

/// Create and initialize a Knight object given its position.
/// \param p Position of turret.

CKnight::CKnight(eSprite t, const Vector2& p) : CObject(t, p) {
    m_pFrameEvent = new LEventTimer(0.12f);
    m_bStatic = false;
    m_isKnight = true;
    m_isStun = false;
    this->m_fXScale *= 2.0f;
    this->m_fYScale *= 2.0f;

    stuntime = 0.0f;
    this->m_fRadius *= 1.7f;
} //constructor

CKnight::~CKnight() {
    delete m_pFrameEvent;
} //destructor

void CKnight::move() {
    if (m_pPlayer) { //safety
        const float r = ((CKnight*)m_pPlayer)->m_fRadius; //player radius

        if (m_isStun) {
            Wake();
        }

        // VVV This can be used to chase the player VVV use m_pPlayer->m_vPos and the knight's position to determine
        // when the knight should charge

        if (m_pTileManager->Visible(m_vPos, m_pPlayer->m_vPos, r) && (m_pPlayer->m_vPos.y - m_vPos.y < 25) && (m_pPlayer->m_vPos.y - m_vPos.y > -25)
            && (m_pPlayer->m_vPos.x < m_vPos.x)) { //player visible 
            WalkLeft();
        }
        
        if (m_pTileManager->Visible(m_vPos, m_pPlayer->m_vPos, r) && (m_pPlayer->m_vPos.y - m_vPos.y < 25) && (m_pPlayer->m_vPos.y - m_vPos.y > -25)
            && (m_pPlayer->m_vPos.x > m_vPos.x)) { //player visible 
            WalkRight();
        }

        if (m_pTileManager->Visible(m_vPos, m_pPlayer->m_vPos, r) && (m_pPlayer->m_vPos.x - m_vPos.x < 25) && (m_pPlayer->m_vPos.x - m_vPos.x > -25)
            && (m_pPlayer->m_vPos.y < m_vPos.y)) { //player visible 
            WalkDown();
        }

        if (m_pTileManager->Visible(m_vPos, m_pPlayer->m_vPos, r) && (m_pPlayer->m_vPos.x - m_vPos.x < 25) && (m_pPlayer->m_vPos.x - m_vPos.x > -25)
            && (m_pPlayer->m_vPos.y > m_vPos.y)) { //player visible 
            WalkUp();
        }

        if (!m_pTileManager->Visible(m_vPos, m_pPlayer->m_vPos, r) || (m_isStun)) {
            Stop();
        }
    } //if

    //m_fRoll += 0.2f * m_fRotSpeed * XM_2PI * m_pTimer->GetFrameTime(); //rotate
    //NormalizeAngle(m_fRoll); //normalize to [-pi, pi] for accuracy

    // was 200.0f
    const float delta = 150.0f * m_pTimer->GetFrameTime(); //change in position

    if (m_nSpriteIndex == (UINT)eSprite::KnightWalkRight)
        m_vPos += delta * Vector2::UnitX;

    if (m_nSpriteIndex == (UINT)eSprite::KnightWalkLeft)
        m_vPos -= delta * Vector2::UnitX;

    if (m_nSpriteIndex == (UINT)eSprite::KnightWalkDown)
        m_vPos -= delta * Vector2::UnitY;

    if (m_nSpriteIndex == (UINT)eSprite::KnightWalkUp)
        m_vPos += delta * Vector2::UnitY;

    UpdateFramenumber(); //choose current frame
} //move

void CKnight::UpdateFramenumber() {
    const UINT n = (UINT)m_pRenderer->GetNumFrames(m_nSpriteIndex); //number of frames

    if (n > 1 && m_pFrameEvent && m_pFrameEvent->Triggered())
        m_nCurrentFrame = (m_nCurrentFrame + 1) % n;
} //UpdateFramenumber

void CKnight::WalkLeft() {
    if (m_nSpriteIndex != (UINT)eSprite::KnightWalkLeft)
        m_nSpriteIndex = (UINT)eSprite::KnightWalkLeft;
} //WalkLeft

/// Change the sprite to the walking right sprite. This function will be called
/// in response to device inputs.

void CKnight::WalkRight() {
    if (m_nSpriteIndex != (UINT)eSprite::KnightWalkRight)
        m_nSpriteIndex = (UINT)eSprite::KnightWalkRight;
} //WalkRight

void CKnight::WalkDown() {
    if (m_nSpriteIndex != (UINT)eSprite::KnightWalkDown)
        m_nSpriteIndex = (UINT)eSprite::KnightWalkDown;
} //WalkDown

void CKnight::WalkUp() {
    if (m_nSpriteIndex != (UINT)eSprite::KnightWalkUp)
        m_nSpriteIndex = (UINT)eSprite::KnightWalkUp;
} //WalkUp

void CKnight::Stop() {

    if (m_nSpriteIndex == (UINT)eSprite::KnightWalkRight)
        m_nSpriteIndex = (UINT)eSprite::KnightStandRight;

    if (m_nSpriteIndex == (UINT)eSprite::KnightWalkLeft)
        m_nSpriteIndex = (UINT)eSprite::KnightStandLeft;

    if (m_nSpriteIndex == (UINT)eSprite::KnightWalkDown)
        m_nSpriteIndex = (UINT)eSprite::KnightStandDown;

    if (m_nSpriteIndex == (UINT)eSprite::KnightWalkUp)
        m_nSpriteIndex = (UINT)eSprite::KnightStandUp;

    if (m_nSpriteIndex == (UINT)eSprite::KnightWalkLeftUp)
        m_nSpriteIndex = (UINT)eSprite::KnightStandUp;

    if (m_nSpriteIndex == (UINT)eSprite::KnightWalkRightUp)
        m_nSpriteIndex = (UINT)eSprite::PlayerStandUp;

    if (m_nSpriteIndex == (UINT)eSprite::KnightWalkLeftDown)
        m_nSpriteIndex = (UINT)eSprite::KnightStandDown;

    if (m_nSpriteIndex == (UINT)eSprite::KnightWalkRightDown)
        m_nSpriteIndex = (UINT)eSprite::KnightStandDown;


    m_nCurrentFrame = 0;
} //Stop

const Vector2& CKnight::GetPos() const {
    return m_vPos;
} //GetPos

/// Rotate the turret towards a point and file the gun if it is facing
/// sufficiently close to it.
/// \param pos Target point.

void CKnight::RotateTowards(const Vector2& pos) {
    const Vector2 v = pos - m_vPos; //vector from target to turret
    const float theta = atan2f(v.y, v.x); //orientation of that vector
    float diff = m_fRoll - theta; //difference with turret orientation
    NormalizeAngle(diff); //normalize to [-pi, pi]

    //set rotation speed from diff

    const float fAngleDelta = 0.05f; //allowable angle discrepancy
    const float fTrackingSpeed = 2.0f; //rotation speed when tracking

    if (diff > fAngleDelta)m_fRotSpeed = -fTrackingSpeed; //clockwise
    else if (diff < -fAngleDelta)m_fRotSpeed = fTrackingSpeed; //counterclockwise
    else m_fRotSpeed = 0; //stop rotating

    //fire gun if pointing approximately towards target

    if (fabsf(diff) < fAngleDelta && m_pGunFireEvent->Triggered())
        m_pObjectManager->FireGun(this, eSprite::Bullet2);
} //RotateTowards

/// Response to collision. 
/// \param norm Collision normal.
/// \param d Overlap distance.
/// \param pObj Pointer to object being collided with (defaults to `nullptr`,
/// which means collision with a wall).

void CKnight::Stun() {
    m_isStun = true;
}//Stun

void CKnight::Wake() {
    if (m_pTimer->GetTime() - stuntime >= 1.0f) {
        m_isStun = false;
    }
}

void CKnight::CollisionResponse(const Vector2& norm, float d, CObject* pObj) {
    if (m_bDead)return; //already dead, bail out 

    if (pObj && pObj->isBullet()) { //collision with bullet
        if (m_nHealth == 0) { //health decrements to zero means death 
            m_pAudio->play(eSound::Boom); //explosion
            m_bDead = true; //flag for deletion from object list
            DeathFX(); //particle effects
        } //if

        else { //not a death blow
            m_pAudio->play(eSound::Clang); //impact sound
            const float f = 0.5f + 0.5f * (float)m_nHealth / m_nMaxHealth; //health fraction

            Stun();
            stuntime = m_pTimer->GetTime();
            //stuntime = m_pTimer->GetFrameTime();

            //m_f4Tint = XMFLOAT4(1.0f, f, f, 0); //redden the sprite to indicate damage
        } //else
    } //if
    if (pObj)
    {
        if (!((pObj->m_nSpriteIndex == (UINT)eSprite::arrow_sprite)))
        {
            CObject::CollisionResponse(norm, d, pObj); //default collision response
        }
        if ((pObj->m_nSpriteIndex == (UINT)eSprite::Pulse))
        {
            CObject::CollisionResponse(norm, d, pObj); //default collision response
        }
    }
    else
    {
        CObject::CollisionResponse(norm, d, pObj); //default collision response
    }
} //CollisionResponse

/// Perform a particle effect to mark the death of the turret.

void CKnight::DeathFX() {
    LParticleDesc2D d; //particle descriptor
    d.m_vPos = m_vPos; //center particle at turret center

    d.m_nSpriteIndex = (UINT)eSprite::Smoke;
    d.m_fLifeSpan = 2.0f;
    d.m_fMaxScale = 4.0f;
    d.m_fScaleInFrac = 0.5f;
    d.m_fFadeOutFrac = 0.8f;
    d.m_fScaleOutFrac = 0;
    m_pParticleEngine->create(d);

    d.m_nSpriteIndex = (UINT)eSprite::Spark;
    d.m_fLifeSpan = 0.5f;
    d.m_fMaxScale = 1.5f;
    d.m_fScaleInFrac = 0.4f;
    d.m_fScaleOutFrac = 0.3f;
    d.m_fFadeOutFrac = 0.5f;
    d.m_f4Tint = XMFLOAT4(Colors::Orange);
    m_pParticleEngine->create(d);
} //DeathFX