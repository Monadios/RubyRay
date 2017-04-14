#include<iostream>
#include<cstdlib>

#include "../Components/KeyBoardInputComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/DirectionComponent.h"
#include "../Components/SpeedComponent.h"

void KeyBoardInputComponent::update()
{

  /*
    Should Use event system here
    allow for user mapping of controls
   */
  SDL_PumpEvents();
  keyboard = SDL_GetKeyState(NULL);
  Camera* cam = p->get<Camera>();
  PositionComponent* pos = p->get<PositionComponent>();
  DirectionComponent* dir = p->get<DirectionComponent>();
  SpeedComponent* speed  = p->get<SpeedComponent>();

  if (keyboard[SDLK_UP])
    {
      if(worldMap[int(pos->x + dir->x * speed->moveSpeed)][int(pos->y)] == false) pos->x += dir->x * speed->moveSpeed;
      if(worldMap[int(pos->x)][int(pos->y + dir->y * speed->moveSpeed)] == false) pos->y += dir->y * speed->moveSpeed;
    }
  //move backwards if no wall behind you
  if (keyboard[SDLK_DOWN])
    {
      if(worldMap[int(pos->x - dir->x * speed->moveSpeed)][int(pos->y)] == false) pos->x -= dir->x * speed->moveSpeed;
      if(worldMap[int(pos->x)][int(pos->y - dir->y * speed->moveSpeed)] == false) pos->y -= dir->y * speed->moveSpeed;
    }
  //rotate to the right
  if (keyboard[SDLK_RIGHT])
    {
      //both camera p->direction and camera p->camera->pl must be rotated
      double oldPosDirX = dir->x;
      dir->x = dir->x * cos(-speed->rotSpeed) - dir->y * sin(-speed->rotSpeed);
      dir->y = oldPosDirX * sin(-speed->rotSpeed) + dir->y * cos(-speed->rotSpeed);
      double oldPosPlaneX = cam->plX;
      cam->plX = cam->plX * cos(-speed->rotSpeed) - cam->plY * sin(-speed->rotSpeed);
      cam->plY = oldPosPlaneX * sin(-speed->rotSpeed) + cam->plY * cos(-speed->rotSpeed);
    }
  //rotate to the left
  if (keyboard[SDLK_LEFT])
    {
      //both camera p->direction and camera cam->pl must be rotated
      double oldPosDirX = dir->x;
      dir->x = dir->x * cos(speed->rotSpeed) - dir->y * sin(speed->rotSpeed);
      dir->y = oldPosDirX * sin(speed->rotSpeed) + dir->y * cos(speed->rotSpeed);
      double oldPosPlaneX = cam->plX;
      cam->plX = cam->plX * cos(speed->rotSpeed) - cam->plY * sin(speed->rotSpeed);
      cam->plY = oldPosPlaneX * sin(speed->rotSpeed) + cam->plY * cos(speed->rotSpeed);
    }
}
