//
//  game.cpp
//  GameOfLife
//
//  Created by Paul Becker on 03.09.17.
//  Copyright © 2017 Paul Becker. All rights reserved.
//

#include "game.h"


game::game(int size, std::string rule){
    m_gridSize = size;
    m_rule = parseRuleString(rule);
    m_gameMap = new TBoolMap();

    // get rnd geneator and distribution for initialisation
    std::mt19937 gen;
    std::uniform_int_distribution<int> dis = std::uniform_int_distribution<int>(0, 1);
    for(size_t i = 0; i < m_gridSize; i++){
        m_gameMap->push_back(std::vector<bool>());
        
        for(size_t j = 0; j < m_gridSize; j++){
            if(dis(gen) > 0.5){
                (*m_gameMap)[i].push_back(false);
            }else{
                (*m_gameMap)[i].push_back(true);
            }
        }
    }

    createGridFromGameMap();
}

game::game(std::string rule, std::string inputCsv, std::string outputCsv){
    m_rule = parseRuleString(rule);
    m_inputFile = inputCsv;
    m_outputFile = outputCsv;
    m_gameMap = new TBoolMap();

    readCsv();
    createGridFromGameMap();
}

game::game(std::string rule, std::vector<std::vector<bool>> map){
    m_rule = parseRuleString(rule);
    m_gameMap = &map;
    createGridFromGameMap();
}

game::game(std::string rule, std::vector<std::vector<bool>> map, std::string outputCsv){
    m_rule = parseRuleString(rule);
    m_gameMap = &map;
    createGridFromGameMap();
    m_outputFile = outputCsv;
}

game::game(int size, std::string rule, int winHeight, int winWidth){
    m_gridSize = size;
    m_rule = parseRuleString(rule);
    m_gameMap = new TBoolMap();

    // get rnd geneator and distribution for initialisation
    std::mt19937 gen;
    std::uniform_int_distribution<int> dis = std::uniform_int_distribution<int>(0, 1);
    for(size_t i = 0; i < m_gridSize; i++){
        m_gameMap->push_back(std::vector<bool>());

        for(size_t j = 0; j < m_gridSize; j++){
            if(dis(gen) > 0.5){
                (*m_gameMap)[i].push_back(false);
            }else{
                (*m_gameMap)[i].push_back(true);
            }
        }
    }

    createGridFromGameMap();
    m_vis = new visualizer(winHeight, winWidth, m_gridSize, getMap());
}

game::game(std::string rule, std::string inputCsv, std::string outputCsv, int winHeight, int winWidth){
    m_rule = parseRuleString(rule);
    m_inputFile = inputCsv;
    m_outputFile = outputCsv;
    m_gameMap = new TBoolMap();

    readCsv();
    createGridFromGameMap();
    m_vis = new visualizer(winHeight, winWidth, m_gridSize, getMap());
}

game::game(std::string rule, std::vector<std::vector<bool>> map, int winHeight, int winWidth){
    m_rule = parseRuleString(rule);
    m_gameMap = &map;
    createGridFromGameMap();
    m_vis = new visualizer(winHeight, winWidth, m_gridSize, getMap());
}

game::game(std::string rule, std::vector<std::vector<bool>> map, std::string outputCsv, int winHeight, int winWidth){
    m_rule = parseRuleString(rule);
    m_gameMap = &map;
    m_outputFile = outputCsv;
    m_vis = new visualizer(winHeight, winWidth, m_gridSize, getMap());
}

void game::createGridFromGameMap(){
    m_grid = new TGrid();
    for(int i = 0; i < m_gameMap->size(); i++){
        m_grid->push_back(std::vector<cell*>());
        for(int j = 0; j < m_gameMap->size(); j++){
            if((*m_gameMap)[i][j] == true){
                (*m_grid)[i].push_back(new cell(i, j, true, m_rule, *m_grid));
            }else{
                (*m_grid)[i].push_back(new cell(i, j, false, m_rule, *m_grid));
            }
        }
    }
}

IRule *game::parseRuleString(std::string ruleIdentifier){
    // parse rule identifier and select rule
    IRule *ruleObj = nullptr;
    std::vector<std::string> strs;
    boost::split(strs, ruleIdentifier, boost::is_any_of("/"));

    if(strs[1] == "3"){
        if(strs[0] == "3"){
            ruleObj = new r3_3();
        }

        if(strs[0] == "13"){
            ruleObj = new r13_3();
        }

        if(strs[0] == "23"){
            ruleObj = new r23_3();
        }

        if(strs[0] == "34"){
            ruleObj = new r34_3();
        }

        if(strs[0] == "35"){
            ruleObj = new r35_3();
        }

        if(strs[0] == "2"){
            ruleObj = new r2_3();
        }

        if(strs[0] == "24"){
            ruleObj = new r24_3();
        }

        if(strs[0] == "245"){
            ruleObj = new r245_3();
        }


    }else{
        if(strs[1] == "36" && strs[0] == "125"){
            ruleObj = new r125_36();
        }else{
            // TODO: Error
        }
    }

    return ruleObj;
}

game::~game(){
    delete m_vis;
    delete m_gameMap;
    delete m_grid;
    delete m_rule;
}

TBoolMap game::start(int generations){
    for(int g = 0; g < generations; g++){
        for(int i = 0; i < m_gridSize; i++){
            for(int j = 0; j < m_gridSize; j++){
                (*m_grid)[i][j]->calcState();
            }
        }

        for(int i = 0; i < m_gridSize; i++){
            for(int j = 0; j < m_gridSize; j++){
                (*m_grid)[i][j]->updateState();
            }
        }

        if(m_vis != nullptr){
            m_vis->refresh(getMap());
        }
    }

    if(m_outputFile != ""){
        writeCsv();
    }

    TBoolMap *result = getMap();
    return *result;
}

TBoolMap *game::getMap(){
    for(int i = 0; i < m_gridSize; i++){
        for(int j = 0; j < m_gridSize; j++){
            if((*m_grid)[i][j]->getState() == true){
                (*m_gameMap)[i][j] = true;
            }else{
                (*m_gameMap)[i][j] = false;
            }
        }
    }
    return m_gameMap;
}

int game::countCellsAlive(){
    int res = 0;
    for(int i = 0; i < m_gridSize; i++){
        for(int j = 0; j < m_gridSize; j++){
            if((*m_grid)[i][j]->getState() == true){
                res++;
            }
        }
    }
    return res;
}


void game::readCsv(){
    try{
        std::size_t rowCounter = 0;
        csvRow row;
        TBoolMap *gameMap = new TBoolMap();


        std::ifstream file;
        file.open(m_inputFile, std::ios_base::in | std::ios_base::binary);
        if(file.is_open()){
            while(!file.eof()){
                gameMap->push_back(std::vector<bool>());
                row.readNextRow(file);
                for(std::size_t i = 0; i < row.size(); i++){
                    if(row[i] == "0"){
                        (*gameMap)[rowCounter].push_back(false);
                    }else{
                        (*gameMap)[rowCounter].push_back(true);
                    }
                }

                rowCounter++;
            }
        }

        delete m_gameMap;
        m_gameMap = gameMap;
        if(!checkCsv(m_gridSize)){
            // TODO Error
        }
    }catch(const std::exception& ex){

    }
}

void game::writeCsv(){
    try{
        std::ofstream outFile;
        outFile.open(m_outputFile);

        for(std::size_t i = 0; i <m_gameMap->size(); i++){
            for(std::size_t j = 0; j <m_gameMap->size(); j++){
                if((*m_gameMap)[i][j] == true){
                    outFile << "1";
                }else{
                    outFile << "0";
                }

                if((j + 1) == m_gameMap->size()){
                    outFile << std::endl;
                }else{
                    outFile << ',';
                }
            }
        }

        outFile.close();
    }catch(const std::exception& ex){

    }
}

bool game::checkCsv(int &size){
    int check = 0;
    int sum = 0;
    int tmpY = m_gameMap->size();
    std::vector<int> tmpX;

    for(int i = 0; i < m_gameMap->size(); i++){
        tmpX.push_back((*m_gameMap)[i].size());
    }

    for(int i = 0; i < tmpX.size(); i++){
        sum += tmpX[i];
    }

    check = sum - (tmpY * tmpY);
    if(check == 0){
        size = tmpY;
        return true;
    }else{
        size = 0;
        return false;
    }
}





