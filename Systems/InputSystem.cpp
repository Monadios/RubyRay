#include<iostream>
#include<cstdlib>
#include<cmath>

#include "../Components/KeyBoardInputComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/DirectionComponent.h"
#include "../Components/SpeedComponent.h"
#include "../Systems/InputSystem.h"

void InputSystem::update(std::vector<GameObject*>& entities)
{
  SDL_PumpEvents();
  keyboard = SDL_GetKeyState(NULL);
  for(GameObject* e : entities){
    Camera* cam = e->get<Camera>();
    PositionComponent* pos = e->get<PositionComponent>();
    DirectionComponent* dir = e->get<DirectionComponent>();
    SpeedComponent* speed  = e->get<SpeedComponent>();
    KeyBoardInputComponent* keys = e->get<KeyBoardInputComponent>();
    // Find better way of filtering out incompatible entities
    if(cam == nullptr || pos == nullptr || dir == nullptr
       || speed == nullptr || keys == nullptr){
      continue;
    }

    oldTime = time;
    time = QuickCG::getTicks();
    double frameTime = (time - oldTime) / 1000.0; //frametime is the time this frame has taken, in seconds
    e->get<SpeedComponent>()->moveSpeed = frameTime * e->get<SpeedComponent>()->rotFac;
    e->get<SpeedComponent>()->rotSpeed = frameTime * e->get<SpeedComponent>()->movFac;



    if (keyboard[SDLK_UP])
      {
	if(keys->worldMap[int(pos->x + dir->x * speed->moveSpeed)][int(pos->y)] == false) pos->x += dir->x * speed->moveSpeed;
	if(keys->worldMap[int(pos->x)][int(pos->y + dir->y * speed->moveSpeed)] == false) pos->y += dir->y * speed->moveSpeed;
      }
    //move backwards if no wall behind you
    if (keyboard[SDLK_DOWN])
      {
	if(keys->worldMap[int(pos->x - dir->x * speed->moveSpeed)][int(pos->y)] == false) pos->x -= dir->x * speed->moveSpeed;
	if(keys->worldMap[int(pos->x)][int(pos->y - dir->y * speed->moveSpeed)] == false) pos->y -= dir->y * speed->moveSpeed;
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

    if(keyboard[SDLK_SPACE])
      {
	double x = e->get<DirectionComponent>()->x;
	double y = e->get<DirectionComponent>()->y;

	/*
	  The angle is calculated as the angle between the (0,1) vector and the
	  player direction (x,y) vector.
	  http://stackoverflow.com/questions/5188561/signed-angle-between-two-3d-vectors-with-same-origin-within-the-same-plane
	*/

	double angle = acos(x/(sqrt(pow(x,2)+pow(y,2))));
	double degrees = angle * (180/3.14159);
	if(keys->worldMap[pos->x+(1*cos(angle))][pos->y+(1*sin(angle))] == 2){
	  keys->worldMap[pos->x+(1*cos(angle))][pos->y+(1*sin(angle))] = 0;
	}
      }
  }
}
