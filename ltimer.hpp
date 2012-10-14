#ifndef LTIMER_HPP
#define LTIMER_HPP

#include <QTimer>

class LTimer : public QTimer
{
    Q_OBJECT
public:
    LTimer(QObject *parent = 0);
    ~LTimer();
};

#endif // LTIMER_HPP
