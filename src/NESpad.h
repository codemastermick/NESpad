#ifndef NESpad_h
#define NESpad_h

/* BEGIN BUTTON MAPPING
 * This is the order that the buttons enter the shift register
 * inside the NES controller. Also happens to be the bit positions
 * for a byte representation of all inputs
 */

#define BTN_A 0
#define BTN_B 1
#define BTN_SELECT 2
#define BTN_START 3
#define BTN_UP 4
#define BTN_DOWN 5
#define BTN_LEFT 6
#define BTN_RIGHT 7
// END BUTTON MAPPING

/** 
 * Controller(CLOCK, LATCH, DATA, DELAY=0);
 * The delay is optional, and allows you to artifically slow down controller readings when set.
 * The clock pin must be on an interrupt pin
 * Uno or Nano: 2 or 3
 * Mega: 2, 3, 18, 19, 20 or 21
 **/
class Controller
{
public:
    Controller(int clock, int latch, int data, int delayLength);
    // NOTE: this will cause a 108μs delay due to the NES controller specifications
    void update();
    // Returns true if the specified button is pressed
    bool isPressed(int button);
    // Returns true if the specified button was just released
    bool wasReleased(int button);
    // Returns true if the specified button is being held down
    bool isHeld(int button);
    // Returns true if any button is pressed
    bool hasInput();
    // Prints a table over Serial showing all button states
    void printInputTable();

private:
    void readState(int state);
    void latch();
    int _latchPin;      // Digital pin connected to the latch pin of the NES controller
    int _clockPin;      // Digital pin connected to the clock pin of the NES controller
    int _dataPin;       // Digital pin connected to the data pin of the NES controller
    int _delayLength;   // If greater then 0, delays the readings by X milliseconds
    bool _registerBusy; // If true, the register is busy outputting data
    bool _a;            // Current state of the A button
    bool _b;            // Current state of the B button
    bool _start;        // Current state of the START button
    bool _select;       // Current state of the SELECT button
    bool _up;           // Current state of the UP button
    bool _down;         // Current state of the DOWN button
    bool _left;         // Current state of the LEFT button
    bool _right;        // Current state of the RIGHT button
    bool _aState;       // Last reading of the A button
    bool _bState;       // Last reading of the B button
    bool _selectState;  // Last reading of the SELECT button
    bool _startState;   // Last reading of the START button
    bool _upState;      // Last reading of the UP button
    bool _downState;    // Last reading of the DOWN button
    bool _leftState;    // Last reading of the LEFT button
    bool _rightState;   // Last reading of the RIGHT button
};

#endif