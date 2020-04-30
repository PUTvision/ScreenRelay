#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QScreen>
#include <QPainter>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , screen(QGuiApplication::primaryScreen())
    , screenGeometry(screen->geometry())
    , cursorPixmap(constructCursorPixmap(7))
{
    ui->setupUi(this);

    connect(&timer, &QTimer::timeout, this, &MainWindow::grabAndDisplayFrame);
    timer.setInterval(1000.0 / 30);
    timer.start();

    QTimer::singleShot(0, this, &MainWindow::showFullScreen);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QPixmap MainWindow::constructCursorPixmap(const uint32_t cursor_size)
{
    QPixmap pixmap(cursor_size, cursor_size);
    pixmap.fill(Qt::transparent);

    QPainter cursorPainter(&pixmap);
    cursorPainter.setPen(Qt::red);
    cursorPainter.setBrush(Qt::red);
    cursorPainter.drawEllipse(QPoint(cursor_size / 2, cursor_size / 2), cursor_size / 2, cursor_size / 2);

    return pixmap;
}


void MainWindow::grabAndDisplayFrame() {
    auto pixmap = screen->grabWindow(0);
    auto cursorPosition = mapFromGlobal(QCursor::pos());
    auto cursorX = cursorPosition.x() - screenGeometry.x();
    auto cursorY = cursorPosition.y() - screenGeometry.y();

    if (cursorX >= 0 and cursorX <= screenGeometry.right() and cursorY >= 0 and cursorY <= screenGeometry.bottom()) {
        QPainter painter(&pixmap);
        painter.drawPixmap(cursorX, cursorY, cursorPixmap);
    }

    ui->label->setPixmap(pixmap);
}
