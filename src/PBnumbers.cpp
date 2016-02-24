// Author: Riley Raschke
// © 2016 rrappsdev.com
// DWTFYW Licensce - Just mention me
//

#ifndef PBnumbers_h
#include "PBnumbers.h"
#endif

/**
 * PUBLIC
 */
PBnumbers::PBnumbers(){ }

PBnumbers::PBnumbers( const PBnumbers& other ){
   this->nNumsVect = other.nNumsVect;
   this->pNumsVect = other.pNumsVect;
}

PBnumbers::PBnumbers( PBnumbers&& other ){
   this->nNumsVect = other.nNumsVect;
   this->pNumsVect = other.pNumsVect;
}

PBnumbers& PBnumbers::operator=( const PBnumbers& other ){
   this->nNumsVect = other.nNumsVect;
   this->pNumsVect = other.pNumsVect;
   return *this;
}

PBnumbers& PBnumbers::operator=( PBnumbers&& other ){
   this->nNumsVect = other.nNumsVect;
   this->pNumsVect = other.pNumsVect;
   return *this;
}


/**
 * Custom Constructors
 */
PBnumbers::PBnumbers(const vector<int>& nNumsOther, const vector<int>& pNumsOther){
   this->nNumsVect = std::move(nNumsOther);
   this->pNumsVect = std::move(pNumsOther);
   std::sort( nNumsVect.begin(), nNumsVect.end() );
   std::sort( pNumsVect.begin(), pNumsVect.end() );
}
PBnumbers::PBnumbers(vector<int>&& nNumsOther, vector<int>&& pNumsOther){
   this->nNumsVect = std::move(nNumsOther);
   this->pNumsVect = std::move(pNumsOther);
   std::sort( nNumsVect.begin(), nNumsVect.end() );
   std::sort( pNumsVect.begin(), pNumsVect.end() );
}

PBnumbers::PBnumbers(int n1, int n2, int n3, int n4, int n5, int p1 ){
   nNumsVect.push_back(n1);
   nNumsVect.push_back(n2);
   nNumsVect.push_back(n3);
   nNumsVect.push_back(n4);
   nNumsVect.push_back(n5);
   pNumsVect.push_back(p1);
}


/**
 * Functions
 */

bool PBnumbers::isEqual( const PBnumbers& rhs ) const {
   return this->operator==(rhs);
}

bool PBnumbers::in( const vector<PBnumbers>& set ) const {
   vector<PBnumbers>::const_iterator itr, end;
   end = set.end();
   for(itr = set.begin(); itr < end; ++itr){
      if( this->operator==( *itr ) ){
         return true;
      }
   }
   return false;
}

string PBnumbers::toString() const {
   string numbers = "";
   char buffer[64];
   char *pos = buffer;
   vector<int>::const_iterator itr;
   vector<int>::const_iterator end = nNumsVect.end();
   for( itr = nNumsVect.begin(); itr < end; ++itr){
      sprintf( pos, " %2d", *itr);;
      numbers += pos;
   }
   numbers += " P";
   end = pNumsVect.end();
   for( itr = pNumsVect.begin(); itr < end; ++itr){
      sprintf( pos, " %2d", *itr);;
      numbers += pos;
   }
   return numbers;
}


/**
 * Operators
 */
bool PBnumbers::operator==( const PBnumbers& rhs ) const {
   vector<int>::const_iterator tItr;
   vector<int>::const_iterator tEnd = nNumsVect.end();
   vector<int>::const_iterator oItr = rhs.nNumsVect.begin();

   for(tItr = this->nNumsVect.begin(); tItr < tEnd; ++tItr){
      if( *tItr != *oItr ){
         return false;
      }
      ++oItr;
   }

   tEnd = this->pNumsVect.end();
   oItr = rhs.pNumsVect.begin();

   for(tItr = this->pNumsVect.begin(); tItr < tEnd; ++tItr){
      if( *tItr != *oItr ){
         return false;
      }
      ++oItr;
   }

   return true;
}


/**
 * Friends
 */
ostream& operator<<( ostream& output, const PBnumbers& nums){
   string s;
   output << nums.toString();
   return output;
}

istream& operator>>( istream& input, PBnumbers& nums){
   string s;
   input >> s;
   // TODO: parse input?
   nums = PBnumbers();
   return input;
}

