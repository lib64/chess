#include "bishop.h"
#include "square.h"
#include "board.h"

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
    Square *toSquare = board->getSquare(to.x(), to.y());
    Piece *toPiece = toSquare->piece();

    int dx = to.x() - from.x();
    int dy = to.y() - from.y();

    if(toPiece != nullptr) {
        if(static_cast<int>(toPiece->getOwner()) == static_cast<int>(board->getTurn())) {
            return false;
        }
    }

    if(abs(dx) != abs(dy)) {
        return false;
    }

    int x = from.x();
    int y = from.y();

    if(dy < 0) {
        // top left
        if(dx < 0) {
            while(x != to.x() && y != to.y()) {
                if( (x == from.x() && y == from.y()) || (x == to.x() && y == to.y())) {
                    --x;--y;
                    continue;
                }
                Piece * piece = board->getSquare(x,y)->piece();
                if(piece != nullptr) {
                    return false;
                }
                --x; --y;
            }
        }
        // top right
        else {
            while(x != to.x() && y != to.y()) {
                if( (x == from.x() && y == from.y()) || (x == to.x() && y == to.y())) {
                    ++x;--y;
                    continue;
                }
                Piece * piece = board->getSquare(x,y)->piece();
                if(piece != nullptr) {
                    return false;
                }
                ++x; --y;
            }
        }
    }
    else {
        // bottom left
        if(dx < 0) {
            while(x != to.x() && y != to.y()) {
                if( (x == from.x() && y == from.y()) || (x == to.x() && y == to.y())) {
                    --x;++y;
                    continue;
                }
                Piece * piece = board->getSquare(x,y)->piece();
                if(piece != nullptr) {
                    return false;
                }
                --x; ++y;
            }
        }
        // bottom right
        else {
            while(x != to.x() && y != to.y()) {
                if( (x == from.x() && y == from.y()) || (x == to.x() && y == to.y())) {
                    ++x;++y;
                    continue;
                }
                Piece * piece = board->getSquare(x,y)->piece();
                if(piece != nullptr) {
                    return false;
                }
                ++x; ++y;
            }
        }
    }

    return true;
}
