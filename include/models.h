#pragma once

struct Vec2i
{
  int x = 0;
  int y = 0;
};

struct BoardCell
{
  int x = 0;
  int y = 0;
};

struct Mat2
{
  float m[2][2];
};

struct Mat3
{
  float m[3][3];
};

enum Rotation
{
  DEG0,
  DEG90,
  DEG180,
  DEG270,
};

enum Action
{
  NONE,
  MOVE_LEFT,
  MOVE_RIGHT,
  MOVE_DOWN,
  INSTANT_DOWN,
  ROTATE
};