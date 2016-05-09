#ifndef PARSEGTF_H
#define PARSEGTF_H

#include <string>
#include <vector>
#include <fstream>
#include <exception>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <future>
#include <iterator>

struct GTFOptions {
    std::vector<int> field_list;
    std::vector<std::string> attribute_list;
    std::string feature_type;
    bool clean_attributes;
};

using string_map = std::unordered_map<std::string, std::string>;

void readGTFFile(std::istream &input_stream,std::ostream&, const GTFOptions &options);
std::string getGTFFields(const std::string &, const GTFOptions& options);

string_map ParseGTFAttributes(const std::string&);

#endif /* end of include guard: PARSEGTF_H */
