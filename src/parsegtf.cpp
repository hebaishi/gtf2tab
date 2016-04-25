#include "parsegtf.hpp"
#include "utility.hpp"

class badline: public std::exception
{
  virtual const char* what() const throw(){
      return "Badly formatted line";
  }
} badline;

using str_vec_iter = std::vector<std::string>::iterator;

struct block_process {
    std::vector <std::string> operator() (str_vec_iter begin, str_vec_iter end, const GTFOptions &options) {
        std::vector <std::string> result_vector;
        for (auto it = begin; it != end ; it++) {
            result_vector.push_back(
                getGTFFields(*it, options)
            );
        }
        return std::move(result_vector);
    }
};

std::vector<std::string> parallel_parse(str_vec_iter begin, str_vec_iter end, const GTFOptions & options) {

    const size_t MIN_SIZE = 10000;

    size_t length = std::distance(begin, end);

    if (length < MIN_SIZE) {
        return block_process() (begin, end, std::ref(options));
    }

    size_t num_threads = std::max((unsigned int)2, std::thread::hardware_concurrency());
    size_t block_size = length / num_threads;

    str_vec_iter current_begin, current_end;
    current_begin = begin;

    std::vector< std::future<std::vector<std::string>>> handle_vector;

    for (size_t i=0 ; i < (num_threads - 1) ; i++) {
        current_end=current_begin;
        std::advance(current_end, block_size);
        handle_vector.push_back(
            std::async(
                std::launch::async, block_process(), current_begin, current_end, std::ref(options)
            )
        );
        current_begin = current_end;
    }

    handle_vector.push_back(
        std::async(
            std::launch::async, block_process(), current_begin, end, std::ref(options)
        )
    );

    std::vector<std::string> final_results;

    std::for_each(handle_vector.begin(), handle_vector.end(), [&final_results](auto &element){
        auto result = element.get();
        std::move(result.begin(), result.end(), std::back_inserter(final_results));
    });

    return std::move(final_results);
}

void readGTFFile(std::istream &input_stream, std::ostream &output_stream,  const GTFOptions& options) {

    const size_t buffer_size = 262'144;
    std::string line;
    string_map att_map;
    std::vector <std::string> line_buffer, result_buffer;
    size_t line_count = 0;

    auto post_data = [&](){
        result_buffer = parallel_parse(
            line_buffer.begin(), line_buffer.end(), options
        );
        std::for_each(result_buffer.begin(), result_buffer.end() , [&output_stream](auto &element){
            output_stream << element;
        });
        line_buffer.clear();
    };

    while (getline(input_stream, line)) {
        line_count++;
        if (line[0] != '#') {
            line_buffer.push_back(std::move(line));
            if (line_buffer.size() >= buffer_size) {
                post_data();
            }
        }
    }
    if (line_buffer.size() > 0) {
        post_data();
    }
}

std::string getGTFFields(const std::string &line, const GTFOptions& options){

    std::vector <std::string> tokens;
    Tokenize(line, tokens, "\t");

    if (tokens.size() < 9) {
        throw badline;
    }

    std::string output("");

    if (options.feature_type.empty() || tokens[2] == options.feature_type) {
        for (size_t index = 0 ; index < options.field_list.size() ; index++) {
            output += tokens[options.field_list[index]];
            output += "\t";
        }
        string_map attribute = ParseGTFAttributes(tokens[8]);

        for(auto &element : options.attribute_list){
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

string_map ParseGTFAttributes(const std::string &line){
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
