/// \file Game.cpp
/// \brief Code for the game class CGame.

#include "Game.h"
#include "Arrows.h"
#include "GameDefines.h"
#include "SpriteRenderer.h"
#include "ComponentIncludes.h"
#include "ParticleEngine.h"
#include "TileManager.h"
#include "Windowdescriptor.h"
#include "shellapi.h"
#include <string.h>
/// Delete the renderer, the object manager, and the tile manager. The renderer
/// needs to be deleted before this destructor runs so it will be done elsewhere.

CGame::~CGame(){
  delete m_pParticleEngine;
  delete m_pObjectManager;
  delete m_pTileManager;
} //destructor

/// Initialize the renderer, the tile manager and the object manager, load 
/// images and sounds, and begin the game.

void CGame::Initialize(){
  m_pRenderer = new LSpriteRenderer(eSpriteMode::Batched2D); 
  m_pRenderer->Initialize(eSprite::Size); 
  LoadImages(); //load images from xml file list
  
  m_pTileManager = new CTileManager((size_t)m_pRenderer->GetWidth(eSprite::Tile));
  m_pObjectManager = new CObjectManager; //set up the object manager 
  LoadSounds(); //load the sounds for this game

  m_pParticleEngine = new LParticleEngine2D(m_pRenderer);

  BeginGame();
} //Initialize

/// Load the specific images needed for this game. This is where `eSprite`
/// values from `GameDefines.h` get tied to the names of sprite tags in
/// `gamesettings.xml`. Those sprite tags contain the name of the corresponding
/// image file. If the image tag or the image file are missing, then the game
/// should abort from deeper in the Engine code leaving you with an error
/// message in a dialog box.

void CGame::LoadImages(){  
  m_pRenderer->BeginResourceUpload();

  m_pRenderer->Load(eSprite::Tile,    "tile"); 
  m_pRenderer->Load(eSprite::Crystal0, "crystal0");
  m_pRenderer->Load(eSprite::Crystal1, "crystal1");
  m_pRenderer->Load(eSprite::ButtonUp, "buttonUp");
  m_pRenderer->Load(eSprite::ButtonDown, "buttonDown");
  m_pRenderer->Load(eSprite::Player,  "player");
  m_pRenderer->Load(eSprite::Bullet,  "bullet");
  m_pRenderer->Load(eSprite::Bullet2, "bullet2");
  m_pRenderer->Load(eSprite::Bullet3, "bullet3");
  m_pRenderer->Load(eSprite::Pulse,   "pulse");
  m_pRenderer->Load(eSprite::Smoke,   "smoke");
  m_pRenderer->Load(eSprite::Spark,   "spark");
  m_pRenderer->Load(eSprite::Turret,  "turret");
  m_pRenderer->Load(eSprite::Line,    "greenline"); 
  m_pRenderer->Load(eSprite::arrow_sprite, "arrow_sprite");
  m_pRenderer->Load(eSprite::OpenDoor, "OpenDoor");
  m_pRenderer->Load(eSprite::LockedDoor, "LockedDoor");
  m_pRenderer->Load(eSprite::PlayerStandRight, "vStandRight");
  m_pRenderer->Load(eSprite::PlayerStandLeft, "vStandLeft");
  m_pRenderer->Load(eSprite::PlayerWalkRightSpriteSheet, "vWalkRightSheet");
  m_pRenderer->Load(eSprite::PlayerWalkRight, "vWalkRight");
  m_pRenderer->Load(eSprite::PlayerWalkLeftSpriteSheet, "vWalkLeftSheet");
  m_pRenderer->Load(eSprite::PlayerWalkLeft, "vWalkLeft");
  m_pRenderer->Load(eSprite::PlayerStandDown, "vStandDown");
  m_pRenderer->Load(eSprite::PlayerStandUp, "vStandUp");
  m_pRenderer->Load(eSprite::PlayerWalkDownSpriteSheet, "vWalkDownSheet");
  m_pRenderer->Load(eSprite::PlayerWalkDown, "vWalkDown");
  m_pRenderer->Load(eSprite::PlayerWalkUpSpriteSheet, "vWalkUpSheet");
  m_pRenderer->Load(eSprite::PlayerWalkUp, "vWalkUp");
  m_pRenderer->Load(eSprite::PlayerWalkLeftUp, "vWalkUp");
  m_pRenderer->Load(eSprite::PlayerWalkLeftDown, "vWalkDown");
  m_pRenderer->Load(eSprite::PlayerWalkRightUp, "vWalkUp");
  m_pRenderer->Load(eSprite::PlayerWalkRightDown, "vWalkDown");
  m_pRenderer->Load(eSprite::KnightStandRight, "vSKstandRight");
  m_pRenderer->Load(eSprite::KnightStandLeft, "vSKstandLeft");
  m_pRenderer->Load(eSprite::KnightWalkRightSpriteSheet, "vSKwalkRightSheet");
  m_pRenderer->Load(eSprite::KnightWalkRight, "vSKwalkRight");
  m_pRenderer->Load(eSprite::KnightWalkLeftSpriteSheet, "vSKwalkLeftSheet");
  m_pRenderer->Load(eSprite::KnightWalkLeft, "vSKwalkLeft");
  m_pRenderer->Load(eSprite::KnightStandDown, "vSKstandDown");
  m_pRenderer->Load(eSprite::KnightStandUp, "vSKstandUp");
  m_pRenderer->Load(eSprite::KnightWalkDownSpriteSheet, "vSKwalkDownSheet");
  m_pRenderer->Load(eSprite::KnightWalkDown, "vSKwalkDown");
  m_pRenderer->Load(eSprite::KnightWalkUpSpriteSheet, "vSKwalkUpSheet");
  m_pRenderer->Load(eSprite::KnightWalkUp, "vSKwalkUp");
  m_pRenderer->Load(eSprite::KnightWalkLeftUp, "vSKwalkUp");
  m_pRenderer->Load(eSprite::KnightWalkLeftDown, "vSKwalkDown");
  m_pRenderer->Load(eSprite::KnightWalkRightUp, "vSKwalkUp");
  m_pRenderer->Load(eSprite::KnightWalkRightDown, "vSKwalkDown");
  

  m_pRenderer->EndResourceUpload();
} //LoadImages

/// Initialize the audio player and load game sounds.

void CGame::LoadSounds(){
  m_pAudio->Initialize(eSound::Size);
  m_pAudio->Load(eSound::Grunt, "grunt");
  m_pAudio->Load(eSound::Clang, "clang");
  m_pAudio->Load(eSound::Gun, "gun");
  m_pAudio->Load(eSound::Ricochet, "ricochet");
  m_pAudio->Load(eSound::Start, "start");
  m_pAudio->Load(eSound::Boom, "boom");
  m_pAudio->Load(eSound::Pulse, "pulse");
  m_pAudio->Load(eSound::Bump, "bump");
} //LoadSounds

/// Release all of the DirectX12 objects by deleting the renderer.

void CGame::Release(){
  delete m_pRenderer;
  m_pRenderer = nullptr; //for safety
} //Release

/// Ask the object manager to create a player object and turrets specified by
/// the tile manager.

void CGame::CreateObjects(){
  std::vector<Vector2> turretpos; //vector of turret positions
  Vector2 playerpos; //player positions
  std::vector<Vector2> knightpos;
  std::vector<Vector2> doorpos;
  std::vector<Vector2> arrowpos;
  std::vector<Vector2> switchpos;
  std::vector<Vector2> buttonpos;
  m_pTileManager->GetObjects(turretpos, playerpos, knightpos, doorpos, arrowpos, switchpos, buttonpos); //get positions
  
  //m_pPlayer = (CPlayer*)m_pObjectManager->create(eSprite::Player, playerpos);

  for(const Vector2& pos: turretpos)
    m_pObjectManager->create(eSprite::Turret, pos);

  for (const Vector2& pos : buttonpos)
      m_pObjectManager->create(eSprite::ButtonUp, pos);

  for (const Vector2& pos : knightpos)
      m_pObjectManager->create(eSprite::KnightStandDown, pos);

  for (const Vector2& pos : doorpos)
      m_pObjectManager->create(eSprite::LockedDoor, pos);

  for (const Vector2& pos : switchpos)
      m_pObjectManager->create(eSprite::Crystal0, pos);

  //for (const Vector2& pos : arrowpos)
   //   m_pObjectManager->create(eSprite::arrow_sprite, pos);

(arrows*)m_pObjectManager->create(eSprite::arrow_sprite, /*Vector2(100.0f, h / 2.0f)*/Vector2(500,500));

  // this is to create the standing sprite of the player
  const float h = m_pRenderer->GetHeight(eSprite::PlayerStandDown);
  m_pPlayer = (CPlayer*)m_pObjectManager->create(eSprite::PlayerStandDown, /*Vector2(100.0f, h / 2.0f)*/ playerpos);
  //Aimer = (arrows*)m_pObjectManager->create(eSprite::arrow_sprite, Vector2(100.0f, h / 2.0f));
} //CreateObjects

/// Call this function to start a new game. This should be re-entrant so that
/// you can restart a new game without having to shut down and restart the
/// program. Clear the particle engine to get rid of any existing particles,
/// delete any old objects out of the object manager and create some new ones.

void CGame::BeginGame(){  
  m_pParticleEngine->clear(); //clear old particles
  
  switch(m_nNextLevel){
    case 0: m_pTileManager->LoadMap("Media\\Maps\\map1.txt"); break;
    case 1: m_pTileManager->LoadMap("Media\\Maps\\map2.txt"); break;
    case 2: m_pTileManager->LoadMap("Media\\Maps\\map3.txt"); break;
    case 3: m_pTileManager->LoadMap("Media\\Maps\\map4.txt"); break;
    case 4: m_pTileManager->LoadMap("Media\\Maps\\map5.txt"); break;
    case 5: m_pTileManager->LoadMap("Media\\Maps\\map6.txt"); break;
    case 6: m_pTileManager->LoadMap("Media\\Maps\\test.txt"); break;
  } //switch

  m_pObjectManager->clear(); //clear old objects
  CreateObjects(); //create new objects (must be after map is loaded) 
  m_pAudio->stop(); //stop all  currently playing sounds
  m_pAudio->play(eSound::Start); //play start-of-game sound
  m_eGameState = eGameState::Playing; //now playing

  //numSwitch = m_pObjectManager->GetNumOffSwitch(); // currently unused
} //BeginGame

/// Poll the keyboard state and respond to the key presses that happened since
/// the last frame.

void CGame::KeyboardHandler(){
  m_pKeyboard->GetState(); //get current keyboard state
  
  if(m_pKeyboard->TriggerDown(VK_F1)) //help
    ShellExecute(0, 0, "https://larc.unt.edu/code/topdown/", 0, 0, SW_SHOW);
  
  if(m_pKeyboard->TriggerDown(VK_F2)) //toggle frame rate
    m_bDrawFrameRate = !m_bDrawFrameRate;
  
  if(m_pKeyboard->TriggerDown(VK_F3)) //toggle AABB drawing
    m_bDrawAABBs = !m_bDrawAABBs; 

  if(m_pKeyboard->TriggerDown(VK_BACK)) //start game
    BeginGame();

  if(m_pKeyboard->TriggerDown(VK_LBUTTON)) //fire gun
    m_pObjectManager->FireGun(m_pPlayer, eSprite::Bullet);

  if(m_pKeyboard->TriggerDown(VK_RBUTTON)) //fire gun
    m_pObjectManager->FireGun(m_pPlayer, eSprite::Bullet2);

  if(m_pKeyboard->TriggerDown(VK_MBUTTON)) //fire gun
    m_pObjectManager->FireGun(m_pPlayer, eSprite::Bullet3);

  if(m_pKeyboard->TriggerDown(VK_SPACE)) //fire gun
    m_pObjectManager->ShowPulse(m_pPlayer, eSprite::Pulse);

  if(m_pKeyboard->TriggerDown('H'))
    m_pObjectManager->m_pPlayer->m_fRoll = 50;//Take out the if statement because this is supposed to update every frame. This is just how we test it.

  if(m_pKeyboard->TriggerDown('G')) //toggle god mode
    m_bGodMode = !m_bGodMode;
} //KeyboardHandler

/// Poll the XBox controller state and respond to the controls there.

void CGame::ControllerHandler(){
  if(!m_pController->IsConnected())return;

  m_pController->GetState(); //get state of controller's controls 
  
  if(m_pPlayer){ //safety
      if (m_pPlayer == nullptr)return; // return if player is dead
   
      //L stick movement
     /* double arrowX2 = m_pController->GetLThumb().x * 3;
      double arrowY2 = m_pController->GetLThumb().y * 3;
      m_pPlayer->m_vPos.x += arrowX2;
      m_pPlayer->m_vPos.y += arrowY2;*/

    if (m_pController->GetButtonAToggle()) //fire gun
        m_pObjectManager->ShowPulse(m_pPlayer, eSprite::Pulse);
    if (m_pController->GetButtonYToggle()) //Dev button to advance to next level
    {
        if (m_bGodMode)
        {
            if (m_nNextLevel < 7)
                m_nNextLevel++;
            else
                m_nNextLevel = 0;
            m_eGameState = eGameState::Waiting;
        }
    }
    if (m_pController->GetButtonRSToggle()) //Turn on God Mode
        m_bGodMode = !m_bGodMode;
    if(m_pController->GetDPadRight()) //strafe right
      m_pPlayer->WalkRight();
    if(m_pController->GetDPadLeft()) //strafe left
      m_pPlayer->WalkLeft();
    if(m_pController->GetDPadDown()) //strafe back
      m_pPlayer->WalkDown();
    if (m_pController->GetDPadUp()) //strafe up
        m_pPlayer->WalkUp(); 
    if (m_pController->GetDPadUp() && m_pController->GetDPadLeft())
        m_pPlayer->WalkLeftUp();
    if (m_pController->GetDPadLeft() && m_pController->GetDPadDown())
        m_pPlayer->WalkLeftDown();
    if (m_pController->GetDPadUp() && m_pController->GetDPadRight())
        m_pPlayer->WalkRightUp();
    if (m_pController->GetDPadDown() && m_pController->GetDPadRight())
        m_pPlayer->WalkRightDown();
    if (!m_pController->GetDPadRight() && !m_pController->GetDPadLeft() && !m_pController->GetDPadUp() && !m_pController->GetDPadDown())
        m_pPlayer->Stop();

  } //if*/
} //ControllerHandler

/// Draw the current frame rate to a hard-coded position in the window.
/// The frame rate will be drawn in a hard-coded position using the font
/// specified in `gamesettings.xml`.

void CGame::DrawFrameRateText(){
  const std::string s = std::to_string(m_pTimer->GetFPS()) + " fps"; //frame rate
  const Vector2 pos(m_nWinWidth - 128.0f, 30.0f); //hard-coded position
  m_pRenderer->DrawScreenText(s.c_str(), pos); //draw to screen
} //DrawFrameRateText

/// Draw the god mode text to a hard-coded position in the window using the
/// font specified in `gamesettings.xml`.

void CGame::DrawGodModeText(){
  const Vector2 pos(64.0f, 30.0f); //hard-coded position
  //m_pRenderer->SetBgColor(Colors::White);
  m_pRenderer->DrawScreenText("God Mode", pos, Colors::Green); //draw to screen
} //DrawGodModeText

/// Ask the object manager to draw the game objects. The renderer is notified of
/// the start and end of the frame so that it can let Direct3D do its
/// pipelining jiggery-pokery.

void CGame::RenderFrame(){
  m_pRenderer->BeginFrame(); //required before rendering

  m_pObjectManager->draw(); //draw objects
  m_pParticleEngine->Draw(); //draw particles
  if(m_bDrawFrameRate)DrawFrameRateText(); //draw frame rate, if required
  if(m_bGodMode)DrawGodModeText(); //draw god mode text, if required    
  m_pRenderer->EndFrame(); //required after rendering
} //RenderFrame

/// Make the camera follow the player, but don't let it get too close to the
/// edge unless the world is smaller than the window, in which case we just
/// center everything.

/*void getWindow()
{
    if (Windowdescriptor::get() == GetFocus()) 
    {
        RECT rect;
        GetWindowRect(Windowdescriptor::get(), &rect);
        POINT cursor;
        GetCursorPos(&cursor);
        
    }
    //Note implement this later if you have extra time
}*/


void CGame::FollowCamera(){
  if(m_pPlayer == nullptr)return; //safety

  Vector3 vCameraPos(m_pPlayer->GetPos()); //player position

  if(m_vWorldSize.x > m_nWinWidth){ //world wider than screen
    vCameraPos.x = std::max(vCameraPos.x, m_nWinWidth/2.0f); //stay away from the left edge
    vCameraPos.x = std::min(vCameraPos.x, m_vWorldSize.x - m_nWinWidth/2.0f);  //stay away from the right edge
  } //if
  else vCameraPos.x = m_vWorldSize.x/2.0f; //center horizontally.
  
  if(m_vWorldSize.y > m_nWinHeight){ //world higher than screen
    vCameraPos.y = std::max(vCameraPos.y, m_nWinHeight/2.0f);  //stay away from the bottom edge
    vCameraPos.y = std::min(vCameraPos.y, m_vWorldSize.y - m_nWinHeight/2.0f); //stay away from the top edge
  } //if
  else vCameraPos.y = m_vWorldSize.y/2.0f; //center vertically

  m_pRenderer->SetCameraPos(vCameraPos); //camera to player
} //FollowCamera

/// This function will be called regularly to process and render a frame
/// of animation, which involves the following. Handle keyboard input.
/// Notify the audio player at the start of each frame so that it can prevent
/// multiple copies of a sound from starting on the same frame.  
/// Move the game objects. Render a frame of animation. 

void CGame::ProcessFrame(){
  KeyboardHandler(); //handle keyboard input
  ControllerHandler(); //handle controller input
  m_pAudio->BeginFrame(); //notify audio player that frame has begun
  
  m_pTimer->Tick([&](){ //all time-dependent function calls should go here
    m_pObjectManager->move(); //move all objects
    m_pTileManager->CheckForVisibility();
    FollowCamera(); //make camera follow player
    m_pParticleEngine->step(); //advance particle animation
    m_pObjectManager->PlayerPressButton(); // check if a button is being pressed
    m_pObjectManager->KnightPressButton();
  });

  RenderFrame(); //render a frame of animation
  ProcessGameState(); //check for end of game
} //ProcessFrame

/// Take action appropriate to the current game state. If the game is currently
/// playing, then if the player has been killed or all turrets have been
/// killed, then enter the wait state. If the game has been in the wait
/// state for longer than 3 seconds, then restart the game.

// Nathan here. This is the function we'll need to change once we start making more levels and puzzles
void CGame::ProcessGameState(){
  static float t = 0; //time at start of game

  //if (numSwitch == 1)
      //m_pAudio->play(eSound::Clang);

  switch(m_eGameState){
  case eGameState::Playing: {
      if (m_pPlayer == nullptr || m_pObjectManager->GetDoorEnter()) { //|| m_pObjectManager->GetNumTurrets() == 0){
          m_eGameState = eGameState::Waiting; //now waiting
          t = m_pTimer->GetTime(); //start wait timer
      } //if
      else if (m_pObjectManager->GetNumOffSwitch() == 0 && m_pObjectManager->GetNumButtonUp() == 0) {
          m_pObjectManager->UnlockDoor();
      }
  }
      break;

    case eGameState::Waiting:{
        if(m_pObjectManager->GetDoorEnter())
            m_nNextLevel = (m_nNextLevel + 1); //advance next level
        BeginGame(); //restart game
      } //if
      break;
  } //switch
} //CheckForEndOfGame

