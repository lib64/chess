#ifndef PIECE_H
#define PIECE_H

#include <QtCore>

class Piece
{
public:

    enum class Type {
        Pawn,
        Knight,
        Bishop,
        Rook,
        Queen,
        King
    };
    enum class Owner {
        White,
        Black
    };

private:

    QRectF _rect;
    Piece::Type _type;
    Piece::Owner _owner;
    bool _hasMoved;

public:

    Piece(const QRectF &rect, Piece::Type type, Piece::Owner owner);

    virtual ~Piece();

    Piece::Type getType() const;
    Piece::Owner getOwner() const;

    virtual QString to_string() const = 0;

    bool getHasMoved() const;
    void setHasMoved(bool hasMoved);

};

#endif // PIECE_H
