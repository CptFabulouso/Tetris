#pragma once

#include <iostream>
#include <vector>
#include "models.h"
#include "ShapeModel.h"

class Player
{
private:
  static constexpr float ACTION_TIMEOUT = 0.1;
  Action m_lastAction;
  float m_actionTimeout = ACTION_TIMEOUT;

public:
  Player() {}

  Action getAction(float dt);

private:
  Action getNextAction(float dt);
};