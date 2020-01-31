#include "knight.h"
#include "square.h"
#include "board.h"

const QVector<QPoint> Knight::_moves = {
    QPoint(-1, -2),
    QPoint( 1, -2),
    QPoint( 2, -1),
    QPoint( 2,  1),
    QPoint( 1,  2),
    QPoint(-1,  2),
    QPoint(-2,  1),
    QPoint(-2, -1)
};

Knight::Knight(const QRectF &rect, Owner owner)
    : Piece(rect, Piece::Type::Knight,owner) {}

QString Knight::to_string() const
{
    return (getOwner() == Piece::Owner::White) ? "♘" : "♞";
}

bool Knight::isMoveValid(Board *board, const QPoint &from, const QPoint &to, int turn)
{
    Square *toSquare = board->getSquare(to.x(), to.y());
    Piece *toPiece = toSquare->piece();

    if(toPiece != nullptr) {
        if(static_cast<int>(toPiece->getOwner()) == turn) {
            return false;
        }
    }

    for(int i = 0; i < _moves.size(); i++) {
        QPoint offset(from.x() + _moves[i].x(), from.y() + _moves[i].y());
        if(offset == to) {
            return true;
        }
    }

    return false;
}
