// Riley Raschke
// Class::BigInt Implementation

#ifndef BigInt_h
#include "BigInt.h"
#endif

using namespace std;

template<typename T>
void Swap(T& , T& );

int FSAForInt(string);

template<typename T>
void Swap(T& first, T& second)
{
   T temp;

   temp = first;
   first = second;
   second = temp;
}

int FSAForInt(string s)
{
  int state = 0;
  string::iterator itr;

  for (itr = s.begin(); itr < s.end(); ++itr)
    switch (state)
    {
      case 0: if (isspace(*itr))
                state = 0;
              else if (*itr == '+' || *itr == '-')
                state = 1;
              else if (isdigit(*itr))
                state = 2;
              else
                state = 4;
              break;
      case 1: if (isdigit(*itr))
                state = 2;
              else
                state = 4;
              break;
      case 2: if (isdigit(*itr))
                state = 2;
              else if (isspace(*itr))
                state = 3;
              else
                state = 4;
              break;
      case 3: if (isspace(*itr))
                state = 3;
              else
                state = 4;
              break;
      case 4: ;
    }

  return state == 2 || state == 3;
}

istream& operator>>(istream& input, BigInt& num)
{
  string s;

  input >> s;
  num = BigInt(s);

  return input;
}

ostream& operator<<(ostream& output, const BigInt& num)
{
  deque<char>::const_reverse_iterator itr;

  if (num.sign == NEGATIVE)
    output << '-';

  for (itr = num.digits.rbegin(); itr != num.digits.rend(); ++itr)
    output << *itr;

  return output;
}

BigInt::BigInt()
{
   sign = ZERO;
   digits.push_front('0');
}

BigInt::BigInt( int num )
{
   if(num == 0)
   {
      digits.push_back((num+48));
      sign = ZERO;
   }
   else if(num > 0)
   {
      sign = POSITIVE;
   }
   else if(num < 0)
   {
      sign = NEGATIVE;
   }

   if(sign != ZERO)
   {
      if(sign == NEGATIVE)
         num *= -1;
      while(num != 0)
      {
         digits.push_back(((num%10)+48));
         num /= 10;
      }
   }
}

BigInt::BigInt(const string str)
{
   if(!FSAForInt(str))
   {
      sign = ZERO;
      digits.push_front('0');
   }
   else
   {
      string::const_iterator itr;
      sign = POSITIVE;
      for(itr = str.begin(); itr < str.end(); ++itr)
         if(isspace(*itr))
            continue;
         else if(isdigit(*itr))
            digits.push_front(*itr);
         else if(*itr == '-')
            sign = NEGATIVE;

      while(!digits.empty() && digits.back() == '0')
         digits.pop_back();

      if(digits.empty())
      {
         sign = ZERO;
         digits.push_front('0');
      }
   }
}

BigInt::BigInt(const BigInt& other)
{
   sign = other.sign;
   digits = other.digits;
}

bool BigInt::operator==( const BigInt& rhs ) const
{
   if(this->sign != rhs.sign)
      return false;

   if(this->digits.size() != rhs.digits.size())
      return false;

   return (this->digits == rhs.digits);
}

bool BigInt::operator< ( const BigInt& rhs ) const
{
   if(rhs==*this)
      return false;
   else if(this->sign != rhs.sign)
   {
      if(this->sign != NEGATIVE && rhs.sign != POSITIVE)
         return false;
      else if(this->sign != POSITIVE  && rhs.sign != NEGATIVE)
         return true;
   }
   else if(this->sign != NEGATIVE)
   {
      if(this->digits.size() > rhs.digits.size())
         return false;
      else if(this->digits.size() < rhs.digits.size())
         return true;
   }
   else
   {
      if(this->digits.size() < rhs.digits.size())
         return false;
      else if(this->digits.size() > rhs.digits.size())
         return true;
   }

   deque<char> LHS(this->digits), RHS(rhs.digits);

   if(this->sign != NEGATIVE)
   {
      while(RHS.size() > 0)
      {
         if(LHS.back() < RHS.back())
            return true;

         if(LHS.back() > RHS.back())
            return false;

         RHS.pop_back();
         LHS.pop_back();
      }
   }
   else
   {
      while(RHS.size() > 0)
      {
         if(LHS.back() > RHS.back())
            return true;

         if(LHS.front() < RHS.front())

            return false;

         RHS.pop_back();
         LHS.pop_back();
      }
   }

   cerr << "\n\nI messed up. Result Invalid\n\n";
   return false;
}

BigInt  BigInt::operator+ (const BigInt& copyRight) const
{
   BigInt LHS(*this), RHS(copyRight), Answer;

   if(LHS.sign == POSITIVE && RHS.sign == POSITIVE)       // Positive+Positive
   {
      Answer.sign = POSITIVE;
      deque<char> leftover;
      int carry = 0, a, b;

      while(!LHS.digits.empty() && !RHS.digits.empty())    // Add untill one is empty
      {
         a=LHS.digits.front()-48;
         b=RHS.digits.front()-48;
         a+=carry;                         // account for carry
         a+=b;                            // add
         Answer.digits.push_back((a%10)+48);    // store
         carry = a/10;                      // store carry
         LHS.digits.pop_front();
         RHS.digits.pop_front();
      }

      if(!LHS.digits.empty())      // determine whats left
         leftover = LHS.digits;
      else if(!RHS.digits.empty())
         leftover = RHS.digits;

      while(!leftover.empty())   // Add ramaining digits; account for possible carry.
      {
         a = leftover.front();
         if(carry == 0)
            Answer.digits.push_back(a);   // store
         else
         {
            a += carry;                         // account for carry
            Answer.digits.push_back(((a-48)%10)+48);    // store
            carry = (a-48)/10;                      // store carry
         }
         leftover.pop_front();
      }

      if(carry > 0)                   // If there is still a carry, add it.
         Answer.digits.push_back(carry+48);

      Answer.digits.pop_front();         // clear origianl 0 value
      while(Answer.digits.back() == '0')    // Clear Leading 0's
         Answer.digits.pop_back();

      return Answer;
   }
   else if(LHS.sign == POSITIVE && RHS.sign == NEGATIVE) // Positive+Negative
   {
      int carry = 0, a, b;
      RHS.sign = POSITIVE;    // flip sign for comparsion

      if(LHS==RHS)         // See if Answer will be 0;
      {
         Answer.sign = ZERO;
         return Answer;
      }
      else if(LHS < RHS)       // determine sign
      {
         Swap(LHS,RHS);      // swap values as needed to continue
         Answer.sign = NEGATIVE;
      }
      else
      {
         Answer.sign = POSITIVE;
      }

      while(!RHS.digits.empty())   // Untill the Right side is empty
      {
         a=LHS.digits.front()-48;
         b=RHS.digits.front()-48;
         a+=carry;       // check for a borrow
         if(a-b < 0)      // check if carry is needed
         {
            a+=10;
            a-=b;       // subtract
            carry = -1; // store carry
         }
         else
         {
            a-=b;      // subtract
            carry = 0;    // store carry
         }

         if(a==10) --a;   // In case A was 0 and was forced to borrow left when b = 0 also
         Answer.digits.push_back(a+48);   //store
         LHS.digits.pop_front();
         RHS.digits.pop_front();
      }

      while(!LHS.digits.empty())
      {
         a=LHS.digits.front()-48;
         a+=carry; // account for carry
         if(a < 0) // continue carry if needed.
         {
            carry = -1;
            a=9;
         }
         else
            carry = 0;

         Answer.digits.push_back(a+48); // store whats left on the LHS
         LHS.digits.pop_front();
      }

      Answer.digits.pop_front();          // clear origianl 0 value
      while(Answer.digits.back() == '0')    // clear leading 0's
         Answer.digits.pop_back();

      return Answer;
   }
   else if(LHS.sign == NEGATIVE && RHS.sign == NEGATIVE) // Negative+Negative
   {
      LHS.sign = POSITIVE;
      RHS.sign = POSITIVE;
      Answer = LHS+RHS;          // recurse as double positive
      Answer.sign = NEGATIVE;    // flip the sign
      return Answer;
   }
   else if(LHS.sign == NEGATIVE && RHS.sign == POSITIVE) // Negative+Positive
   {
      Answer = RHS+LHS;    // Flip the equation, Recurse back to operator +(-x)
      return Answer;
   }
   else if(LHS.sign == ZERO)
      return RHS;
   else                // The right hand side must be zero at this point
      return LHS;
}

BigInt  BigInt::operator- (const BigInt& copyRight) const
{
   BigInt LHS(*this), RHS(copyRight);

   if(RHS.sign == POSITIVE)
   {
      RHS.sign = NEGATIVE;
      return (*this + RHS);
   }
   else if(RHS.sign == NEGATIVE)
   {
      RHS.sign = POSITIVE;
      return (*this + RHS);
   }
   else
      return LHS;
}

BigInt BigInt::operator* (char digit) const  // Multiplication by digit [0,9]
{
   BigInt lhs(*this), ans(0);
   int Carry = 0, A, B=digit-48;

   int * carry = &Carry;
   int * a = &A;
   int * b = &B;

   if(*b == 0)                // Set the Sign
      return ans;
   else
      ans.sign = lhs.sign;

   while(!lhs.digits.empty()) // Multiply individually, carry as needed.
   {
      *a=(lhs.digits.front()-48);
      *a *= *b;
      *a += *carry;
      ans.digits.push_back((*a % 10)+48);
      *carry = *a/10;
      lhs.digits.pop_front();
   }

   if(*carry > 0)            // Store Additional carry;
      ans.digits.push_back(*carry+48);

   ans.digits.pop_front();   // clear original 0 value
   return ans;
}

BigInt BigInt::operator* (const BigInt& RightSide) const // BigInt*BigInt
{
   BigInt LHS(*this), RHS(RightSide), Answer(0);
   vector<BigInt> AddMe;    // Vector of Partial Multiples, Elementary BigNumber Multipication style
   vector<BigInt>::iterator itr, end;
   Sign SaveSign = ZERO;
   int I, J, B;

   BigInt * lhs = &LHS;
   BigInt * rhs = &RHS;
   BigInt * ans = &Answer;
   int * i = &I, *j = &J, *b = &B;
   Sign * savedSign = &SaveSign;

   if(lhs->sign == ZERO || rhs->sign == ZERO)
   {
      return *ans;
   }
   else if(lhs->sign == NEGATIVE && rhs->sign == NEGATIVE) // Set the sign
   {
      lhs->sign = POSITIVE;
      rhs->sign = POSITIVE;
      return *lhs * *rhs; // Recurse as a Positive*Positive
   }
   else if(lhs->sign == rhs->sign)
      *savedSign = POSITIVE;
   else
   {
      *savedSign = NEGATIVE;
      lhs->sign = POSITIVE;
      rhs->sign = POSITIVE;
   }

   if(*lhs < *rhs) // Put the lengthy BigInt on the Left
      Swap(*lhs,*rhs);

   for(*i = 0; !rhs->digits.empty(); ++*i, rhs->digits.pop_front())
   {
      *b = RHS.digits.front();
      AddMe.push_back((*lhs * *b));

      if(AddMe.back().sign != ZERO)    // If the multiple is not 0
      {
         for(*j = 0; *j < *i; ++*j)       // Insert 0's or *10 until number starts at correct decimal position
            AddMe.back().digits.push_front('0');
      }
   }

   end = AddMe.end();    // Save end location for the following loop
   for(itr = AddMe.begin(); itr < end; ++itr) // Total the contents of AddMe
   {
      *ans = *ans + *itr;
   }

   ans->sign = SaveSign; // Set the Saved Sign
   return *ans;
}

BigInt  BigInt::operator/ ( const BigInt& rhs ) const
{
   BigInt
      Answer,
      Copy(*this),
      Jump(1),
      LHS(*this),
      RHS(rhs),
      Uno(1),
      Temp1,
      Temp2,
      Temp3;

   BigInt
      *thisCP = &Copy,
      *JumpPtr = &Jump,
      *Lptr = &LHS,
      *Rptr = &RHS,
      *One = &Uno,
      *Ans = &Answer,
      *temp1 = &Temp1,
      *temp2 = &Temp2,
      *temp3 = &Temp3;

   thisCP->sign = POSITIVE;
   Lptr->sign = POSITIVE;
   Rptr->sign = POSITIVE;

   int LHSsize = Lptr->digits.size();

   if((*Lptr == *Rptr) == false)
   {
      for(int i = 0; i < LHSsize; JumpPtr->digits.push_front('0'), ++i);

      while(JumpPtr->digits.size() > 0)
      {
         *temp3 = *JumpPtr * *Rptr;
         while( (*temp2 = ((*temp1 = *Ans+*JumpPtr) * *Rptr)) < *thisCP || *temp2 == *thisCP)
         {
            *Lptr = *Lptr - *temp3;
            *Ans = *temp1;
         }
         JumpPtr->digits.pop_front();
      }
   }
   else
   {
      *Ans = BigInt(1);
   }

   if((Lptr->sign == NEGATIVE && Rptr->sign == POSITIVE) || (Lptr->sign == POSITIVE && Rptr->sign == NEGATIVE))
      Ans->sign = NEGATIVE;

   return Answer;
}

BigInt  BigInt::operator% ( const BigInt& rhs ) const
{
   BigInt Ans;
   Ans = *this/rhs;
   return *this-(rhs*Ans);
}

BigInt  BigInt::operator^ ( const int power ) const
{
   BigInt Ans = *this;
   BigInt *ans = &Ans;
   int i = power - 1;
   if(power == 0)
      return BigInt(1);

   while(i > 0)
   {
      *ans = *this * *ans;
      --i;
   }
   return *ans;
}

BigInt BigInt::Factorial() const
{
   BigInt start(2), answer(1), One(1), End(*this);
   BigInt *sta = &start,
      *ans = &answer,
      *N = &End,
      *one = &One;
   *N = *N+1;

   while(*sta < *N)
   {
      *ans = *sta * *ans;
      *sta = *sta + *one;
   }

   return *ans;
}

vector<BigInt> BigInt::FibonacciSequence(const BigInt& n) const
{
   BigInt i(1), end(n), first(1), second(1), one(1);
   BigInt *I = &i,
      *End = &end,
      *First = &first,
      *Second = &second,
      *One = &one;
   vector<BigInt> Ans;

   while(*I < *End)
   {
      Ans.push_back(*First);
      *Second = *First + *Second;
      *First = *Second - *First;
      *I = *I + *One;
   }

   return Ans;
}

vector<BigInt> BigInt::FibonacciSequence(const BigInt& startSeries, const BigInt& endSeries) const
{
   BigInt i(1), end(endSeries), begin(startSeries), first(1), second(1), one(1);
   BigInt *I = &i,
      *End = &end,
      *First = &first,
      *Second = &second,
      *One = &one,
      *StartPush = &begin;
   vector<BigInt> Ans;
   Ans.clear();

   while(*I < *End)
   {
      if(*StartPush < *I || *StartPush == *I)
         Ans.push_back(*First);

      *Second = *First + *Second;
      *First = *Second - *First;
      *I = *I + *One;
   }

   return Ans;
}

BigInt BigInt::Square() const
{
   return *this**this;
}

BigInt BigInt::Cube() const
{
   return ((*this**this)**this);
}



