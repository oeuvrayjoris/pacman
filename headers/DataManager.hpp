//
// Created by Jordan on 28/12/2017.
//

#ifndef IMACGL_DATAMANAGER_HPP
#define IMACGL_DATAMANAGER_HPP


#include <iostream>
#include "../include/rapidjson/document.h"
#include "../include/rapidjson/writer.h"
#include "../include/rapidjson/stringbuffer.h"

class DataManager {

public:
    DataManager();

    rapidjson::Document importFromJson(std::string fileName);
    
    void exportInJson(std::string datas[]);

};


#endif //IMACGL_DATAMANAGER_HPP
