/**
 * \file MediatorDecay.h
 *
 * \ingroup MediatorVisibleDecay
 * 
 * \brief Class def header for a class MediatorDecay
 *
 * @author br
 */

/** \addtogroup MediatorVisibleDecay

    @{*/
#ifndef MEDIATORDECAY_H
#define MEDIATORDECAY_H

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
   \class MediatorDecay
   User defined class MediatorDecay ... these comments are used to generate
   doxygen documentation!
 */
class MediatorDecay{

public:

  /// Default constructor
  MediatorDecay(){}

  /// Default destructor
  ~MediatorDecay(){}

  void MD();

  /*  double ProbabilityDecay(double mass, double px, double px, double pz, double e)
  {
    double Partial_width = k*alpha_EM*pow(VB_mass,3.0)
      *pow(96.0,-1.0)*pow(pi,-3.0)*pow(f_pion,-2.0)
      *pow(1-(pow(mass_pion,2.0)*pow(VB_mass,-2.0)),3.0);

    double Tau = pow(Partial_width,-1.0);
          
    Ephemeral.SetPxPyPzE(VB_Px,VB_Py,VB_Pz,VB_E);
          
    double boost_mag = Ephemeral.Beta();

    double lbar = boost_mag*c*Tau;

    double P_decay = exp(-frontend[j]*pow(lbar,-1.0))
      -exp(-backend[j]*pow(lbar,-1.0));
  }
  */
  TLorentzVector Ephemeral;

};

#endif
/** @} */ // end of doxygen group 

