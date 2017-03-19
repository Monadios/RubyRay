#include "./Utils/quickcg.h"

void render()
{
  for(int x = 0; x < w; x++)
    {
      //calculate ray position and direction
      double cameraX = 2 * x / double(w) - 1; //x-coordinate in camera space
      double rayPosX = p->posX;
      double rayPosY = p->posY;
      double rayDirX = p->dirX + p->planeX * cameraX;
      double rayDirY = p->dirY + p->planeY * cameraX;

      //which box of the map we're in
      int mapX = int(rayPosX);
      int mapY = int(rayPosY);

      //length of ray from current position to next x or y-side
      double sideDistX;
      double sideDistY;

      //length of ray from one x or y-side to next x or y-side
      double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
      double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
      double perpWallDist;

      //what direction to step in x or y-direction (either +1 or -1)
      int stepX;
      int stepY;

      int hit = 0; //was there a wall hit?
      int side; //was a NS or a EW wall hit?

      //calculate step and initial sideDist
      if (rayDirX < 0)
	{
	  stepX = -1;
	  sideDistX = (rayPosX - mapX) * deltaDistX;
	}
      else
	{
	  stepX = 1;
	  sideDistX = (mapX + 1.0 - rayPosX) * deltaDistX;
	}
      if (rayDirY < 0)
	{
	  stepY = -1;
	  sideDistY = (rayPosY - mapY) * deltaDistY;
	}
      else
	{
	  stepY = 1;
	  sideDistY = (mapY + 1.0 - rayPosY) * deltaDistY;
	}
      //perform DDA
      while (hit == 0)
	{
	  //jump to next map square, OR in x-direction, OR in y-direction
	  if (sideDistX < sideDistY)
	    {
	      sideDistX += deltaDistX;
	      mapX += stepX;
	      side = 0;
	    }
	  else
	    {
	      sideDistY += deltaDistY;
	      mapY += stepY;
	      side = 1;
	    }
	  //Check if ray has hit a wall
	  if (worldMap[mapX][mapY] > 0) hit = 1;
	}

      //Calculate distance of perpendicular ray (oblique distance will give fisheye effect!)
      if (side == 0) perpWallDist = (mapX - rayPosX + (1 - stepX) / 2) / rayDirX;
      else           perpWallDist = (mapY - rayPosY + (1 - stepY) / 2) / rayDirY;

      //Calculate height of line to draw on screen
      int lineHeight = (int)(h / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + h / 2;
      if(drawStart < 0) drawStart = 0;
      int drawEnd = lineHeight / 2 + h / 2;
      if(drawEnd >= h) drawEnd = h - 1;
      //texturing calculations
      int texNum = worldMap[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

      //calculate value of wallX
      double wallX; //where exactly the wall was hit
      if (side == 0) wallX = rayPosY + perpWallDist * rayDirY;
      else           wallX = rayPosX + perpWallDist * rayDirX;
      wallX -= floor((wallX));

      //x coordinate on the texture
      int texX = int(wallX * double(texWidth));
      if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
      if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;
      for(int y = drawStart; y < drawEnd; y++)
	{
	  int d = y * 256 - h * 128 + lineHeight * 128; //256 and 128 factors to avoid floats
	  int texY = ((d * texHeight) / lineHeight) / 256;
	  int color = texture[texNum][texWidth * texY + texX];
	  //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
	  if(side == 1) color = (color >> 1) & 8355711;
	  buffer[y][x] = color;
	}

      //SET THE ZBUFFER FOR THE SPRITE CASTING
      ZBuffer[x] = perpWallDist; //perpendicular distance is used

      //FLOOR CASTING
      double floorXWall, floorYWall; //x, y position of the floor texel at the bottom of the wall

      //4 different wall directions possible
      if(side == 0 && rayDirX > 0)
	{
	  floorXWall = mapX;
	  floorYWall = mapY + wallX;
	}
      else if(side == 0 && rayDirX < 0)
	{
	  floorXWall = mapX + 1.0;
	  floorYWall = mapY + wallX;
	}
      else if(side == 1 && rayDirY > 0)
	{
	  floorXWall = mapX + wallX;
	  floorYWall = mapY;
	}
      else
	{
	  floorXWall = mapX + wallX;
	  floorYWall = mapY + 1.0;
	}

      double distWall, distPlayer;

      distWall = perpWallDist;
      distPlayer = 0.0;
      if (drawEnd < 0) drawEnd = h; //becomes < 0 when the integer overflows
      //draw the floor from drawEnd to the bottom of the screen
      for(int y = drawEnd + 1; y < h; y++)
	{
	  currentDist = h / (2.0 * y - h); //you could make a small lookup table for this instead
	  double weight = (currentDist - distPlayer) / (distWall - distPlayer);

	  double currentFloorX = weight * floorXWall + (1.0 - weight) * p->posX;
	  double currentFloorY = weight * floorYWall + (1.0 - weight) * p->posY;

	  int floorTexX, floorTexY;
	  floorTexX = int(currentFloorX * texWidth) % texWidth;
	  floorTexY = int(currentFloorY * texHeight) % texHeight;

	  //floor
	  buffer[y][x] = (texture[3][texWidth * floorTexY + floorTexX] >> 1) & 8355711;
	  //ceiling (symmetrical!)
	  buffer[h - y][x] = texture[6][texWidth * floorTexY + floorTexX];

	}
    }

  //SPRITE CASTING
  //sort sprites from far to close
  for(int i = 0; i < numObstacles; i++)
    {
      spriteOrder[i] = i;
      spriteDistance[i] = ((p->posX - sprite[i]->x) * (p->posX - sprite[i]->x) + (p->posY - sprite[i]->y) * (p->posY - sprite[i]->y)); //sqrt not taken, unneeded
    }
  combSort(spriteOrder, spriteDistance, numObstacles);

  std::for_each(std::begin(sprite), std::end(sprite), [=](GameObject* e)
		{
		  e->update();
		});

  //after sorting the sprites, do the projection and draw them
  for(int i = 0; i < numObstacles; i++)
    {
      //translate sprite position to relative to camera
      double spriteX = sprite[spriteOrder[i]]->x - p->posX;
      double spriteY = sprite[spriteOrder[i]]->y - p->posY;

      //transform sprite with the inverse camera matrix
      // [ p->planeX   p->dirX ] -1                                       [ p->dirY      -p->dirX ]
      // [               ]       =  1/(p->planeX*p->dirY-p->dirX*p->planeY) *   [                 ]
      // [ p->planeY   p->dirY ]                                          [ -p->planeY  p->planeX ]

      double invDet = 1.0 / (p->planeX * p->dirY - p->dirX * p->planeY); //required for correct matrix multiplication

      double transformX = invDet * (p->dirY * spriteX - p->dirX * spriteY);
      double transformY = invDet * (-p->planeY * spriteX + p->planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

      int spriteScreenX = int((w / 2) * (1 + transformX / transformY));

      //parameters for scaling and moving the sprites
#define uDiv 1
#define vDiv 1
#define vMove 0.0
      int vMoveScreen = int(vMove / transformY);

      //calculate height of the sprite on screen
      int spriteHeight = abs(int(h / (transformY))) / vDiv; //using "transformY" instead of the real distance prevents fisheye
      //calculate lowest and highest pixel to fill in current stripe
      int drawStartY = -spriteHeight / 2 + h / 2 + vMoveScreen;
      if(drawStartY < 0) drawStartY = 0;
      int drawEndY = spriteHeight / 2 + h / 2 + vMoveScreen;
      if(drawEndY >= h) drawEndY = h - 1;

      //calculate width of the sprite
      int spriteWidth = abs( int (h / (transformY))) / uDiv;
      int drawStartX = -spriteWidth / 2 + spriteScreenX;
      if(drawStartX < 0) drawStartX = 0;
      int drawEndX = spriteWidth / 2 + spriteScreenX;
      if(drawEndX >= w) drawEndX = w - 1;

      //loop through every vertical stripe of the sprite on screen
      for(int stripe = drawStartX; stripe < drawEndX; stripe++)
	{
	  //the conditions in the if are:
	  //1) it's in front of camera plane so you don't see things behind you
	  //2) it's on the screen (left)
	  //3) it's on the screen (right)
	  //4) ZBuffer, with perpendicular distance
	  if(transformY > 0 && stripe > 0 && stripe < w && transformY < ZBuffer[stripe])
	    for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
	      {
		int d = (y-vMoveScreen) * 256 - h * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
		int tex = sprite[spriteOrder[i]]->texture;
		int texY;
		int texX;
		texX = int(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;
		texY = ((d * texHeight) / spriteHeight) / 256;
		Uint32 color = texture[tex][texWidth * texY + texX]; //get current color from the texture
		if((color & 0x00FFFFFF) != 0) buffer[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
	      }
	}
    }


  drawBuffer(buffer[0]);
  for(int x = 0; x < w; x++) for(int y = 0; y < h; y++) buffer[y][x] = 0;
  //clear the buffer instead of cls()
  redraw();
}
