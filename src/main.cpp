#include <iostream>
#include "csvcollection.h"

int main(int argc, char** argv) {
    if(argc < 2){
        std::cout << "There is not csv file to process" << std::endl;
        return 1;
    }
    if(argc < 3){
        std::cout << "Please specify type of csv file(mac, dos, unix)" << std::endl;
    }
    mongo::client::initialize();
    std::string database, collection, file, file2;
    file  = std::string(argv[1]);
    file2 = "../res/application.properties";
    std::string del = std::string (argv[2]);
    char delimiter='\n';
    if(del=="mac")delimiter='\r';
    else if(del=="unix")delimiter='\n';
    else if(del=="dos")delimiter='\r';
    csvcollection csvcollection1(delimiter);
    csvcollection1.set_parameters_connection(file2);
    csvcollection1.populate_from_csv(file);
    std::cout << csvcollection1.get_info_from_collection() << std::endl;
    return 0;
}
