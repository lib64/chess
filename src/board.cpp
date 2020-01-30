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
        _whitePieces.append(pawn);
    }

    for(int i = 0; i < BOARD_SIZE; i++) {
        Pawn *pawn = new Pawn(_rect, Piece::Owner::Black);
        getSquare(i, 1)->setPiece(pawn);
        _blackPieces.push_back(pawn);
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
    _whitePieces.push_back(wr1);
    _whitePieces.push_back(wr2);
    _blackPieces.push_back(br1);
    _blackPieces.push_back(br2);

    // knights
    Knight *wk1 = new Knight(_rect, Piece::Owner::White);
    Knight *wk2 = new Knight(_rect, Piece::Owner::White);
    Knight *bk1 = new Knight(_rect, Piece::Owner::Black);
    Knight *bk2 = new Knight(_rect, Piece::Owner::Black);
    getSquare(1,7)->setPiece(wk1);
    getSquare(6,7)->setPiece(wk2);
    getSquare(1,0)->setPiece(bk1);
    getSquare(6,0)->setPiece(bk2);
    _whitePieces.push_back(wk1);
    _whitePieces.push_back(wk2);
    _blackPieces.push_back(bk1);
    _blackPieces.push_back(bk2);

    // bishops
    Bishop *wb1 = new Bishop(_rect, Piece::Owner::White);
    Bishop *wb2 = new Bishop(_rect, Piece::Owner::White);
    Bishop *bb1 = new Bishop(_rect, Piece::Owner::Black);
    Bishop *bb2 = new Bishop(_rect, Piece::Owner::Black);
    getSquare(2,7)->setPiece(wb1);
    getSquare(5,7)->setPiece(wb2);
    getSquare(2,0)->setPiece(bb1);
    getSquare(5,0)->setPiece(bb2);
    _whitePieces.push_back(wb1);
    _whitePieces.push_back(wb2);
    _blackPieces.push_back(bb1);
    _blackPieces.push_back(bb2);

    // queens
    Queen *wq = new Queen(_rect, Piece::Owner::White);
    Queen *bq = new Queen(_rect, Piece::Owner::Black);
    getSquare(3,7)->setPiece(wq);
    getSquare(3,0)->setPiece(bq);
    _whitePieces.push_back(wq);
    _blackPieces.push_back(bq);

    // kings
    King *wk = new King(_rect, Piece::Owner::White);
    King *bk = new King(_rect, Piece::Owner::Black);
    getSquare(4,7)->setPiece(wk);
    getSquare(4,0)->setPiece(bk);
    _whitePieces.push_back(wk);
    _blackPieces.push_back(bk);
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

    for(int i = 0; i < _whitePieces.size(); i++) {
        delete _whitePieces[i];
    }
    for(int i = 0; i < _blackPieces.size(); i++) {
        delete _blackPieces[i];
    }

    for(int y = 0; y < BOARD_SIZE; y++) {
        for(int x = 0; x < BOARD_SIZE; x++) {
            Square *square = getSquare(x,y);
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

void Board::changeTurn()
{
    _turn = (_turn == Board::Player::White)
            ? Board::Player::Black
            : Board::Player::White;
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

    Piece *king = nullptr;
    QPoint kingPos;

    // find king
    for(int y = 0; y < BOARD_SIZE; y++) {
        for(int x = 0; x < BOARD_SIZE; x++) {

            Piece *current = getSquare(x,y)->piece();
            if(current != nullptr) {
                if(current->getType() == Piece::Type::King &&
                   static_cast<int>(current->getOwner()) == static_cast<int>(player)) {
                    king = current;
                    kingPos.setX(x);
                    kingPos.setY(y);
                }
            }

        }
    }

    if(king == nullptr) {
        throw std::invalid_argument("there is no king.. something is wrong");
    }

    // check if any piece owned by otherPlayer is attacking the player king

    for(int y = 0; y < BOARD_SIZE; y++) {
        for(int x = 0; x < BOARD_SIZE; x++) {

            Piece *current = getSquare(x,y)->piece();
            if(current != nullptr) {
                if( static_cast<int>(current->getOwner()) == static_cast<int>(otherPlayer)) {
                    Validator val = getValidator(current->getType());
                    if(val(this, QPoint(x,y), kingPos)) {
                        // player is in check
                        return true;
                    }
                }
            }

        }
    }

    return false;
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

        for(int y = 0; y < BOARD_SIZE; y++) {
            for(int x = 0; x < BOARD_SIZE; x++) {

                if(x == matrixPos.x() && y == matrixPos.y()) {
                    continue;
                }
                if(getValidator(piece->getType())(this,matrixPos,QPoint(x,y))) {
                    getSquare(x,y)->setIsHighlighted(true);
                    update();
                }
            }
        }

    } else {

        Square *srcSquare = getSquare(_squareSelected.x(), _squareSelected.y());
        Piece *srcPiece = srcSquare->piece();

        Square *destSquare = getSquare(matrixPos.x(), matrixPos.y());
        Piece *destPiece = destSquare->piece();

        if(destSquare->isHighlighted()) {

            // move the src piece
            srcSquare->setPiece(nullptr);
            destSquare->setPiece(srcPiece);
            srcPiece->setHasMoved(true);

            // if moving player is in check
            if(inCheck(getTurn())) {

                QMessageBox *msgBox = new QMessageBox;
                msgBox->setText("Illegal move: puts moving player in check.");
                msgBox->exec();

                _isSelected = false;
                clearHighlighs();
                return;
            }

            // if non-moving player is in check
            if(inCheck( (getTurn() == Board::Player::White) ? Board::Player::Black : Board::Player::White )) {


                update();
                QMessageBox *msgBox = new QMessageBox;
                msgBox->setText("check.");
                msgBox->exec();


            }


            // delete the dest piece
            if(destPiece != nullptr) {
                if(getTurn() == Board::Player::White) {
                    _blackPieces.erase(_blackPieces.begin()+_blackPieces.indexOf(destPiece));
                } else {
                    _whitePieces.erase(_whitePieces.begin()+_whitePieces.indexOf(destPiece));
                }
                delete destPiece;
            }


            changeTurn();
        }

        _isSelected = false;
        clearHighlighs();
    }
}

Validator getValidator(Piece::Type type)
{
    bool (*val)(Board *, const QPoint &, const QPoint &);
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
