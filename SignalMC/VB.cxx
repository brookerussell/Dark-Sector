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
  float vx,vy,vz,ve,vmass,px,py,pz,pe,omass;
  k.Branch("vbosons",&vbosons,"vbosons/I");
  k.Branch("vx",&vx,"vx/F");
  k.Branch("vy",&vy,"vy/F");
  k.Branch("vz",&vz,"vz/F");
  k.Branch("ve",&ve,"ve/F");
  k.Branch("vmass",&vmass,"vmass/F");
  k.Branch("px",&px,"px/F");
  k.Branch("py",&py,"py/F");
  k.Branch("pz",&pz,"pz/F");
  k.Branch("pe",&pe,"pe/F");
  k.Branch("omass",&omass,"omass/F");
  //z->cd();
  TH1F *vbx = new TH1F("vbx","",400,-200,200);
  TH1F *vby = new TH1F("vby","",400,-2,2);
  TH1F *vbz = new TH1F("vbz","",400,-2,2);
  TH1F *vbmass = new TH1F("vbmass","",1100,0,1.1);
  TH1F *phx = new TH1F("phx","",400,-2,2);
  TH1F *phy = new TH1F("phy","",400,-2,2);
  TH1F *phz = new TH1F("phz","",400,-2,2);
  TH1F *oldmass = new TH1F("oldmass","",1100,0,1.1);
  TH1F *vrf = new TH1F("vrf","",200,-1000,1000);
  TH1F *vlf = new TH1F("vlf","",1100,0,1.1);
  TH1F *prf = new TH1F("prf","",200,-1000,1000);
  TH1F *plf = new TH1F("plf","",200,-1000,1000);
  int ctr = 0;
  Int_t mentries = (Int_t)l->GetEntries();
  //  for(Int_t i=0; i<mentries; i++)
  for(Int_t i=0; i<1000; i++)
  {
      l->GetEntry(i);
      for(Int_t j=0; j<mesons; j++)
	//for(Int_t j=0; j<100; j++)
      //if(mass < 0.6 || mass == 0.95778)
	//{
	  TLorentzVector meson_lf;
	  meson_lf.SetPxPyPzE(mx,my,mz,me);
	  TLorentzVector zero_m;
	  zero_m.SetPxPyPzE(0,0,0,0);
	  TLorentzVector com;
	  //	  com = meson_lf + zero_m;
	  //meson_lf.Boost(-com.BoostVector());
	  vx = meson_lf[0];
	  vy = meson_lf[1];
	  vz = meson_lf[2];
	  ve = meson_lf[3];
	  //meson_lf.Boost(-meson_lf.BoostVector());
	  //TLorentzVector meson_rf;
	  //meson_rf.SetPxPyPzE(meson_lf[0],
	  //		      meson_lf[1],
	  //		      meson_lf[2],
	  //		      meson_lf[3]);
	  // TESTING THE BOOST -- REMOVE THIS LATER
	  //meson_rf.Boost(com.BoostVector());
	  //px = meson_rf[0];
	  //py = meson_rf[1];
	  //pz = meson_rf[2];
	  //pe = meson_rf[3];
	  /*	  TGenPhaseSpace event_k;
	  for(float m = 0.140; m<0.630; m+=0.010)
	    {
	  double masses[2] = {m,0.0};
	  if(mass > m)
	    {
	  event_k.SetDecay(meson_lf,2,masses);
	  event_k.Generate();
	  TLorentzVector *vectorBoson = event_k.GetDecay(0);
	  TLorentzVector *photonInitial = event_k.GetDecay(1);
	  TLorentzVector VectorBoson_rf = *vectorBoson;
	  TLorentzVector PhotonInitial_rf = *photonInitial;
	  float vb_rfinv = VectorBoson_rf.Mag2();
	  vrf->Fill(vb_rfinv);
	  float ph_rfinv = PhotonInitial_rf.Mag2();
	  prf->Fill(ph_rfinv);
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
			    PhotonInitial_rf[3]); */
	  /* test to follow */
	  //VectorBoson_lf.Boost(VectorBoson_lf.BoostVector());
	  //PhotonInitial_lf.Boost(PhotonInitial_lf.BoostVector());	  
	  /*float vb_lfinv = VectorBoson_lf.Mag();
	  vlf->Fill(vb_lfinv);
	  float ph_lfinv = PhotonInitial_lf.Mag();
	  plf->Fill(ph_lfinv);
	  vx = VectorBoson_lf[0];
	  vy = VectorBoson_lf[1];
	  vz = VectorBoson_lf[2];
	  ve = VectorBoson_lf[3];
	  vmass = m;
	  px = PhotonInitial_lf[0];
	  py = PhotonInitial_lf[1];
	  pz = PhotonInitial_lf[2];
	  pe = PhotonInitial_lf[3];
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
	  /*zero_m.Clear();
	  com.Clear();
	  meson_rf.Clear();
	  VectorBoson_rf.Clear();
	  PhotonInitial_rf.Clear();
	  VectorBoson_lf.Clear();
	  PhotonInitial_lf.Clear(); */
	  //} // <-- end if
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
  //fout->Append(vrf); fout->Append(prf); fout->Append(vlf); fout->Append(plf);
  z->Close();
  fout->Write();
  //fout->Close();
}

#endif
