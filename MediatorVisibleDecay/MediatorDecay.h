/**
 * \file MediatorDecay.h
 *
 * \ingroup MediatorVisibleDecay
 * 
 * \brief Class def header for a class MediatorDecay
 *
 * @author br
 */

/** \addtogroup MediatorVisibleDecay

    @{*/
#ifndef MEDIATORDECAY_H
#define MEDIATORDECAY_H

#include <iostream>
#include <math.h>
#include <TFile.h>
#include <TTree.h>
#include <TNtuple.h>
#include <TGenPhaseSpace.h>
#include <TLorentzVector.h>
#include <TVector3.h>
#include <TH1F.h>
#include <TH2F.h>

/**
   \class MediatorDecay
   User defined class MediatorDecay ... these comments are used to generate
   doxygen documentation!
 */
class MediatorDecay{

public:

  /// Default constructor
  MediatorDecay(){}

  /// Default destructor
  ~MediatorDecay(){}

  void MD();

  /// SBN detectors geometry variables                                       
  float frontend [3] = {110.0,470.0,600.0}; // front end distance of each TPC  
  float backend [3] = {133.6,480.0,619.6}; // back end distance of each TPC 
  float xdist [3] = {2.0,1.25,3.6}; // x-direction width from beam center 
  float ydist[3] = {2.0,1.25,3.9}; // y-direction width from beam center

  float c = 299792458; // speed of light
  float alpha_EM = 7.29735257*pow(10.0,-3.0); // fine structure constant
  float pi = 3.141592653589;
  float f_pion = 0.093;
  float mass_pion = 0.1349766; // Pi0 mass in GeV

};

#endif
/** @} */ // end of doxygen group 

