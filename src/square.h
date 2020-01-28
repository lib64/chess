#ifndef SQUARE_H
#define SQUARE_H

#include "piece.h"

#include <QGraphicsRectItem>

class Square : public QGraphicsObject
{
    Q_OBJECT

    QPoint _matrixPos;
    QRectF _rect;
    Piece *_piece;
    QPixmap *_texture;

public:

    Square(const QPoint &matrixPos, const QRectF &rect, QGraphicsItem *parent, QPixmap *texture);
    Piece *piece() const;
    void setPiece(Piece *piece);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

protected:

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

signals:

    void leftClick(const QPoint &matrixPos);
    void rightClick(const QPoint &matrixPos);

};

#endif // SQUARE_H
