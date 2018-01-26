#ifndef CSVMONGODB_CSVCOLLECTION_H
#define CSVMONGODB_CSVCOLLECTION_H

#include <iostream>
#include <gtest/gtest_prod.h>
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

    std::vector<std::string> parse_csv_row(const std::string &row);
    FRIEND_TEST(csvcollectiontest, parse_csv_row_Test);

    std::pair<std::string, std::string> parse_properties_row(const std::string &row);
    FRIEND_TEST(csvcollectiontest, parse_properties_row_Test);

public:
    csvcollection();

    void set_parameters_connection(const std::string &properties_filename);

    bool populate_from_csv(const std::string &filename);

    std::string get_database();

    std::string get_collection();

    std::string get_ipv4();

    std::string get_port();
};


#endif //CSVMONGODB_CSVCOLLECTION_H
