#ifndef DARKSECTOR_SIGNALMC_SAMPLE_CXX
#define DARKSECTOR_SIGNALMC_SAMPLE_CXX

#include "test.h"
#include <TFile.h>
#include <TTree.h>

void test::A(const std::string file_name)
{
  // this is the output file
  auto fout = TFile::Open(file_name.c_str(),"RECREATE");
  TTree tree("tree","");
  test data;
  tree.Branch("test",data.GetName(),&data);

  float marker;
  data.marker;
  tree.Fill();
  tree.Write();
  fout->Close();
}

#endif
