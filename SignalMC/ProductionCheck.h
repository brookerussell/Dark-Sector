/**
 * \file ProductionCheck.h
 *
 * \ingroup SignalMC
 * 
 * \brief Class def header for a class ProductionCheck
 *
 * @author ber9
 */

/** \addtogroup SignalMC

    @{*/
#ifndef PRODUCTIONCHECK_H
#define PRODUCTIONCHECK_H

#include <iostream>
#include <math.h>
#include <TFile.h>
#include <TTree.h>
#include <TNtuple.h>
#include <TH1F.h>
#include <TH2F.h>

/**
   \class ProductionCheck
   User defined class ProductionCheck ... these comments are used to generate
   doxygen documentation!
 */
class ProductionCheck{

public:

  /// Default constructor
  ProductionCheck(){}

  /// Default destructor
  ~ProductionCheck(){}

  void CheckAll();
  
};

#endif
/** @} */ // end of doxygen group 

