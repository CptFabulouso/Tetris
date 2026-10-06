#pragma once

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

class Tetromino
{
private:
  const ShapeModel *m_shapeModel;
  std::vector<BoardCell> m_shapeCells;
  Vec2i m_position{0, 0};
  Rotation m_rotation = DEG0;

public:
  Tetromino(const ShapeModel *model);

  const std::vector<BoardCell> &getCells();
  const ShapeModel *getModel() const;
  const Vec2i &getPosition() const;
  const Rotation getRotation() const;
  void move(Vec2i direction);
  void rotate(int direction);
  void setPosition(Vec2i position);
  void setRotation(Rotation rotation);

private:
  void calculateShapeCellsPosition();
  const Mat2 getRotationMatrix() const;
};

namespace TetrominoModels
{
  const ShapeModel JShape({{0, 0}, {0, 1}, {1, 1}, {2, 1}});
  const ShapeModel LShape({{0, 1}, {1, 1}, {2, 1}, {2, 0}});
  const ShapeModel IShape({{1, 0}, {1, 1}, {1, 2}, {1, 3}});
  const ShapeModel OShape({{0, 0}, {1, 0}, {0, 1}, {1, 1}});
  const ShapeModel SShape({{0, 1}, {1, 1}, {1, 0}, {2, 0}});
  const ShapeModel TShape({{0, 1}, {1, 1}, {1, 0}, {2, 1}});
  const ShapeModel ZShape({{0, 0}, {1, 0}, {1, 1}, {2, 1}});
}
