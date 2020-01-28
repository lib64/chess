#include "rook.h"

Rook::Rook(const QRectF &rect, Piece::Owner owner)
    : Piece(rect, Piece::Type::Rook, owner)
{

}

QString Rook::to_string() const
{
    return (getOwner() == Piece::Owner::White) ? "♖" : "♜";
}

bool Rook::isMoveValid(Board *board, const QPoint &from, const QPoint &to)
{

}
