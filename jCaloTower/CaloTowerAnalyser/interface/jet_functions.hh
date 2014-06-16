#ifndef JET_FUNCTIONS_HH
#define JET_FUNCTIONS_HH

bool sortbypt(const jJet &a, const jJet &b) { return a.pt() > b.pt(); }

bool sortbyrho(const jJet &a, const jJet &b) { 
   return a.pt()/a.area() > b.pt()/b.area();
}
void CaloTowerAnalyser::getJets(std::vector < fastjet::PseudoJet > &constits,std::vector < fastjet::PseudoJet > &jets) { 

  double rParam = 0.4;
  fastjet::JetDefinition jetDef(fastjet::antikt_algorithm, rParam);    
  int activeAreaRepeats = 1;
  double ghostArea = 0.01;
  double ghostEtaMax = 7.0;
  fastjet::GhostedAreaSpec fjActiveArea(ghostEtaMax,activeAreaRepeats,ghostArea);
  fastjet::AreaDefinition fjAreaDefinition( fastjet::active_area, fjActiveArea );
  fastjet::ClusterSequenceArea* thisClustering_ = new fastjet::ClusterSequenceArea(constits, jetDef, fjAreaDefinition);
  std::vector<fastjet::PseudoJet> out_jets = sorted_by_pt(thisClustering_->inclusive_jets(5.0));
  delete thisClustering_;
  for(unsigned int i0 = 0; i0 < out_jets.size(); i0++) jets.push_back(out_jets[i0]);

  return;
}
double CaloTowerAnalyser::getMedian(const std::vector<jJet> & jets)
{
  //std::sort(jets.begin(),jets.end(),sortbyrho);
  std::vector<jJet> jetSort=jets;
  std::sort(jetSort.begin(),jetSort.end(), sortbyrho);  
  double median_energy=0.;
  if(jetSort.size() > 2) {
    if(jetSort.size() % 2 == 0 ) {
      int index1 = jetSort.size() / 2;
      median_energy=((double)((double)jetSort.at(index1).pt()/(double)jetSort.at(index1).area() + (double)jetSort.at(index1+1).pt()/(double)jetSort.at(index1+1).area()))/2.0;
    } else {
      int index1 = (int)jetSort.size() / 2;
      median_energy=((double)jetSort.at(index1).pt()/(double)jetSort.at(index1).area());
    }
  }
  return median_energy;

}
int CaloTowerAnalyser::getMedianSeed(const std::vector<jJet> & jets)
{
  //std::sort(jets.begin(),jets.end(),sortbyrho);
  std::vector<jJet> jetSort=jets;
  std::sort(jetSort.begin(),jetSort.end(), sortbyrho);  
  int seed=0;
  if(jetSort.size() > 2) {
    if(jetSort.size() % 2 == 0 ) {
      int index1 = jetSort.size() / 2;
      seed=jetSort.at(index1).ringSums().at(0);
    } else {
      int index1 = jetSort.size() / 2;
      seed=jetSort.at(index1).ringSums().at(0);
    }
  }
  return seed;

}
///MASK VERSION

std::vector<jJet> CaloTowerAnalyser::getL1JetsMask(const std::vector< std::vector<int> > & input, std::vector<std::vector< int > > mask, std::vector<std::vector< int > > mask_donut, int seedthresh1, int seedthresh2) {
  //seedthresh1 is the seedthreshold on the central tower
  //seedthresh2 is the threshold on all towers a la zero suppression
  //jetsize is the +/- number to span i.e. +/- 1 = 3x3
  /////vetowindowsize is the +/- number window to look at to potentially veto the central tower
  /////THIS MUST CHANGE
  std::vector<jJet> L1_jJets;
  TriggerTowerGeometry g;
  int etasize=(mask.size()-1)/2;
  int phisize=(mask.at(0).size()-1)/2;
  int nringsveto =etasize;

  int etasizedonut=(mask_donut.size()-1)/2;
  int phisizedonut=(mask_donut.at(0).size()-1)/2;
  int nstripsdonut =4;
  /////////////////
  //std::cout << input.size() << ", " << input[0].size() << std::endl;
  for ( int i = 0; i < (int)input.size(); i++) {
    for ( int j = 0; j < (int)input[i].size(); j++) {
      std::vector<int> jetTower;
      //std::cout << "new: (" << i << ", " << j << ", " << input[i][j] << ")" << std::endl;
      int numtowersaboveme=0;
      int numtowersabovethresh=0;

      std::vector<int> localsums(nringsveto+1,0); //to hold the ring sums (+1 for centre)
      std::vector<int> areas(nringsveto+1,0); //to hold the ring areas (i.e. when we get up against the boundaries)
      //std::vector<int> outerstrips(nstripsdonut,0); //to hold the energies in the 4 surrounding outer strips (excluding corners)
      std::vector<std::pair<int,int>> outerstrips(nstripsdonut,std::make_pair(0,0)); //to hold the energies in the 4 surrounding outer strips (excluding corners)//AND THEIR AREAS!
      areas[0]=1;
      int jetarea = 1;
      //int pusarea=0;
      for(int l=(j-phisizedonut); l<=(j+phisizedonut); l++) {
	for(int k=(i-etasizedonut); k<=(i+etasizedonut); k++) {
	  if(k < 0 || k > 55) continue; //i.e. out of bounds of eta<3
	  //std::cout << " k = " << k << ", l = " << l << ", i =" << i << ", j = " << j << std::endl;
	  unsigned int dk = k-i+etasizedonut;
	  unsigned int dl = l-j+phisizedonut;


	  //	       std::cout << dk << std::endl;
	  //	       std::cout << dl << std::endl;
	  //make a co-ordinate transform at the phi boundary
	  int newl;
	  if(l < 0) { newl = l+72; } 
	  else if (l > 71) { newl = l-72; } 
	  else { newl = l; }

	  if (l != j && k != i)
	  {
	    jetTower.push_back(input[k][newl]);
	  }
	  if(input[k][newl] > seedthresh2) { numtowersabovethresh++; }
	  if(dl < mask_donut.size() && dk < mask_donut.at(0).size())
	  {
	    if(mask_donut[dl][dk] != 0)
	    {
	      outerstrips[mask_donut[dl][dk]-1].first+=input[k][newl];
	      outerstrips[mask_donut[dl][dk]-1].second++;
	      //	     std::cout << mask_donut[dl][dk];
	    }
	  }

	}
	//std::cout << std::endl;
      }
      //std::cout << std::endl;
      for(int l=(j-phisize); l<=(j+phisize); l++) {
	for(int k=(i-etasize); k<=(i+etasize); k++) {
	  unsigned int dk = k-i+etasize;
	  unsigned int dl = l-j+phisize;
	  if(k < 0 || k > 55) continue; //i.e. out of bounds of eta<3
	  //std::cout << " k = " << k << ", l = " << l << ", i =" << i << ", j = " << j << std::endl;
	  //	       std::cout << dk << std::endl;
	  //	       std::cout << dl << std::endl;
	  //make a co-ordinate transform at the phi boundary
	  int newl;
	  if(l < 0) { newl = l+72; } 
	  else if (l > 71) { newl = l-72; } 
	  else { newl = l; }

	  if (l != j && k != i)
	  {
	    jetTower.push_back(input[k][newl]);
	  }
	  if(input[k][newl] > seedthresh2) { numtowersabovethresh++; }
	  if(dl < mask.size() && dk < mask.at(0).size())
	  {
	    if (mask[dl][dk] == 2){if(input[k][newl]>input[i][j]) {numtowersaboveme++;}}
	    else if (mask[dl][dk] == 1){if(input[k][newl]>=input[i][j]) {numtowersaboveme++;}}
	    /*
	       if((k+l) > (i+j) ) { if(input[k][newl] > input[i][j]) { numtowersaboveme++; } }
	       else if( ((k+l) == (i+j)) && (k-i) > (l-j)) { if(input[k][newl] > input[i][j]) { numtowersaboveme++; } } //this line is to break the degeneracy along the diagonal treating top left different to bottom right
	       else { if(input[k][newl] >= input[i][j]) { numtowersaboveme++; } }
	       */
	    for( int m=0; m<nringsveto+1;m++) { //+1 for centre of jet (n steps is n+1 rings!)
	      if((abs(i-k) == m && abs(j-l) <= m) || (abs(i-k) <= m && abs(j-l) == m)) { 
		//i.e. we are now in ring m
		localsums[m] += input[k][newl]; 
		if (mask[dl][dk] != 0) {areas[m] += 1; jetarea++;}
		break; //no point continuining since can only be a member of one ring
	      }
	    }
	  }

	}
      }
      //now we have a jet candidate centred at i,j, with the ring energies and areas defined
      //now we have the L1 jet candidate:
      if(numtowersaboveme == 0 && input[i][j] > seedthresh1) {
	double totalenergy=0.0;
	//std::cout << "iEta: " << g.old_iEta(i) << ", iPhi: " << g.old_iPhi(j) << ", r0: " << localsums[0] <<  ", r1: " << localsums[1] << ", r2: " << localsums[2] << ", r3: " << localsums[3] << ", r4: " << localsums[4] << std::endl;
	for(int ring=0; ring < (int)localsums.size(); ring++) { totalenergy += localsums[ring]; }
	//this is with PUS:
	if(totalenergy > 0.0) {
	  //TEMP
	  //areas.at(areas.size()-1)=pusarea;

	  //TEMP
	  //L1_jJets.push_back(jJet(totalenergy, g.old_iEta(i), g.old_iPhi(j), localsums, areas, outerstrips,jetTower,jetarea));
	  L1_jJets.push_back(jJet(totalenergy, g.old_iEta(i), g.old_iPhi(j), localsums, areas, outerstrips,jetarea));
	}

      }

    }
  }
  //sort by highest pT before ending
  std::sort(L1_jJets.begin(), L1_jJets.end(), sortbypt);  

  return L1_jJets;

}

std::vector<jJet> CaloTowerAnalyser::getL1Jets(const std::vector< std::vector<int> > & input, int jetsize, int vetowindowsize, int seedthresh1, int seedthresh2) {
  //seedthresh1 is the seedthreshold on the central tower
  //seedthresh2 is the threshold on all towers a la zero suppression
  //jetsize is the +/- number to span i.e. +/- 1 = 3x3
  //vetowindowsize is the +/- number window to look at to potentially veto the central tower

  std::vector<jJet> L1_jJets;
  TriggerTowerGeometry g;

  //std::cout << input.size() << ", " << input[0].size() << std::endl;

  for ( int i = 0; i < (int)input.size(); i++) {
    for ( int j = 0; j < (int)input[i].size(); j++) {
      std::vector<int> jetTower;
      //std::cout << "new: (" << i << ", " << j << ", " << input[i][j] << ")" << std::endl;
      int numtowersaboveme=0;
      int numtowersabovethresh=0;
      int seedtower = input[i][j];  
      std::vector<int> localsums(jetsize+1,0); //to hold the ring sums (+1 for centre)
      std::vector<int> areas(jetsize+1,0); //to hold the ring areas (i.e. when we get up against the boundaries)
      std::vector<std::pair<int,int>> outerstrips(4,std::make_pair(0,0)); //to hold the energies in the 4 surrounding outer strips (excluding corners)
      int jetarea = 1;
      //int pusarea = 0;
      for(int k=(i-jetsize); k<=(i+jetsize); k++) {
	for(int l=(j-jetsize); l<=(j+jetsize); l++) {
	  if(k < 0 || k > 55) continue; //i.e. out of bounds of eta<3
	  //std::cout << " k = " << k << ", l = " << l << ", i =" << i << ", j = " << j << std::endl;

	  //make a co-ordinate transform at the phi boundary
	  int newl;
	  if(l < 0) { newl = l+72; } 
	  else if (l > 71) { newl = l-72; } 
	  else { newl = l; }
	  if (l != j && k != i)
	  {
	    jetTower.push_back(input[k][newl]);
	  }
	  if(input[k][newl] > seedthresh2) { numtowersabovethresh++; }

	  //to decide which ring to assign energy to
	  for( int m=0; m<jetsize+1;m++) { //+1 for centre of jet (n steps is n+1 rings!)
	    if((abs(i-k) == m && abs(j-l) <= m) || (abs(i-k) <= m && abs(j-l) == m)) { 
	      //i.e. we are now in ring m
	      if (m <= vetowindowsize) localsums[m] += input[k][newl]; 
	      areas[m]+=1;
	      if(m == jetsize) { //i.e. we are in the outer ring and want to parameterise PU
		if( (k-i) == m && abs(j-l) <= (m-1) ) { outerstrips[0].first += input[k][newl];outerstrips[0].second+=1;}
		if( (i-k) == m && abs(j-l) <= (m-1) ) { outerstrips[1].first += input[k][newl];outerstrips[1].second+=1;}
		if( (l-j) == m && abs(i-k) <= (m-1) ) { outerstrips[2].first += input[k][newl];outerstrips[2].second+=1;}
		if( (j-l) == m && abs(i-k) <= (m-1) ) { outerstrips[3].first += input[k][newl];outerstrips[3].second+=1;}
	      }

	      if(m > 0 && m <= vetowindowsize) { //i.e. don't compare the central tower or towers outside vetowindowsize
		jetarea++;
		if((k+l) > (i+j) ) { if(input[k][newl] > input[i][j]) { numtowersaboveme++; } }
		else if( ((k+l) == (i+j)) && (k-i) > (l-j)) { if(input[k][newl] > input[i][j]) { numtowersaboveme++; } } //this line is to break the degeneracy along the diagonal treating top left different to bottom right
		else { if(input[k][newl] >= input[i][j]) { numtowersaboveme++; } }

	      }
	      break; //no point continuining since can only be a member of one ring
	    }
	  }

	}
      }

      //now we have a jet candidate centred at i,j, with the ring energies and areas defined

      //now we have the L1 jet candidate:
      if(numtowersaboveme == 0 )
      {
	//std::cout << input[i][j] << "  "  << localsums[0] << std::endl;
	{
	  if(input[i][j] > seedthresh1) 
	  {

	    double totalenergy=0.0;
	    //std::cout << "iEta: " << g.old_iEta(i) << ", iPhi: " << g.old_iPhi(j) << ", r0: " << localsums[0] <<  ", r1: " << localsums[1] << ", r2: " << localsums[2] << ", r3: " << localsums[3] << ", r4: " << localsums[4] << std::endl;
	    for(int ring=0; ring < (int)localsums.size(); ring++) { totalenergy += localsums[ring]; }
	    //this is with PUS:
	    //for(int ring=0; ring < (int)localsums.size()-1; ring++) { totalenergy += localsums[ring]; }
	    //std::sort(outerstrips.begin(),outerstrips.end());
	    //totalenergy = totalenergy - (3.5 * (outerstrips[1] + outerstrips[2]));

	    //this means we have a viable candidate
	    if(totalenergy > 0.0) {
	      L1_jJets.push_back(jJet(totalenergy, g.old_iEta(i), g.old_iPhi(j), localsums, areas, outerstrips,jetTower,jetarea, seedtower));
	    }
	    //std::cout << localsums[0] << std::endl;
	  }

	} 
      }
    }
  }

  //sort by highest pT before ending
  std::sort(L1_jJets.begin(), L1_jJets.end(), sortbypt);  

  return L1_jJets;

}


std::vector<int> CaloTowerAnalyser::closestJetDistance(const std::vector<jJet> & jJets) {

  std::vector<int> distances(jJets.size(),-1);

  bool summary=false;

  //std::cout << "event size: " << jJets.size() << std::endl;

  if(jJets.size() > 0) { //will get distance =999 for closest distance if only 1 jet
    for(int i=0; i<(int)jJets.size(); i++) {
      int closestDR2 = 999;

      //std::cout << i << " closest to " << distances[i] << std::endl;

      for(int j=0; j<(int)jJets.size(); j++) {
	if(i!=j && jJets[i].DeltaR2(jJets[j]) < closestDR2) { closestDR2 = jJets[i].DeltaR2(jJets[j]); }
      }
      distances[i] = closestDR2;
      //std::cout << i << " closest distance " << closestDR2 << std::endl;

    }

  } else { std::cout << "no jets in collection" << std::endl; throw 1; }

  if(summary) {
    for(unsigned int i=0; i< distances.size(); i++) {
      std::cout << "jet " << i << " (" << jJets[i].pt() << ", " << jJets[i].iEta() << ", " << jJets[i].iPhi() << ") closest = " << distances[i] << std::endl; 
    }

  }

  return distances;
}


#endif
