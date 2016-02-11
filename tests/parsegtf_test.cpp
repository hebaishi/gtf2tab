#define BOOST_TEST_MODULE parsegtf_function_tests
#include <boost/test/unit_test.hpp>

#include "parsegtf.hpp"

BOOST_AUTO_TEST_CASE( parseGTF_tests )
{
    std::string line = "";
    std::unordered_map <std::string, std::string> att_map;

    att_map = ParseGTFAttributes(line);
    BOOST_CHECK( att_map["gene_name"] == "" );
    BOOST_CHECK( att_map["gene_id"] == "" );
    BOOST_CHECK( att_map["gene_version"] == "" );

    line = "gene_id \"ENSDARG00000000887\"; gene_version \"7\"; transcript_id \"ENSDART00000138849\"; transcript_version \"1\"; exon_number \"7\"; gene_name \"GTSF1 (1 of 2)\"; gene_source \"ensembl_havana\"; gene_biotype \"protein_coding\"; transcript_name \"GTSF1 (1 of 2)-003\"; transcript_source \"havana\"; transcript_biotype \"protein_coding\";";
    att_map = ParseGTFAttributes(line);
    BOOST_CHECK( att_map["gene_name"] == "GTSF1 (1 of 2)" );
    BOOST_CHECK( att_map["gene_id"] == "ENSDARG00000000887" );
    BOOST_CHECK( att_map["gene_version"] == "7" );

}

BOOST_AUTO_TEST_CASE( getGTFFields_tests )
{


}
