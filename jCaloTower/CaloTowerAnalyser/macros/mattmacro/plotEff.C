void plotEff(){

   std::vector<TString> jettype;
   jettype.push_back("5400");
//   jettype.push_back("5450");
   std::vector<TString> jetnum;
   jetnum.push_back("algo1");
   jetnum.push_back("algo2");

   TFile* f = TFile::Open("ttbar_match.root");

   for(auto iType = jettype.begin(); iType != jettype.end(); iType++){
     for(auto iJet = jetnum.begin(); iJet!=jetnum.end();iJet++){
       TGraphAsymmErrors* nopus = f->Get(*iType+"_nopus/jet1_"+*iJet);
       TGraphAsymmErrors* donut = f->Get(*iType+"_donut/jet1_"+*iJet);
       TGraphAsymmErrors* global = f->Get(*iType+"_global/jet1_"+*iJet);
       TGraphAsymmErrors* gct = f->Get("gct/jet1_"+*iJet);

       TLegend* leg = new TLegend(0.2,0.2,0.48,0.5);
       leg->SetFillColor(0);
       leg->AddEntry(nopus,"No PUS","lep");
       leg->AddEntry(donut,"Donut Sub","lep");
       leg->AddEntry(global,"Global Sub","lep");
       leg->AddEntry(gct,"GCT","lep");

       TCanvas * c = new TCanvas("c","",600,600);

       c->cd();

       nopus->SetLineColor(1);
       nopus->Draw("alp");

       donut->SetLineColor(2);
       donut->Draw("lp same");

       global->SetLineColor(4);
       global->Draw("lp same");
       gct->SetLineColor(8);
       gct->Draw("lp same");

       leg->Draw();


       c->SaveAs("output/matching_efficiency_jet1_"+*iType+"_"+*iJet+".png");
     }
   }
}
