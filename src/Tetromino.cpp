#include "Tetromino.h"

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

  Mat3 rotationMatrix = m_shapeModel->getRotationMatrix(m_rotation);

  for (int i = 0; i < modelCells.size(); i++)
  {
    Vec2i cell = modelCells[i];
    int x = rotationMatrix.m[0][0] * cell.x + rotationMatrix.m[0][1] * cell.y + rotationMatrix.m[0][2];
    int y = rotationMatrix.m[1][0] * cell.x + rotationMatrix.m[1][1] * cell.y + rotationMatrix.m[1][2];

    x += m_position.x + m_shapeModel->getSize() / 2;
    y += m_position.y + m_shapeModel->getSize() / 2;

    if (i < m_shapeCells.size())
    {
      m_shapeCells[i].x = x;
      m_shapeCells[i].y = y;
    }
  }
}

Mat2 Tetromino::getRotationMatrix() const
{
  if (m_rotation == DEG0)
  {
    return {{
        {1, 0},
        {0, 1},
    }};
  }
  if (m_rotation == DEG90)
  {
    return {{
        {0, -1},
        {1, 0},
    }};
  }
  if (m_rotation == DEG180)
  {
    return {{
        {-1, 0},
        {0, -1},
    }};
  }
  return {{
      {0, 1},
      {-1, 0},
  }};
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
  int numOfRotation = static_cast<int>(Rotation::DEG270 + 1);

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
