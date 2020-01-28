#include "king.h"

King::King(const QRectF &rect, Owner owner)
    : Piece(rect, Piece::Type::King, owner)
{

}

QString King::to_string() const
{
    return (getOwner() == Piece::Owner::White) ? "♔" : "♚";
}

bool King::isMoveValid(Board *board, const QPoint &from, const QPoint &to)
{

}
