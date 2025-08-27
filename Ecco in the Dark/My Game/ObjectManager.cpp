/// \file ObjectManager.cpp
/// \brief Code for the the object manager class CObjectManager.

#include "ObjectManager.h"
#include "ComponentIncludes.h"
#include "Arrows.h"
#include "Player.h"
#include "Turret.h"
#include "Bullet.h"
#include "Pulse.h"
#include "Knight.h"
#include "Door.h"
#include "Switches.h"
#include "Button.h"
#include "ParticleEngine.h"
#include "Helpers.h"
#include "GameDefines.h"
#include "TileManager.h"

/// Create an object and put a pointer to it at the back of the object list
/// `m_stdObjectList`, which it inherits from `LBaseObjectManager`.
/// \param t Sprite type.
/// \param pos Initial position.
/// \return Pointer to the object created.

CObject* CObjectManager::create(eSprite t, const Vector2& pos){
  CObject* pObj = nullptr;

  switch(t){ //create object of type t
    //case eSprite::Player:  pObj = new CPlayer(pos); break;
    case eSprite::Turret:  pObj = new CTurret(pos); break;
    case eSprite::OpenDoor:pObj = new CDoor(pos); break;
    case eSprite::LockedDoor:pObj = new CDoor(pos); break;
    case eSprite::Crystal0:pObj = new Switches(pos); break;
    case eSprite::Crystal1:pObj = new Switches(pos); break;
    case eSprite::ButtonUp:pObj = new CButton(pos); break;
    case eSprite::ButtonDown:pObj = new CButton(pos); break;
    case eSprite::Bullet:  pObj = new CBullet(eSprite::Bullet,  pos); break;
    case eSprite::Bullet2: pObj = new CBullet(eSprite::Bullet2, pos); break;
    case eSprite::Bullet3: pObj = new CBullet(eSprite::Bullet3, pos); break;
    case eSprite::Pulse:   pObj = new CPulse(eSprite::Pulse, pos); break;
    case eSprite::PlayerWalkLeft:pObj = new CPlayer(eSprite::PlayerWalkLeft, pos); break;
    case eSprite::PlayerWalkRight:pObj = new CPlayer(eSprite::PlayerWalkRight, pos); break;
    case eSprite::PlayerStandLeft:pObj = new CPlayer(eSprite::PlayerStandLeft, pos); break;
    case eSprite::PlayerStandRight:pObj = new CPlayer(eSprite::PlayerStandRight, pos); break;
    case eSprite::arrow_sprite:pObj = new arrows(pos); break;
    case eSprite::PlayerWalkDown:pObj = new CPlayer(eSprite::PlayerWalkDown, pos); break;
    case eSprite::PlayerWalkUp:pObj = new CPlayer(eSprite::PlayerWalkUp, pos); break;
    case eSprite::PlayerStandDown:pObj = new CPlayer(eSprite::PlayerStandDown, pos); break;
    case eSprite::PlayerStandUp:pObj = new CPlayer(eSprite::PlayerStandUp, pos); break;
    case eSprite::PlayerWalkLeftUp:pObj = new CPlayer(eSprite::PlayerWalkLeftUp, pos); break;
    case eSprite::PlayerWalkLeftDown:pObj = new CPlayer(eSprite::PlayerWalkLeftDown, pos); break;
    case eSprite::PlayerWalkRightUp:pObj = new CPlayer(eSprite::PlayerWalkRightUp, pos); break;
    case eSprite::PlayerWalkRightDown:pObj = new CPlayer(eSprite::PlayerWalkRightDown, pos); break;
    case eSprite::KnightWalkLeft:pObj = new CKnight(eSprite::KnightWalkLeft, pos); break;
    case eSprite::KnightWalkRight:pObj = new CKnight(eSprite::KnightWalkRight, pos); break;
    case eSprite::KnightStandLeft:pObj = new CKnight(eSprite::KnightStandLeft, pos); break;
    case eSprite::KnightStandRight:pObj = new CKnight(eSprite::KnightStandRight, pos); break;
    case eSprite::KnightWalkDown:pObj = new CKnight(eSprite::KnightWalkDown, pos); break;
    case eSprite::KnightWalkUp:pObj = new CKnight(eSprite::KnightWalkUp, pos); break;
    case eSprite::KnightStandDown:pObj = new CKnight(eSprite::KnightStandDown, pos); break;
    case eSprite::KnightStandUp:pObj = new CKnight(eSprite::KnightStandUp, pos); break;
    default: pObj = new CObject(t, pos);
  } //switch
  
  m_stdObjectList.push_back(pObj); //push pointer onto object list
  return pObj; //return pointer to created object
} //create

/// Draw the tiled background and the objects in the object list.

void CObjectManager::draw(){
  m_pTileManager->Draw(eSprite::Tile); //draw tiled background

  if(m_bDrawAABBs)
    m_pTileManager->DrawBoundingBoxes(eSprite::Line); //draw AABBs

  LBaseObjectManager::draw();
} //draw

/// Perform collision detection and response for each object with the world
/// edges and for all objects with another object, making sure that each pair
/// of objects is processed only once.

void CObjectManager::BroadPhase(){
  LBaseObjectManager::BroadPhase(); //collide with other objects

  //collide with walls

  for(CObject* pObj: m_stdObjectList) //for each object
    if(!pObj->m_bDead){ //for each non-dead object, that is
      for(int i=0; i<2; i++){ //can collide with 2 edges simultaneously
        Vector2 norm; //collision normal
        float d = 0; //overlap distance
        BoundingSphere s(Vector3(pObj->m_vPos), pObj->m_fRadius);
        
        if(m_pTileManager->CollideWithWall(s, norm, d)) //collide with wall
          pObj->CollisionResponse(norm, d); //respond 
      } //for
  } //for
} //BroadPhase

/// Perform collision detection and response for a pair of objects. Makes
/// use of the helper function Identify() because this function may be called
/// with the objects in an arbitrary order.
/// \param p0 Pointer to the first object.
/// \param p1 Pointer to the second object.

void CObjectManager::NarrowPhase(CObject* p0, CObject* p1){
  Vector2 vSep = p0->m_vPos - p1->m_vPos; //vector from *p1 to *p0
  const float d = p0->m_fRadius + p1->m_fRadius - vSep.Length(); //overlap

  if(d > 0.0f){ //bounding circles overlap
    vSep.Normalize(); //vSep is now the collision normal

    if (p0->m_isPlayer && p1->m_isPulse) {return;}

    p0->CollisionResponse( vSep, d, p1); //this changes separation of objects
    p1->CollisionResponse(-vSep, d, p0); //same separation and opposite normal
  } //if
} //NarrowPhase

/// Create a bullet object and a flash particle effect. It is assumed that the
/// object is round and that the bullet appears at the edge of the object in
/// the direction that it is facing and continues moving in that direction.
/// \param pObj Pointer to an object.
/// \param bullet Sprite type of bullet.

void CObjectManager::FireGun(CObject* pObj, eSprite bullet){
  m_pAudio->play(eSound::Gun);

  const Vector2 view = pObj->GetViewVector(); //firing object view vector

  //code to alter for the position of the bullet here

  double angleX = view.x;
  double angleY = view.y;

  float ARCTOA = atan2(angleY, angleX);
  ARCTOA = ARCTOA + 90;
  float position = ARCTOA;

  //view.x = cosf(angleX);
  //view.y = sinf(angleY);

  //end

  const float w0 = 0.5f*m_pRenderer->GetWidth(pObj->m_nSpriteIndex); //firing object width
  const float w1 = m_pRenderer->GetWidth(bullet); //bullet width
  const Vector2 pos = pObj->m_vPos + (w0 + w1) * view; //bullet initial position

  //create bullet object

  CObject* pBullet = create(bullet, pos); //create bullet
  
  const Vector2 norm = VectorNormalCC(view); //normal to view direction
  const float m = 2.0f*m_pRandom->randf() - 1.0f; //random deflection magnitude
  const Vector2 deflection = 0.01f*m*norm; //random deflection

  pBullet->m_vVelocity = pObj->m_vVelocity + 500.0f*(view + deflection);
  pBullet->m_fRoll  = pObj->m_fRoll;

  //particle effect for gun fire
  
  LParticleDesc2D d;

  d.m_nSpriteIndex = (UINT)eSprite::Spark;
  d.m_vPos = pos;
  d.m_vVel = pObj->m_fSpeed*view;
  d.m_fLifeSpan = 0.25f;
  d.m_fScaleInFrac = 0.4f;
  d.m_fFadeOutFrac = 0.5f;
  d.m_fMaxScale = 0.5f;
  d.m_f4Tint = XMFLOAT4(Colors::Yellow);
  
  m_pParticleEngine->create(d);
} //FireGun

void CObjectManager::ShowPulse(CObject* pObj, eSprite pulse) 
{
    m_pAudio->play(eSound::Pulse);
    const Vector2 view = pObj->GetViewVector(); //firing object view vector
    float w0 = 0.5f * m_pRenderer->GetWidth(pObj->m_nSpriteIndex); //firing object width
    float w1 = m_pRenderer->GetWidth(pulse); //pulse width
    Vector2 subHeight = Vector2(0.0f, m_pRenderer->GetHeight(pObj->m_nSpriteIndex));
    const Vector2 pos = pObj->m_vPos - subHeight; //pulse initial position
    CObject* pPulse = create(pulse, pos); //create pulse

    const Vector2 norm = VectorNormalCC(view); //normal to view direction
    const float m = 2.0f * m_pRandom->randf() - 1.0f; //random deflection magnitude
    const Vector2 deflection = 0.01f * m * norm; //random deflection

    //pPulse->m_vVelocity = pObj->m_vVelocity + 500.0f * (view + deflection);
    pPulse->m_fRoll = pObj->m_fRoll;

    //particle effect for gun fire

    /*LParticleDesc2D d;

    d.m_nSpriteIndex = (UINT)eSprite::Spark;
    d.m_vPos = pos;
    d.m_vVel = pObj->m_fSpeed * view;
    d.m_fLifeSpan = 0.25f;
    d.m_fScaleInFrac = 0.4f;
    d.m_fFadeOutFrac = 0.5f;
    d.m_fMaxScale = 0.5f;
    d.m_f4Tint = XMFLOAT4(Colors::Yellow);

    m_pParticleEngine->create(d);*/
}

double CObjectManager::pointer(CObject* pObj, eSprite bullet)
{
    m_pAudio->play(eSound::Gun);

    const Vector2 view = pObj->GetViewVector(); //firing object view vector
    const float w0 = 0.5f * m_pRenderer->GetWidth(pObj->m_nSpriteIndex); //firing object width
    const float w1 = m_pRenderer->GetWidth(bullet); //bullet width
    const Vector2 pos = pObj->m_vPos + (w0 + w1) * view; //bullet initial position
    
   


    
     // mouse coord display
    /*if (m_pPlayer) {
        HWND my_hWnd = GetFocus();
        POINT mousePos;
        RECT screenRect;
        GetCursorPos(&mousePos);
        GetWindowRect(my_hWnd, &screenRect);
        Vector2 camPos = m_pRenderer->GetCameraPos();
        Vector2 mapOffset = Vector2(
            (m_nWinWidth / 2.f) - (m_vWorldSize.x / 2.f),
            (m_nWinHeight / 2.f) - (m_vWorldSize.y / 2.f)
        );
        if (m_vWorldSize.x > m_nWinWidth)
            mapOffset.x = (m_nWinWidth / 2.f) - camPos.x;
        if (m_vWorldSize.y > m_nWinHeight)
            mapOffset.y = (m_nWinHeight / 2.f) - camPos.y;
        Vector2 mCoord = Vector2(
            mousePos.x - screenRect.left - mapOffset.x,
            m_nWinHeight - (mousePos.y - screenRect.top) - mapOffset.y
        );
        std::string coordTxt;
        coordTxt = "Mouse Coord: " + std::to_string(mCoord.x) + ", " + std::to_string(mCoord.y);
        m_pRenderer->DrawScreenText(coordTxt.c_str(), Vector2(20.f, 20.f));
        coordTxt = "Player Coord: " + std::to_string(m_pPlayer->GetPos().x) + ", " + std::to_string(m_pPlayer->GetPos().y);
        m_pRenderer->DrawScreenText(coordTxt.c_str(), Vector2(20.f, 60.f));
        coordTxt = "Camera Coord: " + std::to_string(camPos.x) + ", " + std::to_string(camPos.y);
        m_pRenderer->DrawScreenText(coordTxt.c_str(), Vector2(20.f, 180.f));
        coordTxt = "Screen/World Offset: " + std::to_string(mapOffset.x) + ", " + std::to_string(mapOffset.y);
        m_pRenderer->DrawScreenText(coordTxt.c_str(), Vector2(20.f, 140.f));
        coordTxt = "Rotation Angle: " + std::to_string((180.f / XM_PI) * atan2f(
            (mCoord.y - m_pPlayer->GetPos().y), (mCoord.x - m_pPlayer->GetPos().x)));
        m_pRenderer->DrawScreenText(coordTxt.c_str(), Vector2(20.f, 100.f));
    }*/
    // end mouse coord display

    //create bullet object

    CObject* pBullet = create(bullet, pos); //create bullet

    const Vector2 norm = VectorNormalCC(view); //normal to view direction
    const float m = 2.0f * m_pRandom->randf() - 1.0f; //random deflection magnitude
    const Vector2 deflection = 0.01f * m * norm; //random deflection

    pBullet->m_vVelocity = pObj->m_vVelocity + 500.0f * (view + deflection);
    pBullet->m_fRoll = pObj->m_fRoll;

    return 0;
}

/// Reader function for the number of turrets. 
/// \return Number of turrets in the object list.

const size_t CObjectManager::GetNumTurrets() const{
  size_t n = 0; //number of turrets
  
  for(CObject* pObj: m_stdObjectList) //for each object
    if(pObj->m_nSpriteIndex == (UINT)eSprite::Turret)
      n++;

  return n;
} //GetNumTurrets

const bool CObjectManager::GetNumOffSwitch() const {
    size_t n = 0; //number of switches

    for (CObject* pObj : m_stdObjectList) //for each object
        if (pObj->m_nSpriteIndex == (UINT)eSprite::Crystal0)
            n++;

    return n;
}

const bool CObjectManager::GetNumOnSwitch() const {
    size_t n = 0; //number of switches

    for (CObject* pObj : m_stdObjectList) //for each object
        if (pObj->m_nSpriteIndex == (UINT)eSprite::Crystal1)
            n++;

    return n;
}

const bool CObjectManager::GetNumButtonUp() const {
    size_t n = 0; //number of switches

    for (CObject* pObj : m_stdObjectList) //for each object
        if (pObj->m_nSpriteIndex == (UINT)eSprite::ButtonUp)
            n++;

    return n;
}

// this fuction check to see if the player or the knight is on the button
void CObjectManager::PlayerPressButton() {
    for (CObject* pObj : m_stdObjectList)
        if (pObj->m_nSpriteIndex == (UINT)eSprite::ButtonUp || pObj->m_nSpriteIndex == (UINT)eSprite::ButtonDown) {
            Vector2 buttPos = pObj->GetPos();
            for (CObject* presser : m_stdObjectList) {
                if (presser->isPlayer() /*|| presser->isKnight()*/) {
                    Vector2 presPos = presser->GetPos();
                    if ((buttPos.y - presPos.y < 25) && (buttPos.y - presPos.y > -25) && (buttPos.x - presPos.x < 25) && (buttPos.x - presPos.x > -25)) {
                        pObj->press();
                    }
                    //else if (presser->isPlayer() /*|| presser->isKnight()*/) {
                    //    Vector2 presPos = presser->GetPos();
                    //    if ((buttPos.y - presPos.y < 125) && (buttPos.y - presPos.y > -125) && (buttPos.x - presPos.x < 125) && (buttPos.x - presPos.x > -125)) {
                    //        pObj->press();
                    //    }
                    //}
                    else {
                        pObj->unPress();
                    }
                }
            }
        }   
}

void CObjectManager::KnightPressButton() {
    if (m_pPlayer == nullptr)return;

    for (CObject* pObj : m_stdObjectList)
        if (pObj->m_nSpriteIndex == (UINT)eSprite::ButtonUp || pObj->m_nSpriteIndex == (UINT)eSprite::ButtonDown) {
            Vector2 buttPos = pObj->GetPos();
            for (CObject* presser : m_stdObjectList) {
                if (/*presser->isPlayer() ||*/ presser->isKnight()) {
                    Vector2 presPos = presser->GetPos();
                    if ((buttPos.y - presPos.y < 25) && (buttPos.y - presPos.y > -25) && (buttPos.x - presPos.x < 25) && (buttPos.x - presPos.x > -25)) {
                        pObj->press();
                    }
                    //else if (presser->isPlayer() /*|| presser->isKnight()*/) {
                    //    Vector2 presPos = presser->GetPos();
                    //    if ((buttPos.y - presPos.y < 125) && (buttPos.y - presPos.y > -125) && (buttPos.x - presPos.x < 125) && (buttPos.x - presPos.x > -125)) {
                    //        pObj->press();
                    //    }
                    //}
                    else if ((buttPos.y - m_pPlayer->m_vPos.y > 25) && (buttPos.y - m_pPlayer->m_vPos.y < -25) && (buttPos.x - m_pPlayer->m_vPos.x > 25) && (buttPos.x - m_pPlayer->m_vPos.x < -25)) {
                        pObj->unPress();
                    }
                }
            }
        }
}

void CObjectManager::UnlockDoor() {
    for (CObject* pObj : m_stdObjectList)
        if (pObj->m_nSpriteIndex == (UINT)eSprite::LockedDoor)
            pObj->m_nSpriteIndex = (UINT)eSprite::OpenDoor;
            //m_pDoor->m_nSpriteIndex = (UINT)eSprite::OpenDoor);
}

// this allows the player to leave the level
const bool CObjectManager::GetDoorEnter(/*CObject* pObj, eSprite OpenDoor*/) const {
    bool touch = false;

    for (CObject* pObj : m_stdObjectList) //for each object
        if (pObj->m_nSpriteIndex == (UINT)eSprite::OpenDoor)
            touch = pObj->m_isStun;
            //touch = true;

    return touch;
}

const size_t CObjectManager::GetNumKnights() const {
    size_t n = 0; //number of turrets

    for (CObject* pObj : m_stdObjectList) //for each object
        if (pObj->m_nSpriteIndex == (UINT)eSprite::KnightStandDown)
            n++;

    return n;
} //GetNumKnights