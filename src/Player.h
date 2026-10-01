#pragma once

#include <iostream>
#include <vector>
#include "models.h"
#include "ShapeModel.h"

namespace Rotations
{
  constexpr Mat2 deg0 = {{
      {1, 0},
      {0, 1},
  }};
  constexpr Mat2 deg90 = {{
      {0, -1},
      {1, 0},
  }};

  constexpr Mat2 deg180 = {{
      {-1, 0},
      {0, -1},
  }};

  constexpr Mat2 deg270 = {{
      {0, 1},
      {-1, 0},
  }};
}

class Player
{
private:
  ShapeModel m_shapeModel;
  Vec2i m_shapePosition;
  std::vector<BoardCell> m_shapeCells;
  Rotation m_rotation = DEG0;

public:
  Player() {}

  void attachModel(const ShapeModel &model);

  void move(Vec2i direction);

  void rotate();

  const std::vector<BoardCell> &getCells();
  const ShapeModel &getModel() const;
  const Vec2i &getPosition() const;

private:
  const Mat2 getRotationMatrix() const;
};