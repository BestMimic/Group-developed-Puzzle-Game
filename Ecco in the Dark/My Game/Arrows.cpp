#pragma once
#define __L4RC_ARROW
#include "SpriteRenderer.h"
#include "Common.h"
#include "Component.h"
#include "SpriteDesc.h"
#include "BaseObject.h"
#include "EventTimer.h"
#include "Game.h"
#include "GameDefines.h"
#include "ComponentIncludes.h"
#include "ParticleEngine.h"
#include "TileManager.h"
#include "Windowdescriptor.h"
#include "shellapi.h"
#include <string.h>
#include "Arrows.h"
#include "Player.h"
#include "Helpers.h"


arrows::arrows(const Vector2& p) : CObject(eSprite::arrow_sprite, p) {
    m_bStatic = true;
    m_fRadius = 0;
};


void arrows::move()
{
    CObject::move();
    if (m_pPlayer) 
    { //safety
       this->m_vPos = m_pPlayer->GetPos();
       
        const float r = ((arrows*)m_pPlayer)->m_fRadius; //player radius
        if (m_pTileManager->Visible(m_vPos, m_pPlayer->m_vPos, r))
            RotateAround(m_pPlayer->m_vPos);
        if (m_pController->GetButtonBToggle()) //fire gun
            m_pObjectManager->FireGun(this, eSprite::Bullet2);
        if (m_pController->GetButtonYToggle()) //fire gun
            m_pObjectManager->FireGun(this, eSprite::Bullet);
        if (m_pController->GetButtonXToggle()) //fire gun
            m_pObjectManager->FireGun(this, eSprite::Bullet3);
        

       // NormalizeAngle(m_fRoll);
        //m_pPlayer->m_vPos
      // if (m_pTileManager->Visible(m_vPos, m_pPlayer->m_vPos, r)) //player visible
          
           
        
       
    } 
}

void arrows::CollisionResponse(const Vector2& norm, float d, CObject* pObj) 
{

}

void arrows::RotateAround(const Vector2& pos)
{
    const Vector2 v = m_pPlayer->m_vPos;
    Vector3 GetArrowPos;
    if (m_nSpriteIndex == (UINT)eSprite::arrow_sprite)
        m_nSpriteIndex = (UINT)eSprite::arrow_sprite;
    double arrowX = m_pController->GetRThumb().x;
    double arrowY = m_pController->GetRThumb().y;
    double TOA = arrowY / arrowX;
    float diff = m_fRoll - TOA;
    float ARCTOA = atan2(arrowY, arrowX);
    float position = ARCTOA;
    NormalizeAngle(position);
    m_fRoll = position - 1.5708;

    //this->m_vPos.x += sqrt(pow(arrowX, 2) / (pow(arrowY, 2) + pow(arrowX, 2))) * 80;
   // this->m_vPos.y += sqrt(pow(arrowY, 2) / (pow(arrowY, 2) + pow(arrowX, 2))) * 80;
    if (arrowX >= 0) 
    {
        this->m_vPos.x += sqrt(pow(arrowX, 2) / (pow(arrowY, 2) + pow(arrowX, 2))) * 80;

    }
    else
    {
       this->m_vPos.x -= sqrt(pow(arrowX, 2) / (pow(arrowY, 2) + pow(arrowX, 2))) * 80;

    }
    if (arrowY >= 0)
    {
        this->m_vPos.y += sqrt(pow(arrowY, 2) / (pow(arrowY, 2) + pow(arrowX, 2))) * 80;

    }
    else
    {
        this->m_vPos.y -= sqrt(pow(arrowY, 2) / (pow(arrowY, 2) + pow(arrowX, 2))) * 80;

    }
}

//git test

/*void arrows::aim()
{

    Vector3 GetArrowPos;
    if (m_nSpriteIndex == (UINT)eSprite::arrow_sprite)
        m_nSpriteIndex = (UINT)eSprite::arrow_sprite;
    double arrowX = m_pController->GetRThumb().x;
    double arrowY = m_pController->GetRThumb().y;
    double TOA = arrowY / arrowX;
    float ARCTOA = atan2(arrowY, arrowX);
    Aimer->m_fRoll = ARCTOA;
    Aimer->m_vPos = m_vPos;
}


arrows::arrows(eSprite t, const Vector2& p) : CObject(t, p) {
    m_pFrameEvent = new LEventTimer(0.12f);
    m_isPlayer = false;
    m_bStatic = false;
    m_isPulse = false;
    m_fXScale *= 2.0f;
    m_fYScale *= 2.0f;
}

arrows::~arrows() {
    delete m_pFrameEvent;
}*/

