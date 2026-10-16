#pragma once

#include "raylib.h"
#include "models.h"
#include "ShapeModel.h"
#include "BoardCell.h"

class Tetromino
{
private:
  const ShapeModel *m_shapeModel;
  std::vector<BoardCell> m_shapeCells;
  Vec2i m_position{0, 0};
  Rotation m_rotation = DEG0;

public:
  explicit Tetromino(const ShapeModel &model);
  Tetromino(const ShapeModel &model, Color color);
  explicit Tetromino(const ShapeModel &&model) = delete;

  const std::vector<BoardCell> &getCells() const;
  const ShapeModel *getModel() const;
  Vec2i getPosition() const;
  Rotation getRotation() const;
  void move(Vec2i direction);
  void rotate(int direction);
  void setPosition(Vec2i position);
  void setRotation(Rotation rotation);
  void setColor(Color color);

private:
  void calculateShapeCellsPosition();
  Mat2 getRotationMatrix() const;
};

namespace TetrominoModels
{
  extern const ShapeModel JShape;
  extern const ShapeModel LShape;
  extern const ShapeModel IShape;
  extern const ShapeModel OShape;
  extern const ShapeModel SShape;
  extern const ShapeModel TShape;
  extern const ShapeModel ZShape;
}