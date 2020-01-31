#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Board;

class Pawn : public Piece
{
public:
    Pawn(const QRectF &rect, Piece::Owner owner);

    virtual ~Pawn() {}

    QString to_string() const;

    static bool isMoveValid(Board *board, const QPoint &from, const QPoint &to, int turn);

};

#endif // PAWN_H
