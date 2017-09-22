//
//  game.h
//  GameOfLife
//
//  Created by Paul Becker on 03.09.17.
//  Copyright © 2017 Paul Becker. All rights reserved.
//

#ifndef game_h
#define game_h

#include <vector>
#include <random>
#include <string>
#include <boost/algorithm/string.hpp>

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

#include "cell.h"
#include "visualizer.h"
#include "rules.h"
#include "csvrow.h"

namespace pb{
    typedef std::vector<std::vector<cell*>> TGrid;
    typedef std::vector<std::vector<bool>> TBoolMap;
    typedef std::vector<std::vector<std::string>> TStringMap;

    class game{
    private:
        int m_gridSize;

        std::string m_inputFile;
        std::string m_outputFile;

        TGrid *m_grid;
        TBoolMap *m_gameMap;
        IRule *m_rule;
        visualizer *m_vis;

        void init();
        void createGridFromGameMap();
        IRule *parseRuleString(std::string ruleIdentifier);
        TBoolMap *getMap();

        void readCsv();
        void writeCsv();

        int countCellsAlive();
        bool checkCsv(int &size);
    
public:
        // computation mode on constructor
        game(int size, std::string rule);
        game(std::string rule, std::string inputCsv, std::string outputCsv);
        game(std::string rule, TBoolMap map);
        game(std::string rule, TBoolMap map, std::string outputCsv);

        // computation mode off constructor
        game(int size, std::string rule, int winHeight, int winWidth);
        game(std::string rule, std::string inputCsv, std::string outputCsv, int winHeight, int winWidth);
        game(std::string rule, TBoolMap map, int winHeight, int winWidth);
        game(std::string rule, TBoolMap map, std::string outputCsv,int winHeight, int winWidth);

        TBoolMap start(int generations);
        ~game();
    };
}

#endif /* game_h */
