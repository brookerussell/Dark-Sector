/**
 * \file ERAnaTrial.h
 *
 * \ingroup SignalMC
 * 
 * \brief Class def header for a class ERAnaTrial
 *
 * @author ber9
 */

/** \addtogroup SignalMC

    @{*/

#ifndef ERTOOL_ERANATRIAL_H
#define ERTOOL_ERANATRIAL_H

#include "ERTool/Base/AnaBase.h"

namespace ertool {

  /**
     \class ERAnaTrial
     User custom Analysis class made by kazuhiro
   */
  class ERAnaTrial : public AnaBase {
  
  public:

    /// Default constructor
    ERAnaTrial(const std::string& name="ERAnaTrial");

    /// Default destructor
    virtual ~ERAnaTrial(){}

    /// Reset function
    virtual void Reset();

    /// Function to accept fclite::PSet
    void AcceptPSet(const ::fcllite::PSet& cfg);

    /// Called @ before processing the first event sample
    void ProcessBegin();

    /// Function to evaluate input showers and determine a score
    bool Analyze(const EventData &data, const ParticleGraph &ps);

    /// Called after processing the last event sample
    void ProcessEnd(TFile* fout=nullptr);

  };
}
#endif

/** @} */ // end of doxygen group 
