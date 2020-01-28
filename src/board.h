#ifndef BOARD_H
#define BOARD_H

#include "square.h"
#include "piece.h"


#include <QGraphicsItem>
#include <QGraphicsObject>

#define BOARD_SIZE 8

class Board : public QGraphicsObject
{

public:

    enum class Player {
        White,
        Black
    };

private:

    QVector<QVector<Square *>> _squares;

    QRectF _rect;
    Board::Player _turn;
    QPixmap *_whitePixmap;
    QPixmap *_blackPixmap;

    void initSquares();

    void initPieces();

public:
    Board(const QRectF &rect, QGraphicsItem *parent=nullptr);

    ~Board();

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

    Square *getSquare(int x, int y);

    Board::Player getTurn() const;

    void changeTurn();

public slots:

    void on_actionSquareLeftClick(const QPoint &matrixPos);

};

#endif // BOARD_H
