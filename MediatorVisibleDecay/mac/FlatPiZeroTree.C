{
  gROOT->Reset();

  TFile* f = new TFile("PiNtuple.root");
  TTree *np = (TTree*)f->Get("np");

  const int kMaxParticles = 10000;
  Int_t npizero;
  Float_t neutral_mom[kMaxParticles];

  // Grabbing the branches from TFile f for the Pi0                             
  np->SetBranchAddress("npizero",&npizero); // Number of Pi0's in ntuple
  np->SetBranchAddress("neutral_mom",&neutral_mom);// Pi0 3-momentum

  TFile* fout = TFile::Open("Pizero_input.root","RECREATE");
  TTree pz("pz","");

  Int_t nevent,numberpizeros;
  Double_t pizeroPx,pizeroPy,pizeroPz,pizeroE;

  pz.Branch("nevent",&nevent,"nevent/I"); // Event number
  pz.Branch("numberpizeros",&numberpizeros,"numberpizeros/I"); // Pizero unique number
  pz.Branch("pizeroPx",&pizeroPx,"pizeroPx/D"); // Pi0 Px
  pz.Branch("pizeroPy",&pizeroPy,"pizeroPy/D"); // Pi0 Py
  pz.Branch("pizeroPz",&pizeroPz,"pizeroPz/D"); // Pi0 Pz
  pz.Branch("pizeroE",&pizeroE,"pizeroE/D"); // Pi0 E

  int ctr = 0; // Instantiate counter for unique Pi0

  Int_t entries = (Int_t)np->GetEntries();
  for(Int_t i=0; i<entries; i++)
    {
      np->GetEntry(i);

      nevent = i; // Catalogue each individual POT

      for(Int_t j=0; j<npizero; j++)
	{
	  ctr++;
	  numberpizeros = ctr; // Catalogue each individual POT
	  pizeroPx = neutral_mom[0]; // Pi0 Px
	  pizeroPy = neutral_mom[1]; // Pi0 Py
	  pizeroPz = neutral_mom[2]; // Pi0 Pz
	  
	  // Inferred Pi0 energy
	  pizeroE = sqrt(0.13497*0.13497+
			 neutral_mom[0]*neutral_mom[0]+
			 neutral_mom[1]*neutral_mom[1]+
			 neutral_mom[2]*neutral_mom[2]);
	  
	  pz.Fill(); // Fill tree
	} // <-- end j loop
    } // <-- end i loop
  f->Close();
  fout->Write();
}
