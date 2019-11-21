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
    Controller(int clock, int latch, int data, int delayLength = 0);
    // NOTE: this will cause a 108 microsecond delay due to the NES controller specifications
    void update();
    // Returns true if the specified button is pressed
    bool isPressed(int button);
    // Returns true if any button is pressed
    bool hasInput();
    // Prints a table over Serial showing all button states
    void printInputTable();

private:
    void readState(int state);
    void latch(); //TODO remove delay
    int _latchPin;
    int _clockPin;
    int _dataPin;
    int _delayLength;
    bool _latched;
    bool _a;
    bool _b;
    bool _start;
    bool _select;
    bool _up;
    bool _down;
    bool _left;
    bool _right;
    bool _aState;
    bool _bState;
    bool _selectState;
    bool _startState;
    bool _upState;
    bool _downState;
    bool _leftState;
    bool _rightState;
};

#endif