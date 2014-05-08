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
  jJet(double pt, int ieta, int iphi, std::vector<int> ringsums, std::vector<int> ringareas, std::vector<int> outerstrips);
  jJet(double pt, int ieta, int iphi, std::vector<int> ringsums, std::vector<int> ringareas, std::vector<int> outerstrips,std::vector<int> towers);
  int iEta() const;
  int iPhi() const;
  double pt() const;
  std::vector<int> ringSums() const;
  std::vector<int> ringAreas() const;
  std::vector<int> getOuterStrips() const;
  std::vector<int> getTowers() const;
  int DeltaR2(const jJet & jet2) const;
  int PUE();
  double eatDonut(); //the energy after PUsubtraction
  double eatGlobe(double median); //the energy after global PUsubtraction

private:
  double mpt;
  int mieta;
  int miphi;
  std::vector<int> mringsums;
  std::vector<int> mringareas;
  std::vector<int> mouterstrips;
  std::vector<int> mtowers;
};

jJet::jJet(double pt, int ieta, int iphi) : mpt(pt), mieta(ieta), miphi(iphi) {}
jJet::jJet(double pt, int ieta, int iphi, std::vector<int> ringsums, std::vector<int> ringareas, std::vector<int> outerstrips) : mpt(pt), mieta(ieta), miphi(iphi), mringsums(ringsums), mringareas(ringareas), mouterstrips(outerstrips) {
   std::sort(mouterstrips.begin(), mouterstrips.end());
}
jJet::jJet(double pt, int ieta, int iphi, std::vector<int> ringsums, std::vector<int> ringareas, std::vector<int> outerstrips,std::vector<int> towers) : mpt(pt), mieta(ieta), miphi(iphi), mringsums(ringsums), mringareas(ringareas), mouterstrips(outerstrips),mtowers(towers) {
   std::sort(mouterstrips.begin(), mouterstrips.end());
   //std::sort(mtowers.begin(), mtowers.end());
}

int jJet::iEta() const { return mieta; }
int jJet::iPhi() const { return miphi; }
double jJet::pt() const { return mpt; }
std::vector<int> jJet::ringSums() const { return mringsums; }
std::vector<int> jJet::ringAreas() const { return mringareas; }
std::vector<int> jJet::getOuterStrips() const { return mouterstrips; }
std::vector<int> jJet::getTowers() const { return mtowers; }
int jJet::PUE() { return (mouterstrips[1] + mouterstrips[2]); } //i.e. sum up the middle two energies

double jJet::eatDonut() {
   double lastringsum = this->ringSums().at(this->ringSums().size() - 1);
   double donutenergy = this->PUE() * 3.5; //3.5 = 7x7 / 2x7
   return (this->pt() - lastringsum - donutenergy);
}

double jJet::eatGlobe(double median) {
   return (this->pt() - median);
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

bool sortbypt(const jJet &a, const jJet &b) { return a.pt() > b.pt(); }

bool sortbyrho(const jJet &a, const jJet &b) { 
 int  area1=0;
 int  area2=0;
   for(std::vector<int>::iterator j=a.ringAreas().begin();j!=a.ringAreas().end();++j) area1 += *j;
   for(std::vector<int>::iterator j=b.ringAreas().begin();j!=b.ringAreas().end();++j) area2 += *j;
   return a.pt()/area1 > b.pt()/area2;
}

#endif
