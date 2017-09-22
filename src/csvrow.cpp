#include "csvrow.h"

std::string const& csvRow::operator [](std::size_t index) const {
    return m_data[index];
}

std::size_t csvRow::size() const {
    return m_data.size();
}

void csvRow::readNextRow(std::ifstream &str){
    m_data.clear();
    std::string line;
    std::string cell;

    std::getline(str, line);
    std::stringstream lineStream(line);
    while(std::getline(lineStream, cell, ',')){
        m_data.push_back(cell);
    }

    if(!lineStream && cell.empty()){
        m_data.push_back("");
    }
}
