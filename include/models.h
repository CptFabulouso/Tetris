#pragma once

struct Vec2i
{
  int x = 0;
  int y = 0;
};

enum class Rotation : unsigned int
{
  Deg0 = 0,
  Deg90 = 1,
  Deg180 = 2,
  Deg270 = 3,
};

enum class Action
{
  None,
  MoveLeft,
  MoveRight,
  MoveDown,
  InstantDown,
  Rotate
};