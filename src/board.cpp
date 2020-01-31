#include "board.h"

#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"

#include <QBrush>
#include <QObject>
#include <QMessageBox>

#include <QDebug>

void Board::initSquares()
{
    qreal sw = _rect.width() / BOARD_SIZE;
    qreal sh = _rect.height() / BOARD_SIZE;

    for(int y = 0; y < BOARD_SIZE; y++) {

        bool isWhite = (y % 2 == 0) ? true : false;
        QVector<Square *> row;
        for(int x = 0; x < BOARD_SIZE; x++) {

            QPixmap *pix = (isWhite) ? _whitePixmap : _blackPixmap;
            QPixmap *pixSelected = (isWhite) ? _whitePixmapSelected : _blackPixmapSelected;

            Square *square = new Square(QPoint(x,y), QRectF(0,0,sw,sh), this, pix, pixSelected);

            QObject::connect(square, &Square::leftClick, this, &Board::on_actionSquareLeftClick);

            square->setPos(x * sw, y * sh);
            row.push_back(square);

            isWhite = !isWhite;
        }
        _squares.push_back(row);
    }
}

void Board::initPieces()
{
    // pawns
    for(int i = 0; i < BOARD_SIZE; i++) {
        Pawn *pawn = new Pawn(_rect, Piece::Owner::White);
        getSquare(i, 6)->setPiece(pawn);
    }

    for(int i = 0; i < BOARD_SIZE; i++) {
        Pawn *pawn = new Pawn(_rect, Piece::Owner::Black);
        getSquare(i, 1)->setPiece(pawn);
    }

    // rooks
    Rook *wr1 = new Rook(_rect, Piece::Owner::White);
    Rook *wr2 = new Rook(_rect, Piece::Owner::White);
    Rook *br1 = new Rook(_rect, Piece::Owner::Black);
    Rook *br2 = new Rook(_rect, Piece::Owner::Black);
    getSquare(0,7)->setPiece(wr1);
    getSquare(7,7)->setPiece(wr2);
    getSquare(0,0)->setPiece(br1);
    getSquare(7,0)->setPiece(br2);

    // knights
    Knight *wk1 = new Knight(_rect, Piece::Owner::White);
    Knight *wk2 = new Knight(_rect, Piece::Owner::White);
    Knight *bk1 = new Knight(_rect, Piece::Owner::Black);
    Knight *bk2 = new Knight(_rect, Piece::Owner::Black);
    getSquare(1,7)->setPiece(wk1);
    getSquare(6,7)->setPiece(wk2);
    getSquare(1,0)->setPiece(bk1);
    getSquare(6,0)->setPiece(bk2);

    // bishops
    Bishop *wb1 = new Bishop(_rect, Piece::Owner::White);
    Bishop *wb2 = new Bishop(_rect, Piece::Owner::White);
    Bishop *bb1 = new Bishop(_rect, Piece::Owner::Black);
    Bishop *bb2 = new Bishop(_rect, Piece::Owner::Black);
    getSquare(2,7)->setPiece(wb1);
    getSquare(5,7)->setPiece(wb2);
    getSquare(2,0)->setPiece(bb1);
    getSquare(5,0)->setPiece(bb2);

    // queens
    Queen *wq = new Queen(_rect, Piece::Owner::White);
    Queen *bq = new Queen(_rect, Piece::Owner::Black);
    getSquare(3,7)->setPiece(wq);
    getSquare(3,0)->setPiece(bq);

    // kings
    King *wk = new King(_rect, Piece::Owner::White);
    King *bk = new King(_rect, Piece::Owner::Black);
    getSquare(4,7)->setPiece(wk);
    getSquare(4,0)->setPiece(bk);

}

Board::Board(const QRectF &rect, QGraphicsItem *parent)
    : QGraphicsObject(parent)
{

    _rect = rect;
    _turn = Board::Player::White;

    _isSelected = false;
    _squareSelected = QPoint(-1,-1);

    _isWhiteInCheck = false;
    _isBlackInCheck = false;

    _whitePixmap = new QPixmap(":/images/white.jpg");
    _blackPixmap = new QPixmap(":/images/black.jpg");
    _whitePixmapSelected = new QPixmap(":/images/white-selected.jpg");
    _blackPixmapSelected = new QPixmap(":/images/black-selected.jpg");

    initSquares();
    initPieces();

}

Board::~Board()
{
    delete _whitePixmap;
    delete _blackPixmap;
    delete _whitePixmapSelected;
    delete _blackPixmapSelected;

    for(int y = 0; y < BOARD_SIZE; y++) {
        for(int x = 0; x < BOARD_SIZE; x++) {
            Square *square = getSquare(x,y);
            Piece *piece = square->piece();
            if(piece != nullptr) {
                delete piece;
            }
            square->deleteLater();
        }
    }
}

QRectF Board::boundingRect() const
{
    return _rect;
}

void Board::paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *)
{

}

Square *Board::getSquare(int x, int y)
{
    return _squares.at(y).at(x);
}

Board::Player Board::getTurn() const
{
    return _turn;
}

Board::Player Board::getOtherTurn() const
{
    return (_turn == Board::Player::White) ? Board::Player::Black : Board::Player::White;
}

QString Board::getPlayerString(Board::Player player)
{
    return (player == Board::Player::White) ? "White" : "Black";
}

void Board::changeTurn()
{
    _turn = (_turn == Board::Player::White)
            ? Board::Player::Black
            : Board::Player::White;
}

void Board::getMovesForSquare(QVector<Move> &out, const QPoint &matrixPos)
{
    Square *square = getSquare(matrixPos.x(), matrixPos.y());
    Piece *piece = square->piece();
    if(piece == nullptr) {
        return;
    }
    for(int y = 0; y < BOARD_SIZE; y++) {
        for(int x = 0; x < BOARD_SIZE; x++) {
            if(x == matrixPos.x() && y == matrixPos.y()) {
                continue;
            }
            if(getValidator(piece->getType())(this,matrixPos,QPoint(x,y), static_cast<int>(piece->getOwner()))) {
                out.push_back(Move(matrixPos, QPoint(x,y)));
            }
        }
    }
}

void Board::highlightSquares(const QVector<QPoint> &squares)
{
    for(int i = 0; i < squares.size(); i++) {
        getSquare(squares[i].x(), squares[i].y())->setIsHighlighted(true);
        getSquare(squares[i].x(), squares[i].y())->update();
    }
}

void Board::clearHighlighs()
{
    for(int y = 0; y < BOARD_SIZE; y++) {
        for(int x = 0; x < BOARD_SIZE; x++) {
            getSquare(x,y)->setIsHighlighted(false);
        }
    }
    update();
}

bool Board::inCheck(Board::Player player)
{
    Board::Player otherPlayer = (player == Board::Player::White) ? Board::Player::Black : Board::Player::White;
    QPoint kingPos = findKing(player);
    for(int y = 0; y < BOARD_SIZE; y++) {
        for(int x = 0; x < BOARD_SIZE; x++) {
            Piece *current = getSquare(x,y)->piece();
            if(current != nullptr) {
                if( static_cast<int>(current->getOwner()) != static_cast<int>(otherPlayer)) {
                    continue;
                }
                Validator val = getValidator(current->getType());
                if(val(this, QPoint(x,y), kingPos, static_cast<int>(otherPlayer))) {
                    return true;
                }
            }
        }
    }
    return false;
}

QPoint Board::findKing(Board::Player player)
{
    QPoint kingPos;
    bool found = false;
    for(int y = 0; y < BOARD_SIZE; y++) {
        for(int x = 0; x < BOARD_SIZE; x++) {
            Piece *current = getSquare(x,y)->piece();
            if(current != nullptr) {
                if(current->getType() == Piece::Type::King &&
                   static_cast<int>(current->getOwner()) == static_cast<int>(player)) {
                    kingPos = QPoint(x,y);
                    found = true;
                }
            }

        }
    }
    if(!found) {
        throw std::invalid_argument("king not found");
    }
    return kingPos;
}

void Board::on_actionSquareLeftClick(const QPoint &matrixPos)
{
    Square *square = getSquare(matrixPos.x(), matrixPos.y());
    Piece *piece = square->piece();

    if(!_isSelected) {

        if(piece == nullptr) {
            return;
        }
        if(static_cast<int>(piece->getOwner()) != static_cast<int>(getTurn())) {
            return;
        }
        _isSelected = true;
        _squareSelected = matrixPos;


        QVector<Move> moves;
        getMovesForSquare(moves, matrixPos);

        QVector<QPoint> points;
        for(int i = 0; i < moves.size(); i++) {
            points.push_back(moves[i].to());
        }

        highlightSquares(points);


    } else {

        Square *srcSquare = getSquare(_squareSelected.x(), _squareSelected.y());
        Piece *srcPiece = srcSquare->piece();

        if(square->isHighlighted()) {

            // move the src piece
            srcSquare->setPiece(nullptr);
            square->setPiece(srcPiece);
            srcPiece->setHasMoved(true);

            // if moving player is in check
            if(inCheck(getTurn())) {
                QMessageBox *msgBox = new QMessageBox;
                msgBox->setWindowTitle("Illegal Move!");
                msgBox->setText("This move would put the moving player ("+getPlayerString(getTurn())+") in check.");
                msgBox->exec();

                // undo move
                square->setPiece(piece);
                srcSquare->setPiece(srcPiece);
                srcPiece->setHasMoved(false);

                changeTurn();
            }
            // if non-moving player is in check
            else if(inCheck(getOtherTurn())) {

                // todo checkmate

                update();
                QMessageBox *msgBox = new QMessageBox;
                msgBox->setText(getPlayerString(getOtherTurn()) + " is in check.");
                msgBox->exec();

                // delete the dest piece
                if(piece != nullptr) {
                    delete piece;
                }
            }

            changeTurn();

        }
        _isSelected = false;
        clearHighlighs();
    }
}

Validator getValidator(Piece::Type type)
{
    bool (*val)(Board *, const QPoint &, const QPoint &, int);
    switch(type) {
    case Piece::Type::Pawn: val = & Pawn::isMoveValid; break;
    case Piece::Type::Rook: val = & Rook::isMoveValid; break;
    case Piece::Type::Bishop: val = & Bishop::isMoveValid; break;
    case Piece::Type::Knight: val = & Knight::isMoveValid; break;
    case Piece::Type::Queen: val = & Queen::isMoveValid; break;
    case Piece::Type::King: val = & King::isMoveValid; break;
    }
    return val;
}
