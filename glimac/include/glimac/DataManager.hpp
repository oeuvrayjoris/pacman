//
// Created by Jordan on 28/12/2017.
//

#ifndef IMACGL_DATAMANAGER_HPP
#define IMACGL_DATAMANAGER_HPP


#include <iostream>
#include "../rapidjson/document.h"
#include "../rapidjson/writer.h"
#include "../rapidjson/stringbuffer.h"
#include "../rapidjson/filereadstream.h"
#include "Board.hpp"
#include "Pacman.hpp"
#include "Ghost.hpp"
#include <cstdio>
#include <stdexcept>               // std::runtime_error
#include "../rapidjson/error/error.h" // rapidjson::ParseResult

class DataManager {

public:
    DataManager();

    rapidjson::Document importFromJson(std::string &fileName);

    void exportInJson();

};


#endif //IMACGL_DATAMANAGER_HPP
