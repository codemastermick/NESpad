#include <Arduino.h>
#include <NESpad.h>

unsigned long debounceDelay = 108;  // length of time between readings, in microseconds
unsigned long lastDebounceTime = 0; // the last time the output pin was toggled

Controller::Controller(int clockPin, int latchPin, int dataPin, int delayLength = 0)
{
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, INPUT);
    digitalWrite(latchPin, LOW);

    _latchPin = latchPin;
    _clockPin = clockPin;
    _dataPin = dataPin;
    _delayLength = delayLength;
    _registerBusy = false;
}

void Controller::latch()
{
    digitalWrite(_latchPin, HIGH); // pulse the latch pin HIGH
    delayMicroseconds(12);         // wait the required 12 ms
    digitalWrite(_latchPin, LOW);  // drop the latch pin LOW again
    _registerBusy = true;          // set the latched flag to true to indicate we are reading the register
    rawData = 0xFF;

    _aState = _a;
    _bState = _b;
    _upState = _up;
    _downState = _down;
    _leftState = _left;
    _rightState = _right;
    _startState = _start;
    _selectState = _select;

    _a = false;
    _b = false;
    _up = false;
    _down = false;
    _left = false;
    _right = false;
    _start = false;
    _select = false;

    for (int i = 0; i < 8; i++)
    {
        readState(i);
        digitalWrite(_clockPin, HIGH);
        delayMicroseconds(6);
        digitalWrite(_clockPin, LOW);
        delayMicroseconds(6);
    }
    _registerBusy = false;

    if (_a)
    {
        bitClear(rawData, BTN_A);
    }
    if (_b)
    {
        bitClear(rawData, BTN_B);
    }
    if (_up)
    {
        bitClear(rawData, BTN_UP);
    }
    if (_down)
    {
        bitClear(rawData, BTN_DOWN);
    }
    if (_left)
    {
        bitClear(rawData, BTN_LEFT);
    }
    if (_right)
    {
        bitClear(rawData, BTN_RIGHT);
    }
    if (_select)
    {
        bitClear(rawData, BTN_SELECT);
    }
    if (_start)
    {
        bitClear(rawData, BTN_START);
    }
}

void Controller::readState(int pos)
{
    if (digitalRead(_dataPin) == LOW)
    {
        if (pos == BTN_A)
        {
            _a = true;
        }
        else if (pos == BTN_B)
        {
            _b = true;
        }
        else if (pos == BTN_SELECT)
        {
            _select = true;
        }
        else if (pos == BTN_START)
        {
            _start = true;
        }
        else if (pos == BTN_UP)
        {
            _up = true;
        }
        else if (pos == BTN_DOWN)
        {
            _down = true;
        }
        else if (pos == BTN_LEFT)
        {
            _left = true;
        }
        else if (pos == BTN_RIGHT)
        {
            _right = true;
        }
    }
}

// BEGIN Button States
bool Controller::isPressed(int button)
{
    switch (button)
    {
    case BTN_A:
        return !_aState && _a;
    case BTN_B:
        return !_bState && _b;
    case BTN_START:
        return !_startState && _start;
    case BTN_SELECT:
        return !_selectState && _select;
    case BTN_UP:
        return !_upState && _up;
    case BTN_DOWN:
        return !_downState && _down;
    case BTN_LEFT:
        return !_leftState && _left;
    case BTN_RIGHT:
        return !_rightState && _right;
    default:
        return false;
    }
}

bool Controller::isHeld(int button)
{
    switch (button)
    {
    case BTN_A:
        return _aState && _a;
    case BTN_B:
        return _bState && _b;
    case BTN_START:
        return _startState && _start;
    case BTN_SELECT:
        return _selectState && _select;
    case BTN_UP:
        return _upState && _up;
    case BTN_DOWN:
        return _downState && _down;
    case BTN_LEFT:
        return _leftState && _left;
    case BTN_RIGHT:
        return _rightState && _right;
    default:
        return false;
    }
}

bool Controller::wasReleased(int button)
{
    switch (button)
    {
    case BTN_A:
        return _aState && !_a;
    case BTN_B:
        return _bState && !_b;
    case BTN_START:
        return _startState && !_start;
    case BTN_SELECT:
        return _selectState && !_select;
    case BTN_UP:
        return _upState && !_up;
    case BTN_DOWN:
        return _downState && !_down;
    case BTN_LEFT:
        return _leftState && !_left;
    case BTN_RIGHT:
        return _rightState && !_right;
    default:
        return false;
    }
}
// END Button States

bool Controller::hasInput()
{
    return _a || _b || _start || _select || _up || _down || _left || _right;
}

void Controller::update()
{
    if (!_registerBusy)
    {
        latch();
        if (_delayLength > 0)
        {
            delay(_delayLength);
        }
    }
}

// BEGIN Convenience Methods
void Controller::printInputTable()
{
    byte currentBtn = 0;

    Serial.println("---------------");
    Serial.println("A|B|-|+|U|D|L|R");
    for (byte i = 0; i < 8; i++)
    {
        Serial.print(buttonStateAsChar(currentBtn));
        if (i < 7)
        {
            Serial.print("|");
        }
        currentBtn++;
    }
    Serial.println();
    Serial.println("---------------");
}

char Controller::buttonStateAsChar(int button)
{
    if (wasReleased(button))
    { // Write 3 if released
        return RELEASED;
    }
    else if (isHeld(button))
    { // Write 2 if held
        return HELD;
    }
    else if (isPressed(button))
    { // Write 1 if pressed
        return PRESSED;
    }

    if (!isPressed(button) && !isHeld(button) && !wasReleased(button))
    { // Write 0 if not held
        return NONE;
    }
}

void Controller::printRawData()
{
    for (byte i = 0; i < 8; i++)
    {
        Serial.print(bitRead(rawData, i));
    }
}
// END Convenience Methods