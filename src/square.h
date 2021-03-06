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
    QPixmap *_textureSelected;

    bool _isHighlighted;

public:

    Square(const QPoint &matrixPos, const QRectF &rect, QGraphicsItem *parent, QPixmap *texture, QPixmap *textureSelected);
    Piece *piece() const;
    void setPiece(Piece *piece);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    bool isHighlighted() const;
    void setIsHighlighted(bool isHighlighted);

    QPoint matrixPos() const;

protected:

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

signals:

    void leftClick(const QPoint &matrixPos);
    void rightClick(const QPoint &matrixPos);

};

#endif // SQUARE_H
