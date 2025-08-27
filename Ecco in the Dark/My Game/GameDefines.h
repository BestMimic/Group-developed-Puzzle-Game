/// \file GameDefines.h
/// \brief Game specific defines.

#ifndef __L4RC_GAME_GAMEDEFINES_H__
#define __L4RC_GAME_GAMEDEFINES_H__

#include "Defines.h"

/// \brief Sprite enumerated type.
///
/// An enumerated type for the sprites, which will be cast to an unsigned
/// integer and used for the index of the corresponding texture in graphics
/// memory. `Size` must be last.

enum class eSprite: UINT{
  Background, Bullet, Bullet2, Bullet3, Pulse, Player, Turret, Smoke, Spark, Tile, Crystal0, Crystal1, ButtonUp, ButtonDown, Line, arrow_sprite, OpenDoor, LockedDoor,
  PlayerWalkLeftSpriteSheet, PlayerWalkRightSpriteSheet, PlayerStandLeftSpriteSheet,
  PlayerStandRightSpriteSheet, PlayerWalkLeft, PlayerWalkRight, PlayerWalkDownSpriteSheet, 
  PlayerWalkUpSpriteSheet, PlayerStandDownSpriteSheet, PlayerStandUpSpriteSheet, 
  PlayerWalkLeftUp, PlayerWalkRightUp, PlayerWalkLeftDown, PlayerWalkRightDown,
  PlayerWalkDown, PlayerWalkUp, PlayerStandRight, PlayerStandDown, PlayerStandLeft, PlayerStandUp,
  KnightWalkLeftSpriteSheet, KnightWalkRightSpriteSheet, KnightStandLeftSpriteSheet,
  KnightStandRightSpriteSheet, KnightWalkLeft, KnightWalkRight, KnightWalkDownSpriteSheet,
  KnightWalkUpSpriteSheet, KnightStandDownSpriteSheet, KnightStandUpSpriteSheet,
  KnightWalkLeftUp, KnightWalkRightUp, KnightWalkLeftDown, KnightWalkRightDown,
  KnightWalkDown, KnightWalkUp, KnightStandRight, KnightStandDown, KnightStandLeft, KnightStandUp,
  Size  //MUST BE LAST
}; //eSprite

/// \brief Sound enumerated type.
///
/// An enumerated type for the sounds, which will be cast to an unsigned
/// integer and used for the index of the corresponding sample. `Size` must 
/// be last.

enum class eSound: UINT{
  Start, Boom, Clang, Grunt, Gun, Ricochet,Pulse,Bump,
  Size  //MUST BE LAST
}; //eSound

/// \brief Game state enumerated type.
///
/// An enumerated type for the game state, which can be either playing or
/// waiting a short interval for the level to end after winning or losing to
/// let sounds and particle effects play to the end without being cut short.

enum class eGameState{
  Playing, Waiting
}; //eGameState

#endif //__L4RC_GAME_GAMEDEFINES_H__
