#ifndef _L_AUTOMATON
#define _L_AUTOMATON

#include "lmatrix.hpp"
#include "set.hpp"
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
    int awidth, aheight;
    LMatrix <statecode> field1;
    LMatrix <statecode> field2;
    LMatrix <statecode> *back;
    Set <int> bear, survive;
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
    
    Automaton(int w, int h, QString rule, QObject *parent=0) :
        awidth(w), aheight(h), QObject(parent)
    {
        field1 = LMatrix <statecode> (awidth, aheight);
        field2 = LMatrix <statecode> (awidth, aheight);
        front = &field1;
        back = &field2;
        counter = 0;
        counter_max = 50;

        for (int i=0; i<aheight; i++)
            for (int j=0; j<awidth; j++)
                field1(i,j) = field2(i,j) = 0;
        StateCount[0] = awidth*aheight;

        int find = rule.indexOf("/");
        for (int i = find+1; i<rule.length(); i++) {
            int count = rule[i].toAscii() - ASCIIZEROCODE;
            bear.add(count);
        }
        for (int i = 0; i<find; i++) {
            int count = rule[i].toAscii() - ASCIIZEROCODE;
            survive.add(count);
        }
        running = true;
    }

    Automaton &operator = (const Automaton &right)
    {
        if (this == &right)
            return *this;
        awidth = right.awidth;
        aheight = right.aheight;

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
};
#endif
