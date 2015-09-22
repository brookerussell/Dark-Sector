#ifndef VB_CXX
#define VB_CXX

#include "VB.h"

void VB::PseudoscalarMeson()
{
  TFile* z = new TFile("Woburn.root");
  TTree *l = (TTree*)z->Get("l");
  int mesons;
  float mid,mx,my,mz,me,mnew,mass;
  l->SetBranchAddress("mesons",&mesons);
  l->SetBranchAddress("mid",&mid);
  l->SetBranchAddress("mx",&mx);
  l->SetBranchAddress("my",&my);
  l->SetBranchAddress("mz",&mz);
  l->SetBranchAddress("me",&me);
  l->SetBranchAddress("mnew",&mnew);
  l->SetBranchAddress("mass",&mass);

  TFile* fout = TFile::Open("Stoneham.root","RECREATE");
  TTree k("k","");
  int vbosons,mesonMotherID;
  double  vx,vy,vz,ve,vxlf,vylf,vzlf,velf,vxrf,vyrf,vzrf,verf,v,vl,vr,vmass,omass, px,py,pz,pe,p;
  k.Branch("vbosons",&vbosons,"vbosons/I");
  k.Branch("mesonMotherID",&mesonMotherID,"mesonMotherID/I");
  k.Branch("vx",&vx,"vx/D"); // lab frame vectorboson momentum
  k.Branch("vy",&vy,"vy/D");
  k.Branch("vz",&vz,"vz/D");
  k.Branch("ve",&ve,"ve/D"); // lab frame vectorboson energy
  k.Branch("v",&v,"v/D"); // lab frame vectorboson 3-momentum
  k.Branch("vmass",&vmass,"vmass/D"); // vectorboson mass
  k.Branch("vxlf",&vxlf,"vxlf/D"); // lab frame initial meson momentum 
  k.Branch("vylf",&vylf,"vylf/D");
  k.Branch("vzlf",&vzlf,"vzlf/D");
  k.Branch("velf",&velf,"velf/D"); // lab frame initial meson energy
  k.Branch("vxrf",&vxrf,"vxrf/D"); // rest frame initial meson momentum 
  k.Branch("vyrf",&vyrf,"vyrf/D");
  k.Branch("vzrf",&vzrf,"vzrf/D");
  k.Branch("verf",&verf,"verf/D"); // rest frame initial meson energy
  k.Branch("vl",&vl,"vl/D"); // lab frame meson 3-momentum
  k.Branch("vr",&vr,"vr/D"); // rest frame meson 3-momentum
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
  TH1F *vrf = new TH1F("vrf","Meson Invariant Mass (Rest Frame)",1100,0,1.1);
  TH1F *vlf = new TH1F("vlf","Meson Invariant Mass (Lab Frame)",1100,0,1.1);
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
  TLorentzVector com, zero_m;
  Int_t mentries = (Int_t)l->GetEntries();
  for(Int_t i=0; i<mentries; i++)
  //  for(Int_t i=0; i<10000; i++)
  {
      l->GetEntry(i);
      vxlf = mx; // meson lab frame momentum components 
      vylf = my;
      vzlf = mz;
      //std::cout << "E= "<< me << " PX= "<< mx << " PY= " << my << " PZ = " << mz << std::endl; 
      velf = me; // meson energy lab frame
      vl = sqrt(mx*mx+my*my+mz*mz); // meson lab frame 3-momentum
      TLorentzVector meson_lf;
      meson_lf.SetPxPyPzE(mx,my,mz,me);
      //float vlfinv = meson_lf.M(); //meson lab frame invariant mass
      float vlfinv = meson_lf.Mag();
      vlf->Fill(vlfinv);
      std::cout << "LF = " << vlf << std::endl;
      zero_m.SetPxPyPzE(0,0,0,0);
      com = meson_lf + zero_m;
      // boost meson to its rest frame
      meson_lf.Boost(-com.BoostVector());
      //meson_lf.Boost(-meson_lf.Px()/meson_lf.E(),
      //	     -meson_lf.Py()/meson_lf.E(),
      //	     -meson_lf.Px()/meson_lf.E());
      TLorentzVector meson_rf;
      meson_rf.SetPxPyPzE(meson_lf[0],
			  meson_lf[1],
			  meson_lf[2],
			  meson_lf[3]);
      //vxrf = meson_lf.Px(); // meson rest fram momentum components
      //vyrf = meson_lf.Py();
      //vzrf = meson_lf.Pz();
      vxrf = meson_rf[0];
      vyrf = meson_rf[1];
      vzrf = meson_rf[2];
      verf = meson_rf[3];
      //std::cout<<"Rest frame IV:" << vxrf << vyrf << vzrf << std::endl;
      //verf = meson_lf.E(); // meson energy rest frame
      vr = sqrt(meson_lf.Px()*meson_lf.Px()
		+meson_lf.Py()*meson_lf.Py()
		+meson_lf.Pz()*meson_lf.Pz()); //
      float vrfinv = meson_rf.Mag(); // meson rest frame invariant mass
      vrf->Fill(std::abs(vrfinv));
      std::cout<< "RF = " << vrf << std::endl;
      if (vlf == vrf) {std::cout<<"lab frame: "<< vlf<<" rest frame: "<< vrf<<std::endl;}
      if (mid == 1 || mid == 4)
	{
	  TLorentzVector meson_rf;
	  meson_rf.SetPxPyPzE(vxrf,vyrf,vzrf,verf);
	  TGenPhaseSpace event_k;
	  for(float m = 0.140; m<0.630; m+=0.010) // vector boson masses
	    {
	      double masses[2] = {m,0.0};
	      if(mass > m)
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
		  VectorBoson_rf.Boost(VectorBoson_rf.BoostVector());
		  PhotonInitial_rf.Boost(PhotonInitial_rf.BoostVector());
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
		  voblf->Fill(std::abs(vm));
		  float pm = PhotonInitial_lf.Mag(); //lab frame
		  plf->Fill(std::abs(pm));
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
		  omass = mass;
		  mesonMotherID = mid;
		  mesonid->Fill(mid);
		  vbx->Fill(vx);
		  vby->Fill(vy);
		  vbz->Fill(vz);
		  vbe->Fill(ve);
		  phx->Fill(px);
		  phy->Fill(py);
		  phz->Fill(pz);
		  phe->Fill(pe);
		  vbmass->Fill(vmass); // vectorboson mass
		  oldmass->Fill(mass); // original mass
		  ctr++;
		  // Clear all 4-momenta, otherwise a sefault will result
		  meson_lf.Clear();
		  meson_rf.Clear();
		  VectorBoson_rf.Clear();
		  PhotonInitial_rf.Clear();
		  VectorBoson_lf.Clear();
		  PhotonInitial_lf.Clear();
		} // <-- end if
	    } // <-- end m for loop
	} // <-- end eta/eta' if
      if(mid == 2 || mid == 3 || mid == 5)
	{
	  vx = mx;
	  vy = my;
	  vz = mz;
	  ve = me;
	  vbx->Fill(vx);
	  vby->Fill(vy);
	  vbz->Fill(vz);
	  vbe->Fill(ve);
	  v = sqrt(vx*vx+vy*vy+vz*vz);
	  vmass = omass;
	  vbmass->Fill(vmass);
	  omass = mass;
	  oldmass->Fill(mass);
	  mesonMotherID = mid;
	  mesonid->Fill(mid);
	  dtr++;
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
