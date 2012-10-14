#include "automaton.hpp"
#include <iostream>
#include <cstdlib>

void Automaton::Update(void)
{
    if (counter_max == 100) return;
    if (counter < counter_max) {
        counter++;
        return;
    }

    counter = 0;
    for (int i=0; i<aheight; i++)
        for (int j=0; j<awidth; j++) {
            StateCount[(*front)(i,j)]--;
            int neigh_live = Neighbours(i,j,LLIVE);
            int current = (*front)(i,j);

            if (current == LLIVE && survive.in(neigh_live)) (*back)(i,j) = LLIVE;
            else (*back)(i,j) = LDEAD;

            if (current == LDEAD && bear.in(neigh_live)) (*back)(i,j) = LLIVE;
            else (*back)(i,j) = LDEAD;
            StateCount[(*back)(i,j)]++;
        }
    LMatrix <statecode> *temp;
    temp = front;
    front = back;
    back = temp;
    emit updated();
}

int Automaton::Neighbours(int x, int y, statecode code) const
{
    int ret=0;

    int cx[3] = {x-1, x, x+1};
    int cy[3] = {y-1, y, y+1};

    if (x == 0) cx[0] = aheight -1;
    else if (x == aheight - 1) cx[2] = 0;

    if (y == 0) cy[0] = awidth -1;
    else if (y == awidth - 1) cy[2] = 0;

    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++){
            if ((cx[i] == x) && (cy[j] == y)) continue;
            statecode curr_state = (*front)(cx[i],cy[j]);
            if (curr_state == code) ret++;
        }
    return ret;
}

void Automaton::Draw(int x, int y, statecode val)
{
    StateCount[(*front)(x,y)]--;
    (*front)(x,y) = val;
    StateCount[(*front)(x,y)]++;
}

void Automaton::Randomize()
{
    for (int i=0; i<aheight; i++)
        for (int j=0; j<awidth; j++) {
            StateCount[(*front)(i,j)]--;
            (*front)(i,j) = rand() % 2;
            StateCount[(*front)(i,j)]++;
        }
    emit updated();
}

void Automaton::Clear()
{
    for (int i=0; i<aheight; i++)
        for (int j=0; j<awidth; j++) {
            StateCount[1] = 0;
            (*front)(i,j) = 0;
            StateCount[0] = awidth*aheight;
        }
    emit updated();
}

void Automaton::ChangeSpeed(int speed)
{
    counter_max = 100 - speed;
}
