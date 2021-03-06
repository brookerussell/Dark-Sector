/**
 * \file Decay.h
 *
 * \ingroup SignalMC
 * 
 * \brief Class def header for a class Decay
 *
 * @author ber9
 */

/** \addtogroup SignalMC

    @{*/
#ifndef DECAY_H
#define DECAY_H

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
   \class Decay
   User defined class Decay ... these comments are used to generate
   doxygen documentation!
 */
class Decay{

public:

  /// Default constructor
  Decay(){}

  /// Default destructor
  ~Decay(){}

  void Detector();
};

#endif
/** @} */ // end of doxygen group 

