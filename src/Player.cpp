#include "Player.h"
#include "raylib.h"

Action Player::getAction()
{
  if (IsKeyPressed(KEY_LEFT))
  {
    return Action::MOVE_LEFT;
  }
  else if (IsKeyPressed(KEY_RIGHT))
  {
    return Action::MOVE_RIGHT;
  }
  else if (IsKeyPressed(KEY_UP))
  {
    return Action::ROTATE;
  }
  else if (IsKeyPressed(KEY_DOWN))
  {
    // TODO:
  }
  return Action::NONE;
}
