#include "Tetromino.h"

namespace
{
  Vec2i rotateInBox(Vec2i currentCell, Rotation rotation, int modelSize)
  {
    const int m = modelSize - 1;
    switch (rotation)
    {
    case Rotation::Deg0:
      return {currentCell.x, currentCell.y};
    case Rotation::Deg90:
      return {m - currentCell.y, currentCell.x};
    case Rotation::Deg180:
      return {m - currentCell.x, m - currentCell.y};
    case Rotation::Deg270:
      return {currentCell.y, m - currentCell.x};
    }
    return currentCell;
  }
}

Tetromino::Tetromino(const ShapeModel &model) : m_shapeModel(&model)
{
  m_shapeCells.resize(model.getCells().size());
  calculateShapeCellsPosition();
}

Tetromino::Tetromino(const ShapeModel &model, Color color) : Tetromino(model)
{
  setColor(color);
}

void Tetromino::calculateShapeCellsPosition()
{
  const std::vector<Vec2i> &modelCells = m_shapeModel->getCells();
  int modelSize = m_shapeModel->getSize();

  for (int i = 0; i < modelCells.size(); i++)
  {
    if (i < m_shapeCells.size())
    {
      Vec2i rotatedPosition = rotateInBox(modelCells[i], m_rotation, modelSize);
      m_shapeCells[i].x = m_position.x + rotatedPosition.x;
      m_shapeCells[i].y = m_position.y + rotatedPosition.y;
    }
  }
}

const std::vector<BoardCell> &Tetromino::getCells() const
{
  return m_shapeCells;
}

const ShapeModel *Tetromino::getModel() const
{
  return m_shapeModel;
}

Vec2i Tetromino::getPosition() const
{
  return m_position;
}

Rotation Tetromino::getRotation() const
{
  return m_rotation;
}

void Tetromino::move(Vec2i direction)
{
  m_position.x += direction.x;
  m_position.y += direction.y;
  calculateShapeCellsPosition();
}

void Tetromino::rotate(int direction)
{
  int r = static_cast<int>(m_rotation);
  int numOfRotation = static_cast<int>(Rotation::Deg270) + 1;

  m_rotation = static_cast<Rotation>(((r + direction) % numOfRotation + 4) % numOfRotation);
  calculateShapeCellsPosition();
}

void Tetromino::setPosition(Vec2i position)
{
  m_position = position;
  calculateShapeCellsPosition();
}

void Tetromino::setRotation(Rotation rotation)
{
  m_rotation = rotation;
  calculateShapeCellsPosition();
}

void Tetromino::setColor(Color color)
{
  for (BoardCell &cell : m_shapeCells)
  {
    cell.color = color;
  }
}

namespace TetrominoModels
{
  const ShapeModel JShape({{0, 0}, {0, 1}, {1, 1}, {2, 1}});
  const ShapeModel LShape({{0, 1}, {1, 1}, {2, 1}, {2, 0}});
  const ShapeModel IShape({{0, 1}, {1, 1}, {2, 1}, {3, 1}});
  const ShapeModel OShape({{0, 0}, {1, 0}, {0, 1}, {1, 1}});
  const ShapeModel SShape({{0, 1}, {1, 1}, {1, 0}, {2, 0}});
  const ShapeModel TShape({{0, 1}, {1, 1}, {1, 0}, {2, 1}});
  const ShapeModel ZShape({{0, 0}, {1, 0}, {1, 1}, {2, 1}});
}
