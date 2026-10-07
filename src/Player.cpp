#include <iostream>
#include "Player.h"
#include "raylib.h"

Action Player::getAction(float dt)
{
  Action nextAction = getNextAction(dt);

  if (nextAction != m_lastAction)
  {
    m_actionTimeout = ACTION_TIMEOUT;
    m_lastAction = nextAction;
    return nextAction;
  }

  m_actionTimeout -= dt;
  if (m_actionTimeout < 0)
  {
    m_actionTimeout = ACTION_TIMEOUT;
    return nextAction;
  }

  return Action::NONE;
}

Action Player::getNextAction(float dt)
{
  if (IsKeyDown(KEY_LEFT))
  {
    return Action::MOVE_LEFT;
  }
  else if (IsKeyDown(KEY_RIGHT))
  {
    return Action::MOVE_RIGHT;
  }
  else if (IsKeyDown(KEY_DOWN))
  {
    return Action::MOVE_DOWN;
  }
  else if (IsKeyPressed(KEY_UP))
  {
    return Action::ROTATE;
  }
  else if (IsKeyPressed(KEY_SPACE))
  {
    return Action::INSTANT_DOWN;
  }
  return Action::NONE;
}
