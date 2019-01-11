#include <Graph.cpp>

#include <boost/test/unit_test.hpp>

#include <boost/test/output_test_stream.hpp>

using boost::test_tools::output_test_stream;
using namespace aisdi;

BOOST_AUTO_TEST_SUITE()



BOOST_AUTO_TEST_CASE(GivenEmptyGraph_ThenItIsEmpty)
{
    const Graph graph;
    BOOST_CHECK(graph.isEmpty());
}

BOOST_AUTO_TEST_CASE(GivenEmptyGraph_ThenItIsConnected)
{
    const Graph graph;
    BOOST_CHECK(graph.isConnected());
}

BOOST_AUTO_TEST_CASE(GivenNonEmptyNotConnectedGraph_WhenCheckingConnection_ThenItIsNotConnected)
{
    Graph graph;
    graph.add(0, 1);
    graph.add(2, 3);

    BOOST_CHECK( !graph.isConnected() );
}

BOOST_AUTO_TEST_CASE(GivenNonEmptyConnectedGraph_WhenCheckingConnection_ThenItIsConnected) {
    Graph graph;
    graph.add(0, 1);
    graph.add(0, 2);
    graph.add(0, 3);
    graph.add(3, 4);
    graph.add(1, 4);

    BOOST_CHECK( graph.isConnected() );

}

BOOST_AUTO_TEST_CASE(GivenNonEmptyComplicatedNotConnectedGraph_WhenCheckingConnection_ThenItIsNotConnected)
{
    Graph graph;
    graph.add(0, 1);
    graph.add(0, 2);
    graph.add(0, 3);
    graph.add(1, 2);
    graph.add(1, 5);
    graph.add(1, 9);
    graph.add(2, 5);
    graph.add(2, 6);
    graph.add(3, 4);
    graph.add(3, 6);
    graph.add(4, 12);
    graph.add(4, 13);
    graph.add(5, 6);
    graph.add(5, 8);
    graph.add(5, 9);
    graph.add(6, 7);
    graph.add(6, 8);
    graph.add(6, 12);
    graph.add(7, 13);
    graph.add(8, 9);
    graph.add(10, 14);
    graph.add(10, 15);
    graph.add(11, 16);
    graph.add(12, 16);
    graph.add(13, 16);
    graph.add(14, 15);

    BOOST_CHECK( !graph.isConnected() );
}

BOOST_AUTO_TEST_CASE(GivenNonEmptyComplicatedConnectedGraph_WhenCheckingConnection_ThenItIsConnected) {
    Graph graph;
    graph.add(0, 1);
    graph.add(0, 2);
    graph.add(0, 3);
    graph.add(1, 2);
    graph.add(1, 5);
    graph.add(1, 9);
    graph.add(2, 5);
    graph.add(2, 6);
    graph.add(3, 4);
    graph.add(3, 6);
    graph.add(4, 12);
    graph.add(4, 13);
    graph.add(5, 6);
    graph.add(5, 8);
    graph.add(5, 9);
    graph.add(6, 7);
    graph.add(6, 8);
    graph.add(6, 12);
    graph.add(7, 13);
    graph.add(8, 9);
    graph.add(10, 14);
    graph.add(10, 15);
    graph.add(11, 16);
    graph.add(12, 16);
    graph.add(13, 16);
    graph.add(14, 15);

    graph.add(1, 14);
    graph.add(8, 10);

    BOOST_CHECK(graph.isConnected());

}

BOOST_AUTO_TEST_CASE(GivenEmptyGraph_WhenPerformingPrintBridges_ThenItDoesntThrow)
{
    const Graph graph;
    BOOST_CHECK_NO_THROW(graph.printGreatBridges());
}

BOOST_AUTO_TEST_CASE(GivenNotGreatBridgedGraph_WhenPerformingPrintBridges_ThenOutputIsEmpty) {
    Graph graph;
    graph.add(0, 1);
    graph.add(0, 2);
    graph.add(1, 2);

    output_test_stream stream;

    graph.printGreatBridges(stream);
    BOOST_CHECK( stream.is_empty() );

}

BOOST_AUTO_TEST_CASE(GivenNonEmptyGraph_WhenPerformingPrintBridges_ThenItWorks) {
    Graph graph;
    graph.add(0, 1);
    graph.add(1, 2);
    graph.add(2, 3);
    graph.add(3, 0);
    graph.add(0, 2);

    output_test_stream stream;

    graph.printGreatBridges(stream);
    BOOST_CHECK( stream.is_equal( "0 2\n" ) );

}

BOOST_AUTO_TEST_CASE(GivenNonEmptyComplicatedGraph_WhenPerformingPrintBridges_ThenItWorks) {
    Graph graph;
    graph.add(0, 1);
    graph.add(0, 2);
    graph.add(0, 6);
    graph.add(1, 2);
    graph.add(1, 4);
    graph.add(2, 3);
    graph.add(3, 4);
    graph.add(3, 5);
    graph.add(4, 5);
    graph.add(5, 6);

    output_test_stream stream;

    graph.printGreatBridges(stream);
    BOOST_CHECK( stream.is_empty() );

}

BOOST_AUTO_TEST_CASE(GivenNonEmptyLineGraph_WhenPerformingPrintBridges_ThenItWorks) {
    Graph graph;
    graph.add(0, 1);
    graph.add(1, 2);
    graph.add(2, 3);
    graph.add(3, 4);
    graph.add(4, 5);
    graph.add(5, 6);

    output_test_stream stream;

    graph.printGreatBridges(stream);
    BOOST_CHECK( stream.is_equal("1 2\n2 3\n3 4\n4 5\n") );

}

BOOST_AUTO_TEST_CASE(GivenKonradsGraph_WhenPerformingPrintBridges_ThenItWorks) {
    Graph graph;
    graph.add(0, 1);
    graph.add(0, 2);
    graph.add(0, 3);
    graph.add(1, 4);
    graph.add(1, 5);
    graph.add(4, 5);
    graph.add(2, 6);
    graph.add(2, 7);
    graph.add(6, 7);
    graph.add(3, 8);
    graph.add(3, 9);
    graph.add(8, 9);

    output_test_stream stream;

    graph.printGreatBridges(stream);
    BOOST_CHECK( stream.is_equal("0 1\n0 2\n0 3\n1 4\n1 5\n2 6\n2 7\n3 8\n3 9\n") );

}

BOOST_AUTO_TEST_CASE(GivenNonGreatBridgedGraph_WhenPerformingPrintBridges_ThenItWorks) {
    Graph graph;
    graph.add(0, 1);
    graph.add(0, 2);
    graph.add(0, 3);
    graph.add(0, 4);
    graph.add(0, 5);
    graph.add(1, 2);
    graph.add(2, 3);
    graph.add(3, 4);
    graph.add(4, 5);
    graph.add(5, 1);

    output_test_stream stream;

    graph.printGreatBridges(stream);
    BOOST_CHECK( stream.is_empty() );

}

BOOST_AUTO_TEST_SUITE_END()
