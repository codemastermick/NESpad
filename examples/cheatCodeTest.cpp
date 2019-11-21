#include <Arduino.h>
#include <NESpad.h>

// Uncomment one of the following lines to enable or disable cheat codes
// Disabling cheat codes reduces the update delay to 108μs where enabling creates a 125ms delay

#define CHEAT_CODES_ENABLED   // Causes 125ms delay in the controller.update()
// #define CHEAT_CODES_DISABLED // Causes a 108μs delay in controller.update()
#ifdef CHEAT_CODES_ENABLED
int inputDelay = 125;                        // through experimenting, 125ms seems to be enough to allow accurate readings without creating too much delay in the code
int maxDelayBetweenButtons = inputDelay * 4; // Under the default 125ms delay, this allows for a 1 second gap between buttons
long lastInputTime = 0;                      // Last button press in a cheat code sequence
long currentInputTime = 0;                   // Current time in milliseconds, used to limit time between button pushes

int konamiCode[] = {0x4, 0x4, 0x5, 0x5, 0x6, 0x7, 0x6, 0x7, 0x1, 0x0, 0x3};
int konamiVar = 0;
int bloodCode[] = {0x0, 0x1, 0x0, 0x2, 0x0, 0x1, 0x1};
int bloodVar = 0;
Controller controller(2, 3, 4, inputDelay); // No artificial delay, allowing rapid response
#endif

#ifdef CHEAT_CODES_DISABLED
Controller controller(2, 3, 4); // 125ms delay to make cheat codes possible
#endif

void checkForKonamiCode()
{
    if (controller.hasInput())
    {
        if (controller.isPressed(konamiCode[konamiVar]))
        {
            lastInputTime = millis();
            konamiVar++;
        }
        else
        {
            lastInputTime = millis();
            konamiVar = 0;
        }

        if (konamiVar == 11)
        {
            Serial.println("Konami code entered succesfully!");
            lastInputTime = millis();
            konamiVar = 0;
        }
        Serial.print("Konami code progress:\t");
        Serial.println(konamiVar);
    }
}

void checkForBloodCode()
{
    if (controller.hasInput())
    {
        if (controller.isPressed(bloodCode[bloodVar]))
        {
            lastInputTime = millis();
            bloodVar++;
        }
        else
        {
            lastInputTime = millis();
            bloodVar = 0;
        }

        if (bloodVar == 7)
        {
            Serial.println("Blood code entered succesfully!");
            lastInputTime = millis();
            bloodVar = 0;
        }
        Serial.print("Blood code progress:\t");
        Serial.println(bloodVar);
    }
}

void setup()
{
    Serial.begin(9600);
    Serial.println("NESpad Test");
    Serial.println("A|B|-|+|U|D|L|R");
    Serial.println("- is SELECT and + is START");
}

void loop()
{
    controller.update();
    currentInputTime = millis();
    if (currentInputTime - lastInputTime >= maxDelayBetweenButtons)
    {
        konamiVar = 0;
        bloodVar = 0;
    }
    controller.printInputTable();
    checkForKonamiCode();
    checkForBloodCode();
}