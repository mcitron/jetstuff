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
  jJet(double pt, int ieta, int iphi, std::vector<int> ringsums, std::vector<int> ringmax,double jetFirMomEta,double jetFirMomPhi,double jetSecMomEta, double jetSecMomPhi,double covEtaPhi, std::vector<int> ringareas, std::vector<std::pair<int,int> > outerstrips, int jetarea);
  jJet(double pt, int ieta, int iphi, std::vector<int> ringsums,std::vector<int> ringsumsec,std::vector<int> ringsumshc, std::vector<int> ringmax,double jetFirMomEta, double jetFirMomPhi, double jetSecMomEta, double jetSecMomPhi,double covEtaPhi,std::vector<int> ringareas,  std::vector<std::pair<int,int> > outerstrips, int jetarea);
  jJet(double pt, int ieta, int iphi, std::vector<int> ringsums, std::vector<int> ringareas, std::vector<std::pair<int,int> > outerstrips,std::vector<int> towers, int jetarea);
  jJet(double pt, int ieta, int iphi, std::vector<int> ringsums, std::vector<int> ringareas, std::vector<std::pair<int,int> > outerstrips, std::vector<int> towers, int jetarea,int seedtower);
  int iEta() const;
  int iPhi() const;
  int gEta() const;
  int gPhi() const;
  double pt() const;
  void setPt(double pt);
  bool isolatedJet(const std::vector<jJet>& jetCollection, double dR2Max);
  int minDeltaR2(const std::vector<jJet>& jetCollection) const;
  std::vector<int> ringSums() const;
  std::vector<int> ringSumsEC() const;
  std::vector<int> ringSumsHC() const;
  std::vector<int> ringMax() const;
  std::vector<int> ringAreas() const;
  std::vector<std::pair<int,int> > getOuterStrips() const;
  std::vector<int> getTowers() const;
  int DeltaR2(const jJet & jet2) const;
  int PUE();
  double eatDonut(); //the energy after PUsubtraction
  double eatGlobe(double median); //the energy after global PUsubtraction
  int area() const;
  double firPhi() const;
  double firEta() const;
  double secPhi() const;
  double secEta() const;
  double covEtaPhi() const;
  int getOuterSum() const;
private:
  double mpt;
  int mieta;
  int miphi;
  int mgeta;
  int mgphi;
  int mbx;
  std::vector<int> mringsums;
  std::vector<int> mringsumsec;
  std::vector<int> mringsumshc;
  std::vector<int> mringmax;
  double mfireta;
  double mfirphi;
  double mseceta;
  double msecphi;
  double mcov;
  std::vector<int> mringareas;
  std::vector<std::pair<int,int>> mouterstrips;
  std::vector<int> mtowers;
  int marea;
  int mseed;
};

#endif
