#include <QMainWindow>
#include <QApplication>
#include "qwidlcdclock.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMainWindow *w = new QMainWindow();
    w->setWindowTitle(QMainWindow::tr("Pomodoro Timer"));
    w->resize(250,250);

    QWidget *centralWidget = new QWidget(w);

    QWidLCDClock *pomodoroTimer = new QWidLCDClock(centralWidget, 1, 0);
    pomodoroTimer->setFixedSize(245, 245);

    w->setCentralWidget(centralWidget);
    w->show();

    pomodoroTimer->StartTimer();

    return a.exec();
}
