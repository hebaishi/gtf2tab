#define BOOST_TEST_MODULE Utility_function_tests
#include <boost/test/unit_test.hpp>

#include "utility.hpp"

BOOST_AUTO_TEST_CASE( fieldListFromString_tests )
{
    BOOST_CHECK ( fieldListFromString(",,,,") == std::vector<int>({}) );
    BOOST_CHECK ( fieldListFromString("1,,,,") == std::vector<int>({0}) );
    BOOST_CHECK ( fieldListFromString(",,1,,") == std::vector<int>({0}) );
    BOOST_CHECK ( fieldListFromString("1") == std::vector<int>({0}) );

    BOOST_CHECK ( fieldListFromString("1,3,5,7") == std::vector<int>({0,2,4,6}) );
    BOOST_CHECK ( fieldListFromString("1,3,3,5,5,7") == std::vector<int>({0,2,4,6}) );
    BOOST_CHECK ( fieldListFromString("1,3,4-8,9") == std::vector<int>({0,2,3,4,5,6,7,8}) );
    BOOST_CHECK ( fieldListFromString("1-3,6,8") == std::vector<int>({0,1,2,5,7}) );
}

BOOST_AUTO_TEST_CASE( buildHeader_tests )
{
    BOOST_CHECK( buildHeader(std::vector<int>({}), std::vector<std::string>({})) == "" );
    BOOST_CHECK( buildHeader(std::vector<int>({0,2,4}), std::vector<std::string>({})) == "seqname\tfeature\tend" );
    BOOST_CHECK( buildHeader(std::vector<int>({}), std::vector<std::string>({"gene_biotype", "gene_id"})) == "gene_biotype\tgene_id" );
    BOOST_CHECK( buildHeader(std::vector<int>({0,2,4}), std::vector<std::string>({"gene_id", "gene_biotype"})) == "seqname\tfeature\tend\tgene_id\tgene_biotype" );
}

BOOST_AUTO_TEST_CASE( Tokenize_tests )
{
    auto tokenize_check = [] (const std::string &input, const std::string &del) {
        std::vector <std::string> result;
        Tokenize(input, result, del);
        return result;
    };

    BOOST_CHECK( tokenize_check("field1", "\t") ==  std::vector<std::string> {"field1"});
    BOOST_CHECK( tokenize_check("field1\t", "\t") ==  std::vector<std::string> {"field1"});
    BOOST_CHECK( tokenize_check("\tfield1", "\t") ==  std::vector<std::string> {"field1"});
    BOOST_CHECK( tokenize_check("field1", "\t") ==  std::vector<std::string> {"field1"});
    BOOST_CHECK( tokenize_check("field1", "\t") ==  std::vector<std::string> {"field1"});
}

BOOST_AUTO_TEST_CASE(ParseArguments_tests){

    auto parsearguments_test = [](const std::vector<std::string> &commandline_args, string_map &test_map , std::string& filename){
        filename = "";
        test_map = string_map({});
        ParseArguments(commandline_args, test_map, filename);
    };

    std::string filename;
    string_map test_map;

    parsearguments_test({"./gtf2tab"}, test_map, filename);
    BOOST_CHECK( test_map == string_map({}) );
    BOOST_CHECK( filename == "" );

    parsearguments_test({"./gtf2tab", "file.txt" }, test_map, filename);
    BOOST_CHECK( test_map == string_map({}) );
    BOOST_CHECK( filename == "file.txt" );

    parsearguments_test({"./gtf2tab", "-a", "gene_id" }, test_map, filename);
    BOOST_CHECK( test_map == string_map({ {"-a", "gene_id"} }) );
    BOOST_CHECK( filename == "" );

    parsearguments_test({"./gtf2tab", "-a", "gene_id", "file2.txt" }, test_map, filename);
    BOOST_CHECK( test_map == string_map({ {"-a", "gene_id"} }) );
    BOOST_CHECK( filename == "file2.txt" );

    parsearguments_test({"./gtf2tab", "-a", "gene_id", "-f", "1-9", "file3.txt"}, test_map, filename);
    BOOST_CHECK( test_map == string_map({ {"-a", "gene_id"}, {"-f", "1-9"} }) );
    BOOST_CHECK( filename == "file3.txt" );
}
