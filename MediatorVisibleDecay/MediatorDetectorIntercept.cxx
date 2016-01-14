#ifndef MEDIATORDETECTORINTERCEPT_CXX
#define MEDIATORDETECTORINTERCEPT_CXX

#include "MediatorDetectorIntercept.h"

void MediatorDetectorIntercept::MDI()
{
  TFile* f = new TFile("MediatorSelection_output.root");
  TTree *ms = (TTree*)f->Get("ms");

  int nVB,mesonMother_id,Pi0_id;
  double VB_PX,VB_PY,VB_PZ,VB_ENERGY,VB_MOM,VB_MASS;

  ms->SetBranchAddress("nVB",&nVB);
  ms->SetBranchAddress("mesonMother_id",&mesonMother_id);
  ms->SetBranchAddress("Pi0_id",&Pi0_id);
  ms->SetBranchAddress("VB_PX",&VB_PX);
  ms->SetBranchAddress("VB_PY",&VB_PY);
  ms->SetBranchAddress("VB_PZ",&VB_PZ);
  ms->SetBranchAddress("VB_ENERGY",&VB_ENERGY);
  ms->SetBranchAddress("VB_MOM",&VB_MOM);
  ms->SetBranchAddress("VB_MASS",&VB_MASS);

  TFile* fout = TFile::Open("MediatorDetectorIntercept_output.root","RECREATE")\
    ;
  TTree mdi("mdi","");

  int nvb,mesonMomID,pi0ID;
  double vb_px,vb_py,vb_pz,vb_e,vb_mass;
  TLorentzVector vb;

  mdi.Branch("nvb",&nvb,"nvb/I");
  mdi.Branch("mesonMomID",&mesonMomID,"mesonMomID/I");
  mdi.Branch("pi0ID",&pi0ID,"pi0ID/I");
  mdi.Branch("vb_px",&vb_px,"vb_px/D");
  mdi.Branch("vb_py",&vb_py,"vb_py/D");
  mdi.Branch("vb_pz",&vb_pz,"vb_pz/D");
  mdi.Branch("vb_e",&vb_e,"vb_e/D");
  mdi.Branch("vb_mass",&vb_mass,"vb_mass/D");
  mdi.Branch("vb",&vb); // VB 4-vector

  Int_t entries = (Int_t)ms->GetEntries();

  std::cout << "Only save mediators which intercept the detector." << std::endl;

  for(Int_t i=0; i<entries; i++)
    {
      ms->GetEntry(i);
      
      // Copy component momentum
      double VB_Px_temp = VB_PX;
      double VB_Py_temp = VB_PY;
      double VB_Pz_temp = VB_PZ;
    
      // Temporarily make component momentum positive definite
      if(VB_Px_temp<0) {VB_Px_temp = VB_PX*-1;}
      if(VB_Py_temp<0) {VB_Py_temp = VB_PY*-1;}
      if(VB_Pz_temp<0) {VB_Pz_temp = VB_PZ*-1;}

      for(int j=0; j<3; j++) // Loop over detector array
      if(VB_Px_temp/VB_Pz_temp < xdist[j]/frontend[j])
	{
	  if(VB_Py_temp/VB_Pz_temp < ydist[j]/frontend[j])
	    {
	      mesonMomID = mesonMother_id;
	      pi0ID = Pi0_id;

	      vb_px = VB_PX;
	      vb_py = VB_PY;
	      vb_pz = VB_PZ;
	      vb_e = VB_ENERGY;
	      vb_mass = VB_MASS;
	      vb.SetPxPyPzE(VB_PX,
			    VB_PY,
			    VB_PZ,
			    VB_ENERGY);
	      mdi.Fill();
	    }
	}
    }
  f->Close();
  fout->Write();
}
#endif
