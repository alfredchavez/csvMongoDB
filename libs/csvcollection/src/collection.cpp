#include <mongo/client/dbclient.h>
#include "collection.h"

using mongo::BSONObj;
using mongo::BSONObjBuilder;
using mongo::BSONObjIterator;

void collection::set_collection(mongo::DBClientConnection &conn, const std::string &db_name, const std::string &coll_name){
    connection = &conn;
    database_name = db_name;
    collection_name = coll_name;
}

bool collection::empty_collection(){
    try{
        (*connection).remove(database_name + "." + collection_name, BSONObj());
    } catch(mongo::DBException &exception){
        std::cout << "exception: " << exception.what() << std::endl;
        return false;
    }
    return true;
}

bool collection::insert_document(const std::vector<std::pair<std::string, std::string> > &row){
    size_t num_rows = row.size();
    BSONObjBuilder obj_builder;
    obj_builder.genOID();
    for(auto &field: row){
        obj_builder.append(field.first, field.second);
    }
    BSONObj obj = obj_builder.obj();
    try{
        (*connection).insert(database_name + "." + collection_name, obj);
    } catch (mongo::DBException &exception){
        std::cout << "Exception: " << exception.what() << std::endl;
        return false;
    }
    return true;
}

std::string collection::info(){
    return "";
}
