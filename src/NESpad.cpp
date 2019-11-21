#include <Arduino.h>
#include <NESpad.h>

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
    _latched = false;
}

void Controller::latch()
{
    digitalWrite(_latchPin, HIGH); // pulse the latch pin HIGH
    delayMicroseconds(12);         // wait the required 12 ms
    digitalWrite(_latchPin, LOW);  // drop the latch pin LOW again
    _latched = true;               // set the latched flag to true to indicate we are reading the register

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

    if (_delayLength > 0)
    {
        delay(_delayLength);
    }
    _latched = false;
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

bool Controller::isPressed(int button)
{
    if (button == BTN_A)
        return _a;
    if (button == BTN_B)
        return _b;
    if (button == BTN_SELECT)
        return _select;
    if (button == BTN_START)
        return _start;
    if (button == BTN_UP)
        return _up;
    if (button == BTN_DOWN)
        return _down;
    if (button == BTN_LEFT)
        return _left;
    if (button == BTN_RIGHT)
        return _right;
}

bool Controller::hasInput()
{
    return _a || _b || _start || _select || _up || _down || _left || _right;
}

void Controller::update()
{
    if (!_latched)
    {
        latch();
    }
}

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