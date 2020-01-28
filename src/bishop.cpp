#include "bishop.h"

Bishop::Bishop(const QRectF &rect, Piece::Owner owner)
    : Piece(rect, Piece::Type::Bishop, owner)
{

}

QString Bishop::to_string() const
{
    return (getOwner() == Piece::Owner::White) ? "♗" : "♝";
}

bool Bishop::isMoveValid(Board *board, const QPoint &from, const QPoint &to)
{

}
