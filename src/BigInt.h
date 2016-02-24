// Riley Raschke

#ifndef BigInt_h
#define BigInt_h

#include <iostream>
#include <string>
#include <deque>
#include <vector>

using namespace std;

typedef enum {NEGATIVE, ZERO, POSITIVE} Sign;

class BigInt
{
   friend ostream& operator<<( ostream& output, const BigInt& );
   friend istream& operator>>( istream& input, BigInt& );
public:
   BigInt();                                        // constructor; digits = 0
   BigInt( int num );                               // constructor; digits = num
   BigInt( const string str );                      // constructor; digits = str
   BigInt( const BigInt& other );                   // copy constructor

   bool    operator==( const BigInt& rhs ) const;   // Equality
   bool    operator< ( const BigInt& rhs ) const;   // Less Than

   BigInt  operator+ ( const BigInt& rhs ) const;   // Addition
   BigInt  operator- ( const BigInt& rhs ) const;   // Subtraction
   BigInt  operator* ( char digit ) const;          // Multiplication by digit
                                                    // '0' <= digit <= '9'
   BigInt  operator* ( const BigInt& rhs ) const;   // Multiplication
   BigInt  operator/ ( const BigInt& rhs ) const;   // Division
   BigInt  operator% ( const BigInt& rhs ) const;   // Modulus
   BigInt  operator^ ( const int power ) const;     // Exponent

   BigInt Factorial() const;
   vector<BigInt> FibonacciSequence(const BigInt& n) const;
   vector<BigInt> FibonacciSequence(const BigInt& startSeries, const BigInt& endSeries) const;
   BigInt Square() const;
   BigInt Cube() const;

private:
   Sign sign;
   deque<char> digits;
};

#endif

