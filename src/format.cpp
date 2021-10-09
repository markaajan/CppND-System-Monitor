#include <string>

#include "format.h"

using std::string;

// DONE: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    int sec = (int)seconds;
    int hh = 0, mm = 0, ss = 0;
    ss = sec % 60;
    sec -= ss;
    sec /= 60;
    mm = sec % 60;
    sec -= mm;
    hh = sec / 24;
    string ret = ((hh<10?"0" + std::to_string(hh):std::to_string(hh)) + ":" + (mm<10?"0" + std::to_string(mm):std::to_string(mm))+ ":" + (ss<10?"0" + std::to_string(ss):std::to_string(ss)));


    return (ret); 
}
