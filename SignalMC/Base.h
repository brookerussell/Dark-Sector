/**
 * \file Base.h
 *
 * \ingroup SignalMC
 * 
 * \brief Class def header for a class Base
 *
 * @author ber9
 */

/** \addtogroup SignalMC

    @{*/
#ifndef BASE_H
#define BASE_H

#include <iostream>
#include "TObject.h"
#include "TMath.h"

/**
   \class Base
   User defined class Base ... these comments are used to generate
   doxygen documentation!
 */
class Base : public TObject {

 protected:
  double fPx; // x component of momentum
  double fPy;  
  double fPz;   
  double fMass; // the mass square of this particle
  double fBx; // x intercept at the vertex
  double fBy;   
  double fBz; // z intercept at the vertex
  double fVertex[3]; // vertex position
  double fXfirst; // x coordinate of the first point of track
  double fXlast; // xcoordinate of the last point of track
  double fYfirst;
  double fYlast;
  double fZfirst;
  double fZlast;
  
public:

  /// Default constructor
  Base(){}

  /// Default destructor
  ~Base(){}

  double GetPx() const { return fPx; }
  double GetPy() const { return fPy; }
  double GetPz() const { return fPz; }
  double GetMass() const { return fMass; }
  double GetBx() const { return fBx; }
  double GetBy() const { return fBy; }
  double GetBz() const { return fBz; }
  double GetVertex(Int_t i=0) {return (i<3)?fVertex[i]:0;} // ????
  double GetXfirst() const { return fXfirst; }
  double GetXlast() const { return fXlast; }
  double GetYfirst() const { return fYfirst; }
  double GetYlast() const { return fYlast; }
  double GetZfirst() const {return fZfirst; }
  double GetZlast() const {return fZlast; }

};

#endif
/** @} */ // end of doxygen group 

