#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class Board;

class Bishop : public Piece
{
public:
    Bishop(const QRectF &rect, Piece::Owner owner);

    virtual ~Bishop() {}

    QString to_string() const;

    static bool isMoveValid(Board *board, const QPoint &from, const QPoint &to, int turn);

};

#endif // BISHOP_H
