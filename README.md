# NESpad

A highly optimized NES Controller Library for Arduino

## Features

* Friendly names for shift register pins
* Provides function for checking button state
* Has an optional artificial delay
* Can provide support for cheat codes

## Getting started

The pins on the NES controller are numbered clockwise, starting from the top right.

![NES controller pinout](extras/controller_pinout.png?raw=true)  

| NES Pin       | Arduino Pin   |
| :-------------|-------------: |
| GND           | GND           |
| CLOCK         | 2             |
| STROBE        | 3             |
| DATA          | 4             |
| N/C           | No Connect    |
| N/C           | No Connect    |
| +5V           | 5V            |

```cpp
// include this near the top of your source file
#include <NESpad.h>
// create a Controller instance
Controller rapidFireController(2, 3, 4); // this controller's update method is 108μs due to NES specifications
Controller controller(2, 3, 4, 125);     // this controller's update method is 125ms due to artificial delay

void loop()
{
  // run myController.update() anywhere during the main loop
  rapidFireController.update();
  controller.update();
  // so long as you act on the states after calling update()
  controller.printInputTable();
}
```

## Tuning the artficial delay

I've found that 125ms is a pretty good delay if you want a really short input window between button presses being registered. As you increase this, you will start to see lag. Try to keep it to 500ms or less to prevent massive input lag. 250ms will allow most button presses to be registered, while not introducing too much of a delay in the update function.
