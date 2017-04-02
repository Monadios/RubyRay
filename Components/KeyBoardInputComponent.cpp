#include "../Components/KeyBoardInputComponent.h"
#include<iostream>
void KeyBoardInputComponent::update()
{

  /*
    Should Use event system here
    allow for user mapping of controls
   */
  SDL_PumpEvents();
  keyboard = SDL_GetKeyState(NULL);
  Camera* cam = p->get<Camera>();

  if (keyboard[SDLK_UP])
    {
      if(worldMap[int(p->posX + p->dirX * p->moveSpeed)][int(p->posY)] == false) p->posX += p->dirX * p->moveSpeed;
      if(worldMap[int(p->posX)][int(p->posY + p->dirY * p->moveSpeed)] == false) p->posY += p->dirY * p->moveSpeed;
    }
  //move backwards if no wall behind you
  if (keyboard[SDLK_DOWN])
    {
      if(worldMap[int(p->posX - p->dirX * p->moveSpeed)][int(p->posY)] == false) p->posX -= p->dirX * p->moveSpeed;
      if(worldMap[int(p->posX)][int(p->posY - p->dirY * p->moveSpeed)] == false) p->posY -= p->dirY * p->moveSpeed;
    }
  //rotate to the right
  if (keyboard[SDLK_RIGHT])
    {
      //both camera p->direction and camera p->camera->pl must be rotated
      double oldPosDirX = p->dirX;
      p->dirX = p->dirX * cos(-p->rotSpeed) - p->dirY * sin(-p->rotSpeed);
      p->dirY = oldPosDirX * sin(-p->rotSpeed) + p->dirY * cos(-p->rotSpeed);
      double oldPosPlaneX = cam->plX;
      cam->plX = cam->plX * cos(-p->rotSpeed) - cam->plY * sin(-p->rotSpeed);
      cam->plY = oldPosPlaneX * sin(-p->rotSpeed) + cam->plY * cos(-p->rotSpeed);
    }
  //rotate to the left
  if (keyboard[SDLK_LEFT])
    {
      //both camera p->direction and camera cam->pl must be rotated
      double oldPosDirX = p->dirX;
      p->dirX = p->dirX * cos(p->rotSpeed) - p->dirY * sin(p->rotSpeed);
      p->dirY = oldPosDirX * sin(p->rotSpeed) + p->dirY * cos(p->rotSpeed);
      double oldPosPlaneX = cam->plX;
      cam->plX = cam->plX * cos(p->rotSpeed) - cam->plY * sin(p->rotSpeed);
      cam->plY = oldPosPlaneX * sin(p->rotSpeed) + cam->plY * cos(p->rotSpeed);
    }

  if(keyboard[SDLK_SPACE]){
    p->shoot = true;
  }

}
