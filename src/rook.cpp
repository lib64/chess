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

bool Rook::isMoveValid(Board *board, const QPoint &from, const QPoint &to, int turn)
{
    Square *toSquare = board->getSquare(to.x(), to.y());
    
    Piece *toPiece = toSquare->piece();
    
    int dx = to.x() - from.x();
    int dy = to.y() - from.y();

    if(toPiece != nullptr) {
        if(static_cast<int>(toPiece->getOwner()) == turn) {
            return false;
        }
    }

    if(from.x() != to.x() && from.y() != to.y()) {
        return false;
    }

    if(dx == 0) {
        // down
        if(dy > 0) {
            for(int y = from.y(); y != to.y(); y++) {
                if(y == from.y() || y == to.y()) {
                    continue;
                }
                Piece *current = board->getSquare(from.x(), y)->piece();
                if(current != nullptr) {
                    return false;
                }
            }
        }
        // up
        else {
            for(int y = from.y(); y != to.y(); y--) {
                if(y == from.y() || y == to.y()) {
                    continue;
                }
                Piece *current = board->getSquare(from.x(), y)->piece();
                if(current != nullptr) {
                    return false;
                }
            }
        }
    } else {
        // right
        if(dx > 0) {
            for(int x = from.x(); x != to.x(); x++) {
                if(x == from.x() || x == to.x()) {
                    continue;
                }
                Piece *current = board->getSquare(x, from.y())->piece();
                if(current != nullptr) {
                    return false;
                }
            }
        }
        // left
        else {
            for(int x = from.x(); x != to.x(); x--) {
                if(x == from.x() || x == to.x()) {
                    continue;
                }
                Piece *current = board->getSquare(x, from.y())->piece();
                if(current != nullptr) {
                    return false;
                }
            }
        }
    }

    return true;
}
