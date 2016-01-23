#ifndef SANITYPLOTS_CXX
#define SANITYPLOTS_CXX

#include "SanityPlots.h"

void SanityPlots::CheckNMP()
{
  // -----------------------------------------------------
  //    N e u t r a l   M e s o n   P r o d u c t i o n  
  // ----------------------------------------------------- 

  TFile* f0 = new TFile("NeutralMesonProduction_output.root");
  TTree* nmp = (TTree*)f0->Get("nmp");

  std::cout<<"WRITING neutral meson sanity plots."<<std::endl;
  f0->Close();
} // <-- end void

void SanityPlots::CheckMP()
{
  // --------------------------------------------                     
  //    M e d i a t o r    P r o d u c t i o n                        
  // -------------------------------------------- 

  TFile* f1 = new TFile("MediatorProduction_output.root");
  TTree *mp = (TTree*)f1->Get("mp");

  std::cout<<"WRITING mediator production sanity plots."<<std::endl;
  f1->Close();
} // <-- end void

void SanityPlots::CheckMS()
{
  // ----------------------------------------
  //   M e d i a t o r    S e l e c t i o n
  // ----------------------------------------

  TFile* f2 = new TFile("MediatorSelection_output.root");
  TTree *ms = (TTree*)f2->Get("ms");

  std::cout<<"WRITING mediator selection sanity plots."<<std::endl;
  f2->Close();
} // <-- end void

void SanityPlots::CheckMDI()
{
  // --------------------------------------------------------- 
  //   M e d i a t o r   D e t e c t o r   I n t e r c e p t
  // ---------------------------------------------------------

  TFile* f3 = new TFile("MediatorDetectorIntercept_output.root");
  TTree *mdi = (TTree*)f3->Get("mdi");

  std::cout<<"WRITING mediator detector intercept sanity plots."<<std::endl;
  f3->Close();
} // <-- end void

void SanityPlots::CheckMD()
{
  // -------------------------------
  //   M e d i a t o r   D e c a y
  // -------------------------------

  TFile *f4 = new TFile("MediatorDecay_output.root");
  TTree *md = (TTree*)f4->Get("md");

  std::cout<<"WRITING mediator decay sanity plots."<<std::endl;
  f4->Close();
} // <-- end void

#endif
