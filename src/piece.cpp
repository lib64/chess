#include "piece.h"

Piece::Piece(const QRectF &rect, Piece::Type type, Piece::Owner owner)
{
    _type = type;
    _owner = owner;
    _rect = rect;
    _hasMoved = false;
}

Piece::~Piece() {}

Piece::Type Piece::getType() const
{
    return _type;
}

Piece::Owner Piece::getOwner() const
{
    return _owner;
}

bool Piece::getHasMoved() const
{
    return _hasMoved;
}

void Piece::setHasMoved(bool hasMoved)
{
    _hasMoved = hasMoved;
}

