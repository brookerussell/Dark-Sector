#ifndef MEDIATORDECAY_CXX
#define MEDIATORDECAY_CXX

#include "MediatorDecay.h"

void MediatorDecay::MD()
{
  TFile* f = new TFile("MediatorDetectorIntercept_output.root");
  TTree *mdi = (TTree*)f->Get("mdi");

  int nvb,mesonMomID,pi0ID;
  double vb_px,vb_py,vb_pz,vb_e,vb_mass;

  mdi->SetBranchAddress("nvb",&nvb);
  mdi->SetBranchAddress("mesonMomID",&mesonMomID);
  mdi->SetBranchAddress("pi0ID",&pi0ID);
  mdi->SetBranchAddress("vb_px",&vb_px);
  mdi->SetBranchAddress("vb_py",&vb_py);
  mdi->SetBranchAddress("vb_pz",&vb_pz);
  mdi->SetBranchAddress("vb_e",&vb_e);
  mdi->SetBranchAddress("vb_mass",&vb_mass);

  TFile* fout = TFile::Open("MediatorDecay","RECREATE");
  TTree md("md","");

  double pi0_px,pi0_py,pi0_pz,pi0_e;
  double ph1_px,ph1_py,ph1_pz,ph1_e;
  double ph2_px,ph2_py,ph2_pz,ph2_e;
  double ph3_px,ph3_py,ph3_pz,ph3_e;
  TLorentzVector pi0,ph1,ph2,ph3;

  md.Branch("pi0_px",&pi0_px,"pi0_px/F");
  md.Branch("pi0_py",&pi0_py,"pi0_py/F");
  md.Branch("pi0_pz",&pi0_pz,"pi0_pz/F");
  md.Branch("pi0_e",&pi0_e,"pi0_e/F");
  md.Branch("pi0",&pi0);
  md.Branch("ph1_px",&ph1_px,"ph1_px/F");
  md.Branch("ph1_py",&ph1_py,"ph1_py/F");
  md.Branch("ph1_pz",&ph1_pz,"ph1_pz/F");
  md.Branch("ph1_e",&ph1_e,"ph1_e/F");
  md.Branch("ph1",&ph1);
  md.Branch("ph2_px",&ph2_px,"ph2_px/F");
  md.Branch("ph2_py",&ph2_py,"ph2_py/F");
  md.Branch("ph2_pz",&ph2_pz,"ph2_pz/F");
  md.Branch("ph2_e",&ph2_e,"ph2_e/F");
  md.Branch("ph2",&ph2);
  md.Branch("ph3_px",&ph3_px,"ph3_px/F");
  md.Branch("ph3_py",&ph3_py,"ph3_py/F");
  md.Branch("ph3_pz",&ph3_pz,"ph3_pz/F");
  md.Branch("ph3_e",&ph3_e,"ph3_e/F");
  md.Branch("ph3",&ph3);

  Int_t entries = (Int_t)mdi->GetEntries();

  TLorentzVector Temp;

  std::cout<<"Decay the mediator to Pi0s and photons."<<std::endl;

  for(Int_t i=0; i<entries; i++)
    {

      mdi->GetEntry(i);

      Temp.SetPxPyPzE(vb_px,vb_py,vb_pz,vb_e);
        
      TGenPhaseSpace event_d;
      double masses_d[2] = {0.139,0.0};
      event_d.SetDecay(Temp,2,masses_d);
      event_d.Generate();
      TLorentzVector *pizero = event_d.GetDecay(0);
      TLorentzVector *photon1 = event_d.GetDecay(1);
      pi0 = *pizero;
      ph1 = *photon1;

      pi0_px = pi0.Px();
      pi0_py = pi0.Py();
      pi0_pz = pi0.Pz();
      pi0_e = pi0.E();
      ph1_px = ph1.Px();
      ph1_py = ph1.Py();
      ph1_pz = ph1.Pz();
      ph1_e = ph1.E();
        
      TGenPhaseSpace event_f;
      double mass_f[3] = {0.0,0.0};
      event_f.SetDecay(pi0,2,mass_f);
      event_f.Generate();
      TLorentzVector *photon2 = event_f.GetDecay(0);
      TLorentzVector *photon3 = event_f.GetDecay(1);
      ph2 = *photon2;
      ph3 = *photon3;

      ph2_px = ph2.Px();
      ph2_py = ph2.Py();
      ph2_pz = ph2.Pz();
      ph2_e = ph2.E();
      ph3_px = ph3.Px();
      ph3_py = ph3.Py();
      ph3_pz = ph3.Pz();
      ph3_e = ph3.E();

      md.Fill();
        
      Ephemeral.Clear();
      Temp.Clear();
      pi0.Clear();
      ph1.Clear();
      ph2.Clear();
      ph3.Clear();
    } // <-- end i loop

  f->Close();
  fout->Write();  
} // <-- end void


#endif