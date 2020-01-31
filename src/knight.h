#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Board;

class Knight : public Piece
{
public:

    static const QVector<QPoint> _moves;

    Knight(const QRectF &rect, Piece::Owner owner);

    virtual ~Knight() {}

    QString to_string() const;

    static bool isMoveValid(Board *board, const QPoint &from, const QPoint &to, int turn);

};

#endif // KNIGHT_H
