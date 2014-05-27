#ifndef CALIBRATIONPARAMS_HH
#define CALIBRATIONPARAMS_HH

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
   donut,
   nopus,
   global
};

std::vector<double> getLut(const jetType & type){

   double donutLut[48]=
   {
     0.577715, 0.001912, 9.997410, 0.788259, 0.136887, 1.379856,
     0.601278, 0.000864, 9.990172, 1.748361, 0.110393, 0.693095,
     0.604247, 0.000130, 9.999849, 0.875459, 0.177560, 2.038274,
     0.560054, 0.000031, 9.999992, 0.889820, 0.122843, 1.505073,
     0.571769, 0.001733, 9.859563, 0.806462, 0.147504, 1.837979,
     0.602169, 0.000122, 9.999999, 0.855320, 0.181937, 2.103586,
     0.579443, 0.001599, 9.992034, 2.129323, 0.085680, 0.000000,
     0.577769, 0.001965, 9.998436, 0.789226, 0.134395, 1.405397
   };

   double globalLut[48]=
   {

     0.566207, 0.599793, 9.998307, 1.657615, 0.101169, 0.000018,
     0.622006, 0.003353, 9.999998, 2.010044, 0.138838, 0.982124,
     0.586944, 0.000072, 9.999751, 2.412395, 0.096922, 0.000000,
     0.554829, 0.007854, 9.999941, 1.870371, 0.087240, 0.000000,
     0.559890, 0.003037, 9.999956, 1.949975, 0.089923, 0.000000,
     0.576387, 0.000383, 9.998561, 2.250723, 0.092234, 0.000000,
     0.590891, 0.000000, 9.999092, 2.515913, 0.096558, 0.121088,
     0.565726, 0.281931, 9.999742, 1.611882, 0.094854, 0.000008

   };

   double nopusLut[48]=
   {
     0.593960,  0.001950, 9.999681, 0.456358, 0.245626, 2.501213,
     0.631245, 0.000477, 9.984649, 0.935553, 0.196693, 2.087692,
     0.586454, 0.001532, 9.921435, 0.721164, 0.168367, 2.168667,
     0.585589, 0.001708, 9.999599, 0.526033, 0.209418, 2.565975,
     0.584994, 0.001510, 9.999757, 0.504712, 0.220591, 2.674319,
     0.576558, 0.002302, 9.946843, 0.737511, 0.150601, 2.041995,
     0.621093, 0.000024, 9.992533, 0.955613, 0.173735, 1.951149,
     0.504539, 4.593394, 10.000000,  0.300372, 0.279033, 2.669730
   };

   std::vector<double> donutVec,globalVec,nopusVec;

   for(int i=0; i<48; i++){

     if(type==jetType::donut) donutVec.push_back(donutLut[i]);
     else if(type==jetType::global) globalVec.push_back(globalLut[i]);
     else if(type==jetType::nopus)nopusVec.push_back(nopusLut[i]);

   }

   if(type==jetType::donut){

     return donutVec;

   }else if(type==jetType::global){

     return globalVec;

   }else if(type==jetType::nopus){

     return nopusVec;

   }else{
     std::cout << "Invalid string to get lut" << std::endl;
     return std::vector<double>();
   }

}

std::vector<jJet> calibrateL1Jets(const std::vector<jJet>& inJets, const std::vector<double>& lut, double ptMin, double ptMax){

  std::vector<jJet> outJets;

  for(auto iJet = inJets.begin(); iJet!=inJets.end(); iJet++){

    //If the pt of the jet is outside of the calibration range, add the jet to the calibrated jets and do nothing
    if(iJet->pt()<ptMin || iJet->pt()>ptMax){
      outJets.push_back(*iJet);
    }else{

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

