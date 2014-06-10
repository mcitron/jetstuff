void plotFit(){

   std::vector<TString> jettype;
   jettype.push_back("p0eta_-28to-14");
   jettype.push_back("p0eta_-14to0");
   jettype.push_back("p0eta_0to14");
   jettype.push_back("p0eta_14to28");

   jettype.push_back("p1eta_-28to-14");
   jettype.push_back("p1eta_-14to0");
   jettype.push_back("p1eta_0to14");
   jettype.push_back("p1eta_14to28");
   std::vector<TString> iscalib;
   iscalib.push_back("_calib");
   iscalib.push_back("");

   TFile* f = TFile::Open("alljet_fitplots.root");

   for(auto iType = jettype.begin(); iType != jettype.end(); iType++){
   for(auto iIscalib = iscalib.begin(); iIscalib != iscalib.end(); iIscalib++){

         TGraphAsymmErrors* nopus = f->Get("5400"+*iIscalib+"_nopus/"+*iType);
         TGraphAsymmErrors* nopusseed = f->Get("5450"+*iIscalib+"_nopus/"+*iType);
         TGraphAsymmErrors* donut = f->Get("5450"+*iIscalib+"_donut/"+*iType);
         TGraphAsymmErrors* global = f->Get("5400"+*iIscalib+"_global/"+*iType);
         //TGraphAsymmErrors* gct = f->Get("gct/"+*iJet+*iPt);
	 TMultiGraph * hs = new TMultiGraph("hs",*iType);
         TLegend* leg = new TLegend(0.7,0.2,1.0,0.5);
         leg->SetFillColor(0);
         leg->AddEntry(nopus,"No PUS","lep");
         leg->AddEntry(nopusseed,"No PUS Seed","lep");
         leg->AddEntry(donut,"Donut Sub","lep");
         leg->AddEntry(global,"Global Sub","lep");

         TCanvas * c = new TCanvas("c","",600,600);

         c->cd();

         nopus->SetLineColor(1);
         //nopus->Draw("alp");
         nopusseed->SetLineColor(3);
         //nopusseed->Draw("alp");
	 donut->SetLineColor(2);
	 //donut->Draw("lp same");
	 global->SetLineColor(4);
	 /////global->Draw("lp same");
	 hs->Add(nopus,"lp");
	 hs->Add(nopusseed,"lp");
	 hs->Add(donut,"lp");
	 hs->Add(global,"lp");
	 //gct->SetLineColor(8);
	 //if(*iJet!="alljet") gct->Draw("lp same");
	 hs->Draw("a");
	 //leg->Draw();

	 c->SaveAs("output/"+*iType+*iIscalib+"_fits.png");

   }
}
}
