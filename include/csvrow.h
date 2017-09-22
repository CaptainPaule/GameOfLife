//
//  csvrow.h
//  GameOfLife
//
//  Created by Paul Becker on 03.09.17.
//  Copyright © 2017 Paul Becker. All rights reserved.
//

#ifndef csvrow_h
#define csvrow_h

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>


class csvRow{
private:
    std::vector<std::string> m_data;

public:
    std::string const& operator[](std::size_t index) const;

    std::size_t size() const;
    void readNextRow(std::ifstream &str);
};


#endif /* csvrow_h */
