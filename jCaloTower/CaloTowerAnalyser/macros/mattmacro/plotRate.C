void plotRate(){

   std::vector<TString> jettype;
   jettype.push_back("5400");
//   jettype.push_back("5450");
   std::vector<TString> jetnum;
   jetnum.push_back("algo1");
   //jetnum.push_back("algo2");

   TFile* f = TFile::Open("ratePlots.root");

   for(auto iType = jettype.begin(); iType != jettype.end(); iType++){
      //  for(auto iJet = jetnum.begin(); iJet!=jetnum.end();iJet++){
      TH1D* nopus = f->Get(*iType+"_nopus/5400_nopusjet1");
      TH1D* donut = f->Get(*iType+"_donut/5400_donutjet1");
      TH1D* global = f->Get(*iType+"_global/5400_globaljet1");
      TH1D* gct = f->Get("gct/gctjet1");

      TLegend* leg = new TLegend(0.2,0.2,0.48,0.5);
      leg->SetFillColor(0);
      leg->AddEntry(nopus,"No PUS","lep");
      leg->AddEntry(donut,"Donut Sub","lep");
      leg->AddEntry(global,"Global Sub","lep");
      leg->AddEntry(gct,"GCT","lep");

      TCanvas * c = new TCanvas("c","",600,600);

      c->cd();

      nopus->SetLineColor(1);
      nopus->Draw();

      donut->SetLineColor(2);
      donut->Draw("same");

      global->SetLineColor(4);
      global->Draw("same");
      gct->SetLineColor(8);
      gct->Draw("same");


      leg->Draw();

      c->SaveAs("output/rate_"+*iType+"_jet1_thesh20.png");
      //}
   }
}
