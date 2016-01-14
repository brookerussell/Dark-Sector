/**
 * \file MediatorSelection.h
 *
 * \ingroup MediatorVisibleDecay
 * 
 * \brief Class def header for a class MediatorSelection
 *
 * @author br
 */

/** \addtogroup MediatorVisibleDecay

    @{*/
#ifndef MEDIATORSELECTION_H
#define MEDIATORSELECTION_H

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
   \class MediatorSelection
   User defined class MediatorSelection ... these comments are used to generate
   doxygen documentation!
 */
class MediatorSelection{

public:

  /// Default constructor
  MediatorSelection(){}

  /// Default destructor
  ~MediatorSelection(){}

  void MS();
};

#endif
/** @} */ // end of doxygen group 

