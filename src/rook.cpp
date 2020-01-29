#include "rook.h"
#include "square.h"
#include "board.h"

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

    Square *fromSquare = board->getSquare(from.x(), from.y());
    Square *toSquare = board->getSquare(to.x(), to.y());
    
    Piece *fromPiece = fromSquare->piece();
    Piece *toPiece = toSquare->piece();
    
    int dx = to.x() - from.x();
    int dy = to.y() - from.y();

    if(from.x() != to.x() && from.y() != to.y()) {
        return false;
    }


    QVector<QPoint> middlePoints;



    return true;
}
