#ifndef QWIDLCDCLOCK_H
#define QWIDLCDCLOCK_H

#include <QLCDNumber>
#include <QTimer>
#include <QTime>

class QWidLCDClock : public QLCDNumber
{
    Q_OBJECT
public:
    QWidLCDClock(QWidget *parent, int minutes, int seconds)
    {
        m_Timer = new QTimer();
        m_TimeDisplay = new QTime(0, minutes, seconds);
        setParent(parent);
        display(m_TimeDisplay->toString());
        connect(m_Timer, SIGNAL(timeout()), this, SLOT(ShowTime()));
        connect(this, SIGNAL(TimeElapsed()), this, SLOT(StopTimer()));
    }
    ~QWidLCDClock()
    {
        delete m_TimeDisplay;
        delete m_Timer;
    }

    void StartTimer()
    {
        m_Timer->start(1000);
    }

private:
    QTimer  *m_Timer;
    QTime   *m_TimeDisplay;
signals:
    void TimeElapsed();
private slots:
    void ShowTime()
    {
        m_TimeDisplay->setHMS(0,
                              m_TimeDisplay->addSecs(-1).minute(),
                              m_TimeDisplay->addSecs(-1).second());
        display(m_TimeDisplay->toString());
        if (m_TimeDisplay->minute() == 0 && m_TimeDisplay->second() == 0)
            emit TimeElapsed();
    }
    void StopTimer()
    {
        m_Timer->stop();
    }
};

#endif // QWIDLCDCLOCK_H
