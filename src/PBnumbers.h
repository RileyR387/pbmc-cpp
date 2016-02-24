// Author: Riley Raschke
// © 2016 rrappsdev.com
// DWTFYW Licensce - Just mention me
//

#ifndef PBnumbers_h
#define PBnumbers_h

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class PBnumbers
{
   friend ostream& operator<<( ostream&, const PBnumbers& );
   friend istream& operator>>( istream&, PBnumbers& );

   public:

      static const int INVALID_PB_NUMS_EXCEPTION = 10005;
      static const int INVALID_COMPARISON        = 10006;
      static const int DEFAULT_N_MAX   = 69;
      static const int DEFAULT_N_COUNT = 5;
      static const int DEFAULT_P_MAX   = 26;
      static const int DEFAULT_P_COUNT = 1;

      PBnumbers();
      PBnumbers( const PBnumbers& );
      PBnumbers( PBnumbers&& );
      PBnumbers& operator=( const PBnumbers& rhs );
      PBnumbers& operator=( PBnumbers&& rhs );

      PBnumbers(const vector<int>&, const vector<int>&  );
      PBnumbers(vector<int>&& , vector<int>&& );
      PBnumbers(int n1, int n2, int n3, int n4, int n5, int p1);

      string toString() const;
      bool   isEqual( const PBnumbers& rhs ) const;
      bool   in( const vector<PBnumbers>& set ) const;

      bool operator==( const PBnumbers& rhs ) const;

   private:
      vector<int> nNumsVect;
      vector<int> pNumsVect;
};

#endif
