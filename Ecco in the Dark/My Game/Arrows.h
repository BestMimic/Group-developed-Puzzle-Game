#ifndef __L4RC_GAME_ARROW
#define __L4RC_GAME_ARROW

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

class arrows : public CObject {
protected:
    LEventTimer* m_pFrameEvent = nullptr; ///< Frame event timer.

    void UpdateFramenumber(); ///< Update frame number.

public:

    
    static void aim();///Aiming aparatus
    arrows(const Vector2& p);
    const Vector2& GetArrowPos() const; ///< Get position of arrow
    void RotateAround(const Vector2&);
    void move();
    virtual void CollisionResponse(const Vector2&, float, CObject* = nullptr); ///< Collision response.
    //virtual ~arrows(); ///< Destructor.
}; //CPlayer
#endif 