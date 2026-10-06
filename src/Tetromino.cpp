#include "Tetromino.h"

Tetromino::Tetromino(const ShapeModel *model) : m_shapeModel(model)
{
  m_shapeCells.resize(model->getCells().size());
  calculateShapeCellsPosition();
}

void Tetromino::calculateShapeCellsPosition()
{
  if (!m_shapeModel)
  {
    return;
  }
  std::vector<Vec2i> modelCells = m_shapeModel->getCells();

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

const Mat2 Tetromino::getRotationMatrix() const
{
  if (m_rotation == DEG0)
  {
    return Rotations::deg0;
  }
  if (m_rotation == DEG90)
  {
    return Rotations::deg90;
  }
  if (m_rotation == DEG180)
  {
    return Rotations::deg180;
  }
  return Rotations::deg270;
}

const std::vector<BoardCell> &Tetromino::getCells()
{
  return m_shapeCells;
}

const ShapeModel *Tetromino::getModel() const
{
  return m_shapeModel;
}

const Vec2i &Tetromino::getPosition() const
{
  return m_position;
}

const Rotation Tetromino::getRotation() const
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
  m_rotation = static_cast<Rotation>((static_cast<int>(m_rotation) + direction) % static_cast<int>(Rotation::DEG270 + 1));
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
