/**
 * \file SanityPlots.h
 *
 * \ingroup MediatorVisibleDecay
 * 
 * \brief Class def header for a class SanityPlots
 *
 * @author br
 */

/** \addtogroup MediatorVisibleDecay

    @{*/
#ifndef SANITYPLOTS_H
#define SANITYPLOTS_H

#include <iostream>
#include <math.h>
#include <TFile.h>
#include <TTree.h>
#include <TNtuple.h>
#include <TH1F.h>
#include <TH2F.h>

/**
   \class SanityPlots
   User defined class SanityPlots ... these comments are used to generate
   doxygen documentation!
 */
class SanityPlots{

public:

  /// Default constructor
  SanityPlots(){}

  /// Default destructor
  ~SanityPlots(){}

  void Check();
};

#endif
/** @} */ // end of doxygen group 

