#pragma once
#define __L4RC_SWITCH
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
#include "Switches.h"
#include "Player.h"
#include "Helpers.h"





Switches::Switches(const Vector2& p) : CObject(eSprite::Crystal0 , p) {
    m_bStatic = true;
    m_isSwitch = true;
    this->m_isStun = false;
    m_nSpriteIndex = (UINT)eSprite::Crystal0;
    //m_fRadius = 0;
};

void Switches::move()
{
    const float delta = 150.0f * m_pTimer->GetFrameTime(); //change in position

    //UpdateFramenumber(); //choose current frame
}

void Switches::UpdateFramenumber() {
    const UINT n = (UINT)m_pRenderer->GetNumFrames(m_nSpriteIndex); //number of frames

    //if (n > 1 && m_pFrameEvent && m_pFrameEvent->Triggered())
        m_nCurrentFrame = (m_nCurrentFrame + 1) % n;
} //UpdateFramenumber

void Switches::activation() 
{
    if (this->m_isStun == false) 
    {
        m_nSpriteIndex = (UINT)eSprite::Crystal1;
        m_pAudio->play(eSound::Clang);
        this->m_isStun = true;
    }
    else if (this->m_isStun == true)
    {
        m_pAudio->play(eSound::Bump);
        m_nSpriteIndex = (UINT)eSprite::Crystal0;
        this->m_isStun = false;
    }
        

        //  if (m_pPlayer) {}
    //return m_isStun;
}

void Switches::CollisionResponse(const Vector2& norm, float d, CObject* pObj)
{
    if (pObj && pObj->isBullet()) 
    { //collision with bullet
        //m_pAudio->play(eSound::Clang);
        activation();
    }
}

const Vector2& Switches::GetPos() const {
    return m_vPos;
}