#include "square.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>

Square::Square(const QPoint &matrixPos, const QRectF &rect, QGraphicsItem *parent, QPixmap *texture)
    : QGraphicsObject(parent)
{
    _matrixPos = matrixPos;
    _piece = nullptr;
    _rect = rect;
    _texture = texture;
}

Piece *Square::piece() const
{
    return _piece;
}

void Square::setPiece(Piece *piece)
{
    _piece = piece;
}

QRectF Square::boundingRect() const
{
    return _rect;
}

void Square::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    QBrush brush(*_texture);
    painter->setBrush(brush);
    painter->drawRect(_rect);

    QFont font;
    font.setPointSize(static_cast<int>(_rect.width() / 1.2));
    painter->setFont(font);

    if(_piece != nullptr) {
        QFontMetrics fm(font);
        int w = fm.width(_piece->to_string());
        int h = fm.height();

        qreal px = boundingRect().center().x() - w / 2;
        qreal py = boundingRect().center().y() + h / 2 - h / 6;

        painter->drawText(static_cast<int>(px), static_cast<int>(py), _piece->to_string());
    }
}

void Square::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        emit leftClick(_matrixPos);
    }
}
