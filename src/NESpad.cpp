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

    _aState = _a;
    _a = false;
    _bState = _b;
    _b = false;
    _upState = _up;
    _up = false;
    _downState = _down;
    _down = false;
    _leftState = _left;
    _left = false;
    _rightState = _right;
    _right = false;
    _startState = _start;
    _start = false;
    _selectState = _select;
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

#pragma region Button States
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
#pragma endregion

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

#pragma region Convenience Methods
void Controller::printInputTable()
{
    if (hasInput())
    {
        Serial.println("---------------");
        Serial.println("A|B|-|+|U|D|L|R");
        Serial.print(isPressed(BTN_A) ? 1 : 0);
        Serial.print("|");
        Serial.print(isPressed(BTN_B) ? 1 : 0);
        Serial.print("|");
        Serial.print(isPressed(BTN_SELECT) ? 1 : 0);
        Serial.print("|");
        Serial.print(isPressed(BTN_START) ? 1 : 0);
        Serial.print("|");
        Serial.print(isPressed(BTN_UP) ? 1 : 0);
        Serial.print("|");
        Serial.print(isPressed(BTN_DOWN) ? 1 : 0);
        Serial.print("|");
        Serial.print(isPressed(BTN_LEFT) ? 1 : 0);
        Serial.print("|");
        Serial.println(isPressed(BTN_RIGHT) ? 1 : 0);
        Serial.println("---------------");
    }
}
#pragma endregion