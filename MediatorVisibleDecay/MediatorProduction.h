/**
 * \file MediatorProduction.h
 *
 * \ingroup MediatorVisibleDecay
 * 
 * \brief Class def header for a class MediatorProduction
 *
 * @author br
 */

/** \addtogroup MediatorVisibleDecay

    @{*/
#ifndef MEDIATORPRODUCTION_H
#define MEDIATORPRODUCTION_H

#include <iostream>
#include <math.h>
#include <TFile.h>
#include <TTree.h>
#include <TNtuple.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TH1D.h>
#include <TLorentzVector.h>
#include <TVector3.h>
#include <TGenPhaseSpace.h>

/**
   \class MediatorProduction
   User defined class MediatorProduction ... these comments are used to generate
   doxygen documentation!
 */
class MediatorProduction{

public:

  /// Default constructor
  MediatorProduction(){}

  /// Default destructor
  ~MediatorProduction(){}

  void MP();
};

#endif
/** @} */ // end of doxygen group 

