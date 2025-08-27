#pragma once
#define __L4RC_BUTTON
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
#include "Button.h"
#include "Player.h"
#include "Helpers.h"





CButton::CButton(const Vector2& p) : CObject(eSprite::ButtonUp, p) {
    m_bStatic = true;
    m_isSwitch = true;
    this->m_isStun = true;
    m_nSpriteIndex = (UINT)eSprite::ButtonUp;
    //m_fRadius = 0;
};

void CButton::move()
{
    const float delta = 150.0f * m_pTimer->GetFrameTime(); //change in position

    //UpdateFramenumber(); //choose current frame
}

void CButton::UpdateFramenumber() {
    const UINT n = (UINT)m_pRenderer->GetNumFrames(m_nSpriteIndex); //number of frames

    //if (n > 1 && m_pFrameEvent && m_pFrameEvent->Triggered())
    m_nCurrentFrame = (m_nCurrentFrame + 1) % n;
} //UpdateFramenumber

void CButton::press() {
    //if (this->m_isStun) {
        activation();
    //}
    /*else {
        
        Deactivate();
    }*/
}

void CButton::unPress() {
    Deactivate();
}

void CButton::Deactivate() {
    /*if (!this->m_isStun)
        m_pAudio->play(eSound::Bump);*/
    m_nSpriteIndex = (UINT)eSprite::ButtonUp;
    this->m_isStun = true;
}

void CButton::activation()
{
    m_nSpriteIndex = (UINT)eSprite::ButtonDown;
    m_pAudio->play(eSound::Clang);
    /*if (m_nSpriteIndex == (UINT)eSprite::ButtonDown)
        m_pAudio->play(eSound::Bump);*/
    this->m_isStun = false;
    /*else if (this->m_isStun == true)
    {
        m_pAudio->play(eSound::Bump);
        m_nSpriteIndex = (UINT)eSprite::ButtonUp;
        this->m_isStun = false;
    }*/


    //  if (m_pPlayer) {}
//return m_isStun;
}

void CButton::CollisionResponse(const Vector2& norm, float d, CObject* pObj)
{
    //if (pObj && pObj->isBullet())
    //{ //collision with bullet
    //    //m_pAudio->play(eSound::Clang);
    //    activation();
    //}
}

const Vector2& CButton::GetPos() const {
    return m_vPos;
}