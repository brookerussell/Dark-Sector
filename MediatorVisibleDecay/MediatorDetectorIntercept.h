/**
 * \file MediatorDetectorIntercept.h
 *
 * \ingroup MediatorVisibleDecay
 * 
 * \brief Class def header for a class MediatorDetectorIntercept
 *
 * @author br
 */

/** \addtogroup MediatorVisibleDecay

    @{*/
#ifndef MEDIATORDETECTORINTERCEPT_H
#define MEDIATORDETECTORINTERCEPT_H

#include <iostream>
#include <math.h>
#include <TFile.h>
#include <TTree.h>
#include <TNtuple.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TLorentzVector.h>

/**
   \class MediatorDetectorIntercept
   User defined class MediatorDetectorIntercept ... these comments are used to generate
   doxygen documentation!
 */
class MediatorDetectorIntercept{

public:

  /// Default constructor
  MediatorDetectorIntercept(){}

  /// Default destructor
  ~MediatorDetectorIntercept(){}

  void MDI();

  /// ### SBN detectors geometry variables ###
  float frontend [3] = {110.0,470.0,600.0}; // front end distance of each TPC
  float backend [3] = {133.6,480.0,619.6}; // back end distance of each TPC
  float xdist [3] = {2.0,1.25,3.6}; // x-direction width from beam center
  float ydist[3] = {2.0,1.25,3.9}; // y-direction width from beam center

};

#endif
/** @} */ // end of doxygen group 

