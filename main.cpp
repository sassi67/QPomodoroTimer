#include <QMainWindow>
#include <QApplication>
#include "qwidlcdclock.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

#ifdef _DEBUG
const int POMODORO_INTERVAL = 2;
#else
const int POMODORO_INTERVAL = 25;
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMainWindow *w = new QMainWindow();
    w->setWindowTitle(QMainWindow::tr("Pomodoro Timer"));
    w->resize(250,250);

    QWidget *centralWidget = new QWidget(w);
    // add a vertical layout to hold
    // first line: LCDNumber
    // second line: a horizontal layout (with 2 buttons)
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *buttonLayout = new QHBoxLayout;

    QWidLCDClock *pomodoroTimer = new QWidLCDClock(centralWidget, POMODORO_INTERVAL, 0);
    pomodoroTimer->setFixedSize(245, 245);

    // create two buttons: "Start/Stop" and "Settings"
    QPushButton *btnStartStop = new QPushButton;
    QPushButton *btnSettings = new QPushButton;
    btnStartStop->setText(QMainWindow::tr("Start"));
    btnSettings->setText(QMainWindow::tr("Settings"));
    // connect the event clicked to the StartStop of the timer
    QObject::connect(btnStartStop, SIGNAL(clicked()), pomodoroTimer, SLOT(StartStopTimer()));
    QObject::connect(btnStartStop, &QPushButton::clicked, btnStartStop,
                     [=](){ if (btnStartStop->text() == QMainWindow::tr("Start"))
                                btnStartStop->setText(QMainWindow::tr("Stop"));
                            else
                                btnStartStop->setText(QMainWindow::tr("Start"));
                        });

    // add the two buttons to the bottom layout
    buttonLayout->addWidget(btnStartStop);
    buttonLayout->addWidget(btnSettings);

    // add LCDNumber and bottom layout to the main layout
    mainLayout->addWidget(pomodoroTimer);
    mainLayout->addLayout(buttonLayout);

    // set the main components on the window and show it
    centralWidget->setLayout(mainLayout);
    w->setCentralWidget(centralWidget);
    w->show();


    return a.exec();
}
