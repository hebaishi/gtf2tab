#include <iostream>

#include "parsegtf.hpp"
#include "utility.hpp"
#include "easyprint"

void printUsage() {
    std::cerr
    << "Usage: gtf2tab OPTIONS INPUT_FILE" << std::endl
    << std::endl
    << "Options:" << std::endl
    << "    If no input file is specified, standard input is used" << std::endl
    << std::endl
    << "    -a ATTRIBUTE_LIST    Comma-separated list of attributes. Examples" << std::endl
    << "                         for an Ensembl GTF are gene_id and gene_biotype." << std::endl
    << std::endl
    << "    -f FIELDLIST         GTF fields to print, as a comma-separated list of" << std::endl
    << "                         integers. Hyphens can also be used to specify a range" << std::endl
    << "                         of values" << std::endl
    << std::endl
    << "    -t FEATURETYPE       Type of GTF feature to print." << std::endl
    << std::endl
    << "    -o OUTPUTFILE        Output filename. Default is standard output" << std::endl
    << std::endl
    << "    -h                   Display help" << std::endl
    << std::endl
    << "Example:" << std::endl
    << "     To extract columns 1-4 and gene_id, gene_biotype" << std::endl
    << "     from file.gtf the command would be:" << std::endl
    << std::endl
    << "     gtf2tab -f 1-4 -a gene_id,gene_biotype file.gtf" << std::endl
    << std::endl;
}

int main(int argc, char const *argv[]) {

    if (argc == 1) {
        printUsage();
        exit(0);
    }

    std::unordered_map<std::string, std::string> option;

    std::string input_filename("-");
    option["-o"] = "-";

    ParseArguments(argc, argv, option, input_filename);

    if (option.find("-h") != option.end()) {
        printUsage();
        exit(0);
    }

    if (option["-f"].empty() && option["-a"].empty()) {
        std::cerr << "Error! No fields or attributes specified" << std::endl;
        exit(-1);
    }

    std::vector <int> field_list = fieldListFromString(option["-f"]);

    std::vector<std::string> attribute_list;
    Tokenize( option["-a"], attribute_list, "," );

    std::ifstream input_file_stream;
    if (input_filename != "-") {
        openStream(input_file_stream, input_filename);
    }
    std::istream& input_stream = (input_filename == "-") ? std::cin : input_file_stream;

    std::string output_filename(option["-o"]);
    std::ofstream output_file_stream;
    if (output_filename != "-") {
        openStream(output_file_stream, output_filename);
    }
    std::ostream& output_stream = (output_filename == "-") ? std::cout : output_file_stream;

    if (input_stream && output_stream) {
        output_stream << buildHeader(field_list, attribute_list) << std::endl;
        readGTFFile(input_stream, output_stream, field_list, attribute_list, option["-t"]);
        return 0;
    } else {
        return -1;
    }
}
