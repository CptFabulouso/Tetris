#include "Player.h"

void Player::attachModel(const ShapeModel &model)
{
  m_shapeModel = model;
  m_shapePosition.y = 0;
  m_shapeCells.resize(model.getCells().size());
}

void Player::move(Vec2i direction)
{
  m_shapePosition.x += direction.x;
  m_shapePosition.y += direction.y;
}

void Player::rotate()
{
  m_rotation = static_cast<Rotation>((static_cast<int>(m_rotation) + 1) % static_cast<int>(Rotation::DEG270 + 1));
}

const std::vector<BoardCell> &Player::getCells()
{
  std::vector<Vec2i> modelCells = m_shapeModel.getCells();

  Mat3 rotationMatrix = m_shapeModel.getRotationMatrix(m_rotation);

  for (int i = 0; i < modelCells.size(); i++)
  {
    Vec2i cell = modelCells[i];
    int x = rotationMatrix.m[0][0] * cell.x + rotationMatrix.m[0][1] * cell.y + rotationMatrix.m[0][2];
    int y = rotationMatrix.m[1][0] * cell.x + rotationMatrix.m[1][1] * cell.y + rotationMatrix.m[1][2];

    x += m_shapePosition.x + m_shapeModel.getSize() / 2;
    y += m_shapePosition.y + m_shapeModel.getSize() / 2;

    if (i < m_shapeCells.size())
    {
      m_shapeCells[i].x = x;
      m_shapeCells[i].y = y;
    }
  }

  return m_shapeCells;
}

const ShapeModel &Player::getModel() const
{
  return m_shapeModel;
}

const Vec2i &Player::getPosition() const
{
  return m_shapePosition;
}

const Mat2 Player::getRotationMatrix() const
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
