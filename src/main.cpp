// Author: Riley Raschke
// © 2016 rrappsdev.com
// DWTFYW Licensce - Just mention me
//

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <thread>

#include <boost/program_options.hpp>
#include <boost/timer/timer.hpp>

#include <PBnumbers.h>
#include <PBgenerator.h>
#include <BigInt.h>

namespace po = boost::program_options;

using namespace std;

void RunMonteCarlo(
      PBgenerator* gen,
      const vector<PBnumbers>& myLines,
      string threadName,
      int* drawCnt,
      PBnumbers* matchedNums,
      bool reseedFlag
   ){

   boost::timer::cpu_timer t;
   boost::timer::cpu_times times;
   PBnumbers result;
   cout << threadName << " Checking Numbers\n";
   *drawCnt=1;
   t.start();
   do {
      if( *drawCnt % 1000000 == 0 ){
         times = t.elapsed();
         cout << threadName
            << " " << setw(11) << *drawCnt
            << " drawings occured. Last one million in " << boost::timer::format(times, 3, "%w") << " wall clock seconds\n";
            t.start();
         if( reseedFlag ) {
            gen->ReSeed();
         }
      }
      result = gen->Generate();
      ++*drawCnt;
   } while( ! result.in(myLines) );
   *matchedNums = result;

   cout << threadName << " Match found on drawing number " << *drawCnt << " !!WINNER!! " << result << "\n";
}

int main( int argc, char** argv ) {

   int lineCount = 10;
   int nCount = 5;
   int pCount = 1;
   int nMax = 69;
   int pMax = 26;
   int threadCount = 2;
   bool multiGen = false;
   bool reseed = false;

   /**
    * Get Args
    */
   po::options_description desc("Allowed options");

   desc.add_options()
      ("help,h", "produce this message")
      ("lines,l", po::value<int>(), "Lines to play")
      ("nCount,nc", po::value<int>(), "Number of regular balls")
      ("pCount,pc", po::value<int>(), "Number of power balls")
      ("nMax", po::value<int>(), "Max value of the regular ball(s)")
      ("pMax", po::value<int>(), "Max value of the power ball(s)")
      ("threads,t", po::value<int>(), "Number of threads to create")
      ("generator,g", "Use a unique generator for each thread. (Faster, no generator mutex lock wait), potentially less random")
      ("reseed,r", "NOTE: Requires -g ; Reseed Every 1 million drawings per thread, each thread is idealy offset by 3.14 seconds; potentially less random even more");

   try {
      po::variables_map vm;
      po::store(po::parse_command_line(argc, argv, desc), vm);
      po::notify(vm);
      if( vm.count("help")    ){ cout << desc << "\n"; return 1;        }
      if( vm.count("lines")   ){ lineCount   = vm["lines"].as<int>();   }
      if( vm.count("nCount")  ){ nCount      = vm["nCount"].as<int>();  }
      if( vm.count("pCount")  ){ pCount      = vm["pCount"].as<int>();  }
      if( vm.count("nMax")    ){ nMax        = vm["nMax"].as<int>();    }
      if( vm.count("pMax")    ){ pMax        = vm["pMax"].as<int>();    }
      if( vm.count("threads") ){ threadCount = vm["threads"].as<int>(); }
      if( vm.count("reseed")  ){ reseed = true; }
      if( vm.count("generator") ){ multiGen = true; }
   } catch (int e){
      cout << desc << "\n";
      return 1;
   }

   if( reseed && ! multiGen ){
      cout << desc << "\n";
      return 1;
   }

   // Print runtime info
   cout << "Playing " << lineCount << " lines against " << threadCount << " threads with\n" <<
      nCount << " regular ball(s) and a max value of: " << nMax << "\n" <<
      pCount << " power ball(s) and a max value of: "   << pMax << "\n";

   vector<thread>    threads;
   vector<PBnumbers> myLines;
   PBgenerator lottery( nCount, pCount, nMax, pMax );

   // Generate and print the players lines
   int  i = 1;
   char line[64];
   for(i = 0; i < lineCount; ++i){
      myLines.push_back( lottery.Generate() );
      sprintf( line, "Line %8d: %s\n",i+1, &(myLines[i].toString()[0]) );
      cout << line ;
   }

   // Storage for each threads return value
   int          drawings[threadCount];
   PBnumbers    matches[threadCount];
   PBgenerator generators[threadCount];

   // Kick off all the threads
   for( i = 0; i < threadCount; ++i){
      sprintf( line, "Thread #%-3d ", i+1);
      string x = line;
      drawings[i] = 0;
      usleep(10000); // stagger thread starts
      if( multiGen ){
         usleep(3141592); // Allow time for new seed PI seconds ;)
         generators[i] = lottery;
         generators[i].ReSeed(); // Remove this and results will be the same for every thread!!! (not desired)
         threads.push_back( std::thread( &RunMonteCarlo, &generators[i], myLines, x, &drawings[i], &matches[i], reseed) );
      } else {
         threads.push_back( std::thread( &RunMonteCarlo, &lottery, myLines, x, &drawings[i], &matches[i], reseed) );
      }
   }

   // Wait for all threads to finish
   for( i = 0; i < threadCount; ++i){
      threads[i].join();
   }

   // summarize drawings and calculate average
   BigInt sum = 0;
   for( i = 0; i < threadCount; ++i){
      sum = sum + drawings[i];
      sprintf( line, "Thread #%-3d took %11d drawings to match: %s\n", i+1, drawings[i], &(matches[i].toString()[0]) );
      string resultInfo = line;
      cout << resultInfo;
   }

   cout << "Avg: " << sum / threadCount << "\n";

   // Show the plays lines again
   cout << "You're lines again:\n";
   for(i = 0; i < lineCount; ++i){
      sprintf( line, "Line %8d: %s\n",i+1, &(myLines[i].toString()[0]) );
      cout << line ;
   }

   return 0;
}

