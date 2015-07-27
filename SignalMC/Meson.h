/**
 * \file Meson.h
 *
 * \ingroup SignalMC
 * 
 * \brief Class def header for a class Meson
 *
 * @author ber9
 */

/** \addtogroup SignalMC

    @{*/
#ifndef MESON_H
#define MESON_H

#include <iostream>
#include <math.h>
#include <TFile.h>
#include <TTree.h>
#include <TNtuple.h>
#include <TH1F.h>
#include <TH2F.h>

/**
   \class Meson
   User defined class Meson ... these comments are used to generate
   doxygen documentation!
 */
class Meson{

public:

  /// Default constructor
  Meson(){}

  /// Default destructor
  ~Meson(){}

  void SetParams();

  //  float* Initial(float arr[]){ return arr;}
  //  {
    //TLorentzVector Original;
    //float mM = sqrt(px*px+py*py+pz*pz); // momentum magnitude
    //float iE = sqrt(mass*mass+mM*mM); // inferred pi0 energy
    //float fakeE = iE-(fakeMass*fakeMass); //CHECK THIS!!!
    //float fakePx = sqrt(px*mM)/iE;
    //float fakePy = sqrt(py*mM)/iE;
    //float fakePz = sqrt(pz*mM)/iE;
    //return float Original[]={fakePx,
  //		      fakePy,
  //		      fakePz,
  //		      fakeE};
    //return Original;
  //};
 protected:
  static float _mass;
  static float _px;
  static float _py;
  static float _pz;
};

#endif
/** @} */ // end of doxygen group 

