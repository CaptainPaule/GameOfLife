//
//  cell.cpp
//  GameOfLife
//
//  Created by Paul Becker on 03.09.17.
//  Copyright © 2017 Paul Becker. All rights reserved.
//

#include "cell.h"

cell::cell(int xPos, int yPos, bool state, IRule *rule, std::vector<std::vector<cell*>> &grid) :
    m_xPos(xPos),
    m_yPos(yPos),
    m_Grid(grid){
    m_State = state;
    m_nextState = false;
    m_rule = rule;
}

bool cell::getState() const {
    return m_State;
}

int cell::getXPos() const {
    return m_xPos;
}

int cell::getYPos() const {
    return m_yPos;
}

void cell::assertBoundaryConditions(int &x, int &y){
    // get grid dimension
    int L = m_Grid.size();


    // assert boundary conditions
    x = x % L;
    y = y % L;

    if(x < 0){
        x += L;
    }

    if(y < 0){
        y += L;
    }
}

bool cell::isAlive(int xPos, int yPos){
    assertBoundaryConditions(xPos, yPos);
    if(m_Grid[xPos][yPos]->getState()){
        return true;
    }else{
        return false;
    }
}

unsigned int cell::countNeigborsAlive(){
    int newXPos = 0;
    int newYPos = 0;
    unsigned int neighborsAlive = 0;
    
    newXPos = m_xPos + 1;
    newYPos = m_yPos;
    if(isAlive(newXPos, newYPos)){
        neighborsAlive++;
    }
    
    newXPos = m_xPos - 1;
    newYPos = m_yPos;
    if(isAlive(newXPos, newYPos)){
        neighborsAlive++;
    }
    
    newYPos = m_yPos + 1;
    newXPos = m_xPos;
    if(isAlive(newXPos, newYPos)){
        neighborsAlive++;
    }
    
    newYPos = m_yPos - 1;
    newXPos = m_xPos;
    if(isAlive(newXPos, newYPos)){
        neighborsAlive++;
    }
    
    newXPos = m_xPos + 1;
    newYPos = m_yPos + 1;
    if(isAlive(newXPos, newYPos)){
        neighborsAlive++;
    }
    
    newXPos = m_xPos - 1;
    newYPos = m_yPos - 1;
    if(isAlive(newXPos, newYPos)){
        neighborsAlive++;
    }
    
    newXPos = m_xPos + 1;
    newYPos = m_yPos - 1;
    if(isAlive(newXPos, newYPos)){
        neighborsAlive++;
    }
    
    newXPos = m_xPos - 1;
    newYPos = m_yPos + 1;
    if(isAlive(newXPos, newYPos)){
        neighborsAlive++;
    }
    
    return neighborsAlive;
}

void cell::nextState() {
    m_nextState = m_rule->applyRule(countNeigborsAlive(), m_State);
}

void cell::calcState(){
    nextState();
}

void cell::setState(bool state){
    m_State = state;
}

void cell::updateState(){
    m_State = m_nextState;
}

