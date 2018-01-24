#include <iostream>
#include "../libs/csvcollection/inc/csvcollection.h"

int main() {
    mongo::client::initialize();
    std::string database, collection, file;
    database = "somedb";
    collection = "somecoll";
    file = "/home/alfred/CLionProjects/csvMongoDB/res/test.csv";
    csvcollection csvcollection1;
    csvcollection1.set_parameters_connection(database,collection);
    csvcollection1.populate_from_csv(file);
    return 0;
}