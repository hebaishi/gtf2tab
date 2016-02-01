#include "utility.hpp"

void ParseArguments(int argc, const char* argv[], string_map &option, std::string &input_filename){
    int option_index = 1;
    while (option_index < argc) {
        if (std::string(argv[option_index])[0] == '-') {
            if ((option_index + 1) < argc) {
                option[argv[option_index]] = argv[option_index + 1];
                option_index += 2;
            } else {
                option[argv[option_index]] = "";
                option_index++;
            }
        } else {
            input_filename.assign(argv[option_index]);
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
    for (auto &element : field_list) {
        header_line += GTF_header[element];
        header_line += "\t";
    }

    for (auto &element : attribute_list) {
        header_line += element;
        header_line += "\t";
    }

    if (!header_line.empty())
        header_line.pop_back();

    return header_line;
}
