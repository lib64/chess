#include "queen.h"
#include "rook.h"
#include "bishop.h"

Queen::Queen(const QRectF &rect, Piece::Owner owner)
    : Piece(rect, Piece::Type::Queen, owner) {}

QString Queen::to_string() const
{
    return (getOwner() == Piece::Owner::White) ? "♕" : "♛";
}

bool Queen::isMoveValid(Board *board, const QPoint &from, const QPoint &to, int turn)
{
    return Bishop::isMoveValid(board, from, to, turn) || Rook::isMoveValid(board, from, to, turn);
}
