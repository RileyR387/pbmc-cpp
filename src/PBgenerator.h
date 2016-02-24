// Author: Riley Raschke
// © 2016 rrappsdev.com
// DWTFYW Licensce - Just mention me
//

#ifndef PBgenerator_h
#define PBgenerator_h

#include <iostream>
#include <vector>
#include <boost/random.hpp>
#include <boost/thread/mutex.hpp>

#include <PBnumbers.h>

using namespace std;

class PBgenerator
{
   public:
      typedef boost::mt19937           base_generator_type;
      //typedef boost::mt11213b           base_generator_type;
      //typedef boost::lagged_fibonacci44497           base_generator_type;
      //typedef boost::taus88           base_generator_type;
      //
      typedef boost::uniform_int<>     dist_type;
      typedef boost::variate_generator<base_generator_type&, dist_type> gen_type;

      PBgenerator();
      PBgenerator( const PBgenerator & );
      PBgenerator& operator=( const PBgenerator& rhs );
      PBgenerator( base_generator_type *generator );
      PBgenerator( base_generator_type &generator );
      PBgenerator( int nCount, int pCount, int nMax, int pMax );

      PBnumbers Generate();

      void ReSeed();
      void ReSeed(int seed);
      void ReSeed(unsigned int seed);

   private:
      int nMax;
      int nCount;
      int pMax;
      int pCount;

      boost::mutex mtx_;

      dist_type nDist;
      dist_type pDist;
      base_generator_type generator;
};

#endif
