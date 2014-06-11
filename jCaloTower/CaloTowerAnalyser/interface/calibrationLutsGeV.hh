#ifndef CALIBRATIONLUTSGEV_HH
#define CALIBRATIONLUTSGEV_HH

namespace luts5400GeV{

  double donutLut[48]= //Goes down to 8
  {
    0.929153,       7.833509,       6.268700,       1.163965,       0.097264,       0.046726,
    0.974399,       8.706300,       9.999791,       2.095357,       0.125052,       0.672648,
    0.813517,       9.996260,       4.120525,       1.443122,       0.074645,       0.000773,
    0.839552,       9.399855,       3.148402,       1.126918,       0.079388,       0.105467,
    0.824015,       9.659682,       4.129917,       1.242116,       0.076801,       0.027425,
    0.771501,       9.623034,       2.452736,       1.226666,       0.066529,       0.165386,
    1.028313,       7.655931,       9.996833,       1.966062,       0.139746,       0.927438,
    0.964559,       6.571517,       9.913743,       1.250615,       0.113622,       0.600257,
  };

  double globalLut[48]= //Goes down to 8
  {
    0.906907,       9.799444,       4.898061,       1.048949,       0.136667,       0.254435,
    0.979404,       7.034494,       3.436158,       2.262959,       0.109428,       0.247115,
    0.923403,       9.999900,       4.586094,       1.717475,       0.104799,       0.000067,
    0.863852,       9.999617,       4.358355,       1.252304,       0.091954,       0.000096,
    0.738636,       9.968689,       1.752450,       0.769343,       0.050463,       0.004559,
    0.836676,       9.999992,       2.904923,       1.273807,       0.077622,       0.000002,
    0.845303,       9.985136,       2.998129,       1.810531,       0.084673,       0.002361,
    0.923338,       8.541081,       5.108460,       1.285704,       0.109812,       0.003085,
  };

  double nopusLut[48]= //Goes down to 6
  {
    0.960762,       9.733996,       9.999053,       0.409394,       0.327634,       2.142593,
    0.924138,       8.197343,       9.993807,       1.646969,       0.098581,       0.524990,
    0.997352,       9.494323,       9.999623,       0.690215,       0.236501,       2.061009,
    1.084247,       1.728260,       -1.000000,      0.620203,       0.231602,       2.495803,
    1.083599,       1.586769,       9.996801,       0.990501,       0.140948,       1.520750,
    1.078956,       1.092015,       -1.000000,      0.986645,       0.155184,       1.920747,
    1.027491,       7.721582,       9.970052,       1.365948,       0.139350,       1.102486,
    0.985093,       7.119665,       9.999996,       0.618612,       0.178457,       1.651888,
  };

}

namespace luts5450GeV{

  double donutLut[48]= //Goes down to 10
  {
    1.262007,       0.000000,       -0.361109,      0.531548,       0.765334,       3.092091,
    1.303844,       0.000000,       9.442419,       1.257421,       0.329662,       2.386020,
    1.120215,       0.888556,       9.999706,       1.319170,       0.180242,       1.904536,
    1.201702,       0.000127,       9.971691,       1.031083,       0.278477,       2.330753,
    1.178966,       0.201476,       9.999936,       1.060136,       0.256258,       2.274167,
    1.242025,       0.000000,       6.436792,       1.133671,       0.297210,       2.376962,
    1.284061,       0.190085,       9.995595,       1.298593,       0.290523,       2.299715,
    1.255484,       0.000000,       7.845377,       0.551300,       0.693816,       3.089215,
  };
  double nopusLut[48]=//Goes down to 10
  {
    1.249371,       0.000000,       3.622436,       0.390962,       1.242418,       3.360190,
    1.330313,       0.000000,       9.737799,       0.785459,       0.570098,       2.948808,
    1.316922,       0.000000,       9.832771,       0.618625,       0.647527,       3.028037,
    1.247742,       0.000000,       8.634000,       0.517111,       0.695001,       3.202538,
    1.268232,       0.000000,       -0.811456,      0.499666,       0.739898,       3.187162,
    1.275962,       0.000000,       4.862013,       0.641343,       0.535853,       3.033366,
    1.344800,       0.000000,       7.455823,       0.764960,       0.543593,       2.936922,
    1.248085,       0.000000,       0.819362,       0.417970,       1.235161,       3.395560,
  };

}


#endif