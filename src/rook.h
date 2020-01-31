#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class Board;

class Rook : public Piece
{
public:
    Rook(const QRectF &rect, Piece::Owner owner);

    virtual ~Rook() {}

    QString to_string() const;

    static bool isMoveValid(Board *board, const QPoint &from, const QPoint &to, int turn);

};

#endif // ROOK_H
