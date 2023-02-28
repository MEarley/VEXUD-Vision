#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
/*vex-vision-config:begin*/
signature Vision10__BLUEROLLER = signature (1, -1561, 575, -493, 713, 5909, 3311, 0.9, 0);
signature Vision10__GREENBOX = signature (2, 0, 0, 0, 0, 0, 0, 3, 0);
signature Vision10__REDROLLER = signature (3, 1213, 10825, 6019, -1549, -555, -1052, 0.8, 0);
signature Vision10__YELLOWDISK = signature (4, 1811, 2283, 2047, -4085, -3707, -3896, 3, 0);
vision Vision10 = vision (PORT10, 28, Vision10__BLUEROLLER, Vision10__GREENBOX, Vision10__REDROLLER, Vision10__YELLOWDISK);
/*vex-vision-config:end*/

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}