#pragma once

struct Vec2i
{
  int x = 0;
  int y = 0;
};

enum class Rotation
{
  Deg0,
  Deg90,
  Deg180,
  Deg270,
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