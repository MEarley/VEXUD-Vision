// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Vision10             vision        10              
// ---- END VEXCODE CONFIGURED DEVICES ----
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Nicholas DiGirolamo                                       */
/*    Created:      Thursday, February 16, 2023                               */
/*    Description:  UDVEX Team 2 Competition Code                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// const gearSetting RED_GEAR_CART = ratio36_1;
const gearSetting GREEN_GEAR_CART = ratio18_1;
// const gearSetting BLUE_GEAR_CART = ratio6_1;

competition compete;
brain my_brain;

// Vision Sensor Prototypes and other settings
#define VISIONRANGEX 315
#define VISIONRANGEY 211

event checkRed = event();
event checkBlue = event();
event checkGreen = event();

void hasBlueCallback();
void hasRedCallback();
void hasGreenCallback();
// End of Vision Sensor Prototypes

controller primary_controller = controller(primary);

motor intake = motor(PORT1, GREEN_GEAR_CART, false);

motor roller = motor(PORT3, GREEN_GEAR_CART, false);

motor launcher = motor(PORT2, GREEN_GEAR_CART, false);

motor stringLauncher = motor(PORT6, GREEN_GEAR_CART, false);


motor rear_left_motor = motor(PORT11, GREEN_GEAR_CART, false);
motor front_left_motor = motor(PORT12, GREEN_GEAR_CART, false);
motor_group left_motor_group = motor_group(rear_left_motor, front_left_motor);

motor rear_right_motor = motor(PORT19, GREEN_GEAR_CART, true);
motor front_right_motor = motor(PORT20, GREEN_GEAR_CART, true);
motor_group right_motor_group = motor_group(rear_right_motor, front_right_motor);

double wheel_travel = 3.25;       // Circumference of the wheel.
double track_width = 12.0;        // Distance between the left and right wheels.
double wheel_base = 10.0;         // Distance between wheels on the same side.
double external_gear_ratio = 1.0; // Gear ratio.
drivetrain drive_train = drivetrain(
  left_motor_group,
  right_motor_group,
  wheel_travel,
  track_width,
  wheel_base,
  distanceUnits::in,
  external_gear_ratio
);

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  my_brain.Screen.print("Pre-Autonomous start!");
  my_brain.Screen.newLine();

  stringLauncher.setBrake(hold);

  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // Vision Sensor Configuration (ADDED)

  checkBlue(hasBlueCallback);
  checkRed(hasRedCallback);
  checkGreen(hasGreenCallback);
  /*
  while (true) {
    checkBlue.broadcastAndWait();
    checkRed.broadcastAndWait();
    checkGreen.broadcastAndWait();
    wait(20, msec);
  }*/

  // End of Vision Sensor Configuration

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  my_brain.Screen.print("Pre-Autonomous complete.");
  my_brain.Screen.newLine();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  my_brain.Screen.print("Autonomous start!");
  my_brain.Screen.newLine();
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  my_brain.Screen.print("Autonomous complete.");
  my_brain.Screen.newLine();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  my_brain.Screen.print("User Control start!");
  my_brain.Screen.newLine();

  bool is_intake_stopped = true;
  bool is_launcher_stopped = true;
  bool is_roller_stopped = true;
  bool is_left_stopped = true;
  bool is_right_stopped = true;
  bool is_string_launched = false;

  float stringDegrees;

  //intake.setVelocity(100, percent); Changed to Voltage
  

  while (true) {

    // Intake control
    if (primary_controller.ButtonL1.pressing()) {
      //intake.spin(forward);
      intake.spin(fwd,12.0,voltageUnits::volt);
      is_intake_stopped = false;
    } else if (primary_controller.ButtonL2.pressing()) {
      //intake.spin(reverse);
      intake.spin(reverse,12.0,voltageUnits::volt);
      is_intake_stopped = false;
    } else {
      intake.stop();
      is_intake_stopped = true;
    }

    // Launcher control
    if (primary_controller.ButtonA.pressing()) {
      //launcher.setVelocity(75, percent);
      //launcher.spin(forward);
      launcher.spin(fwd,12.0 * .75,voltageUnits::volt);
      is_launcher_stopped = false;
    } else if (primary_controller.ButtonX.pressing()) {
      //launcher.setVelocity(100, percent);
      //launcher.spin(forward);
      launcher.spin(fwd,12.0,voltageUnits::volt);
      is_launcher_stopped = false;
    } else if (primary_controller.ButtonB.pressing()) {
      launcher.stop();
      is_launcher_stopped = true;
    }

    // Left drive train control
    int left_drive_speed = primary_controller.Axis3.position();
    if (5 < abs(left_drive_speed)) {
      left_motor_group.setVelocity(left_drive_speed, percent);
      left_motor_group.spin(forward);
      is_left_stopped = false;
    } else if (!is_left_stopped) {
      left_motor_group.stop();
      is_left_stopped = true;
    }

    // Right drive train control
    int right_drive_speed = primary_controller.Axis2.position();
    if (5 < abs(right_drive_speed)) {
      right_motor_group.setVelocity(right_drive_speed, percent);
      right_motor_group.spin(forward);
      is_right_stopped = false;
    } else if (!is_right_stopped) {
      right_motor_group.stop();
      is_right_stopped = true;
    }

    // Roller Control
    if (primary_controller.ButtonR1.pressing()) {
      //roller.spin(forward);
      roller.spin(fwd,6.0,voltageUnits::volt);
      is_roller_stopped = false;
    } else if (primary_controller.ButtonR2.pressing()) {
      //roller.spin(reverse);
      roller.spin(reverse,6.0,voltageUnits::volt);
      is_roller_stopped = false;
    } else {
      roller.stop();
      is_roller_stopped = true;
    }

    // String Launcher Controls
    
    if (primary_controller.ButtonUp.pressing() && primary_controller.ButtonDown.pressing()) {
      //stringDegrees = stringLauncher.position(degrees);
      stringLauncher.spin(fwd,12.0,voltageUnits::volt);
      //stringLauncher.spinToPosition(stringDegrees + 60,rotationUnits::deg,true);
      is_string_launched = true;
      wait(1,sec);
      stringLauncher.stop();
    } 
    else if(is_string_launched){
      //stringLauncher.spinToPosition(stringDegrees - 60,rotationUnits::deg,false);
    }

    checkBlue.broadcastAndWait();
    checkRed.broadcastAndWait();
    checkGreen.broadcastAndWait();

    wait(20, msec);
  }
  my_brain.Screen.print("User Control complete.");
  my_brain.Screen.newLine();
}

// Vision Sensor Function Definitions (ADDED)

void hasBlueCallback() {
  Brain.Screen.setFont(mono40);
  Brain.Screen.clearLine(1, black);
  Brain.Screen.setCursor(Brain.Screen.row(), 1);
  Brain.Screen.setCursor(1, 1);
  Vision10.takeSnapshot(Vision10__BLUEROLLER);
  if (Vision10.objectCount > 0) {
    Brain.Screen.print("Blue Roller Found");
  } else {
    Brain.Screen.print("No Blue Roller");
  }
}

void hasRedCallback() {
  Brain.Screen.setFont(mono40);
  Brain.Screen.clearLine(3, black);
  Brain.Screen.setCursor(Brain.Screen.row(), 1);
  Brain.Screen.setCursor(3, 1);
  Vision10.takeSnapshot(Vision10__REDROLLER);
  if (Vision10.objectCount > 0) {
    Brain.Screen.print("Red Roller Found");
  } else {
    Brain.Screen.print("No Red Roller");
  }
}

void hasGreenCallback() {
  //Brain.Screen.setFont(mono40);
  //Brain.Screen.clearLine(5, black);
  //Brain.Screen.setCursor(Brain.Screen.row(), 1);
  //Brain.Screen.setCursor(5, 1);
  Vision10.takeSnapshot(Vision10__GREENBOX);
  if (Vision10.objectCount > 0) {
    //Brain.Screen.print("Green Object Found");
  } else {
    //Brain.Screen.print("No Green Object");
  }
}

// Called Whenever a Yellow Object is detected
void hasYellowCallback() {
  Brain.Screen.setFont(mono40);
  Brain.Screen.clearLine(5, black);
  Brain.Screen.setCursor(Brain.Screen.row(), 1);
  Brain.Screen.setCursor(5, 1);
  Vision10.takeSnapshot(Vision10__YELLOWDISK);
  if (Vision10.objectCount > 0) {
    Brain.Screen.print("Yellow Disk Found");
    while(Vision10.objects[0].exists && primary_controller.ButtonY.pressing()){
      if(Vision10.objects[0].centerX >= (int)((VISIONRANGEX/2) + 10) && Vision10.objects[0].centerX <= (int)((VISIONRANGEX/2) - 10)){
        right_motor_group.setVelocity(50, percent);
        right_motor_group.spin(forward);
        left_motor_group.setVelocity(50, percent);
        left_motor_group.spin(forward);
      }
      else if(Vision10.objects[0].centerX > (int)(VISIONRANGEX/2)){
        right_motor_group.setVelocity(50, percent);
        right_motor_group.spin(forward);
        left_motor_group.setVelocity(50, percent);
        left_motor_group.spin(reverse);
      }
      else if(Vision10.objects[0].centerX < (int)(VISIONRANGEX/2)){
        right_motor_group.setVelocity(50, percent);
        right_motor_group.spin(reverse);
        left_motor_group.setVelocity(50, percent);
        left_motor_group.spin(forward);
      } else {
        //right_motor_group.stop();
        //left_motor_group.stop();
        /*right_motor_group.setVelocity(75, percent);
        right_motor_group.spin(reverse);
        left_motor_group.setVelocity(75, percent);
        left_motor_group.spin(forward);*/
      }

    }
  } else {
    Brain.Screen.print("No Yellow Disk Found");
  }
}

// End of Vision Function Definitions

//
// Main will set up the competition functions and callbacks.
//
int main() {
  my_brain.Screen.print("Main start!");
  my_brain.Screen.newLine();
  // Set up callbacks for autonomous and driver control periods.
  compete.autonomous(autonomous);
  compete.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  // This was in the competition template. Is this really best practice?
  while (true) {
    wait(100, msec);
  }
  my_brain.Screen.print("Main complete.");
  my_brain.Screen.newLine();
}
