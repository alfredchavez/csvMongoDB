#include <chrono>
#include <fstream>
#include "csvcollection.h"

using mongo::BSONObj;
using mongo::BSONObjBuilder;
using mongo::BSONObjIterator;

bool csvcollection::connect_to_mongo(std::string ipv4, std::string port) {
    mongo::HostAndPort host_and_port(ipv4, std::stoi(port));
    std::string errmsg;
    try {
        connection.connect(host_and_port, errmsg);
    } catch (mongo::DBException &e) {
        std::cout << "EXCEPTION IN CONNECTION: " << e.what() << ", " << errmsg << std::endl;
        return false;
    }
    return true;
}

void csvcollection::add_to_db(const std::vector<std::string> &row) {
    size_t num_cols = header.size();
    if (row.size() != num_cols) {
        std::cout << "some error in counting number of columns";
        std::cout << row[0] << " " <<row.size() << " != " << num_cols;
        std::cout << std::endl;
        return;
    }
    std::vector<std::pair<std::string, std::string> > row_ins;
    for(size_t i=0; i < num_cols; ++i){
      row_ins.push_back(std::make_pair(header.at(i),row.at(i)));
    }
    _collection.insert_document(row_ins);
}

void csvcollection::add_csv(const std::string &filename, int hdrsize){
    std::ifstream csv(filename, std::ifstream::binary);
    csv.ignore(hdrsize + 1);
    char buffer[4096];
    std::string block, remain;
    int itr;
    while(!csv.eof()){
        csv.read(buffer, 4096);
        std::streamsize read_size  = csv.gcount();
        itr = read_size - 1;
        while(itr > -1 && buffer[itr]!='\n')--itr;
        for(int i = 0; i <= itr; ++i){
            block+=buffer[i];
        }
        for(int i = itr+1; i < read_size; ++i){
            remain+=buffer[i];
        }
        add_block(block);
        block = remain;
        remain = "";
    }
    csv.close();
}

void csvcollection::add_block(const std::string &block){
    std::string row;
    for(auto& ch: block){
        if(ch != '\n')row+=ch;
        else {
            if(row=="")continue;
            else add_to_db(parse_csv_row(row));
            row = "";
        }
    }
    if(row!="")add_to_db(parse_csv_row(row));
}

void csvcollection::set_parameters_connection(const std::string &properties_filename) {
    std::ifstream param_file(properties_filename);
    std::string str_param, ipv4,port,database,collection;
    while(!param_file.eof()){
        getline(param_file, str_param);
        auto param = parse_properties_row(str_param);
        if(param.first == "ipv4") ipv4 = param.second;
        if(param.first == "port") port = param.second;
        if(param.first == "database") database = param.second;
        if(param.first == "collection") collection = param.second;
    }
    connect_to_mongo(ipv4, port);
    _collection.set_collection(connection, database,collection);
    parameters = true;
}

std::vector<std::string> csvcollection::parse_csv_row(const std::string &row) {
    std::vector<std::string> ans;
    std::string element;
    bool openquote = false;
    int itr = 0;
    while(itr < row.length()){
        if(row[itr]=='\"'){
            if(itr+1 < row.length()){
                if(row[itr+1]=='\"' && openquote){
                    element += '\"';
                    ++itr;
                }
                else{
                    openquote = !openquote;
                }
            } else {
                openquote = !openquote;
            }
        } else {
            if(row[itr]==','){
                if(openquote) element += row[itr];
                else {
                    ans.push_back(element);
                    element="";
                }
            } else {
                element += row[itr];
            }
        }
        ++itr;
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
    if(!_collection.empty_collection()) return false;
    //
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    //
    std::ifstream reader(filename);
    std::string hdr;
    if (!reader.eof()) getline(reader, hdr);
    header = std::move(parse_csv_row(hdr));
    reader.close();
    add_csv(filename, hdr.length());
    //
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    //
    auto duration_ms = (double)(std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count());
    info += "time: " + std::to_string(duration_ms/1000.0) + " ms\n";
    return true;
}

std::string csvcollection::get_info_from_collection(){
    info +=  _collection.info() + "\n";
    return info;
}

collection csvcollection::get_collection(){
    return _collection;
}

csvcollection::csvcollection() {
    parameters = false;
    info = "";
}

