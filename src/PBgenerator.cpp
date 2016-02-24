// Riley Raschke - 2016
// DWTFYW licensce

#ifndef PBgenerator_h
#include "PBgenerator.h"
#endif

#include <PBnumbers.h>

/**
 * PUBLIC
 */
PBgenerator::PBgenerator(){
   this->generator = base_generator_type(static_cast<unsigned int>(std::time(0)));
   nMax = PBnumbers::DEFAULT_N_MAX;
   pMax = PBnumbers::DEFAULT_P_MAX;
   nCount = PBnumbers::DEFAULT_N_COUNT;
   pCount = PBnumbers::DEFAULT_P_COUNT;
   nDist = dist_type(1, nMax);
   pDist = dist_type(1, pMax);
}

PBgenerator::PBgenerator(const PBgenerator & other ){
   this->generator = other.generator;
   nMax = other.nMax;
   pMax = other.pMax;
   nCount = other.nCount;
   pCount = other.pCount;
   nDist = dist_type(1, nMax);
   pDist = dist_type(1, pMax);
}

PBgenerator& PBgenerator::operator=(const PBgenerator & other ){
   this->generator = other.generator;
   nMax = other.nMax;
   pMax = other.pMax;
   nCount = other.nCount;
   pCount = other.pCount;
   nDist = dist_type(1, nMax);
   pDist = dist_type(1, pMax);
}

PBgenerator::PBgenerator( base_generator_type *gen ){
   nMax = PBnumbers::DEFAULT_N_MAX;
   pMax = PBnumbers::DEFAULT_P_MAX;
   nCount = PBnumbers::DEFAULT_N_COUNT;
   pCount = PBnumbers::DEFAULT_P_COUNT;
   nDist = dist_type(1, nMax);
   pDist = dist_type(1, pMax);

   this->generator = *gen;
}

PBgenerator::PBgenerator( base_generator_type &gen ){
   nMax = PBnumbers::DEFAULT_N_MAX;
   pMax = PBnumbers::DEFAULT_P_MAX;
   nCount = PBnumbers::DEFAULT_N_COUNT;
   pCount = PBnumbers::DEFAULT_P_COUNT;
   nDist = dist_type(1, nMax);
   pDist = dist_type(1, pMax);

   this->generator = gen;
}


PBgenerator::PBgenerator( int nCount, int pCount, int nMax, int pMax ){
   this->generator = base_generator_type(static_cast<unsigned int>(std::time(0)));
   this->nMax = nMax;
   this->pMax = pMax;
   this->nCount = nCount;
   this->pCount = pCount;
   this->nDist = dist_type(1, nMax);
   this->pDist = dist_type(1, pMax);
}

PBnumbers PBgenerator::Generate() {
   mtx_.lock();
   int nNums[nCount];
   int pNums[pCount];

   gen_type ball_gen( generator, nDist);

   int i,j;

   for( i = 0; i < nCount; ++i ){
      nNums[i] = ball_gen();
   }
   for(i = 0; i < nCount; ++i){
      for(j = i+1; j < nCount; ++j){
         if( nNums[i] == nNums[j] ){
           for( i = 0; i < nCount; ++i ){
               nNums[i] = ball_gen();
            }
            i = -1; // NOTE: The for loop will increment this to 0.
            j = nCount;
         }
      }
   }

   gen_type pball_gen( generator , pDist);
   for( i = 0; i < pCount; ++i ){
      pNums[i] = pball_gen();
   }
   for(i = 0; i < pCount; ++i){
      for(j = i+1; j < pCount; ++j){
         if( pNums[i] == pNums[j] ){
           for( i = 0; i < pCount; ++i ){
               pNums[i] = pball_gen();
            }
            i = -1; // NOTE: The for loop will increment this to 0.
            j = pCount;
         }
      }
   }

   mtx_.unlock();
   return PBnumbers(
      vector<int>( nNums, nNums+sizeof(nNums)/sizeof(nNums[0]) ),
      vector<int>( pNums, pNums+sizeof(pNums)/sizeof(pNums[0]) )
   );
}

void PBgenerator::ReSeed(){
   generator.seed(static_cast<unsigned int>(std::time(0)));
}

void PBgenerator::ReSeed(int x ){
   generator.seed( static_cast<unsigned int>(x) );
}

void PBgenerator::ReSeed(unsigned int x ){
   generator.seed(x);
}
