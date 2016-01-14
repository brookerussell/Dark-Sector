#ifndef SANITYPLOTS_CXX
#define SANITYPLOTS_CXX

#include "SanityPlots.h"

void SanityPlots::Check()
{
  TFile* f0 = new TFile("NMP_output.root");
  TTree* nmp = (TTree*)f0->Get("nmp");

  // Instantiating variables to read the NeutralMesonProduction ntuple
  Int_t uniquePi0,Pi0Meson,nMesons;
  Float_t mesonID,mesonPx,mesonPy,mesonPz,mesonE,mesonPnew,mesonMass;
  nmp->SetBranchAddress("uniquePi0",&uniquePi0); // # to track Pi0 parent            
  nmp->SetBranchAddress("Pi0Meson",&Pi0Meson); // tracks meson from Pi0
  nmp->SetBranchAddress("nMesons",&nMesons); // # of newly created mesons     
  nmp->SetBranchAddress("mesonID",&mesonID); // Meson ID                      
  nmp->SetBranchAddress("mesonPx",&mesonPx); // Meson Px (GeV)                
  nmp->SetBranchAddress("mesonPy",&mesonPy); // Meson Py (GeV)                
  nmp->SetBranchAddress("mesonPz",&mesonPz); // Meson Pz (GeV)                
  nmp->SetBranchAddress("mesonE",&mesonE); // Meson energy (GeV)               
  nmp->SetBranchAddress("mesonPnew",&mesonPnew); // Meson 3-momentum        
  nmp->SetBranchAddress("mesonMass",&mesonMass); // Meson mass              

  TFile* f0out = TFile::Open("SanityPlots_output.root","RECREATE");
  TTree sp("sp","");

  TH2F *ie       = new TH2F("ie","Particle ID vs. Energy",5,1,6,1000,0,10);          
  TH2F *msen     = new TH2F("msen","Mass vs. Energy",600,0.5,1.1,800,0,8);         
  TH2F *momne    = new TH2F("momne","P_{new} vs. Energy",800,0,8,800,0,8);
  
  // 3-momentum vs. energy histos
  TH2F *etmome   = new TH2F("etamome","P_{eta} vs. Energy_{eta}",800,0,8,800,0,8);                                                                             
  TH2F *ommome   = new TH2F("ommome","P_{#omega} vs. Energy_{#omega}",800,0,8,800,0,8);                                                                        
  TH2F *rhomome  = new TH2F("rhomome","P_{#rho} vs. Energy_{#rho}",800,0,8,800,0,8);                                                                          
  TH2F *etpmome  = new TH2F("etpmome","P_{#eta'} vs. Energy_{#eta'}",800,0,8,800,0,8);                                                                        
  TH2F *phimome  = new TH2F("phimome","P_{#phi} vs. Energy_{#phi}",800,0,8,800,0,8);                                                                          
  
  // Px vs. Pz & Py vs. Pz histos
  TH2F *etpxpz   = new TH2F("etpxpz", "P_{x_{#eta}} vs. P_{z_{#eta}}",200,-1,1,800,0,8);                                                                       
  TH2F *etpypz   = new TH2F("etpypz", "P_{y_{#eta}} vs. P_{z_{#eta}}",200,-1,1,800,0,8); 
  TH2F *ompxpz   = new TH2F("ompxpz", "P_{x_{#omega}} vs. P_{z_{#omega}}",200,-1,1,800,0,8);                                                                   
  TH2F *ompypz   = new TH2F("ompypz", "P_{y_{#omega}} vs. P_{z_{#omega}}",200,-1,1,800,0,8);                                                                   
  TH2F *rhopxpz  = new TH2F("rhopxpz", "P_{x_{#rho}} vs. P_{z_{#rho}}",200,-1,1,800,0,8);                                                                     
  TH2F *rhopypz  = new TH2F("rhopypz", "P_{y_{#rho}} vs. P_{z_{#rho}}",200,-1,1,800,0,8);                                                                     
  TH2F *etappxpz = new TH2F("etappxpz", "P_{x_{#eta'}} vs. P_{z_{#eta'}}",200,-1,1,800,0,8);                                                                 
  TH2F *etappypz = new TH2F("etappypz", "P_{y_{#eta'}} vs. P_{y_{#eta'}}",200,-1,1,800,0,8);                                                                 
  TH2F *phipxpz  = new TH2F("phipxpz", "P_{x_{#phi}} vs. P_{z_{#phi}}", 200,-1,1,800,0,8);                                                                    
  TH2F *phipypz  = new TH2F("phipypz", "P_{y_{#phi}} vs. P_{z_{#phi}}", 200,-1,1,800,0,8);                                                                    
  
  // Invariant mass histos
  TH1F *inveta   = new TH1F("inveta","#eta Invariant Mass",1100,0,1.1);          
  TH1F *invetap  = new TH1F("invetap","#eta' Invariant Mass",1100,0,1.1);       
  TH1F *invrho   = new TH1F("invrho","#rho Invariant Mass",1100,0,1.1);          
  TH1F *invomega = new TH1F("invomega","#omega Invariant Mass",1100,0,1.1);    
  TH1F *invphi   = new TH1F("invphi","#phi Invariant Mass",1100,0,1.1);          
 
  Int_t f0entries = (Int_t)nmp->GetEntries();
  for(Int_t i=0; i<f0entries; i++)
    {
      nmp->GetEntry(i);

      // Eta Histograms 
      if(mesonID == 1)
	{ 
	  float tempInvMass = sqrt( (mesonE*mesonE) - (mesonPnew*mesonPnew) );
	  etmome->Fill(mesonPnew,mesonE);
	  etpxpz->Fill(mesonPx,mesonPz);
	  etpypz->Fill(mesonPy,mesonPz);
	  inveta->Fill(tempInvMass);
	}
      
      // Omega Histograms 
      if(mesonID == 2)
	{ 
	  float tempInvMass = sqrt( (mesonE*mesonE) - (mesonPnew*mesonPnew) );
	  invomega->Fill(tempInvMass);
	  ommome->Fill(mesonPnew,mesonE);
	  ompxpz->Fill(mesonPx,mesonPz);
	  ompypz->Fill(mesonPy,mesonPz);
	}
      
      // Rho Histograms 
      if(mesonID == 3)
	{
	  float tempInvMass = sqrt( (mesonE*mesonE) - (mesonPnew*mesonPnew) ); 
	  invrho->Fill(tempInvMass);
	  rhomome->Fill(mesonPnew,mesonE);
	  rhopxpz->Fill(mesonPx,mesonPz);
	  rhopypz->Fill(mesonPy,mesonPz);
	}
      
      // Eta prime Histograms 
      if(mesonID == 4)
	{ 
	  float tempInvMass = sqrt( (mesonE*mesonE) - (mesonPnew*mesonPnew) );
	  invetap->Fill(tempInvMass);
	  etpmome->Fill(mesonPnew,mesonE);
	  etappxpz->Fill(mesonPx,mesonPz);
	  etappypz->Fill(mesonPy,mesonPz);
	}
      
      // Phi histograms 
      if(mesonID == 5)
	{ 
	  float tempInvMass = sqrt( (mesonE*mesonE) - (mesonPnew*mesonPnew) );
	  invphi->Fill(tempInvMass);
	  phimome->Fill(mesonPnew,mesonE);
	  phipxpz->Fill(mesonPx,mesonPz);
	  phipypz->Fill(mesonPy,mesonPz);
	}
      
      // Constructed mesons histograms
      ie->Fill(mesonID,mesonE);
      msen->Fill(mesonMass,mesonE);
      momne->Fill(mesonPnew,mesonE);

      sp.Fill();
    } // end i loop

  f0->Close();
  f0out->Write();
} // <-- end void


#endif