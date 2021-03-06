#ifndef MEDIATORDETECTORINTERCEPT_CXX
#define MEDIATORDETECTORINTERCEPT_CXX

#include "MediatorDetectorIntercept.h"

void MediatorDetectorIntercept::MDI()
{
  TFile* f = new TFile("MediatorSelection_output.root");
  TTree *ms = (TTree*)f->Get("ms");

  int eventNUM,UniqueVB,MesonToVB,Pi0ToVB,mesonMother_id;
  double VB_PX,VB_PY,VB_PZ,VB_ENERGY,VB_MASS;

  ms->SetBranchAddress("eventNUM",&eventNUM); // Event number
  ms->SetBranchAddress("UniqueVB",&UniqueVB); // # to track VB
  ms->SetBranchAddress("MesonToVB",&MesonToVB); // Links meson to VB
  ms->SetBranchAddress("Pi0ToVB",&Pi0ToVB); // Links Pi0 to VB
  ms->SetBranchAddress("mesonMother_id",&mesonMother_id);
  ms->SetBranchAddress("VB_PX",&VB_PX);
  ms->SetBranchAddress("VB_PY",&VB_PY);
  ms->SetBranchAddress("VB_PZ",&VB_PZ);
  ms->SetBranchAddress("VB_ENERGY",&VB_ENERGY);
  ms->SetBranchAddress("VB_MASS",&VB_MASS);

  TFile* fout = TFile::Open("MediatorDetectorIntercept_output.root","RECREATE")\
    ;
  TTree mdi("mdi","");

  int event_num,unique_vb,meson2vb,pi02vb,mesonMom_id,detector_id;
  double vb_px,vb_py,vb_pz,vb_e,vb_mass;
  TLorentzVector vb;

  mdi.Branch("event_num",&event_num,"event_num/I"); // Event number
  mdi.Branch("unique_vb",&unique_vb,"unique_vb/I"); // # to track VB
  mdi.Branch("meson2vb",&meson2vb,"meson2vb/I"); // Links meson to VB
  mdi.Branch("pi02vb",&pi02vb,"pi02vb/I"); // Links Pi0 to VB
  mdi.Branch("mesonMom_id",&mesonMom_id,"mesonMom_id/I");
  mdi.Branch("detector_id",&detector_id,"detector_id/I"); // Indicates which detector (SBND, MicroBooNE or ICARUS)
  mdi.Branch("vb_px",&vb_px,"vb_px/D");
  mdi.Branch("vb_py",&vb_py,"vb_py/D");
  mdi.Branch("vb_pz",&vb_pz,"vb_pz/D");
  mdi.Branch("vb_e",&vb_e,"vb_e/D");
  mdi.Branch("vb_mass",&vb_mass,"vb_mass/D");
  mdi.Branch("vb",&vb); // VB 4-vector

  Int_t entries = (Int_t)ms->GetEntries();

  std::cout << "FINDING which mediators intercept detectors" << std::endl;

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
	      // Assign TBranches
	      event_num = eventNUM;
	      unique_vb = UniqueVB;
	      meson2vb = MesonToVB;
	      pi02vb = Pi0ToVB;
	      mesonMom_id = mesonMother_id;
	      detector_id = j;
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

  std::cout << "ONLY save mediators which intercept the detector." << std::endl;

  f->Close();
  fout->Write();
}
#endif
