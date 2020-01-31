#ifndef MOVE_H
#define MOVE_H

#include <QPoint>

class Move {

    QPoint _from;
    QPoint _to;

public:

    Move() {}

    Move(const QPoint &from, const QPoint &to) {
        _from = from;
        _to = to;
    }

    QPoint from() const {
        return _from;
    }
    QPoint to() const {
        return _to;
    }
};



#endif // MOVE_H
