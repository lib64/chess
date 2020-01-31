#include "king.h"
#include "queen.h"
King::King(const QRectF &rect, Owner owner)
    : Piece(rect, Piece::Type::King, owner) {}

QString King::to_string() const
{
    return (getOwner() == Piece::Owner::White) ? "♔" : "♚";
}

// todo queen-side and king-side castle
bool King::isMoveValid(Board *board, const QPoint &from, const QPoint &to, int turn)
{
    int dx = from.x() - to.x();
    int dy = from.y() - to.y();
    if(abs(dx) > 1 || abs(dy)  > 1) {
        return false;
    }
    return Queen::isMoveValid(board, from, to, turn);
}
