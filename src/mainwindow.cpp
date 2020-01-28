#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(_scene);

    _board = new Board(QRectF(0,0,800,800));
    _scene->addItem(_board);

}

MainWindow::~MainWindow()
{
    _board->deleteLater();
    delete ui;
}

