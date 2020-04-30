#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QScreen *const screen;
    const QRect screenGeometry;
    const QPixmap cursorPixmap;
    QTimer timer;

    static QPixmap constructCursorPixmap(uint32_t cursor_size);

private slots:
    void grabAndDisplayFrame();
};
#endif // MAINWINDOW_H
