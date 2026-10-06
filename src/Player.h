#pragma once

#include <iostream>
#include <vector>
#include "models.h"
#include "ShapeModel.h"

class Player
{
private:
  const ShapeModel *m_shapeModel;
  std::vector<BoardCell> m_shapeCells;
  Vec2i m_shapePosition;
  Rotation m_rotation = DEG0;

public:
  Player() {}

  Action getAction();
};