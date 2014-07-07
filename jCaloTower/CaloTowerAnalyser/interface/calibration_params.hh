#ifndef CALIBRATIONPARAMS_HH
#define CALIBRATIONPARAMS_HH

#include "jCaloTower/CaloTowerAnalyser/interface/calibrationLuts.hh"

double calibFit( Double_t *v, Double_t *par ){

  // JETMET uses log10 rather than the ln used here...
  double logX = log(v[0]);

  double term1 = par[1] / ( logX * logX + par[2] );
  double term2 = par[3] * exp( -par[4]*((logX - par[5])*(logX - par[5])) );

  // Final fitting function 
  double f    = par[0] + term1 + term2; 

  return f;
  //return 1.0/f;
}

enum jetType{
  l15400donut,
  l15400global,
  l15400nopus,
  l15450donut,
  l15450nopus,
  l15450global,
  l15450twoStrips,
  l15450threeStrips,
};

std::vector<jJet> calibrateL1Jets(const std::vector<jJet>& inJets, const jetType & type, double ptMin, double ptMax){

  std::vector<double> lut;

  std::vector<jJet> outJets;
  for(int i=0; i<48; i++){

    if(type==jetType::l15400global) lut.push_back(luts5400GeV::globalLut[i]);
    else if(type==jetType::l15400donut) lut.push_back(luts5400GeV::donutLut[i]);
    else if(type==jetType::l15400nopus) lut.push_back(luts5400GeV::nopusLut[i]);
    else if(type==jetType::l15450donut) lut.push_back(luts5450GeV::donutLut[i]);
    else if(type==jetType::l15450global) lut.push_back(luts5450GeV::globalLut[i]);
    else if(type==jetType::l15450nopus) lut.push_back(luts5450GeV::nopusLut[i]);
    else if(type==jetType::l15450twoStrips) lut.push_back(luts5450GeV::twoStripsLut[i]);
    else if(type==jetType::l15450threeStrips) lut.push_back(luts5450GeV::threeStripsLut[i]);

    else std::cout << "Invalid type to get lut" << std::endl;

  }


  for(auto iJet = inJets.begin(); iJet!=inJets.end(); iJet++){

    //If the pt of the jet is outside of the calibration range, add the jet to the calibrated jets and do nothing
    if(iJet->pt()>ptMax){
      outJets.push_back(*iJet);
    }
    else if(iJet->pt()>ptMin){

      double p[6]; //These are the parameters of the fit
      double v[1]; //This is the pt value

      //Load the lut based on the correct eta bin
      if(iJet->iEta()>=-28 && iJet->iEta()<-21){
        p[0]=lut[0];
        p[1]=lut[1];
        p[2]=lut[2];
        p[3]=lut[3];
        p[4]=lut[4];
        p[5]=lut[5];
      }else if(iJet->iEta()>=-21 && iJet->iEta()<-14){
        p[0]=lut[6];
        p[1]=lut[7];
        p[2]=lut[8];
        p[3]=lut[9];
        p[4]=lut[10];
        p[5]=lut[11];
      }else if(iJet->iEta()>=-14 && iJet->iEta()<7){
        p[0]=lut[12];
        p[1]=lut[13];
        p[2]=lut[14];
        p[3]=lut[15];
        p[4]=lut[16];
        p[5]=lut[17];
      }else if(iJet->iEta()>=7 && iJet->iEta()<0){
        p[0]=lut[18];
        p[1]=lut[19];
        p[2]=lut[20];
        p[3]=lut[21];
        p[4]=lut[22];
        p[5]=lut[23];
      }else if(iJet->iEta()>0 && iJet->iEta()<=7){
        p[0]=lut[24];
        p[1]=lut[25];
        p[2]=lut[26];
        p[3]=lut[27];
        p[4]=lut[28];
        p[5]=lut[29];
      }else if(iJet->iEta()>7 && iJet->iEta()<=14){
        p[0]=lut[30];
        p[1]=lut[31];
        p[2]=lut[32];
        p[3]=lut[33];
        p[4]=lut[34];
        p[5]=lut[35];
      }else if(iJet->iEta()>14 && iJet->iEta()<=21){
        p[0]=lut[36];
        p[1]=lut[37];
        p[2]=lut[38];
        p[3]=lut[39];
        p[4]=lut[40];
        p[5]=lut[41];
      }else if(iJet->iEta()>21 && iJet->iEta()<=28){
        p[0]=lut[42];
        p[1]=lut[43];
        p[2]=lut[44];
        p[3]=lut[45];
        p[4]=lut[46];
        p[5]=lut[47];
      }
      v[0]=iJet->pt();
      double correction=1.0*calibFit(v,p);

      jJet newJet=*iJet;
      newJet.setPt(correction*iJet->pt());

      outJets.push_back(newJet);

    }

  }
  return outJets;
}

#endif

