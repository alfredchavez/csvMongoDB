//
// Created by alfred on 1/24/18.
//

#ifndef CSVMONGODB_CSVCOLLECTION_H
#define CSVMONGODB_CSVCOLLECTION_H

#include <iostream>
#include <mongo/client/dbclient.h>
#include <vector>

class csvcollection {
private:
    std::string database;
    std::string collection;
    std::string ipv4;
    std::string port;
    mongo::DBClientConnection connection;
    std::vector<std::string> header;
    bool parameters;

    bool connect_to_mongo();

    void add_to_db(const std::vector<std::string> &row);

    std::vector<std::string> parse_csv_row(const std::string &str);

public:
    csvcollection();

    void set_parameters_connection(std::string database, std::string collection, std::string ipv4 = "localhost",
                                   std::string port = "27017");

    bool populate_from_csv(const std::string &filename);
};


#endif //CSVMONGODB_CSVCOLLECTION_H
