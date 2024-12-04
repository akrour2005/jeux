#ifndef CELL_H
#define CELL_H

class Cell {
protected:
    bool isAlive;
    int x, y;

public:
    virtual ~Cell() {}
    virtual bool nextState(int liveNeighbors) = 0;
    virtual void toggleState();

    void setPosition(int x, int y);
    bool getState() const;
};

#endif
#pragma once