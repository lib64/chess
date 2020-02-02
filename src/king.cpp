#include "king.h"
#include "queen.h"
#include "board.h"

King::King(const QRectF &rect, Owner owner)
    : Piece(rect, Piece::Type::King, owner) {}

QString King::to_string() const
{
    return (getOwner() == Piece::Owner::White) ? "♔" : "♚";
}

// todo queen-side and king-side castle
bool King::isMoveValid(Board *board, const QPoint &from, const QPoint &to, int turn)
{

    Square *square = board->getSquare(from.x(), from.y());
    Piece *piece = square->piece();

    if(!piece->getHasMoved()) {
        if(turn == static_cast<int>(Board::Player::White)) {
            // white queen-side castle
            if(to == QPoint(1,7)) {
                Piece *lrook = board->getSquare(0,7)->piece();
                if(lrook == nullptr) {
                    return false;
                }
                if(lrook->getHasMoved()) {
                    return false;
                }
                if(board->getSquare(1,7)->piece() != nullptr ||
                   board->getSquare(2,7)->piece() != nullptr ||
                   board->getSquare(3,7)->piece() != nullptr) {
                    return false;
                }
                return true;
            }
            // white king side castle
            else if(to == QPoint(6,7)) {
                Piece *rrook = board->getSquare(7,7)->piece();
                if(rrook == nullptr) {
                    return false;
                }
                if(rrook->getHasMoved()) {
                    return false;
                }
                if(board->getSquare(5,7)->piece() != nullptr ||
                   board->getSquare(6,7)->piece() != nullptr) {
                    return false;
                }
                return true;
            }
        }
    }



    int dx = from.x() - to.x();
    int dy = from.y() - to.y();
    if(abs(dx) > 1 || abs(dy)  > 1) {
        return false;
    }
    return Queen::isMoveValid(board, from, to, turn);
}
