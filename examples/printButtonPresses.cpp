#include <Arduino.h>
#include <NESpad.h>

Controller controller(2, 3, 4);

void readController()
{
    if (controller.isPressed(BTN_A))
    {
        Serial.println("A pressed");
    }

    if (controller.isPressed(BTN_B))
    {
        Serial.println("B pressed");
    }

    if (controller.isPressed(BTN_START))
    {
        Serial.println("START pressed");
    }

    if (controller.isPressed(BTN_SELECT))
    {
        Serial.println("SELECT pressed");
    }

    if (controller.isPressed(BTN_UP))
    {
        Serial.println("UP pressed");
    }
    else if (controller.isPressed(BTN_DOWN)) // Note the else: we will not accept two opposing directions at once
    {
        Serial.println("DOWN pressed");
    }

    if (controller.isPressed(BTN_LEFT))
    {
        Serial.println("LEFT pressed");
    }
    else if (controller.isPressed(BTN_RIGHT)) // Note the else: we will not accept two opposing directions at once
    {
        Serial.println("RIGHT pressed");
    }
}

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    controller.update();
    readController();
}