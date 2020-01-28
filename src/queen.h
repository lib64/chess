#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class Board;

class Queen : public Piece
{
public:
    Queen(const QRectF &rect, Piece::Owner owner);

    virtual ~Queen() {}

    QString to_string() const;

    static bool isMoveValid(Board *board, const QPoint &from, const QPoint &to);

};

#endif // QUEEN_H
