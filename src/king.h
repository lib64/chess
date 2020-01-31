#ifndef KING_H
#define KING_H

#include "piece.h"

class Board;

class King : public Piece
{
public:
    King(const QRectF &rect, Piece::Owner owner);

    virtual ~King() {}

    QString to_string() const;

    static bool isMoveValid(Board *board, const QPoint &from, const QPoint &to, int turn);

};

#endif // KING_H
