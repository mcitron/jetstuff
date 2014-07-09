#ifndef CALIBRATIONLUTSGEV_HH
#define CALIBRATIONLUTSGEV_HH

namespace luts5400GeV{

  double donutLut[48]= //Goes down to 8
  {
    
		1.107687,	2.617598,	-0.995368,	0.608654,	0.225621,	2.051860,
		1.040402,	10.000000,	9.999760,	1.386640,	0.210511,	1.596042,
		1.026430,	8.292757,	9.996498,	1.728835,	0.142161,	0.779945,
		1.011743,	6.598743,	0.181362,	0.527063,	0.248330,	2.267487,
		1.004854,	7.080735,	0.287047,	0.466465,	0.280374,	2.396979,
		1.045688,	6.464312,	-0.272457,	0.633066,	0.236195,	2.156932,
		1.042691,	9.999955,	9.941631,	1.401199,	0.200588,	1.540713,
		1.106735,	2.675340,	-0.608986,	0.676154,	0.196698,	1.850680,

  };

  double globalLut[48]= //Goes down to 8
  {

		1.071612,	2.516346,	-0.995093,	1.015214,	0.131224,	0.921075,
		1.061797,	4.916101,	1.147200,	2.010806,	0.116904,	0.443223,
		0.957888,	9.214377,	4.683297,	1.596905,	0.118074,	0.275524,
		0.981087,	7.059414,	-0.482299,	0.315990,	0.322254,	2.771673,
		0.959467,	8.024331,	0.132122,	0.284379,	0.336708,	2.749877,
		1.067062,	3.966805,	0.173792,	1.466214,	0.125065,	0.773163,
		1.093773,	3.703014,	0.028596,	1.929622,	0.119829,	0.620176,
		1.051086,	3.686072,	-0.213896,	0.888897,	0.132643,	0.957735,

  };

  double nopusLut[48]= //Goes down to 6
  {

		1.094573,	1.914835,	-0.999952,	0.529477,	0.198517,	2.045523,
		1.117407,	3.225482,	-0.971224,	0.772645,	0.218468,	2.237276,
		1.113721,	1.907837,	0.386244,	0.914753,	0.162511,	1.750241,
		1.021381,	5.259399,	1.337182,	0.351027,	0.276796,	2.730577,
		1.008247,	5.990503,	9.975187,	0.731619,	0.156460,	1.633716,
		1.133472,	1.367577,	-0.368074,	0.932853,	0.168657,	1.787382,
		1.082999,	5.082858,	-0.170875,	0.588396,	0.252840,	2.479732,
		1.090921,	2.443421,	-0.996960,	0.438731,	0.223473,	2.294779,

  };

}

namespace luts5450GeV{

  double donutLut[48]= //Goes down to 10
  {

		1.176353,	1.600283,	9.999317,	0.555588,	0.407202,	2.800364,
		1.044900,	9.847988,	8.917008,	0.989314,	0.270068,	2.157350,
		1.067125,	7.230923,	9.901153,	1.032539,	0.224409,	1.936026,
		1.032572,	7.362246,	9.646847,	0.902846,	0.229233,	1.972776,
		1.035169,	7.533458,	9.975350,	0.877492,	0.244505,	2.041587,
		1.075946,	6.938594,	9.589037,	1.028061,	0.228567,	1.955146,
		1.057465,	9.691907,	9.438458,	1.014988,	0.264839,	2.141380,
		1.204602,	0.569333,	9.986754,	0.596201,	0.382972,	2.768283,

  };
  double nopusLut[48]=//Goes down to 10
  {

		1.135207,	1.691272,	9.924057,	0.446443,	0.353942,	2.816898,
		1.082423,	6.237323,	9.065346,	0.765314,	0.259257,	2.393838,
		1.050305,	6.768581,	9.143228,	0.558222,	0.288119,	2.584420,
		1.040271,	6.014694,	9.726304,	0.454449,	0.321980,	2.763517,
		1.070310,	4.645037,	9.389391,	0.485691,	0.318993,	2.746986,
		1.131881,	2.982973,	7.391251,	0.671497,	0.269400,	2.516963,
		1.150468,	2.855266,	-0.435234,	0.680916,	0.280744,	2.617447,
		1.135897,	1.966621,	9.966117,	0.449896,	0.343670,	2.794521,

  };


  double globalLut[48]=
  {

		1.085531,	4.183156,	9.991250,	0.602881,	0.299650,	2.434424,
		1.055002,	6.856517,	0.068297,	0.626569,	0.314421,	2.565204,
		1.028772,	7.563128,	8.420669,	1.077799,	0.193607,	1.673155,
		1.102369,	1.681955,	1.135606,	1.163161,	0.158408,	1.493687,
		0.994735,	8.065827,	9.979077,	0.900408,	0.203018,	1.744676,
		1.099447,	4.139690,	-1.000000,	0.650576,	0.283651,	2.483462,
		1.113445,	4.495594,	-0.846377,	0.845567,	0.251797,	2.298157,
		1.011883,	8.118609,	9.999125,	0.452462,	0.371850,	2.628541,

  };

  double twoStripsLut[48]=
  {

		1.193816,	0.326092,	9.992956,	0.550634,	0.389123,	2.816448,
		1.120043,	5.994047,	9.992877,	1.040558,	0.254847,	2.191027,
		1.061440,	7.232220,	9.999679,	0.859012,	0.247188,	2.160822,
		1.030018,	7.286136,	9.981210,	0.746853,	0.255162,	2.208698,
		1.022929,	7.540108,	9.932229,	0.774887,	0.242024,	2.094138,
		1.070107,	7.132736,	9.989234,	0.829048,	0.264329,	2.243055,
		1.131659,	5.797427,	9.999745,	1.055578,	0.250508,	2.171320,
		1.198613,	0.388605,	9.955990,	0.558948,	0.378254,	2.800021,

  };

  double threeStripsLut[48]=
  {

		1.191638,	0.177760,	9.995813,	0.535694,	0.385063,	2.823922,
		1.122600,	5.799849,	9.949315,	0.969199,	0.268179,	2.287426,
		1.032271,	8.573892,	9.579124,	0.701024,	0.286215,	2.376381,
		1.022706,	7.387238,	9.994990,	0.695890,	0.256684,	2.250821,
		1.020582,	7.560766,	9.996453,	0.688272,	0.261669,	2.250614,
		1.059101,	7.631321,	9.982958,	0.738469,	0.287471,	2.366733,
		1.123817,	5.894654,	9.986484,	0.988504,	0.255178,	2.231632,
		1.195202,	0.337839,	9.984505,	0.534382,	0.382514,	2.831762,

  };

}

#endif