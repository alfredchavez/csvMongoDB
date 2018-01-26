#ifndef CSVMONGODB_COLLECTION_H
#define CSVMONGODB_COLLECTION_H

#include <mongo/client/dbclient.h>
#include <iostream>

class collection{
public:
    mongo::DBClientConnection* connection;
    std::string database_name;
    std::string collection_name;
    void set_collection(mongo::DBClientConnection &conn,const std::string &db_name, const std::string &coll_name);
    bool empty_collection();
    bool insert_document(const std::vector<std::pair<std::string,std::string> > &rows);
    std::string info();
};

#endif
