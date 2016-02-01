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
    BOOST_CHECK( tokenize_check("field1", "\t") ==  std::vector<std::string> {"field2"});
    BOOST_CHECK( tokenize_check("field1", "\t") ==  std::vector<std::string> {"field2"});
}

BOOST_AUTO_TEST_CASE(ParseArguments_tests){

    {
        const char* argv [1] ={"./gtf2tab"};
        string_map test_map;
        std::string filename = "";
        ParseArguments(1, argv, test_map, filename);
        BOOST_CHECK( test_map == string_map({}) );
        BOOST_CHECK( filename == "" );
    }

    {
        const char* argv [2] ={"./gtf2tab", "file.txt" };
        string_map test_map;
        std::string filename = "";
        ParseArguments(2, argv, test_map, filename);
        BOOST_CHECK( test_map == string_map({}) );
        BOOST_CHECK( filename == "file.txt" );
    }

    {
        const char* argv [3] ={"./gtf2tab", "-a", "gene_id" };
        string_map test_map;
        std::string filename = "";
        ParseArguments(3, argv, test_map, filename);
        BOOST_CHECK( test_map == string_map({ {"-a", "gene_id"} }) );
        BOOST_CHECK( filename == "" );
    }

    {
        const char* argv [4] ={"./gtf2tab", "-a", "gene_id", "file2.txt" };
        string_map test_map;
        std::string filename = "";
        ParseArguments(4, argv, test_map, filename);
        BOOST_CHECK( test_map == string_map({ {"-a", "gene_id"} }) );
        BOOST_CHECK( filename == "file2.txt" );
    }

    {
        const char* argv [6] ={"./gtf2tab", "-a", "gene_id", "-f", "1-9", "file3.txt"};
        string_map test_map;
        std::string filename = "";
        ParseArguments(6, argv, test_map, filename);
        BOOST_CHECK( test_map == string_map({ {"-a", "gene_id"}, {"-f", "1-9"} }) );
        BOOST_CHECK( filename == "file3.txt" );
    }

}
