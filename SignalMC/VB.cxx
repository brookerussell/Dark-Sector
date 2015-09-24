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
  int vbosons,mesonMotherID;
  double  vx,vy,vz,ve,mxlf,mylf,mzlf,melf,mxrf,myrf,mzrf,merf,v,ml,mr,vmass,omass, px,py,pz,pe,p;
  k.Branch("vbosons",&vbosons,"vbosons/I");
  k.Branch("mesonMotherID",&mesonMotherID,"mesonMotherID/I");
  k.Branch("vx",&vx,"vx/D"); // lab frame vectorboson momentum
  k.Branch("vy",&vy,"vy/D");
  k.Branch("vz",&vz,"vz/D");
  k.Branch("ve",&ve,"ve/D"); // lab frame vectorboson energy
  k.Branch("v",&v,"v/D"); // lab frame vectorboson 3-momentum
  k.Branch("vmass",&vmass,"vmass/D"); // vectorboson mass
  k.Branch("mxlf",&mxlf,"mxlf/D"); // lab frame initial meson momentum 
  k.Branch("mylf",&mylf,"mylf/D");
  k.Branch("mzlf",&mzlf,"mzlf/D");
  k.Branch("melf",&melf,"melf/D"); // lab frame initial meson energy
  k.Branch("mxrf",&mxrf,"mxrf/D"); // rest frame initial meson momentum 
  k.Branch("myrf",&myrf,"myrf/D");
  k.Branch("mzrf",&mzrf,"mzrf/D");
  k.Branch("merf",&merf,"merf/D"); // rest frame initial meson energy
  k.Branch("ml",&ml,"ml/D"); // lab frame meson 3-momentum
  k.Branch("mr",&mr,"mr/D"); // rest frame meson 3-momentum
  k.Branch("px",&px,"px/D"); // lab frame photon momentum
  k.Branch("py",&py,"py/D");
  k.Branch("pz",&pz,"pz/D");
  k.Branch("pe",&pe,"pe/D"); // lab frame photon energy
  k.Branch("p",&p,"p/D"); // lab frame 3-momentum
  k.Branch("omass",&omass,"omass/D"); // meson mass
  //z->cd();
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
  int ctr = 0;
  int dtr = 0;
  TLorentzVector com, zero_m, com_a, zero_a, com_b, zero_b;
  Int_t mentries = (Int_t)l->GetEntries();
  for(Int_t i=0; i<mentries; i++)
     {
     // ### Printing Events ###
     if(i % 10000 == 0){std::cout<<"Event = "<<i<<std::endl;} 
     
     l->GetEntry(i);
     mxlf = mesonPx; // meson lab frame momentum components 
     mylf = mesonPy;
     mzlf = mesonPz;
     melf = mesonE; // meson energy lab frame
     ml = sqrt(mesonPx*mesonPx+mesonPy*mesonPy+mesonPz*mesonPz); // meson lab frame 3-momentum
     TLorentzVector meson_lf;
     meson_lf.SetPxPyPzE(mesonPx,mesonPy,mesonPz,mesonE);
     float mlfinv = meson_lf.Mag();
     mlf->Fill(mlfinv);
     zero_m.SetPxPyPzE(0,0,0,0);
     com = meson_lf + zero_m;
     // boost meson to its rest frame
     meson_lf.Boost(-com.BoostVector());
     TLorentzVector meson_rf;
     meson_rf.SetPxPyPzE(meson_lf[0],
         		  meson_lf[1],
			  meson_lf[2],
			  meson_lf[3]);
     mxrf = meson_rf[0];
     myrf = meson_rf[1];
     mzrf = meson_rf[2];
     merf = meson_rf[3];
     mr = sqrt(meson_lf[0]*meson_lf[0]
		+meson_lf[1]*meson_lf[1]
		+meson_lf[2]*meson_lf[2]); //
     float mrfinv = meson_rf.Mag(); // meson rest frame invariant mesonMass
     mrf->Fill(mrfinv); 
     if (mesonID == 1 || mesonID == 4)
	{
	  TLorentzVector meson_rf;
	  meson_rf.SetPxPyPzE(mxrf,myrf,mzrf,merf);
	  TGenPhaseSpace event_k;
	  for(float m = 0.140; m<0.630; m+=0.010) // vector boson masses
	    {
	      double masses[2] = {m,0.0};
	      if(mesonMass > m)
		{
		  event_k.SetDecay(meson_rf,2,masses);
		  event_k.Generate();
		  TLorentzVector *vectorBoson = event_k.GetDecay(0);
		  TLorentzVector *photonInitial = event_k.GetDecay(1);
		  TLorentzVector VectorBoson_rf = *vectorBoson;
		  TLorentzVector PhotonInitial_rf = *photonInitial;
		  float vb_rfinv = VectorBoson_rf.Mag(); //rest frame
		  vobrf->Fill(vb_rfinv);
		  float ph_rfinv = PhotonInitial_rf.Mag(); //rest frame
		  prf->Fill(ph_rfinv);
		  float restvbx = VectorBoson_rf.Px();
		  float restvby = VectorBoson_rf.Py();
		  float restvbz = VectorBoson_rf.Pz();
		  float restvbe = VectorBoson_rf.E();
		  rvbx->Fill(restvbx);
		  rvby->Fill(restvby);
		  rvbz->Fill(restvbz);
		  rvbe->Fill(restvbe);
		  float restpx = PhotonInitial_rf.Px();
		  float restpy = PhotonInitial_rf.Py();
		  float restpz = PhotonInitial_rf.Pz();
		  float restpe = PhotonInitial_rf.E();
		  rpx->Fill(restpx);
		  rpy->Fill(restpy);
		  rpz->Fill(restpz);
		  rpe->Fill(restpe);
		  /*zero_a.SetPxPyPzE(0,0,0,0);
		  com_a = VectorBoson_rf + zero_a;
		  VectorBoson_rf.Boost(-com_a.BoostVector());
		  //zero_b.SetPxPyPzE(0,0,0,0);
		  //com_b = PhotonInitial_rf + zero_b;
		  PhotonInitial_rf.Boost(-com_a.BoostVector());
		  TLorentzVector VectorBoson_lf;
		  VectorBoson_lf.SetPxPyPzE(VectorBoson_rf[0],
		  		    VectorBoson_rf[1],
		  		    VectorBoson_rf[2],
		  		    VectorBoson_rf[3]);
		  TLorentzVector PhotonInitial_lf;
		  PhotonInitial_lf.SetPxPyPzE(PhotonInitial_rf[0],
		  		    PhotonInitial_rf[1],
		  		    PhotonInitial_rf[2],
		  		    PhotonInitial_rf[3]);
		  float vm = VectorBoson_lf.Mag(); // lab frame
		  voblf->Fill(vm);
		  float pm = PhotonInitial_lf.Mag(); //lab frame
		  plf->Fill(pm);
		  std::cout<<"V LF = "<<vm<<" V RF = "<<vb_rfinv<<" P LF = "<< pm <<" P RF = "<< ph_rfinv<<std::endl;
		  vx = VectorBoson_lf.Px();
		  vy = VectorBoson_lf.Py();
		  vz = VectorBoson_lf.Pz();
		  ve = VectorBoson_lf.E();
		  v = sqrt(vx*vx+vy*vy+vz*vz);
		  vmass = m;
		  px = PhotonInitial_lf.Px();
		  py = PhotonInitial_lf.Py();
		  pz = PhotonInitial_lf.Pz();
		  pe = PhotonInitial_lf.E();
		  p = sqrt(px*pz+py*py+pz*pz);
		  omass = mesonMass;
		  mesonMotherID = mesonID;
		  mesonid->Fill(mesonID);
		  vbx->Fill(vx);
		  vby->Fill(vy);
		  vbz->Fill(vz);
		  vbe->Fill(ve);
		  phx->Fill(px);
		  phy->Fill(py);
		  phz->Fill(pz);
		  phe->Fill(pe);
		  vbmass->Fill(vmass); // vectorboson mesonMass
		  oldmass->Fill(mesonMass); // original mesonMass */
		  ctr++;
		  // Clear all 4-momenta, otherwise a sefault will result
		  meson_lf.Clear();
		  //meson_rf.Clear();
		  VectorBoson_rf.Clear();
		  PhotonInitial_rf.Clear();
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
		  v = sqrt((iE*iE)-(n*n)); // vector boson 3-momentum
		  ve = sqrt((v*v)+(n*n)); // vector boson energy
		  // assign vector boson component momentum (respecting ratio of original meson)
		  vx = (v*mesonPx)/mesonPnew;
		  vy = (v*mesonPy)/mesonPnew;
		  vz = (v*mesonPz)/mesonPnew;
		  vmass = n;
		  vbx->Fill(vx);
		  vby->Fill(vy);
		  vbz->Fill(vz);
		  vbe->Fill(ve);
		  vbmass->Fill(vmass);
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
	  vbosons = ctr+dtr;
	  k.Fill();
	}
    } // <-- end i loop
  z->Close();
  fout->Write();
}

#endif
