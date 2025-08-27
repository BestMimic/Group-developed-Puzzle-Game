/// \file TileManager.h
/// \brief Interface for the tile manager CTileManager.

#ifndef __L4RC_GAME_TILEMANAGER_H__
#define __L4RC_GAME_TILEMANAGER_H__

#include <vector>

#include "Common.h"
#include "Component.h"
#include "Settings.h"
#include "Sprite.h"
#include "GameDefines.h"

/// \brief The tile manager.
///
/// The tile manager is responsible for the tile-based background.

class CTileManager: 
  public CCommon, 
  public LSettings,
  public LComponent
{
  private:
    size_t m_nWidth = 0; ///< Number of tiles wide.
    size_t m_nHeight = 0; ///< Number of tiles high.
    bool turnVisible = false;
    bool visibility = false;
    bool decreasing = false;
    float rgb = 0.0f;
    float start = 0.0f;
    

    float m_fTileSize = 0.0f; ///< Tile width and height.

    char** m_chMap = nullptr; ///< The level map.

    std::vector<BoundingBox> m_vecWalls; ///< AABBs for the walls.
    std::vector<Vector2> m_vecCrystal;///< Switch
    std::vector<Vector2> m_vecTurrets; ///< Turret positions.
    std::vector<Vector2> m_vecKights; ///< Silent Knight positions.
    std::vector<Vector2> m_vecDoors; ///< Position of door.
    std::vector<Vector2> m_vecSights; ///< Places where the knights can see you. (unused)
    std::vector<Vector2> m_vecArrow; ///Arrow position
    std::vector<Vector2> m_vecSwitches; ///< switch position
    std::vector<Vector2> m_vecButtons; ///< botton position
    Vector2 m_vPlayer; ///< Player location.

    void MakeBoundingBoxes(); ///< Make bounding boxes for walls.

  public:
    CTileManager(size_t); ///< Constructor.
    ~CTileManager(); ///< Destructor.

    void LoadMap(char*); ///< Load a map.
    void Draw(eSprite); ///< Draw the map with a given tile.
    void ReactToPulse();
    void CheckForVisibility();
    void DrawBoundingBoxes(eSprite); ///< Draw the bounding boxes.
    ///psst. Nathan here. VVV This will probably need to be changed every time a new object is added to the map VVV
    void GetObjects(std::vector<Vector2>&, Vector2&, std::vector<Vector2>&, std::vector<Vector2>&, std::vector<Vector2>&, std::vector<Vector2>&, std::vector<Vector2>&); ///< Get objects.

    const bool Visible(const Vector2&, const Vector2&, float) const; ///< Check visibility.
    const bool CollideWithWall(BoundingSphere, Vector2&, float&) const; ///< Object-wall collision test.

}; //CTileManager

#endif //__L4RC_GAME_TILEMANAGER_H__