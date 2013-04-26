#ifndef _L_AUTOMATON
#define _L_AUTOMATON

#include "lmatrix.hpp"
#include <QSet>
#include <QString>
#include <QObject>
#include <map>

#define ASCIIZEROCODE 48 //Zero code in ascii table
#define LLIVE 1
#define LDEAD 0

typedef unsigned char statecode;

class Automaton : public QObject {
    Q_OBJECT
private:
    int cellCount;

    int awidth, aheight;

    LMatrix <statecode> field1;
    LMatrix <statecode> field2;
    LMatrix <statecode> *back;
    QSet <int> bear, survive;
    int Neighbours(int x, int y, statecode code) const;
    statecode Cellcode(int x, int y);
    int counter, counter_max;
    statecode drawingnow;
    bool running;
public:
    std::map <statecode, int> StateCount;
    LMatrix <statecode> *front;
    statecode &operator () (int i, int j)
    {
        return (*front)(i,j);
    }
    
    Automaton(int cellCount=40, QString rule="23/3", QObject *parent=0) :
         QObject(parent), cellCount(cellCount)
    {
        awidth = 600;
        aheight = 600;
        field1 = LMatrix <statecode> (aheight, awidth);
        field2 = LMatrix <statecode> (aheight, awidth);
        front = &field1;
        back = &field2;
        counter = 0;
        counter_max = 5;

        for (int i=0; i<aheight; i++)
            for (int j=0; j<awidth; j++)
                field1(i,j) = field2(i,j) = 0;
        StateCount[0] = awidth*aheight;

        int find = rule.indexOf("/");
        for (int i = find+1; i<rule.length(); i++) {
            int count = rule[i].toAscii() - ASCIIZEROCODE;
            bear.insert(count);
        }
        for (int i = 0; i<find; i++) {
            int count = rule[i].toAscii() - ASCIIZEROCODE;
            survive.insert(count);
        }
        running = true;
    }

    Automaton &operator = (const Automaton &right)
    {
        if (this == &right)
            return *this;
        cellCount = right.cellCount;
        field1 = right.field1;
        field2 = right.field2;
        bear = right.bear;
        survive = right.survive;
        StateCount = right.StateCount;
        front = &field1;
        back = &field2;
        return *this;
    }
    void Draw(int x, int y, statecode val);
    int getCellCount();
public slots:
    void Randomize();
    void Clear();
    void Update();
    void ChangeSpeed(int speed);
    void MouseMove(int x, int y);
    void MouseDown(int x, int y);
    void start();
    void stop();
signals:
    void updated();
    void statusChanged(const QString &message, int timeout);
};
#endif
