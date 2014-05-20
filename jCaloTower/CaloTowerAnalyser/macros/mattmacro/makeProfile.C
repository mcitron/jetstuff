void makeProfile()
{
TFile * f = TFile::Open("./global_PUS.root");
TH2D * allhistDonut =  (f->Get("demo/donut_gen/pt_ratio_nvts_algo1"));
TH2D * allhistGlobal =  (f->Get("demo/global_gen/pt_ratio_nvts_algo1"));
TH2D * allhistNopus =  (f->Get("demo/nopus_gen/pt_ratio_nvts_algo1"));
allhistDonut->Sumw2();
TProfile *px = allhistGlobal->ProfileX("px", 0, -1); // where firstYbin = 0 and lastYbin = 9
TProfile *py = allhistDonut->ProfileX("py", 0, -1); // where firstYbin = 0 and lastYbin = 9
TProfile *pz = allhistNopus->ProfileX("pz", 0, -1); // where firstYbin = 0 and lastYbin = 9
//px->Draw();
//px->SetLineColor(1);
py->Draw("same");
py->SetLineColor(2);
pz->Draw("same");
pz->SetLineColor(3);
}

