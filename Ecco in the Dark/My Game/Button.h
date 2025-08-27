#pragma once
#ifndef __L4RC_GAME_BUTTON
#define __L4RC_GAME_BUTTON

#include "GameDefines.h"
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

class CButton : public CObject {
protected:
    LEventTimer* m_pFrameEvent = nullptr; ///< Frame event timer.

    void UpdateFramenumber(); ///< Update frame number.

public:

    CButton(const Vector2& p);
    void move();
    virtual void CollisionResponse(const Vector2&, float, CObject* = nullptr); ///< Collision response.
    virtual void press();
    virtual void unPress();
    void Deactivate();
    void activation();
    const Vector2& GetPos() const;
    //virtual ~arrows(); ///< Destructor.
}; //CButton



#endif
