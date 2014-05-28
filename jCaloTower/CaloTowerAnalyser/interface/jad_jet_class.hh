#ifndef __JAD_JET_STRUCT__
#define __JAD_JET_STRUCT__

#include "SLHCUpgradeSimulations/L1CaloTrigger/interface/TriggerTowerGeometry_new.h"

//struct jJet{
//  double pt;
//  int ieta;
//  int iphi;
//  jJet(double mpt, int mieta, int miphi) : pt(mpt), ieta(mieta), iphi(miphi) {}
//};

class jJet {

public:
  jJet(double pt, int ieta, int iphi);
  jJet(double pt, int ieta, int iphi,int bx);
  jJet(double pt, int ieta, int iphi, std::vector<int> ringsums, std::vector<int> ringareas, std::vector<std::pair<int,int> > outerstrips, int jetarea);
  jJet(double pt, int ieta, int iphi, std::vector<int> ringsums, std::vector<int> ringareas, std::vector<std::pair<int,int> > outerstrips,std::vector<int> towers, int jetarea);
  int iEta() const;
  int iPhi() const;
  int gEta() const;
  int gPhi() const;
  double pt() const;
  void setPt(double pt);
  bool isolatedJet(const std::vector<jJet>& jetCollection, double dR2Max);
  std::vector<int> ringSums() const;
  std::vector<int> ringAreas() const;
  std::vector<std::pair<int,int> > getOuterStrips() const;
  std::vector<int> getTowers() const;
  int DeltaR2(const jJet & jet2) const;
  int PUE();
  double eatDonut(); //the energy after PUsubtraction
  double eatGlobe(double median); //the energy after global PUsubtraction
  int area() const;
  int getOuterSum() const;
private:
  double mpt;
  int mieta;
  int miphi;
  int mgeta;
  int mgphi;
  int mbx;
  std::vector<int> mringsums;
  std::vector<int> mringareas;
  std::vector<std::pair<int,int>> mouterstrips;
  std::vector<int> mtowers;
  int marea;
};

jJet::jJet(double pt, int ieta, int iphi) : mpt(pt), mieta(ieta), miphi(iphi) {}
jJet::jJet(double pt, int geta, int gphi,int bx) : mpt(pt), mgeta(geta), mgphi(gphi),mbx(bx) {}
jJet::jJet(double pt, int ieta, int iphi, std::vector<int> ringsums, std::vector<int> ringareas, std::vector<std::pair<int,int> > outerstrips, int jetarea) : mpt(pt), mieta(ieta), miphi(iphi), mringsums(ringsums), mringareas(ringareas), mouterstrips(outerstrips),marea(jetarea) {
   std::sort(mouterstrips.begin(), mouterstrips.end());
}
jJet::jJet(double pt, int ieta, int iphi, std::vector<int> ringsums, std::vector<int> ringareas, std::vector<std::pair<int,int> > outerstrips, std::vector<int> towers, int jetarea) : mpt(pt), mieta(ieta), miphi(iphi), mringsums(ringsums), mringareas(ringareas), mouterstrips(outerstrips),mtowers(towers),marea(jetarea) {
   std::sort(mouterstrips.begin(), mouterstrips.end());
   std::sort(mtowers.begin(), mtowers.end());
}

int jJet::iEta() const { return mieta; }
int jJet::iPhi() const { return miphi; }
int jJet::gEta() const { return mgeta; }
int jJet::gPhi() const { return mgphi; }
double jJet::pt() const { return mpt; }
std::vector<int> jJet::ringSums() const { return mringsums; }
std::vector<int> jJet::ringAreas() const { return mringareas; }
std::vector<std::pair<int,int> > jJet::getOuterStrips() const { return mouterstrips; }
std::vector<int> jJet::getTowers() const { return mtowers; }

int jJet::getOuterSum() const 
{ 
   int outerRing = 0;
   for (auto ring = mouterstrips.begin(); ring != mouterstrips.end(); ring++) outerRing+=ring->first;
   return outerRing;
}
int jJet::PUE() { return (mouterstrips[1].first + mouterstrips[2].first); } //i.e. sum up the middle two energies

void jJet::setPt(double pt) 
{
   mpt=pt;
}
double jJet::eatDonut() {
   //double lastringsum = this->ringSums().at(this->ringSums().size() - 1);
   double scaleDonut = (double)marea/(double)(mouterstrips[1].second + mouterstrips[2].second);
   double donutenergy = this->PUE() * scaleDonut; //3.5 = 7x7 / 2x7
   return (this->pt() - donutenergy);
}
double jJet::eatGlobe(double median) {
   return (this->pt() - median*this->area());
}
bool jJet::isolatedJet(const std::vector<jJet>& jetCollection, double dR2Max){
   int closeJets=0;
   for(std::vector<jJet>::const_iterator jetIt = jetCollection.begin();
	 jetIt!=jetCollection.end(); jetIt++){
      if(this->DeltaR2(*jetIt)<dR2Max) closeJets++;//Check it's not witin 7x7
   }
   if(closeJets>1) return false;
   else return true;
}

int jJet::DeltaR2(const jJet & jet2) const {

   TriggerTowerGeometry g;

   int newEtaIndex1 = g.new_iEta(this->iEta());
   int newEtaIndex2 = g.new_iEta(jet2.iEta());
   int newPhiIndex1 = g.new_iPhi(this->iPhi());
   int newPhiIndex2 = g.new_iPhi(jet2.iPhi());

   int deltaPhi = abs(newPhiIndex1 - newPhiIndex2);
   if( deltaPhi > 36) {
      deltaPhi = 72 - deltaPhi;
   }

   int deltaR2 = ((newEtaIndex1 - newEtaIndex2) * (newEtaIndex1 - newEtaIndex2)) + (deltaPhi * deltaPhi);

   return deltaR2;

}
int jJet::area() const
{
   return marea;
}
bool sortbypt(const jJet &a, const jJet &b) { return a.pt() > b.pt(); }

bool sortbyrho(const jJet &a, const jJet &b) { 
   return a.pt()/a.area() > b.pt()/b.area();
}

#endif
