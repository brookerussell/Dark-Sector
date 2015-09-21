/**
 * \file sample.h
 *
 * \ingroup SignalMC
 * 
 * \brief Class def header for a class sample
 *
 * @author ber9
 */

/** \addtogroup SignalMC

    @{*/
#ifndef DARKSECTOR_SIGNALMC_SAMPLE_H
#define DARKSECTOR_SIGNALMC_SAMPLE_H

#include "TObject.h"
/**
   \class sample
   User defined class SignalMC ... these comments are used to generate
   doxygen documentation!
 */
class test : public TObject{

public:

  /// Default constructor
  test(){}

  /// Default destructor
  virtual ~test(){};

  void A(const std::string file_name);

  float marker;
};

#endif
/** @} */ // end of doxygen group 

