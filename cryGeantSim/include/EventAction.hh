//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file muonDet/crySim/include/EventAction.hh
/// \brief Definition of the EventAction class
//
// $Id$
// --------------------------------------------------------------
//
#ifndef EventAction_h
#define EventAction_h 1

#include "TAxis.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "TStyle.h"
#include "TPad.h"
#include "TROOT.h"
#include "TColor.h"
#include "TGFrame.h"
#include "TVirtualPad.h"
#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TTree.h"

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "DSEvent.h"
#include "DSParticle.h"

//class HistoManager;

class EventAction : public G4UserEventAction
{
  public:
EventAction(DSEvent*,TTree*);
    virtual ~EventAction();

    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);

    DSEvent *DSEventData;

  private:
    G4int fBDHCID0;

//HistoManager* fHistoManager;
    
    G4int fVerboseLevel;

    TTree* _tree;


  public:
      inline void SetVerbose(G4int val) { fVerboseLevel = val; }
      inline G4int GetVerbose() const { return fVerboseLevel; }
};

#endif
