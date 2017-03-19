#ifndef CAMERA_H
#define CAMERA_H

class Camera
{
public:
  int x;
  int y;

  void render(const std::vector<std::vector<int>>& worldMap);
};

#endif
