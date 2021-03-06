/**
 * \file VB.h
 *
 * \ingroup SignalMC
 * 
 * \brief Class def header for a class VB
 *
 * @author ber9
 */

/** \addtogroup SignalMC

    @{*/
#ifndef VB_H
#define VB_H

#include <iostream>
#include <math.h>
#include <TFile.h>
#include <TTree.h>
#include <TLorentzVector.h>
#include <TVector3.h>
#include <TGenPhaseSpace.h>
#include <TH1F.h>
#include <TH1D.h>
#include <TH2F.h>
/**
   \class VB
   User defined class VB ... these comments are used to generate
   doxygen documentation!
 */
class VB{

public:

  /// Default constructor
  VB(){}

  /// Default destructor
  ~VB(){}

  void PseudoscalarMeson();

  void VectorMeson();
};

#endif
/** @} */ // end of doxygen group 

