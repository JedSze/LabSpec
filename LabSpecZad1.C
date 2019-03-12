double yDist(double *x,double *par){
	return par[0]; //rozklad jednostajny
	}

double pTDist (double *x, double *par){
	//return par[0]; // rozklad jednostajny
	return par[0]*exp(x[0]); // rozklad wykladniczy
}

void LabSpecZad1(){
	double mass; //[GeV/c^2]
	//mass = 0.00051; //elektron
	//mass = 0.13957; //pion+
	mass = 1.115; //lambda

    TCanvas *c1 = new TCanvas("okno","",600,600);
	c1->Divide(2,1);

	TF1 *y = new TF1("y",yDist,-5,5,1); //bo jest stale
	y -> SetParameter(0,1); //tmp
	double normY = 1/(y -> Integral(-5,5));
	y -> SetParameter(0,normY);
	//cout<<"y norm: "<<normY<<endl;


	TF1 *pT = new TF1("pT",pTDist,0,5,1); //in GeV/c
	pT -> SetParameter(0,1); //tmp
	double normPT = 1/(pT -> Integral(0,5));
	pT -> SetParameter(0,normPT);

	TH1D *HistRandRapidity = new TH1D("HistRandRapidity","Histogram of rand rapidity",50,0,5);

	TH1D *HistPseudoRapid = new TH1D("HistPseudoRapid","Histogram of pseudo-rapidity",50,0,5);

	TH1D *HistMT = new TH1D("HistMT","Histogtam of transverse mass",25,0,5);

	double randPT, randY, mT, pZ, theta, pseudoRapidity; // potem zmienic

	for(int i = 0;i<100;i++){

		randPT = pT->GetRandom(); // losujemy pT z jednorodnego
		//cout<<randPT<<endl;
		mT = sqrt(mass*mass+randPT*randPT); // liczymy mT
		HistMT->Fill(mT);

		//cout<<"mT: "<<mT<<endl;
		randY = y -> GetRandom();
		HistRandRapidity->Fill(randY);
		//cout<<"y: "<<randY<<endl;
		pZ= mT*TMath::SinH(randY);
		//cout<<"pZ: "<<pZ<<endl;
		theta = TMath::ATan(randPT/pZ);
		pseudoRapidity = -TMath::Log(TMath::Tan(theta/2));
		//cout<<pseudoRapidity<<endl;
		HistPseudoRapid->Fill(pseudoRapidity);
	}

    c1->cd(1);
	HistRandRapidity->Draw();
	c1->cd(2);
	HistPseudoRapid->Draw();
	//c1->cd(3);
	//HistMT->Draw();
}