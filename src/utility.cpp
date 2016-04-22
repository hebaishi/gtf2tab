#include "utility.hpp"

void ParseArguments(const std::vector <std::string>& commandline_args, string_map &option, std::string &input_filename){
    int option_index = 1;
    int size = commandline_args.size();
    while (option_index < size) {
        if (commandline_args[option_index][0] == '-') {
            if ((option_index + 1) < size) {
                option[commandline_args[option_index]] = commandline_args[option_index + 1];
                option_index += 2;
            } else {
                option[commandline_args[option_index]] = "";
                option_index++;
            }
        } else {
            input_filename = commandline_args[option_index];
            option_index++;
        }
    }
}

void Tokenize(const std::string &s, std::vector <std::string> &tokens , const std::string &delims = " ") {
  int pos = 0;
  int size;
  while (true) {
    pos = s.find_first_not_of(delims,pos);
    size = s.find_first_of(delims, pos) - pos;
    if (pos == -1) break;
    tokens.push_back(s.substr(pos,size));
    pos += size;
  }
}

std::vector<int> fieldListFromString(const std::string& input) {
    std::vector<std::string> items;

    std::vector <int> field_list;
    Tokenize(input, items, ",");
    for (auto &element : items){
        if (element.find("-") != std::string::npos) {
            std::vector<std::string> values;
            Tokenize(element, values, "-");
            int start, end;
            if (values.size() == 2) {
                start = stoi(values[0]);
                end = stoi(values[1]);
                if (start <= end) {
                    for (int index = start ; index <= end ; index++) {
                        field_list.push_back(index);
                    }
                }
            }
        } else {
            field_list.push_back(stoi(element));
        }
    }

    std::for_each(field_list.begin(), field_list.end(), [](int &element) { element--; });
    std::sort(field_list.begin() , field_list.end());
    auto last = std::unique(field_list.begin() , field_list.end());
    field_list.erase(last, field_list.end());

    return field_list;
}

std::string buildHeader(const std::vector<int>& field_list, const std::vector<std::string>& attribute_list) {

    const std::vector <std::string> GTF_header = {"seqname", "source", "feature", "start", "end", "score", "strand", "frame", "attribute"};

    std::string header_line("");

    std::for_each(field_list.cbegin() , field_list.cend(), [&](const int& element){ header_line += GTF_header[element] + "\t"; } );
    std::for_each(attribute_list.cbegin(), attribute_list.cend(), [&](const std::string& element){ header_line += element + "\t"; });
    if (!header_line.empty()){
            header_line.pop_back();
    }

    return header_line;
}
