//
//  cell.h
//  GameOfLife
//
//  Created by Paul Becker on 03.09.17.
//  Copyright © 2017 Paul Becker. All rights reserved.
//

#ifndef cell_h
#define cell_h

#include <vector>
#include "rules.h"

class cell {
private:
    bool m_nextState;
    bool m_State;
    size_t m_xPos;
    size_t m_yPos;
    
    IRule *m_rule;
    std::vector<std::vector<cell*>> const &m_Grid;
    
    cell();
    cell(cell const &rhs);
    
    void assertBoundaryConditions(int &x, int &y);
    bool isAlive(int xPos, int yPos);
    unsigned int countNeigborsAlive();
    void nextState();
    
public:
    cell(int xPos, int yPos, bool state, IRule *rule,std::vector<std::vector<cell*>> &grid);
    ~cell();

    bool getState() const;
    void setState(bool state);
    int getXPos() const;
    int getYPos() const;
    
    void calcState();
    void updateState();
};

#endif /* cell_h */
