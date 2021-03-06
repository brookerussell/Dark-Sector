#ifndef LEPTOPHOBICMC_CXX
#define LEPTOPHOBICMC_CXX

#include "LeptophobicMC.h"

void LeptophobicMC::Run()
{
  TFile *a = new TFile("PiNtuple.root");
  TTree *np = (TTree*)a->Get("np");
  const int kMaxParticles = 10000;
  Int_t npiplus,npiminus,npizero;
  Float_t plus_mom[kMaxParticles],minus_mom[kMaxParticles],neutral_mom[kMaxParticles];
  np->SetBranchAddress("npiplus",&npiplus);
  np->SetBranchAddress("npiminus",&npiminus);
  np->SetBranchAddress("plus_mom",&plus_mom);
  np->SetBranchAddress("minus_mom",&minus_mom);
  np->SetBranchAddress("npizero",&npizero);
  np->SetBranchAddress("neutral_mom",&neutral_mom);
  TFile* fout = TFile::Open("Arlington.root","RECREATE");
  TTree b("b","");
  int plus,minus,neutral;
  float px,py,pz,p,pt,mx,my,mz,m,mt,nx,ny,nz,n;
  b.Branch("plus",&plus,"plus/I");
  b.Branch("px",&px,"px/F");
  b.Branch("py",&py,"py/F");
  b.Branch("pz",&pz,"pz/F");
  b.Branch("p",&p,"p/F");
  b.Branch("minus",&minus,"minus/I");
  b.Branch("mx",&mx,"mx/F");
  b.Branch("my",&my,"my/F");
  b.Branch("mz",&mz,"mz/F");
  b.Branch("m",&m,"m/F");
  b.Branch("neutral",&neutral,"neutral/I");
  b.Branch("nx",&nx,"nx/F");
  b.Branch("ny",&ny,"ny/F");
  b.Branch("nz",&nz,"nz/F");
  b.Branch("n",&n,"n/F");
  TH1F *piplus = new TH1F("piplus","",100,0,10);
  TH1F *piminus = new TH1F("piminus","",100,0,10);
  TH1F *pineutral = new TH1F("pineutral","",100,0,10);  
  int ctr = 0;
  int dtr = 0;
  int etr = 0;
  Int_t entries = (Int_t)np->GetEntries();
  for(Int_t c=0; c<entries; c++)
    //for(Int_t c=0; c<1000; c++)
  {
      np->GetEntry(c);
      for(Int_t d=0; d<npiplus; d++)
	{
	  px = plus_mom[0];
	  py = plus_mom[1];
	  pz = plus_mom[2];
	  p = sqrt(plus_mom[0]*plus_mom[0]
		   +plus_mom[1]*plus_mom[1]
		   +plus_mom[2]*plus_mom[2]);
	  piplus->Fill(p);
	  ctr++;
	}
      for(Int_t e=0; e<npiminus; e++)
	{
	  mx = minus_mom[0];
	  my = minus_mom[1];
	  mz = minus_mom[2];
	  m = sqrt(minus_mom[0]*minus_mom[0]
		   +minus_mom[1]*minus_mom[1]
		   +minus_mom[2]*minus_mom[2]);
	  piminus->Fill(m);
	  dtr++;
	}
      for(Int_t g=0; g<npizero; g++)
	{
	  nx = neutral_mom[0];
	  ny = neutral_mom[1];
	  nz = neutral_mom[2];
	  n = sqrt(neutral_mom[0]*neutral_mom[0]
		   +neutral_mom[1]*neutral_mom[1]
		   +neutral_mom[2]*neutral_mom[2]);
	  pineutral->Fill(n);
	  etr++;
	}
      if(ctr>0)
	{
	  plus = ctr;
	  minus = dtr;
	  neutral = etr;
	  b.Fill();
	}
    }
  a->Close();
  fout->Write();
}

#endif
