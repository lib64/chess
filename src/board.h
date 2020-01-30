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
    QPixmap *_whitePixmapSelected;
    QPixmap *_blackPixmapSelected;

    bool _isSelected;
    QPoint _squareSelected;

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

    void clearHighlighs();

    bool inCheck(Board::Player player);

public slots:

    void on_actionSquareLeftClick(const QPoint &matrixPos);

};

typedef bool (*Validator)(Board *, const QPoint &, const QPoint &);

Validator getValidator(Piece::Type type);

#endif // BOARD_H
