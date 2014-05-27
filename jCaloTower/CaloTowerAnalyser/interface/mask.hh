#ifndef __MATTHEW_MASK_STRUCT__
#define __MATTHEW_MASK_STRUCT__

std::vector< std::vector<int> > mask_square_9by9()
{
   int mask_array[9][9] = {
      { 1,1,1,1,1,1,1,1,2 },
      { 1,1,1,1,1,1,1,2,2 },
      { 1,1,1,1,1,1,2,2,2 },
      { 1,1,1,1,1,2,2,2,2 },
      { 1,1,1,1,0,2,2,2,2 },
      { 1,1,1,1,2,2,2,2,2 },
      { 1,1,1,2,2,2,2,2,2 },
      { 1,1,2,2,2,2,2,2,2 },
      { 1,2,2,2,2,2,2,2,2 }
   };
   std::vector< std::vector<int> > mask;
   for (int i =0; i<9; i++)
   {
      std::vector<int> mask_vec;
      for (int j =0; j<9; j++)
      {
	 mask_vec.push_back(mask_array[i][j]);
      } 
      mask.push_back(mask_vec);
   }
   return mask;
}
std::vector< std::vector<int> > mask_circle_9by9()
{
   int mask_array[9][9] = {
      { 0,0,1,1,1,1,1,0,0 },
      { 0,1,1,1,1,1,1,2,0 },
      { 1,1,1,1,1,1,2,2,2 },
      { 1,1,1,1,1,2,2,2,2 },
      { 1,1,1,1,0,2,2,2,2 },
      { 1,1,1,1,2,2,2,2,2 },
      { 1,1,1,2,2,2,2,2,2 },
      { 0,1,2,2,2,2,2,2,0 },
      { 0,0,2,2,2,2,2,0,0 }
   };
   std::vector< std::vector<int> > mask;
   for (int i =0; i<9; i++)
   {
      std::vector<int> mask_vec;
      for (int j =0; j<9; j++)
      {
	 mask_vec.push_back(mask_array[i][j]);
      } 
      mask.push_back(mask_vec);
   }
   return mask;
}

std::vector< std::vector<int> > mask_donut_11by11()
{
   int mask_array[11][11] = {
      { 0,1,1,1,1,1,1,1,1,1,0 },
      { 4,0,0,0,0,0,0,0,0,0,2 },
      { 4,0,0,0,0,0,0,0,0,0,2 },
      { 4,0,0,0,0,0,0,0,0,0,2 },
      { 4,0,0,0,0,0,0,0,0,0,2 },
      { 4,0,0,0,0,0,0,0,0,0,2 },
      { 4,0,0,0,0,0,0,0,0,0,2 },
      { 4,0,0,0,0,0,0,0,0,0,2 },
      { 4,0,0,0,0,0,0,0,0,0,2 },
      { 4,0,0,0,0,0,0,0,0,0,2 },
      { 0,3,3,3,3,3,3,3,3,3,0 },
   };
   std::vector< std::vector<int> > mask;
   for (int i =0; i<11; i++)
   {
      std::vector<int> mask_vec;
      for (int j =0; j<11; j++)
      {
	 mask_vec.push_back(mask_array[i][j]);
      } 
      mask.push_back(mask_vec);
   }
   return mask;
}
#endif
