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

std::vector<double> getLut(TString type){

  double donutLut[30]=
  {
    0.508484, 0.000008, 9.999994, 1.193011, 0.061629, 0.000000,
    0.589827, 0.000000, 10.000000,  1.415656, 0.106526, 0.807901,
    0.556693, 0.000013, 9.997317, 1.103161, 0.103863, 1.028563,
    0.568842, 0.000184, 9.999943, 1.525391, 0.091236, 0.506861,
    0.491763, 0.278329, 9.313399, 1.189325, 0.059251, 0.000016
  };

  double globalLut[30]=
  {
    0.588336, 0.000000, 9.999686, 1.824371, 0.097040, 0.000000,
    0.592071, 0.000300, 9.999961, 1.414018, 0.113318, 0.905890,
    0.544519, 0.000048, 9.999980, 1.518523, 0.077896, 0.000000,
    0.568818, 0.000169, 9.999943, 1.474017, 0.097394, 0.668829,
    0.587389, 0.000007, 9.998847, 1.807552, 0.094306, 0.000000
  };

  double nopusLut[30]=
  {
    0.596566, 0.001659, 9.999837, 0.558263, 0.187173, 2.199404,
    0.568818, 0.001709, 9.999526, 0.775084, 0.114804, 1.609824,
    0.551183, 0.049413, 9.998395, 0.533633, 0.130805, 2.122670,
    0.564263, 0.000123, 9.945974, 0.695879, 0.126973, 1.950258,
    0.586183, 0.001684, 9.998715, 0.597944, 0.151862, 1.969139
  };

  std::vector<double> donutVec,globalVec,nopusVec;

  for(int i=0; i<30; i++){

    if(type=="donut") donutVec.push_back(donutLut[i]);
    else if(type=="global") globalVec.push_back(globalLut[i]);
    else if(type=="nopus")nopusVec.push_back(nopusLut[i]);

  }

  if(type=="donut"){

    return donutVec;

  }else if(type=="global"){

    return globalVec;

  }else if(type=="nopus"){

    return nopusVec;

  }else{
    std::cout << "Invalid string to get lut" << std::endl;
    return std::vector<double>();
  }

}


#endif

