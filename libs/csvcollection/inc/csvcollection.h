#ifndef CSVMONGODB_CSVCOLLECTION_H
#define CSVMONGODB_CSVCOLLECTION_H

#include <iostream>
#include <gtest/gtest_prod.h>
#include <mongo/client/dbclient.h>
#include <vector>
#include "collection.h"

class collection;

class csvcollection {
private:
    mongo::DBClientConnection connection;
    collection _collection;
    std::vector<std::string> header;
    bool parameters;

    bool connect_to_mongo(std::string ipv4, std::string port);

    void add_to_db(const std::vector<std::string> &row);

    void add_csv(const std::string &filename, int hdrsize);

    void add_block(const std::string &block);

    std::vector<std::string> parse_csv_row(const std::string &row);
    FRIEND_TEST(csvcollectiontest, parse_csv_row_Test);

    std::pair<std::string, std::string> parse_properties_row(const std::string &row);
    FRIEND_TEST(csvcollectiontest, parse_properties_row_Test);

public:
    csvcollection();

    void set_parameters_connection(const std::string &properties_filename);

    bool populate_from_csv(const std::string &filename);

    std::string get_info_from_collection();

    collection get_collection();
};


#endif //CSVMONGODB_CSVCOLLECTION_H
