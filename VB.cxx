#ifndef VB_CXX
#define VB_CXX

#include "VB.h"

void VB::PseudoscalarMeson()
{
  //TFile* z = new TFile("Woburn.root");
  TFile* z = new TFile("Woburn.root");
  TTree *l = (TTree*)z->Get("l");
  //const int kMaxParticles = 10000;
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
  int vbosons;
  double  vx,vy,vz,ve,vxlf,vylf,vzlf,velf,vlfinv,vxrf,vyrf,vzrf,verf,v,vl,vr,vinv,vrfinv,vmass,omass;
  double px,py,pz,pe, p,pinv,VRF,PRF;
  k.Branch("vbosons",&vbosons,"vbosons/I");
  k.Branch("vx",&vx,"vx/D");
  k.Branch("vy",&vy,"vy/D");
  k.Branch("vz",&vz,"vz/D");
  k.Branch("ve",&ve,"ve/D");
  k.Branch("v",&v,"v/D");
  k.Branch("vinv",&vinv,"vinv/D");
  k.Branch("vlfinv",&vlfinv,"vlfinv/D");
  k.Branch("vrfinv",&vrfinv,"vrfinv/D");
  k.Branch("vmass",&vmass,"vmass/F");
  k.Branch("vxlf",&vxlf,"vxlf/D");
  k.Branch("vylf",&vylf,"vylf/D");
  k.Branch("vzlf",&vzlf,"vzlf/D");
  k.Branch("velf",&velf,"velf/D");
  k.Branch("vxrf",&vxrf,"vxrf/D");
  k.Branch("vyrf",&vyrf,"vyrf/D");
  k.Branch("vzrf",&vzrf,"vzrf/D");
  k.Branch("verf",&verf,"verf/D");
  k.Branch("vl",&vl,"vl/D");
  k.Branch("vr",&vr,"vr/D");
  k.Branch("px",&px,"px/D");
  k.Branch("py",&py,"py/D");
  k.Branch("pz",&pz,"pz/D");
  k.Branch("pe",&pe,"pe/D");
  k.Branch("p",&p,"p/D");
  k.Branch("pinv",&pinv,"pinv/D");
  k.Branch("omass",&omass,"omass/F");
  k.Branch("VRF",&VRF,"VRF/D");
  k.Branch("PRF",&PRF,"PRF/D");
  //z->cd();
  TH1F *vbx = new TH1F("vbx","",400,-200,200);
  TH1F *vby = new TH1F("vby","",400,-2,2);
  TH1F *vbz = new TH1F("vbz","",400,-2,2);
  TH1F *vbmass = new TH1F("vbmass","",1100,0,1.1);
  TH1D *phx = new TH1D("phx","",400,-2,2);
  TH1F *phy = new TH1F("phy","",400,-2,2);
  TH1F *phz = new TH1F("phz","",400,-2,2);
  TH1D *phe = new TH1D("phe","",2000,-1000,1000);
  TH1F *oldmass = new TH1F("oldmass","",1100,0,1.1);
  TH1F *vrf = new TH1F("vrf","",200,-1000,1000);
  TH1F *vlf = new TH1F("vlf","",1100,0,1.1);
  TH1F *prf = new TH1F("prf","",200,-1000,1000);
  TH1F *plf = new TH1F("plf","",200,-1000,1000);
  int ctr = 0;
  Int_t mentries = (Int_t)l->GetEntries();
    for(Int_t i=0; i<mentries; i++)
  {
      l->GetEntry(i);
      vxlf = mx;
      vylf = my;
      vzlf = mz;
      velf = me;
      vl = sqrt(mx*mx+my*my+mz*mz);
      TLorentzVector meson_lf;
      meson_lf.SetPxPyPzE(mx,my,mz,me);
      vlfinv = meson_lf.Mag();
      vlf->Fill(vinv);
      meson_lf.Boost(-meson_lf.Px()/meson_lf.E(),
		     -meson_lf.Py()/meson_lf.E(),
		     -meson_lf.Px()/meson_lf.E());
      vxrf = meson_lf.Px();
      vyrf = meson_lf.Py();
      vzrf = meson_lf.Pz();
      verf = meson_lf.E();
      vr = sqrt(meson_lf[0]*meson_lf[0]
		+meson_lf[1]*meson_lf[1]
		+meson_lf[2]*meson_lf[2]);
      vrfinv = meson_lf.Mag();
      TLorentzVector meson_rf;
      meson_rf.SetPxPyPzE(vxrf,vyrf,vzrf,verf);
      TGenPhaseSpace event_k;
      for(float m = 0.140; m<0.630; m+=0.010)
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
	  float vb_rfinv = VectorBoson_rf.Mag2();
	  vrf->Fill(vb_rfinv);
	  float ph_rfinv = PhotonInitial_rf.Mag2();
	  prf->Fill(ph_rfinv);
	  //VectorBoson_rf.Boost(VectorBoson_rf.BoostVector());
	  //PhotonInitial_rf.Boost(PhotonInitial_rf.BoostVector());
	  //TLorentzVector VectorBoson_lf;
	  //VectorBoson_lf.SetPxPyPzE(VectorBoson_rf[0],
	  //		    VectorBoson_rf[1],
	  //		    VectorBoson_rf[2],
	  //		    VectorBoson_rf[3]);
	  //TLorentzVector PhotonInitial_lf;
	  //PhotonInitial_lf.SetPxPyPzE(PhotonInitial_rf[0],
	  //		    PhotonInitial_rf[1],
	  //		    PhotonInitial_rf[2],
	  //		    PhotonInitial_rf[3]);
	  /* test to follow */
	  //VectorBoson_lf.Boost(VectorBoson_lf.BoostVector());
	  //PhotonInitial_lf.Boost(PhotonInitial_lf.BoostVector());	  
	  float vb_lfinv = VectorBoson_rf.Mag();
	  VRF = vb_lfinv;
	  vlf->Fill(vb_lfinv);
	  float ph_lfinv = PhotonInitial_rf.Mag();
	  PRF = ph_lfinv;
	  plf->Fill(ph_lfinv);
	  //	  vx = VectorBoson_lf[0];
	  //vy = VectorBoson_lf[1];
	  //vz = VectorBoson_lf[2];
	  //ve = VectorBoson_lf[3];
	  vx = VectorBoson_rf.Px();
	  vy = VectorBoson_rf.Py();
	  vz = VectorBoson_rf.Pz();
	  ve = VectorBoson_rf.E();
	  vmass = m;
	  //px = PhotonInitial_lf[0];
	  //py = PhotonInitial_lf[1];
	  //pz = PhotonInitial_lf[2];
	  //pe = PhotonInitial_lf[3];
	  px = PhotonInitial_rf.Px();
	  py = PhotonInitial_rf.Py();
	  pz = PhotonInitial_rf.Pz();
	  pe = PhotonInitial_rf.E();
	  omass = mass;
	  vbx->Fill(vx);
	  vby->Fill(vy);
	  vbz->Fill(vz);
	  phx->Fill(px);
	  phy->Fill(py);
	  phz->Fill(pz);
	  vbmass->Fill(vmass);
	  oldmass->Fill(mass);
	  ctr++;
	  k.Fill();
	  meson_lf.Clear();
	  meson_rf.Clear();
	  VectorBoson_rf.Clear();
	  PhotonInitial_rf.Clear();
	  //VectorBoson_lf.Clear();
	  //PhotonInitial_lf.Clear();
	  } // <-- end if
	} // <-- end m for loop
	  //else
	  //{continue;}
      /*  if(ctr>0)
	{
	  vbosons = ctr;
	  k.Fill();
	  }*/
	  //	    } // <-- end if m > mass
  /*else
	    {continue;}
	    } // <-- end m loop */
    } // <-- end i loop
  //vrf->Draw(); prf->Draw(); vlf->Draw(); plf->Draw();
    //    fout->Append(phx); fout->Append(phe);// fout->Append(vlf); fout->Append(plf);
  z->Close();
  fout->Write();
  //fout->Close();
}

#endif
