#include "knight.h"

Knight::Knight(const QRectF &rect, Owner owner)
    : Piece(rect, Piece::Type::Knight,owner)
{

}

QString Knight::to_string() const
{
    return (getOwner() == Piece::Owner::White) ? "♘" : "♞";
}

bool Knight::isMoveValid(Board *board, const QPoint &from, const QPoint &to)
{

}
