#include <NESpad.h>

Controller controller(2, 3, 4);

void showInputTable()
{
    if (controller.hasInput())
    {
        Serial.println("A|B|-|+|U|D|L|R");
        Serial.print(controller.isPressed(BTN_A) ? 1 : 0);
        Serial.print("|");
        Serial.print(controller.isPressed(BTN_B) ? 1 : 0);
        Serial.print("|");
        Serial.print(controller.isPressed(BTN_SELECT) ? 1 : 0);
        Serial.print("|");
        Serial.print(controller.isPressed(BTN_START) ? 1 : 0);
        Serial.print("|");
        Serial.print(controller.isPressed(BTN_UP) ? 1 : 0);
        Serial.print("|");
        Serial.print(controller.isPressed(BTN_DOWN) ? 1 : 0);
        Serial.print("|");
        Serial.print(controller.isPressed(BTN_LEFT) ? 1 : 0);
        Serial.print("|");
        Serial.println(controller.isPressed(BTN_RIGHT) ? 1 : 0);
    }
}

void setup()
{
    Serial.begin(9600);
    Serial.println("NESpad Input Test");
    Serial.println("A|B|-|+|U|D|L|R");
    Serial.println("- is SELECT and + is START");
}

void loop()
{
    controller.update();
    showInputTable();
}