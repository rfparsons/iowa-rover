# Rover_motor_test_clean

This sketch detects when the rover encounters an obstacle and reverses its motion.

## overview

This sketch uses the output of the INA219 curent sensosr to determine 
when the rover's forward motion has been impeded.  Current sensor is
in the path between the 5V supply and the H-bridge.  When a predetermined 
current limit is reached the rover backs away from the obstacle and  
preforms a 180 deg rotation.  This activity is repeated each time that
an obstacle is encountered.

This sketch can be used to evaluate deterioration of a rover's gear motors
after extended use.  The serial output can provide a measure of the no-load 
current draw of the motors at various points in the life of the motors.

The on-board potentiometer determines how far a full turn is. The maximum turn time is 3000 ms, and the trimpot can be adjusted to
set the turn time to anywhere from 1000 ms to 2000 ms.

written by Owen Grossman - April 2024


## files

  * `README.md`: the file you're currently reading c:
  * `Rover_motor_test_clean.ino`: the main sketch file, and where all of the logic happens
  * `motor.h`: H-bridge motor controller class
  * `pins.h`: constants mapping pins to peripherals
  * `signal_proc.h`: implements rolling buffers of variable length and finds their average, minimun and maximum