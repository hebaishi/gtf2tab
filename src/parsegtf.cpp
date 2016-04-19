#include "parsegtf.hpp"
#include "utility.hpp"

class badline: public std::exception
{
  virtual const char* what() const throw(){
      return "Badly formatted line";
  }
} badline;

void readGTFFile(std::istream &input_stream, std::ostream &output_stream,  const std::vector<int> &field_list, const std::vector<std::string> &attribute_list, const std::string& feature_type) {

    std::string line;
    string_map att_map;
    while (getline(input_stream, line)) {
        if (line[0] != '#') {
            std::string output_line;
            output_stream << getGTFFields(line, field_list, attribute_list, feature_type);
        }
    }
}

std::string getGTFFields(const std::string &line, const std::vector<int> &field_list, const std::vector<std::string>& attribute_list, const std::string& feature_type){

    std::vector <std::string> tokens;
    Tokenize(line, tokens, "\t");

    if (tokens.size() < 9) {
        throw badline;
    }

    std::string output("");

    if (feature_type.empty() || tokens[2] == feature_type) {
        for (size_t index = 0 ; index < field_list.size() ; index++) {
            output += tokens[field_list[index]];
            output += "\t";
        }
        string_map attribute = ParseGTFAttributes(tokens[8]);

        for(auto &element : attribute_list){
            output += attribute[element];
            output += "\t";
        }
        if (!output.empty()) {
            output.pop_back();
            output += "\n";
        }
    }

    return output;
}

string_map ParseGTFAttributes(const std::string line){
    string_map att_map;
    int pos_name = 0;
    int size_name;

    int pos_value = 0;
    int size_value;

    std::string start_delims(" ");
    std::string mid_delims(" \"");
    std::string end_delims(" \";");

    while (true) {
      pos_name = line.find_first_not_of(end_delims,pos_name);
      if (pos_name == -1) break;
      size_name = line.find_first_of(start_delims, pos_name) - pos_name;

      pos_value = pos_name + size_name;
      pos_value = line.find_first_not_of(mid_delims,pos_value);
      if (pos_value == -1) break;
      size_value = line.find_first_of("\"", pos_value) - pos_value;

      att_map[ line.substr(pos_name, size_name) ] = line.substr(pos_value, size_value);
      pos_name = pos_value + size_value;

    }
    return att_map;
}
