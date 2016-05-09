#include <iostream>

#include "version.hpp"
#include "parsegtf.hpp"
#include "utility.hpp"

void printUsage() {
    std::cerr
    << "Usage: gtf2tab OPTIONS INPUT_FILE" << std::endl
    << "Version: v" << VERSION::MAJOR << "." << VERSION::MINOR << "." << VERSION::PATCH << "\n" <<
    "\n"
    "Options:"
    "    If no input file is specified, standard input is used\n"
    "\n"
    "    -a ATTRIBUTE_LIST    Comma-separated list of attributes. Examples\n"
    "                         for an Ensembl GTF are gene_id and gene_biotype.\n"
    "\n"
    "    -f FIELDLIST         GTF fields to print, as a comma-separated list of\n"
    "                         integers. Hyphens can also be used to specify a range\n"
    "                         of values\n"
    "\n"
    "    -t FEATURETYPE       Type of GTF feature to print.\n"
    "\n"
    "    -o OUTPUTFILE        Output filename. Default is standard output\n"
    "\n"
    "    -h                   Display help\n"
    "\n"
    "    -C [0/1]             Remove spaces from attributes. Default value is 0\n"
    "\n"
    "Example:\n"
    "     To extract columns 1-4 and gene_id, gene_biotype\n"
    "     from file.gtf the command would be:\n"
    "\n"
    "     gtf2tab -f 1-4 -a gene_id,gene_biotype file.gtf\n"
    "\n";
}

int main(int argc, char const *argv[]) {

    if (argc == 1) {
        printUsage();
        exit(0);
    }

    std::unordered_map<std::string, std::string> cmd_options;

    std::vector <std::string> commandline_args = [](int argc, const char* argv[]){
        std::vector<std::string> vector_result;
        for (int i = 0 ; i < argc ; i++) {
            vector_result.push_back(argv[i]);
        }
        return vector_result;
    } (argc, argv);

    std::string input_filename("-");
    cmd_options["-o"] = "-";

    ParseArguments(commandline_args, cmd_options, input_filename);

    if (cmd_options.find("-h") != cmd_options.end()) {
        printUsage();
        exit(0);
    }

    if (cmd_options["-f"].empty() && cmd_options["-a"].empty()) {
        std::cerr << "Error! No fields or attributes specified" << std::endl;
        exit(-1);
    }

    GTFOptions options;
    options.field_list = fieldListFromString(cmd_options["-f"]);
    Tokenize( cmd_options["-a"], options.attribute_list, "," );
    options.feature_type = cmd_options["-t"];
    if (cmd_options["-C"] == "1") {
        options.clean_attributes = true;
    } else {
        options.clean_attributes = false;
    }

    std::ifstream input_file_stream;
    if (input_filename != "-") {
        openStream(input_file_stream, input_filename);
    }
    std::istream& input_stream = (input_filename == "-") ? std::cin : input_file_stream;

    std::string output_filename(cmd_options["-o"]);
    std::ofstream output_file_stream;
    if (output_filename != "-") {
        openStream(output_file_stream, output_filename);
    }
    std::ostream& output_stream = (output_filename == "-") ? std::cout : output_file_stream;

    if (input_stream && output_stream) {
        output_stream << buildHeader(options.field_list, options.attribute_list) << std::endl;
        readGTFFile(input_stream, output_stream, options);
        return 0;
    } else {
        return -1;
    }
}
