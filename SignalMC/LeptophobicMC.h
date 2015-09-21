/**
 * \file LeptophobicMC.h
 *
 * \ingroup SignalMC
 * 
 * \brief Class def header for a class LeptophobicMC
 *
 * @author ber9
 */

/** \addtogroup SignalMC

    @{*/
#ifndef LEPTOPHOBICMC_H
#define LEPTOPHOBICMC_H

#include <iostream>
#include <math.h>
#include <TTree.h>
#include <TFile.h>
#include <TNtuple.h>
#include <TH1F.h>
#include <TH2F.h>
/**
   \class LeptophobicMC
   User defined class LeptophobicMC ... these comments are used to generate
   doxygen documentation!
 */
class LeptophobicMC{

public:

  /// Default constructor
  LeptophobicMC(){}

  /// Default destructor
  ~LeptophobicMC(){}

  //  void Run(TTree* tree);
  void Run();

};

#endif
/** @} */ // end of doxygen group 

