#ifndef PARSEGTF_H
#define PARSEGTF_H

#include <string>
#include <vector>
#include <fstream>
#include <exception>
#include <iostream>
#include <unordered_map>
#include <cmath>

using string_map = std::unordered_map<std::string, std::string>;

void readGTFFile(std::istream &input_stream,std::ostream&, const std::vector<int> &, const std::vector<std::string> &, const std::string&);
std::string getGTFFields(const std::string &, const std::vector<int>&, const std::vector<std::string>&, const std::string&);

string_map ParseGTFAttributes(const std::string);

#endif /* end of include guard: PARSEGTF_H */
