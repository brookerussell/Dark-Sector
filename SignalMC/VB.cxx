#ifndef VB_CXX
#define VB_CXX

#include "VB.h"

void VB::PseudoscalarMeson()
{
  
  // ###########################################################
  // ### Opening the file from Meson.cxx (note the file must ###
  // ###        match what is set in mac/default.py          ###
  // ###########################################################
  TFile* z = new TFile("Woburn.root");
  // ### Name of the TTree defined in Meson.cxx ###
  TTree *l = (TTree*)z->Get("l");
  
  // ### Grabbing variables for the created mesons ###
  int nMesons;
  float mesonID,mesonPx,mesonPy,mesonPz,mesonE,mesonPnew,mesonMass;
  l->SetBranchAddress("nMesons",&nMesons);
  l->SetBranchAddress("mesonID",&mesonID);
  l->SetBranchAddress("mesonPx",&mesonPx);
  l->SetBranchAddress("mesonPy",&mesonPy);
  l->SetBranchAddress("mesonPz",&mesonPz);
  l->SetBranchAddress("mesonE",&mesonE);
  l->SetBranchAddress("mesonPnew",&mesonPnew);
  l->SetBranchAddress("mesonMass",&mesonMass);
  
  // #############################################################################################
  // ###       Creating a file which will output the results of running this script            ###
  // ### Namely, the vector boson and photons in the lab-frame and the center-of-mass frame    ###
  // #############################################################################################
  TFile* fout = TFile::Open("Stoneham.root","RECREATE");
  TTree k("k","");
  
  // ### Useful variables for storing and creating ###
  int nVbosons,mesonMotherID;
  // ### Variables for the Vector Boson ###
  double  VB_Px,VB_Py,VB_Pz,VB_E,VB_mass, VB_P; 
  
  // ### Variables for tracking the parent meson ###
  double mesonPx_LF,mesonPy_LF,mesonPz_LF,mesonE_LF, mesonP_LF;
  double mesonPx_CMF,mesonPy_CMF,mesonPz_CMF,mesonE_CMF,mesonP_CMF;
  double omass, photon_Px,photon_Py,photon_Pz,photon_E,photon_P;
  
  // ### Number of Vector Bosons created ###
  k.Branch("nVbosons",&nVbosons,"nVbosons/I");
  
  // ### The ID number of the meson which created the Vector Boson ###
  k.Branch("mesonMotherID",&mesonMotherID,"mesonMotherID/I");
  
  // ### The Px component of the Vector Boson ###
  k.Branch("VB_Px",&VB_Px,"VB_Px/D"); // lab frame vectorboson momentum
  
  // ### The Py component of the Vector Boson ###
  k.Branch("VB_Py",&VB_Py,"VB_Py/D");
  
  // ### The Pz component of the Vector Boson ###
  k.Branch("VB_Pz",&VB_Pz,"VB_Pz/D");
  
  // ### The Energy of the Vector Boson ###
  k.Branch("VB_E",&VB_E,"VB_E/D"); // lab frame vectorboson energy
  
  // ### The Vector Boson momentum P = E^2 - m^2 ###
  k.Branch("VB_P",&VB_P,"VB_P/D"); // lab frame vectorboson 3-momentum
  
  // ### The Vector Boson Invariant mass ###
  k.Branch("VB_mass",&VB_mass,"VB_mass/D"); // vectorboson mass
  
  // ### Meson Px (GeV) in the lab frame###
  k.Branch("mesonPx_LF",&mesonPx_LF,"mesonPx_LF/D"); // lab frame initial meson momentum 
  
  // ### Meson Py (GeV) in the lab frame ###
  k.Branch("mesonPy_LF",&mesonPy_LF,"mesonPy_LF/D");
  
  // ### Meson Pz (GeV) in the lab frame ###
  k.Branch("mesonPz_LF",&mesonPz_LF,"mesonPz_LF/D");
  
  // ### Meson Energy in the lab frame (GeV) ###
  k.Branch("mesonE_LF",&mesonE_LF,"mesonE_LF/D"); // lab frame initial meson energy
  
  // ### Meson 3-momentum in the lab frame (GeV) sqrt(Px^2 + Py^2 + P^2) ###
  k.Branch("mesonP_LF",&mesonP_LF,"mesonP_LF/D"); // lab frame meson 3-momentum
  
  // ### Meson Px (GeV) in the Center-of_Mass frame###
  k.Branch("mesonPx_CMF",&mesonPx_CMF,"mesonPx_CMF/D"); // rest frame initial meson momentum 
  
  // ### Meson Py (GeV) in the Center-of_Mass frame###
  k.Branch("mesonPy_CMF",&mesonPy_CMF,"mesonPy_CMF/D");
  
  // ### Meson Pz (GeV) in the Center-of_Mass frame###
  k.Branch("mesonPz_CMF",&mesonPz_CMF,"mesonPz_CMF/D");
  
  // ### Meson E (GeV) in the Center-of_Mass frame###
  k.Branch("mesonE_CMF",&mesonE_CMF,"mesonE_CMF/D"); // rest frame initial meson energy
  
  // ### Meson 3-momentum (GeV) in the Center-of_Mass frame###
  k.Branch("mesonP_CMF",&mesonP_CMF,"mesonP_CMF/D"); // rest frame meson 3-momentum
  
  // ### Photon Px (GeV) ###
  k.Branch("photon_Px",&photon_Px,"photon_Px/D"); // lab frame photon momentum
  
  // ### Photon Py (GeV) ###
  k.Branch("photon_Py",&photon_Py,"photon_Py/D");
  
  // ### Photon Pz (GeV) ###
  k.Branch("photon_Pz",&photon_Pz,"photon_Pz/D");
  
  // ### Photon E (GeV) ###
  k.Branch("photon_E",&photon_E,"photon_E/D"); // lab frame photon energy
  
  // ### Photon 3-momentum (GeV) ###
  k.Branch("photon_P",&photon_P,"photon_P/D"); // lab frame 3-momentum
  
  
  k.Branch("omass",&omass,"omass/D"); // meson mass
  //z->cd();
  
  // ########################
  // ### Histogram Checks ###
  // ########################
  TH1F *mesonid = new TH1F("mesonid","Meson Mother ID",5,1,5);
  TH1F *vbx = new TH1F("vbx","P_{x} (V_{B} lab frame) ",400,-2,2);
  TH1F *vby = new TH1F("vby","P_{y} (V_{B} lab frame)",400,-2,2);
  TH1F *vbz = new TH1F("vbz","P_{z} (V_{B} lab frame)",1200,-2,10);
  TH1F *vbe = new TH1F("vbe","V_{B} Energy (lab frame)",800,0,8);
  TH1F *vbmass = new TH1F("vbmass","V_{B} mass",1100,0,1.1); 
  TH1D *phx = new TH1D("phx","P_{x} (#gamma_{x} lab frame)",400,-2,2);
  TH1F *phy = new TH1F("phy","P_{y} (#gamma_{y} lab frame)",400,-2,2);
  TH1F *phz = new TH1F("phz","P_{z} (#gamma_{z} lab frame)",400,-2,2);
  TH1D *phe = new TH1D("phe","#gamma energy (lab frame)",1600,-8,8);
  TH1F *oldmass = new TH1F("oldmass","Meson mass",600,5,1.1);
  TH1F *mrf = new TH1F("mrf","Meson Invariant Mass (Rest Frame)",1100,0,1.1);
  TH1F *mlf = new TH1F("mlf","Meson Invariant Mass (Lab Frame)",1100,0,1.1);
  TH1F *prf = new TH1F("prf","Photon Invariant Mass (Rest Frame)",2200,-1.1,1.1);
  TH1F *plf = new TH1F("plf","Photon Invariant Mass (Lab Frame)",2200,-1.1,1.1);
  TH1F *voblf = new TH1F("voblf","Vector Boson Invariant Mass (Lab Frame)",1100,0,1.1);
  TH1F *vobrf = new TH1F("vobrf","Vector Boson Invariant Mass (Rest Frame)",1100,0,1.1);
  TH1F *rvbx = new TH1F("rvbx","P_{x} (V_{B} rest frame)",400,-2,2);
  TH1F *rvby = new TH1F("rvby","P_{y} (V_{B} rest frame)",400,-2,2);
  TH1F *rvbz = new TH1F("rvbz","P_{z} (V_{B} rest frame)",400,-2,2);
  TH1F *rvbe = new TH1F("rvbe", "V_{B} Energy (rest frame)", 1600,-8,8);
  TH1F *rpx = new TH1F("rpx","P_{X} (#gamma rest frame)",400,-2,2);
  TH1F *rpy = new TH1F("rpy","P_{Y} (#gamma rest frame)",400,-2,2);
  TH1F *rpz = new TH1F("rpz","P_{Z} (#gamma rest frame)",400,-2,2);
  TH1F *rpe = new TH1F("rpe", "#gamma Energy (rest frame)",400,-2,2);
  
  
  // ### Counters for number of mesons with mass ###
  // ###   greater than the vector boson mass    ###
  int ctr = 0;
  
  // ### Counters for number of mesons with mass ###
  // ###   greater than the vector boson mass    ###
  int dtr = 0;
  
  // ### Defining TLorentzVector for boosts ###
  TLorentzVector com, zero_m, com_a, zero_a, com_b, zero_b;
  
  TLorentzVector labFrameVB, labFramePho;
  // ### Grabbing the number of events (POT) ###
  Int_t mentries = (Int_t)l->GetEntries();
  
  // ###############################
  // ### Looping over all events ###
  // ###############################
  for(Int_t i=0; i<mentries; i++)
  //for(Int_t i=0; i<100; i++)
     {
     // ### Printing Events ###
     if(i % 10000 == 0){std::cout<<"Event = "<<i<<std::endl;} 
     
     // ### Getting current entry for this event ###
     l->GetEntry(i);
     
     // ### Grabbing the mesons (to create a Vector Boson) ###
     mesonPx_LF = mesonPx; // meson lab frame momentum components 
     mesonPy_LF = mesonPy;
     mesonPz_LF = mesonPz;
     mesonE_LF = mesonE; // meson energy lab frame
     
     // ### P = sqrt(Px^2 + Py^2 + Pz^2) ###
     mesonP_LF = sqrt( (mesonPx*mesonPx) + (mesonPy*mesonPy) + (mesonPz*mesonPz) ); // meson lab frame 3-momentum
     
     // ###########################################
     // ### Defining the lab frame of the meson ###
     // ###########################################
     TLorentzVector meson_lf;
     meson_lf.SetPxPyPzE(mesonPx,mesonPy,mesonPz,mesonE);
     
     // ### Saving the invariant mass in the lab frame ###
     float mlfinv = meson_lf.Mag();
     mlf->Fill(mlfinv);
     
     // ### Defining a zero rest frame ###
     zero_m.SetPxPyPzE(0,0,0,0);
     
     // ### Defining the center of mass frame as the lab frame + zero frame ###
     com = meson_lf + zero_m;
     
     // ### Boost meson to its rest frame ###
     meson_lf.Boost(-com.BoostVector());
     
     // ### Defining the meson center-of-mass frame ###
     TLorentzVector meson_cmf;
     
     // ### Setting the Center-of-Mass variables ###
     meson_cmf.SetPxPyPzE(meson_lf[0],
         		  meson_lf[1],
			  meson_lf[2],
			  meson_lf[3]);
     
     // ### Storing to the TTree the CMF variables for the meson ###
     mesonPx_CMF = meson_cmf[0];
     mesonPy_CMF = meson_cmf[1];
     mesonPz_CMF = meson_cmf[2];
     mesonE_CMF = meson_cmf[3];
     mesonP_CMF = sqrt( (meson_lf[0]*meson_lf[0])
		      + (meson_lf[1]*meson_lf[1])
		      + (meson_lf[2]*meson_lf[2]) );
     
     // ### Storing the invariant mass in the center of mass frame ###		      
     float mrfinv = meson_cmf.Mag(); // meson rest frame invariant mesonMass
     mrf->Fill(mrfinv); 
     
     // ##############################################################
     // ### If the meson is a Eta (ID == 1) or Eta-prime (ID == 4) ###
     // ###                     Decay in Flight                    ###
     // ##############################################################
     if (mesonID == 1 || mesonID == 4)
	{
	 
	 // ### Defining the meson center-of-mass frame ###
	 TLorentzVector meson_cmf;
	 // ### Setting the Center-of-Mass variables ###
	 meson_cmf.SetPxPyPzE(mesonPx_CMF,mesonPy_CMF,mesonPz_CMF,mesonE_CMF);
	 // ??????
	 TGenPhaseSpace event_k;
	 
	 // ### Looping over mass ranges in 10 MeV steps ###
	 for(float m = 0.140; m<0.630; m+=0.010) // vector boson masses
	    {
	    
	    // ### Setting a vector of mass ###
	    double masses[2] = {m,0.0};
	    
	    // ### If the mass of the meson is greater than the mass of the ###
	    // ###    vector boson we can allow the Vector Boson decay      ###
	    if(mesonMass > m)
	       {
	       
	       // ### Set the decay of the meson ###
	       event_k.SetDecay(meson_cmf,2,masses);
	       
	       // ### Actually decay the particle ###
	       event_k.Generate();
	       
	       // ### Create a TLorentzVector for the Vector Boson ###
	       TLorentzVector *vectorBoson = event_k.GetDecay(0);
	       // ### Create a TLorentzVector for the Photon ###
	       TLorentzVector *photonInitial = event_k.GetDecay(1);
	       
	       // ### Creating TLorentzVectors to Vector Bosons in the COM ###
	       TLorentzVector VectorBoson_CM = *vectorBoson;
	       // ### Creating TLorentzVectors to Vector Bosons in the COM ###
	       TLorentzVector PhotonInitial_CM = *photonInitial;
	       
	       // ### Calculating the Vector Boson COM Invariant Mass ###
	       float vb_rfinv = VectorBoson_CM.Mag(); //rest frame
	       vobrf->Fill(vb_rfinv);
	       
	       // ### Calculating the Photon COM Invariant Mass ###
	       float ph_rfinv = PhotonInitial_CM.Mag(); //rest frame
	       prf->Fill(ph_rfinv);
		  
	       float restvbx = VectorBoson_CM.Px();
	       float restvby = VectorBoson_CM.Py();
	       float restvbz = VectorBoson_CM.Pz();
	       float restvbe = VectorBoson_CM.E();
	       rvbx->Fill(restvbx);
	       rvby->Fill(restvby);
	       rvbz->Fill(restvbz);
	       rvbe->Fill(restvbe);
		  
	       float restpx = PhotonInitial_CM.Px();
	       float restpy = PhotonInitial_CM.Py();
	       float restpz = PhotonInitial_CM.Pz();
	       float restpe = PhotonInitial_CM.E();
	       rpx->Fill(restpx);
      	       rpy->Fill(restpy);
	       rpz->Fill(restpz);
	       rpe->Fill(restpe);
	       
	       
	       // ### Now boost the Vector Boson back to the lab frame ###
	       TLorentzVector VB_lf;
	       VB_lf.SetPxPyPzE(restvbx, restvby, restvbz, restvbe);
	       
	       // ### Now boost the photon back to the lab frame ###
	       TLorentzVector Pho_lf;
	       Pho_lf.SetPxPyPzE(restpx, restpy, restpz, restpe);
	       
	       
	       // ### Defining the boost frame back to the lab frame ###
	       labFrameVB = VB_lf + meson_lf;
	       labFramePho = Pho_lf + meson_lf;
	       
	       // ### Boosting the VB to the lab frame ###	     
	       VB_lf.Boost(labFrameVB.BoostVector());
	       
	       // ### Boosting the Photon to the lab frame ###
	       Pho_lf.Boost(labFramePho.BoostVector());
	    
	       float invMassAfter = sqrt( (VB_lf[3]*VB_lf[3]) - 
	                             ( (VB_lf[0]*VB_lf[0]) + (VB_lf[1]*VB_lf[1]) + (VB_lf[2]*VB_lf[2]) ));
				     
	       // ### Saving the Vector Bosons to the tree ###			     
	       VB_Px = VB_lf[0];
	       VB_Py = VB_lf[1];
	       VB_Pz = VB_lf[2];
	       VB_E = VB_lf[3];
	       VB_P = sqrt( (VB_Px*VB_Px) + (VB_Py*VB_Py) + (VB_Pz*VB_Pz) );
	       VB_mass = invMassAfter;
	       
	       // ### Saving the photons to the tree ###
	       photon_Px = Pho_lf[0];
	       photon_Py = Pho_lf[1];
	       photon_Pz = Pho_lf[2];
	       photon_E = Pho_lf[3];
	       photon_P = sqrt( (photon_Px*photon_Px) + (photon_Py*photon_Py) + (photon_Pz*photon_Pz) );
	       omass = mesonMass;
	       mesonMotherID = mesonID;
	       
	       //std::cout<<"In Lab frame Inv Mass = "<<invMassAfter<<std::endl;
	       //std::cout<<std::endl;
	         
	       /*zero_a.SetPxPyPzE(0,0,0,0);
	       com_a = VectorBoson_CM + zero_a;
	       VectorBoson_CM.Boost(-com_a.BoostVector());
	       //zero_b.SetPxPyPzE(0,0,0,0);
	       //com_b = PhotonInitial_CM + zero_b;
	       PhotonInitial_CM.Boost(-com_a.BoostVector());
	       TLorentzVector VectorBoson_lf;
	       VectorBoson_lf.SetPxPyPzE(VectorBoson_CM[0],
		  		    VectorBoson_CM[1],
		  		    VectorBoson_CM[2],
		  		    VectorBoson_CM[3]);
	       TLorentzVector PhotonInitial_lf;
	       PhotonInitial_lf.SetPxPyPzE(PhotonInitial_CM[0],
		  		    PhotonInitial_CM[1],
		  		    PhotonInitial_CM[2],
		  		    PhotonInitial_CM[3]);
		  float vm = VectorBoson_lf.Mag(); // lab frame
		  voblf->Fill(vm);
		  float pm = PhotonInitial_lf.Mag(); //lab frame
		  plf->Fill(pm);
		  std::cout<<"V LF = "<<vm<<" V RF = "<<vb_rfinv<<" P LF = "<< pm <<" P RF = "<< ph_rfinv<<std::endl;
		  
		  mesonid->Fill(mesonID);
		  vbx->Fill(VB_Px);
		  vby->Fill(VB_Py);
		  vbz->Fill(VB_Pz);
		  vbe->Fill(VB_E);
		  phx->Fill(photon_Px);
		  phy->Fill(photon_Py);
		  phz->Fill(photon_Pz);
		  phe->Fill(photon_E);
		  vbmass->Fill(VB_mass); // vectorboson mesonMass
		  oldmass->Fill(mesonMass); // original mesonMass */
		  ctr++;
		  // Clear all 4-momenta, otherwise a sefault will result
		  meson_lf.Clear();
		  //meson_cmf.Clear();
		  VectorBoson_CM.Clear();
		  PhotonInitial_CM.Clear();
		  //VectorBoson_lf.Clear();
		  //PhotonInitial_lf.Clear();
		} // <-- end if
	    } // <-- end m for loop
	} // <-- end eta/eta' if
      if(mesonID == 2 || mesonID == 3 || mesonID == 5)
	{
	  for(float n = 0.140; n < 0.630; n+=0.010)
	    {
	      // vector boson (inferred) energy
	      float iE = sqrt((n*n)+(mesonPnew*mesonPnew));
	      if((iE*iE)>(n*n))
		{
		  VB_P = sqrt((iE*iE)-(n*n)); // vector boson 3-momentum
		  VB_E = sqrt((VB_P*VB_P)+(n*n)); // vector boson energy
		  // assign vector boson component momentum (respecting ratio of original meson)
		  VB_Px = (VB_P*mesonPx)/mesonPnew;
		  VB_Py = (VB_P*mesonPy)/mesonPnew;
		  VB_Pz = (VB_P*mesonPz)/mesonPnew;
		  VB_mass = n;
		  vbx->Fill(VB_Px);
		  vby->Fill(VB_Py);
		  vbz->Fill(VB_Pz);
		  vbe->Fill(VB_E);
		  vbmass->Fill(VB_mass);
		  omass = mesonMass;
		  oldmass->Fill(mesonMass);
		  mesonMotherID = mesonID;
		  mesonid->Fill(mesonID);
		  dtr++;
		} // <-- if energy^2 is greater than mesonMass^2
	    } // <-- end n loop
	}
      if(ctr>0)
	{
	  nVbosons = ctr+dtr;
	  k.Fill();
	}
    } // <-- end i loop
  z->Close();
  fout->Write();
}

#endif
