#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <vector>
#include "csvcollection.h"

class csvcollectiontest : public ::testing::Test{
public:
    csvcollection csvcollection1;
};


TEST_F(csvcollectiontest, parse_csv_row_Test){
  std::string teststr = "alfred,chavez,19,aqp,1232424,lunaStr";
  std::vector<std::string> ans;
  ans = csvcollection1.parse_csv_row(teststr);
  EXPECT_EQ(ans.size(), 6);
  EXPECT_EQ(ans.at(0), "alfred");
  EXPECT_EQ(ans.at(1), "chavez");
  EXPECT_EQ(ans.at(2), "19");
  EXPECT_EQ(ans.at(3), "aqp");
  EXPECT_EQ(ans.at(4), "1232424");
  EXPECT_EQ(ans.at(5), "lunaStr");
  teststr = "1999,Chevy,\"Venture \"\"Extended Edition, Very Large\"\"\",,5000.00";
  ans = csvcollection1.parse_csv_row(teststr);
  EXPECT_EQ(ans.size(), 5);
  EXPECT_EQ(ans.at(0), "1999");
  EXPECT_EQ(ans.at(1), "Chevy");
  EXPECT_EQ(ans.at(2), "Venture \"Extended Edition, Very Large\"");
  EXPECT_EQ(ans.at(3), "");
  EXPECT_EQ(ans.at(4), "5000.00");
  teststr = "1999,Chevy,\"Venture \"\"Extended Edition\"\"\",\"\",4900.00";
  ans = csvcollection1.parse_csv_row(teststr);
  EXPECT_EQ(ans.size(), 5);
  EXPECT_EQ(ans.at(0), "1999");
  EXPECT_EQ(ans.at(1), "Chevy");
  EXPECT_EQ(ans.at(2), "Venture \"Extended Edition\"");
  EXPECT_EQ(ans.at(3), "\"");
  EXPECT_EQ(ans.at(4), "4900.00");
}

TEST_F(csvcollectiontest, parse_properties_row_Test){
  std::string teststr = "ipv4 = 127.0.0.1";
  std::pair<std::string,std::string>
  ans = csvcollection1.parse_properties_row(teststr);
  EXPECT_EQ(ans.first, "ipv4");
  EXPECT_EQ(ans.second, "127.0.0.1");
  teststr = "nombre   =    alfred";
  ans = csvcollection1.parse_properties_row(teststr);
  EXPECT_EQ(ans.first, "nombre");
  EXPECT_EQ(ans.second, "alfred");
}

TEST_F(csvcollectiontest, set_parameters_connection_Test){
  csvcollection1.set_parameters_connection("../../../res/test/application.properties");
  EXPECT_EQ(csvcollection1.get_collection().database_name, "csvdb");
  EXPECT_EQ(csvcollection1.get_collection().collection_name, "csvcollection");
}
