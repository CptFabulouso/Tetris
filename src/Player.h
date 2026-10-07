#pragma once

#include <iostream>
#include <vector>
#include "models.h"
#include "ShapeModel.h"

class Player
{
private:
  static constexpr float ACTION_TIMEOUT = 0.1;
  const ShapeModel *m_shapeModel;
  std::vector<BoardCell> m_shapeCells;
  Vec2i m_shapePosition;
  Rotation m_rotation = DEG0;
  Action m_lastAction;
  float m_actionTimeout = ACTION_TIMEOUT;

public:
  Player() {}

  Action getAction(float dt);

private:
  Action getNextAction(float dt);
};