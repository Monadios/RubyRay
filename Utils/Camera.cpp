#include <fstream>
#include <iostream>

#include "../Utils/quickcg.h"
#include "../Utils/json/json.h"
#include "../Utils/Camera.h"
#include "../Components/PositionComponent.h"
#include "../Components/DirectionComponent.h"
#include "../Components/TextureComponent.h"

Camera::Camera(GameObject* _obj, double _dx, double _dy,
	       std::vector<std::vector<int>>& map,
	       std::vector<GameObject*> _sprites) : worldMap(map), obj(_obj)
{
  sprites = _sprites;
  worldMap = map;
  PositionComponent* pos = obj->get<PositionComponent>();
  DirectionComponent* dir = obj->get<DirectionComponent>();
  parser = ConfigFileParser();
  parser.loadFile("./Data/cam.json");
  pX = pos->x;
  pY = pos->y;
  dX = dir->x;
  dY = dir->y;
  plX = parser.getDouble("planeX");
  plY = parser.getDouble("planeY");
  texHeight = parser.getInt("texHeight");
  texWidth  = parser.getInt("texWidth");

  QuickCG::screen(parser.getInt("screenW"),
		  parser.getInt("screenH"),
		  parser.getInt("fullscreen"),
		  parser.getString("windowname"));

  floorColor = (0x666600 >> 1) & 8355711;
  ceilColor  = 0x666666;

  unsigned long tw, th, error = 0;

  for(int i = 0; i < 12; i++){
    texture[i].reserve(texWidth*texHeight);
  }

  // Loading textures

  error |= QuickCG::loadImage(texture[0], tw, th, "Media/eagle.png");
  error |= QuickCG::loadImage(texture[1], tw, th, "Media/redbrick.png");
  error |= QuickCG::loadImage(texture[2], tw, th, "Media/purplestone.png");
  error |= QuickCG::loadImage(texture[3], tw, th, "Media/greystone.png");
  error |= QuickCG::loadImage(texture[4], tw, th, "Media/bluestone.png");
  error |= QuickCG::loadImage(texture[5], tw, th, "Media/mossy.png");
  error |= QuickCG::loadImage(texture[6], tw, th, "Media/wood.png");
  error |= QuickCG::loadImage(texture[7], tw, th, "Media/colorstone.png");
  error |= QuickCG::loadImage(texture[8], tw, th, "Media/barrel.png");
  error |= QuickCG::loadImage(texture[9], tw, th, "Media/pillar.png");
  error |= QuickCG::loadImage(texture[10], tw, th, "Media/greenlight.png");
  error |= QuickCG::loadImage(texture[11], tw, th, "Media/guard.png");
  //TODO: Add actual error handling (throw exception)
  if(error) { std::cout << "error loading images" << std::endl; }
}

void Camera::render(bool floorceil)
{
  for(int _x = 0; _x < QuickCG::w; _x++)
    {
      //calculate ray position and direction
      double cameraX = 2 * _x / double(QuickCG::w) - 1; //x-coordinate in camera space
      double rayPosX = pX;
      double rayPosY = pY;
      double rayDirX = dX + plX * cameraX;
      double rayDirY = dY + plY * cameraX;

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
      int lineHeight = (int)(QuickCG::h / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + QuickCG::h / 2;
      if(drawStart < 0) drawStart = 0;
      int drawEnd = lineHeight / 2 + QuickCG::h / 2;
      if(drawEnd >= QuickCG::h) drawEnd = QuickCG::h - 1;
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
	  int d = y * 256 - QuickCG::h * 128 + lineHeight * 128; //256 and 128 factors to avoid floats
	  int texY = ((d * texHeight) / lineHeight) / 256;
	  int color = texture[texNum][texWidth * texY + texX];
	  //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
	  if(side == 1) color = (color >> 1) & 8355711;
	  buffer[y][_x] = color;
	}

      //SET THE ZBUFFER FOR THE SPRITE CASTING
      ZBuffer[_x] = perpWallDist; //perpendicular distance is used

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
	if (drawEnd < 0) drawEnd = QuickCG::h; //becomes < 0 when the integer overflows
	//draw the floor from drawEnd to the bottom of the screen
	for(int y = drawEnd + 1; y < QuickCG::h; y++)
	  {

	    currentDist = QuickCG::h / (2.0 * y - QuickCG::h); //you could make a small lookup table for this instead
	    double weight = (currentDist - distPlayer) / (distWall - distPlayer);

	    double currentFloorX = weight * floorXWall + (1.0 - weight) * pX;
	    double currentFloorY = weight * floorYWall + (1.0 - weight) * pY;

	    int floorTexX, floorTexY;
	    floorTexX = int(currentFloorX * texWidth) % texWidth;
	    floorTexY = int(currentFloorY * texHeight) % texHeight;
	    if(floorceil){
	      floorColor = (texture[3][texWidth * floorTexY + floorTexX] >> 1) & 8355711;
	      ceilColor = texture[6][texWidth * floorTexY + floorTexX];
	    }
	    //floor
	    buffer[y][_x] = floorColor;
	    //ceiling (symmetrical!)
	    buffer[QuickCG::h - y][_x] = ceilColor;

	  }
      }

  //SPRITE CASTING

  //sort sprites from far to close
  for(int i = 0; i < sprites.size(); i++)
    {
      spriteOrder.push_back(i);
      double x = sprites[i]->get<PositionComponent>()->x;
      double y = sprites[i]->get<PositionComponent>()->y;
      spriteDistance.push_back((pX - x) * (pX - x) + (pY - y) * (pY - y)); //sqrt not taken, unneeded
    }
  combSort(spriteOrder, spriteDistance, (int)sprites.size());

  //after sorting the sprites, do the projection and draw them
  for(int i = 0; i < sprites.size(); i++)
    {
      //translate sprite position to relative to camera
      double spriteX = sprites[spriteOrder[i]]->get<PositionComponent>()->x - pX;
      double spriteY = sprites[spriteOrder[i]]->get<PositionComponent>()->y - pY;

      TextureComponent* texCom = sprites[spriteOrder[i]]->get<TextureComponent>();

      double invDet = 1.0 / (plX * dY - dX * plY); //required for correct matrix multiplication

      double transformX = invDet * (dY * spriteX - dX * spriteY);
      double transformY = invDet * (-plY * spriteX + plX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

      int spriteScreenX = int((QuickCG::w / 2) * (1 + transformX / transformY));

      //parameters for scaling and moving the sprites
#define vDiv 1
#define vMove 0.0
      int vMoveScreen = int(vMove / transformY);

      //calculate height of the sprite on screen
      //using "transformY" instead of the real distance prevents fisheye
      int spriteHeight = abs(int(QuickCG::h / (transformY))) / texCom->heightFactor;

      //calculate lowest and highest pixel to fill in current stripe
      int drawStartY = -spriteHeight / 2 + QuickCG::h / 2 + vMoveScreen;
      if(drawStartY < 0) drawStartY = 0;
      int drawEndY = spriteHeight / 2 + QuickCG::h / 2 + vMoveScreen;
      if(drawEndY >= QuickCG::h) drawEndY = QuickCG::h - 1;

      //calculate width of the sprite
      int spriteWidth = abs( int (QuickCG::h / (transformY))) / texCom->widthFactor;
      int drawStartX = -spriteWidth / 2 + spriteScreenX;
      if(drawStartX < 0) drawStartX = 0;
      int drawEndX = spriteWidth / 2 + spriteScreenX;
      if(drawEndX >= QuickCG::w) drawEndX = QuickCG::w - 1;

      //loop through every vertical stripe of the sprite on screen
      for(int stripe = drawStartX; stripe < drawEndX; stripe++)
	{
	  //the conditions in the if are:
	  //1) it's in front of camera plane so you don't see things behind you
	  //2) it's on the screen (left)
	  //3) it's on the screen (right)
	  //4) ZBuffer, with perpendicular distance
	  if(transformY > 0 && stripe > 0 && stripe < QuickCG::w && transformY < ZBuffer[stripe])
	    for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
	      {
		int d = (y-vMoveScreen) * 256 - QuickCG::h * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
		int texY;
		int texX;
		texX = int(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;
		/*
		  Because the sprites vary in height, it is neccessary to divide
		  the value by the a height variable (1 for 32 pixels height and
		  2 for 64 pixels height)
		*/

		// TODO: Give texcom a texY variable (seperate from heightfactor)
		texY = ((d * texHeight) / spriteHeight) / (256 / 2);
		Uint32 color = texCom->texture[texWidth * texY + texX]; //get current color from the texture
		if((color & 0x00FFFFFF) != 0) buffer[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
	      }
	}
    }

  //clearScreen();
  QuickCG::drawBuffer(buffer[0]);
}

void Camera::updateScreen() const
{
  QuickCG::redraw();
}

void Camera::clearScreen()
{
  for(int x = 0; x < QuickCG::w; x++) for(int y = 0; y < QuickCG::h; y++){
      buffer[y][x] = 0;
    }
}

void Camera::drawMiniMap()
{
  // To implement or not to implement... that is the question
}

void Camera::update()
{
  pX = obj->get<PositionComponent>()->x;
  pY = obj->get<PositionComponent>()->y;
  dX = obj->get<DirectionComponent>()->x;
  dY = obj->get<DirectionComponent>()->y;
  render(parser.getInt("floorceil"));
  clearScreen();
  updateScreen();
}

void Camera::combSort(std::vector<int> order, std::vector<double> dist, int amount)
{
  int gap = amount;
  bool swapped = false;
  while(gap > 1 || swapped)
    {
      //shrink factor 1.3
      gap = (gap * 10) / 13;
      if(gap == 9 || gap == 10) gap = 11;
      if (gap < 1) gap = 1;
      swapped = false;
      for (int i = 0; i < amount - gap; i++)
	{
	  int j = i + gap;
	  if (dist[i] < dist[j])
	    {
	      std::swap(dist[i], dist[j]);
	      std::swap(order[i], order[j]);
	      swapped = true;
	    }
	}
    }
}

