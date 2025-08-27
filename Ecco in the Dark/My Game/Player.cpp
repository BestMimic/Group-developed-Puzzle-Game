/// \file Player.cpp
/// \brief Code for the player object class CPlayer.

#include "Player.h"
#include "ComponentIncludes.h"
#include "Arrows.h"
/// Create and initialize an player object given its initial position.
/// \param t Sprite type.
/// \param p Initial position of player.

CPlayer::CPlayer(eSprite t, const Vector2& p): CObject(t, p){ 
  m_pFrameEvent = new LEventTimer(0.12f);
  m_isPlayer = true;
  m_bStatic = false;
  m_bIsTarget = true;
  m_isPulse = false;
  this->m_fXScale *= 2.0f;
  this->m_fYScale *= 2.0f;
  this->m_fRadius *= 1.7f;
} //constructor

/// Destructor.

CPlayer::~CPlayer(){
  delete m_pFrameEvent;
} //destructor

void CPlayer::CollisionResponse(const Vector2& norm, float d, CObject* pObj) {
    if (m_bDead)return; //already dead, bail out 

    if (pObj && pObj->isBullet()) { //collision with bullet
        if (m_bGodMode) //god mode, does no damage
            m_pAudio->play(eSound::Grunt); //impact sound

        else if (--m_nHealth == 0) { //health decrements to zero means death 
            m_pAudio->play(eSound::Boom); //explosion
            m_bDead = true; //flag for deletion from object list
            DeathFX(); //particle effects
            m_pPlayer = nullptr; //clear common player pointer
        } //if

        else { //not a death blow
            m_pAudio->play(eSound::Grunt); //impact sound
            const float f = 0.5f + 0.5f * (float)m_nHealth / m_nMaxHealth; //health fraction
            m_f4Tint = XMFLOAT4(1.0f, f, f, 0); //redden the health indicator
        } //else
    } //if
    if (pObj && pObj->isKnight()) { //collision with bullet
        if (m_bGodMode) //god mode, does no damage
            m_pAudio->play(eSound::Grunt); //impact sound

        else if (--m_nHealth == 0) { //health decrements to zero means death 
            m_pAudio->play(eSound::Boom); //explosion
            m_bDead = true; //flag for deletion from object list
            DeathFX(); //particle effects
            m_pPlayer = nullptr; //clear common player pointer
        } //if

        else { //not a death blow
            m_pAudio->play(eSound::Grunt); //impact sound
            const float f = 0.5f + 0.5f * (float)m_nHealth / m_nMaxHealth; //health fraction
            m_f4Tint = XMFLOAT4(1.0f, f, f, 0); //redden the health indicator
        } //else
    } //if
    if (pObj)
    {
        if (!((pObj->m_nSpriteIndex == (UINT)eSprite::arrow_sprite)))
        {
            CObject::CollisionResponse(norm, d, pObj); //default collision response
        }
    }
    else 
    {
        CObject::CollisionResponse(norm, d, pObj); //default collision response
    }
} //CollisionResponse

void CPlayer::DeathFX() {
    LParticleDesc2D d; //particle descriptor
    d.m_vPos = m_vPos; //center particle at player center

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
    d.m_f4Tint = XMFLOAT4(Colors::OrangeRed);
    m_pParticleEngine->create(d);

    m_nSpriteIndex = (UINT)eSprite::PlayerStandDown;
} //DeathFX

/// Move in response to device input. The amount of motion is proportional to
/// the frame time.

void CPlayer::move(){
  const float delta = 200.0f*m_pTimer->GetFrameTime(); //change in position

  if (m_nSpriteIndex == (UINT)eSprite::PlayerWalkLeftUp) {
      m_vPos -= delta * Vector2::UnitX;
      m_vPos += delta * Vector2::UnitY;
  }

  if (m_nSpriteIndex == (UINT)eSprite::PlayerWalkLeftDown) {
      m_vPos -= delta * Vector2::UnitX;
      m_vPos -= delta * Vector2::UnitY;
  }

  if (m_nSpriteIndex == (UINT)eSprite::PlayerWalkRightUp) {
      m_vPos += delta * Vector2::UnitX;
      m_vPos += delta * Vector2::UnitY;
  }

  if (m_nSpriteIndex == (UINT)eSprite::PlayerWalkRightDown) {
      m_vPos += delta * Vector2::UnitX;
      m_vPos -= delta * Vector2::UnitY;
  }

  if(m_nSpriteIndex == (UINT)eSprite::PlayerWalkRight)
    m_vPos += delta*Vector2::UnitX; 

  if(m_nSpriteIndex == (UINT)eSprite::PlayerWalkLeft)
    m_vPos -= delta*Vector2::UnitX;

  if (m_nSpriteIndex == (UINT)eSprite::PlayerWalkDown)
      m_vPos -= delta * Vector2::UnitY;

  if (m_nSpriteIndex == (UINT)eSprite::PlayerWalkUp)
      m_vPos += delta * Vector2::UnitY;
  
  UpdateFramenumber(); //choose current frame
} //move

/// Update the frame number in the animation sequence.

void CPlayer::UpdateFramenumber(){
  const UINT n = (UINT)m_pRenderer->GetNumFrames(m_nSpriteIndex); //number of frames

  if(n > 1 && m_pFrameEvent && m_pFrameEvent->Triggered())
    m_nCurrentFrame = (m_nCurrentFrame + 1)%n; 
} //UpdateFramenumber

void arrows::UpdateFramenumber() {
    const UINT n = (UINT)m_pRenderer->GetNumFrames(m_nSpriteIndex); //number of frames

    if (n > 1 && m_pFrameEvent && m_pFrameEvent->Triggered())
        m_nCurrentFrame = (m_nCurrentFrame + 1) % n;
}

/// Change the sprite to the walking left sprite. This function will be called
/// in response to device inputs.

void CPlayer::WalkLeftUp() {
    if (m_nSpriteIndex != (UINT)eSprite::PlayerWalkLeftUp)
        m_nSpriteIndex = (UINT)eSprite::PlayerWalkLeftUp;
}//WalkLeftUp

void CPlayer::WalkLeftDown() {
    if (m_nSpriteIndex != (UINT)eSprite::PlayerWalkLeftDown)
        m_nSpriteIndex = (UINT)eSprite::PlayerWalkLeftDown;
}//WalkLeftDown

void CPlayer::WalkRightUp() {
    if (m_nSpriteIndex != (UINT)eSprite::PlayerWalkRightUp)
        m_nSpriteIndex = (UINT)eSprite::PlayerWalkRightUp;
}//WalkRightUp

void CPlayer::WalkRightDown() {
    if (m_nSpriteIndex != (UINT)eSprite::PlayerWalkRightDown)
        m_nSpriteIndex = (UINT)eSprite::PlayerWalkRightDown;
}//WalkRightDown

void CPlayer::WalkLeft(){
  if(m_nSpriteIndex != (UINT)eSprite::PlayerWalkLeft)
    m_nSpriteIndex = (UINT)eSprite::PlayerWalkLeft;
} //WalkLeft

/// Change the sprite to the walking right sprite. This function will be called
/// in response to device inputs.

void CPlayer::WalkRight(){
  if(m_nSpriteIndex != (UINT)eSprite::PlayerWalkRight)
    m_nSpriteIndex = (UINT)eSprite::PlayerWalkRight;
} //WalkRight

void CPlayer::WalkDown() {
    if (m_nSpriteIndex != (UINT)eSprite::PlayerWalkDown)
        m_nSpriteIndex = (UINT)eSprite::PlayerWalkDown;
} //WalkDown

void CPlayer::WalkUp() {
    if (m_nSpriteIndex != (UINT)eSprite::PlayerWalkUp)
        m_nSpriteIndex = (UINT)eSprite::PlayerWalkUp;
} //WalkUp

/// Change the sprite to a standing sprite, depending on which direction the
/// player is walking.

void CPlayer::Stop(){
  if (m_pPlayer == nullptr)return; // return if player is dead

  if(m_nSpriteIndex == (UINT)eSprite::PlayerWalkRight)
    m_nSpriteIndex = (UINT)eSprite::PlayerStandRight;
  
  if(m_nSpriteIndex == (UINT)eSprite::PlayerWalkLeft)
    m_nSpriteIndex = (UINT)eSprite::PlayerStandLeft;

  if (m_nSpriteIndex == (UINT)eSprite::PlayerWalkDown)
      m_nSpriteIndex = (UINT)eSprite::PlayerStandDown;

  if (m_nSpriteIndex == (UINT)eSprite::PlayerWalkUp)
      m_nSpriteIndex = (UINT)eSprite::PlayerStandUp;

  if (m_nSpriteIndex == (UINT)eSprite::PlayerWalkLeftUp)
      m_nSpriteIndex = (UINT)eSprite::PlayerStandUp;

  if (m_nSpriteIndex == (UINT)eSprite::PlayerWalkRightUp)
      m_nSpriteIndex = (UINT)eSprite::PlayerStandUp;

  if (m_nSpriteIndex == (UINT)eSprite::PlayerWalkLeftDown)
      m_nSpriteIndex = (UINT)eSprite::PlayerStandDown;

  if (m_nSpriteIndex == (UINT)eSprite::PlayerWalkRightDown)
      m_nSpriteIndex = (UINT)eSprite::PlayerStandDown;

  
  m_nCurrentFrame = 0;
} //Stop



const Vector2& CPlayer::GetPos() const {
    return m_vPos;
} //GetPos

