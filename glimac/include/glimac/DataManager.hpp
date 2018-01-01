//
// Created by Jordan on 28/12/2017.
//

#ifndef IMACGL_DATAMANAGER_HPP
#define IMACGL_DATAMANAGER_HPP


#include <iostream>
#include "../rapidjson/document.h"
#include "../rapidjson/writer.h"
#include "../rapidjson/stringbuffer.h"
#include "Board.hpp"
#include "Pacman.hpp"
#include "Ghost.hpp"

class DataManager {

public:
    DataManager();

    rapidjson::Document importFromJson(std::string fileName);

    void exportInJson(std::string datas[]);

};


#endif //IMACGL_DATAMANAGER_HPP
