/**
 * @file    test_graph_load.cpp
 * @author  Chirag Jain <cjain7@gatech.edu>
 */

#include "graphLoad.hpp"
#include "googletest/include/gtest/gtest.h"

#define QUOTE(name) #name
#define STR(macro) QUOTE(macro)
#define FOLDER STR(PROJECT_TEST_DATA_DIR)

/**
 * @brief   builds a graph from BRCA1 sequence
 *          This routine checks for the correctness
 *          of graph loading (format = .txt)
 **/
TEST(graphLoad, graphLoadTxt) 
{
  //get file name
  std::string file = FOLDER;
  file = file + "/BRCA1_seq_graph.txt";

  using VertexIdType = uint32_t;
  using EdgeIdType = uint32_t;

  //load graph

  psgl::graphLoader<VertexIdType, EdgeIdType> g;
  g.loadFromTxt(file);
  auto &graph = g.diCharGraph;

  ASSERT_EQ(graph.numVertices, 139189); 
  ASSERT_EQ(graph.numEdges, 139188); 
}

/**
 * @brief   builds a graph from BRCA1 sequence
 *          This routine checks for the correctness
 *          of graph loading (format = .vg)
 **/
TEST(graphLoad, graphLoadVG) 
{
  //get file name
  std::string file = FOLDER;
  file = file + "/BRCA1_seq_graph.vg";

  using VertexIdType = uint32_t;
  using EdgeIdType = uint32_t;

  //load graph

  psgl::graphLoader<VertexIdType, EdgeIdType> g;
  g.loadFromVG(file);
  auto &graph = g.diCharGraph;

  //test graph is chain built using BRCA1
  //sequence of length 81189

  ASSERT_EQ(graph.numVertices, 81189); 
  ASSERT_EQ(graph.numEdges, 81188); 
}
