#pragma once

#include "models.h"

class Player
{
private:
  static constexpr float ACTION_TIMEOUT = 0.1f;
  Action m_lastAction = Action::None;
  float m_actionTimeout = ACTION_TIMEOUT;

public:
  Player() = default;

  Action getAction(float dt);

private:
  Action getNextAction(float dt);
};