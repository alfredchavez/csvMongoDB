//
// Created by alfred on 1/24/18.
//
#include <fstream>
#include "csvcollection.h"

using mongo::BSONObj;
using mongo::BSONObjBuilder;
using mongo::BSONObjIterator;

bool csvcollection::connect_to_mongo() {
    mongo::HostAndPort host_and_port(ipv4, std::stoi(port));
    std::string errmsg;
    try {
        connection.connect(host_and_port, errmsg);
    } catch (mongo::DBException &e) {
        std::cout << "EXCEPTION IN CONNECTION: " << e.what() << ", " << errmsg << std::endl;
        return false;
    }
    std::cout << "Connected" << std::endl;
    return true;
}

void csvcollection::add_to_db(const std::vector<std::string> &row) {
    size_t num_cols = header.size();
    if (row.size() != num_cols) {
        std::cout << "some error in counting number of columns of csv" << std::endl;
        return;
    }
    BSONObjBuilder obj_builder;
    obj_builder.genOID();
    for (size_t i = 0; i < num_cols; ++i) {
        obj_builder.append(header.at(i), row.at(i));
    }
    BSONObj obj = obj_builder.obj();
    connection.insert(database + "." + collection, obj);
    std::cout << "Inserted row: ";
    for(const auto &i: row){
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}

void
csvcollection::set_parameters_connection(const std::string &properties_filename) {
    std::ifstream param_file(properties_filename);
    std::string str_param;
    while(!param_file.eof()){
        getline(param_file, str_param);
        auto param = parse_properties_row(str_param);
        if(param.first == "ipv4") this->ipv4 = param.second;
        if(param.first == "port") this->port = param.second;
        if(param.first == "database") this->database = param.second;
        if(param.first == "collection") this->collection = param.second;
    }
    param_file.close();
    parameters = true;
}

std::vector<std::string> csvcollection::parse_csv_row(const std::string &row) {
    std::vector<std::string> ans;
    std::string element;
    for (auto &el: row) {
        if (el != ',') element += el;
        else {
            ans.push_back(element);
            element = "";
        }
    }
    ans.push_back(element);
    return ans;
}

std::pair<std::string, std::string> csvcollection::parse_properties_row(const std::string &row) {
    size_t pos = row.find('=');
    if(pos == std::string::npos) pos = row.find(':');
    size_t pre_eq = pos - 1, post_eq = pos + 1;
    while(row[pre_eq]==' ' || row[pre_eq]=='\t') --pre_eq;
    while(row[post_eq]==' ' || row[post_eq]=='\t') ++post_eq;
    std::string attr = row.substr(0, pre_eq + 1);
    std::string val = row.substr(post_eq);
    return std::make_pair(attr,val);
}

bool csvcollection::populate_from_csv(const std::string &filename) {
    if (!parameters) {
        std::cout << "Please set parameters of connection before inserting" << std::endl;
        return false;
    }
    if (!connect_to_mongo()) return false;
    connection.remove(database + "." + collection, BSONObj());
    std::ifstream reader(filename);
    std::string hdr;
    if (!reader.eof()) getline(reader, hdr);
    header = std::move(parse_csv_row(hdr));
    std::string row;
    while (!reader.eof()) {
        getline(reader, row);
        add_to_db(parse_csv_row(row));
    }
    std::cout << "Info" << std::endl;
    auto vec = connection.getCollectionInfos(database,BSONObj());
    for(auto &i: vec){
        std::cout << i << std::endl;
    }
    reader.close();
}

csvcollection::csvcollection() {
    parameters = false;
}


