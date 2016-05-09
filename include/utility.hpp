#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <unordered_map>
#include <iostream>
#include <stdexcept>

using string_map = std::unordered_map<std::string, std::string>;

enum class StreamType{ INPUT, OUTPUT, UNKNOWN };

template <typename STREAMTYPE>
struct stream_type {
    static const StreamType value = StreamType::UNKNOWN;
};

template <>
struct stream_type <std::ifstream> {
    static const StreamType value = StreamType::INPUT;
};


template <>
struct stream_type <std::ofstream> {
    static const StreamType value = StreamType::OUTPUT;
};

template <typename T>
StreamType
get_stream_type(T& val){
    return stream_type<T>::value;
}

template <typename STREAMTYPE>
void openStream(STREAMTYPE &stream, std::string &filename){
    stream.open(filename);
    if (!stream) {
        std::string error;
        std:: cerr << "Failed to open " << filename << " for ";
        if (get_stream_type(stream) == StreamType::INPUT) {
            std::cerr << "input";
        } else {
            std::cerr << "output";
        }
        std::cerr << std::endl;
    }
}

void ParseArguments(const std::vector <std::string>&, string_map &, std::string &);
void Tokenize(const std::string &, std::vector <std::string> &, const std::string &);
std::vector<int> fieldListFromString(const std::string&);
std::string buildHeader(const std::vector<int>&, const std::vector<std::string>&);
void StringReplace(std::string&, const std::string&, const std::string&);


#endif /* end of include guard: UTILITY_H */
