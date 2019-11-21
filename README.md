# NESpad
A highly optimized NES Controller Library for Arduino

## Features
* Friendly names for shift register pins
* Provides function for checking button state
* Has an optional artificial delay
* Can provide support for cheat codes

## Getting started
The pins on the NES controller are numbered clockwise, starting from the top right.

![](extras/controller_pinout.png?raw=true)  

| NES Pin  | Arduino Pin |
| ------------- | ------------- |
| GND  | GND  |
| CLOCK  | 2  |
| STROBE  | 3  |
| DATA  | 4  |
| N/C  | No Connection  |
| N/C  | No Connection  |
| +5V  | 5V  |
```
// your other includes here
#include <NESpad.h>
// any other variables you have
Controller rapidFireController(2,3,4); // this controller's update method is 108μs
Controller controller(2,3,4,125); // this controller's update method is 125ms
// other unrelated functions
void loop()
{
  // it does not matter where in the loop you start calling the update functions
  rapidFireController.update();
  controller.update();
  // so long as you act on the states after calling update()
}
```
