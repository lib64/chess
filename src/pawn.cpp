#include "pawn.h"
#include "board.h"

#include <QPainter>

Pawn::Pawn(const QRectF &rect, Piece::Owner owner)
    : Piece(rect, Piece::Type::Pawn, owner)
{

}

QString Pawn::to_string() const
{
    return (getOwner() == Piece::Owner::White) ? "♙" : "♟";
}

bool Pawn::isMoveValid(Board *board, const QPoint &from, const QPoint &to)
{

    Square *fromSquare = board->getSquare(from.x(), from.y());
    Square *toSquare = board->getSquare(to.x(), to.y());

    Piece *fromPiece = fromSquare->piece();
    Piece *toPiece = toSquare->piece();

    if(toPiece != nullptr) {
        // we cant move one of our pawns to a space occupied by one of our pieces
        if(static_cast<int>(toPiece->getOwner()) == static_cast<int>(board->getTurn())) {
            return false;
        }
    }

    int dx = to.x() - from.x();
    int dy = to.y() - from.y();

    // if we are a white pawn...
    if(board->getTurn() == Board::Player::White) {
        // we cant move down
        if(dy > 0) {
            return false;
        }
    }
    // if we are a black pawn...
    else {
        // we cant move up
        if(dy < 0) {
            return false;
        }
    }

    // if we are moving once in the y direction
    if(abs(dy) == 1) {

        // we cant move more than one space in the x direction
        if(abs(dx) > 1) {
            return false;
        }

        // if we have moved once in the x direction, and one in the y
        if(abs(dx) == 1) {

            // we cant move there unless we are attacking an enemy.
            if(toPiece == nullptr) {
                return false;
            }
        }
    }
    // if we are moveing twice in the y direction
    else if(abs(dy) == 2) {

        // our pawn can not have moved before
        if(fromPiece->getHasMoved()) {
            return false;
        }

        // our pawn cant move in the x direction
        if(abs(dx) != 0) {
            return false;
        }

        // the pawn cant jump any pieces
        Square *middleSquare;

        if(board->getTurn() == Board::Player::White) {
            middleSquare = board->getSquare(from.x(), to.y() + 1);
        } else {
            middleSquare = board->getSquare(from.x(), to.y() - 1);
        }

        if(middleSquare->piece() != nullptr) {
            return false;
        }

    }
    // we cant move more that twice in the y direction
    else {
        return false;
    }

    return true;
}
