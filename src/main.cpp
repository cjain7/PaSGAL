/**
 * @file    main.cpp
 * @author  Chirag Jain <cjain7@gatech.edu>
 */
#include <iostream>


#ifdef VTUNE_SUPPORT
#include <ittnotify.h>
#endif

#include "graphLoad.hpp"
#include "align.hpp"
#include "utils.hpp"
#include "base_types.hpp"
#include "clipp.h"

int main(int argc, char **argv)
{
#ifdef VTUNE_SUPPORT
  __itt_pause();
#endif

  std::string rfile = "", qfile = "", mode = "", ofile = "";

  auto cli = (
      clipp::required("-m") & clipp::value("mode", mode).doc("reference graph format [vg or txt]"),
      clipp::required("-r") & clipp::value("ref", rfile).doc("reference graph file"),
      clipp::required("-q") & clipp::value("query", qfile).doc("query file (fasta/fastq)[.gz]"),
      clipp::required("-o") & clipp::value("output", ofile).doc("output file")
      );

  if(!clipp::parse(argc, argv, cli)) 
  {
    clipp::print ( clipp::make_man_page(cli, argv[0]) );
    exit(1);
  }

  // print execution environment based on which MACROs are set
  // for convenience
  psgl::showExecutionEnv();

  std::cout << "INFO, psgl::main, reference file = " << rfile << " (in " << mode  << " format) " << std::endl;
  std::cout << "INFO, psgl::main, query file = " << qfile << std::endl;

  psgl::graphLoader g;

  if (mode.compare("vg") == 0)
    g.loadFromVG(rfile);
  else if(mode.compare("txt") == 0)
    g.loadFromTxt(rfile);
  else
  {
    std::cerr << "Invalid format " << mode << std::endl;
    exit(1);
  }

  std::vector< psgl::BestScoreInfo > bestScoreVector;

  if (psgl::alignToDAG (qfile, g.diCharGraph, bestScoreVector, psgl::MODE::LOCAL) == PSGL_STATUS_OK)
    std::cout << "INFO, psgl::main, run finished" << std::endl;

  psgl::printResultsToFile (ofile, bestScoreVector);
}
