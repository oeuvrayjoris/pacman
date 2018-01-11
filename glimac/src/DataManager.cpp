//
// Created by Jordan on 28/12/2017.
//

#include "glimac/DataManager.hpp"

DataManager::DataManager() {

}

rapidjson::Document DataManager::importFromJson(std::string &fileName) {

    FILE* fp = fopen(fileName.c_str(), "rb");

    char readBuffer[65536];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    rapidjson::Document d;
    d.ParseStream(is);

    fclose(fp);

    return d;
}

void DataManager::exportInJson(){

}
