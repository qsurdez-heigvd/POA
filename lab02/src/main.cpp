/**
 * @file Implementation of the main program
 *
 * @author Jallon Sarah
 * @author Surdez Quentin
*/

#include <iostream>
#include "src/ship/TIE/TIE.hpp"
#include "src/ship/TIE/TIEInterceptor.hpp"
#include "src/ship/cargo/StarDreadnought.hpp"
#include "src/ship/cargo/Shuttle.hpp"
#include "src/squadron/Squadron.hpp"
#include <vector>
#include <iostream>

using namespace std;

int main() {

   TIE blackLeader;
   blackLeader.setNickName("Black leader");
   TIE blackTwo;
   Shuttle shuttle(23.4);
   Squadron squad("Black Squadron");
   StarDreadnought star(34.5);
   squad += blackLeader;
   squad += blackTwo;
   squad += shuttle;
   squad += star;
   squad.setChief(blackLeader);
   cout << squad << endl;

}