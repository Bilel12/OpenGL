#ifndef _TIMING_H
#define _TIMING_H

#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <complex>
#include <fstream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <vector>
#include <map>
#include <string>

// Import things we need from the standard library
using std::cout;
using std::endl;
using std::thread;
using std::mutex;
using std::lock;
using std::unique_lock;
using std::vector;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::microseconds;
using std::condition_variable;

enum GAMESTATE
{
	LOAD = 0,
	GAME = 1
};

__declspec(selectany) GAMESTATE game_state;

// Define the alias "the_clock" for the clock type we're going to use.
typedef std::chrono::steady_clock the_clock;

// selectany can be used in initializing global data defined by headers, 
// when the same header appears in more than one source file. 
// selectany can only be applied to the actual initialization of 
// global data items that are externally visible.
__declspec(selectany) std::map<std::string, __int64> time_map;

// Start timing
//the_clock::time_point start = the_clock::now();

// Stop timing
//the_clock::time_point end = the_clock::now();

// Compute the difference between the two times in milliseconds
//auto time_taken = duration_cast<milliseconds>(end - start).count();

// Display time taken
//cout << "Thread took " << time_taken << " ms." << endl;


#endif