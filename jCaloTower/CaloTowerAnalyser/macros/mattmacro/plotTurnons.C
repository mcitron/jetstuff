void plotTurnons(){

   std::vector<TString> jettype;
   jettype.push_back("5400_calib");
   //jettype.push_back("5450");
   std::vector<TString> ptcut;
   ptcut.push_back("pt20");
   ptcut.push_back("pt40");
   ptcut.push_back("pt60");
   ptcut.push_back("pt80");
   std::vector<TString> jetnum;
   jetnum.push_back("alljet");
   jetnum.push_back("jet1");
   jetnum.push_back("jet2");
   jetnum.push_back("jet3");
   jetnum.push_back("jet4");

   TFile* f = TFile::Open("matchingEffcut.root");

   for(auto iType = jettype.begin(); iType != jettype.end(); iType++){
     for(auto iJet = jetnum.begin(); iJet!=jetnum.end();iJet++){
       for(auto iPt = ptcut.begin(); iPt!=ptcut.end();iPt++){

         TGraphAsymmErrors* nopus = f->Get(*iType+"_nopus/"+*iJet+*iPt);
         TGraphAsymmErrors* donut = f->Get(*iType+"_donut/"+*iJet+*iPt);
         TGraphAsymmErrors* global = f->Get(*iType+"_global/"+*iJet+*iPt);
         //TGraphAsymmErrors* gct = f->Get("gct/"+*iJet+*iPt);

         TLegend* leg = new TLegend(0.7,0.2,1.0,0.5);
         leg->SetFillColor(0);
         leg->AddEntry(nopus,"No PUS","lep");
         leg->AddEntry(donut,"Donut Sub","lep");
         leg->AddEntry(global,"Global Sub","lep");
         //if(*iJet!="alljet") leg->AddEntry(gct,"GCT","lep");

         TCanvas * c = new TCanvas("c","",600,600);

         c->cd();

         nopus->SetLineColor(1);
         nopus->Draw("alp");
         donut->SetLineColor(2);
         donut->Draw("lp same");
         global->SetLineColor(4);
         global->Draw("lp same");
         //gct->SetLineColor(8);
         //if(*iJet!="alljet") gct->Draw("lp same");

         leg->Draw();

         c->SaveAs("output/turnons_"+*iType+"_"+*iJet+"_"+*iPt+".png");

       }
     }
   }
}
