#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>
#include <Encoder.h>
#include "icons.h"

#define sclk 13
#define mosi 11
#define cs   10
#define rst  9
#define dc   8
#define rotaryA 2
#define rotaryB 3
#define button1 4

#define	BLACK           0x0000
#define	GRAY            0xAD75
#define	BLUE            0x001F
#define	RED             0xF800
#define	GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0
#define LIGHT_YELLOW    0xF7B3
#define DARK_YELLOW     0x9460
#define WHITE           0xFFFF

#define FLICKER_SPEED_MS   500
#define DISPlAY_REFRESH_MS FLICKER_SPEED_MS
#define MAX_TEMP           230

Adafruit_SSD1331 display = Adafruit_SSD1331(&SPI, cs, dc, rst);
Encoder rotaryEncoder(rotaryA, rotaryB);

enum SCREEN {
    MAIN_MENU,
    SET_TEMP,
    SET_TIME
};
SCREEN currentScreen = MAIN_MENU;

int selectedMainmenuItem = -1;
bool flicker = false;
unsigned long flickerMillis = 0;
unsigned long displayRefreshMillis = 0;
long oldPosition  = -999;
bool button1Pressed = false;

bool reflowRunning = false;
bool heatingOn = false;
unsigned long reflowStartMillis = 0;
int currentTemperature = 0;
int targetTemperature = 0;
int targetTimeMins = 0;

void updateRotary(void);
void updateScreen(void);
void clickButton(void);
void changeScreen(SCREEN newScreen);
void drawMainMenu(void);
void drawSetTemp(void);
void drawSetTime(void);
void intRotaryA(void);
void intRotaryB(void);

void setup(void) {
    Serial.begin(115200);

    pinMode(button1, INPUT_PULLUP);

    display.begin();
    changeScreen(MAIN_MENU);
}

void loop() {
    if (millis() - flickerMillis > FLICKER_SPEED_MS) {
        flickerMillis = millis();
        flicker = !flicker;
    }

    if (millis() - displayRefreshMillis > DISPlAY_REFRESH_MS) {
        displayRefreshMillis = millis();
        updateScreen();
    }

    if (digitalRead(button1)) {
        if (!button1Pressed) {
            clickButton();
        }
        button1Pressed = true;
    } else {
        button1Pressed = false;
    }

    if (reflowRunning) {
        long targetMillis = reflowStartMillis + (((long) targetTimeMins) * 60L * 1000L);
        if (targetMillis - millis() <= 0 || targetMillis - millis() > 60L * 60L * 1000L + 1L) {
            reflowRunning = false;
        }
    }

    updateRotary();
}

void updateRotary(void) {
    long newPosition = rotaryEncoder.read() / 4;
    if (newPosition != oldPosition) {
        switch(currentScreen) {
            case MAIN_MENU:
                selectedMainmenuItem += newPosition - oldPosition > 0 ? 1 : -1;
                if (selectedMainmenuItem > 2) {
                    selectedMainmenuItem = -1;
                }
                if (selectedMainmenuItem < -1) {
                    selectedMainmenuItem = 2;
                }
                break;

            case SET_TEMP:
                targetTemperature += newPosition - oldPosition > 0 ? 5 : -5;
                targetTemperature = targetTemperature < 0 ? 0 : targetTemperature;
                targetTemperature = targetTemperature > MAX_TEMP ? MAX_TEMP : targetTemperature;
                break;

            case SET_TIME:
                targetTimeMins += newPosition - oldPosition > 0 ? 1 : -1;
                targetTimeMins = targetTimeMins < 0 ? 0 : targetTimeMins;
                targetTimeMins = targetTimeMins > 60 ? 60 : targetTimeMins;
                break;
        }
        oldPosition = newPosition;
        updateScreen();
    }
}

void updateScreen(void) {
    switch(currentScreen) {
        case MAIN_MENU:
            drawMainMenu();
            break;

        case SET_TEMP:
            drawSetTemp();
            break;

        case SET_TIME:
            drawSetTime();
            break;
    }

    if (reflowRunning) {
        display.fillRect(0, 48, 96, 16, BLACK);

        String timeString = "";
        String tempString = "";

        long millisLeft = ((reflowStartMillis + (((long) targetTimeMins) * 60L * 1000L)) - millis());
        long currentTimeSpendMin = int(millisLeft / (60L * 1000L));

        if (currentTimeSpendMin + 1 < 10) {
            timeString += "0";
        }
        timeString += String(currentTimeSpendMin + 1);
        timeString += " Min left";

        if (currentTemperature < 10) {
            tempString += "0";
        }
        if (currentTemperature < 100) {
            tempString += "0";
        }
        tempString += String(currentTemperature);
        tempString += "C / ";
        if (targetTemperature < 10) {
            tempString += "0";
        }
        if (targetTemperature < 100) {
            tempString += "0";
        }
        tempString += String(targetTemperature);
        tempString += "C";

        display.setTextSize(1);
        display.setTextColor(YELLOW);
        display.setCursor(14, 49);
        display.print(timeString);
        display.setCursor(14, 57);
        display.print(tempString);
    } else {
        display.fillRect(0, 48, 96, 16, BLACK);

        String tempString = "";

        if (currentTemperature < 10) {
            tempString += "0";
        }
        if (currentTemperature < 100) {
            tempString += "0";
        }
        tempString += String(currentTemperature);
        tempString += "C";

        display.setTextSize(1);
        display.setTextColor(currentTemperature > 60 ? RED : YELLOW);
        display.setCursor(36, 49);
        display.print(tempString);
        display.setTextColor(YELLOW);
        display.setCursor(36, 57);
        display.print("IDLE");
    }
}

void clickButton(void) {
    switch(currentScreen) {
        case MAIN_MENU:
            if (selectedMainmenuItem == 0) {
                changeScreen(SET_TEMP);
            } else if (selectedMainmenuItem == 1) {
                if (!reflowRunning) {
                    changeScreen(SET_TIME);
                }
            } else if (selectedMainmenuItem == 2) {
                reflowRunning = !reflowRunning;
                reflowStartMillis = millis();
            }
            break;

        case SET_TEMP:
            changeScreen(MAIN_MENU);
            break;
        
        case SET_TIME:
            changeScreen(MAIN_MENU);
            break;
    }
    updateScreen();
}

void changeScreen(SCREEN newScreen) {
    currentScreen = newScreen;
    display.fillScreen(BLACK);
}

void drawMainMenu(void) {
    for (int i = 0; i < 3; i++) {
        uint8_t offsetX = i * 30;
        display.drawLine(8 + offsetX, 11, 27 + offsetX, 11, YELLOW); // UP
        display.drawLine(8 + offsetX, 36, 27 + offsetX, 36, YELLOW); // DOWN
        display.drawLine(5 + offsetX, 14, 5 + offsetX, 33, YELLOW); // LEFT
        display.drawLine(30 + offsetX, 14, 30 + offsetX, 33, YELLOW); // RIGHT
        display.drawPixel(6 + offsetX, 13, YELLOW);
        display.drawPixel(7 + offsetX, 12, YELLOW);
        display.drawPixel(29 + offsetX, 13, YELLOW);
        display.drawPixel(28 + offsetX, 12, YELLOW);
        display.drawPixel(6 + offsetX, 34, YELLOW);
        display.drawPixel(7 + offsetX, 35, YELLOW);
        display.drawPixel(29 + offsetX, 34, YELLOW);
        display.drawPixel(28 + offsetX, 35, YELLOW);

        display.drawLine(8 + offsetX, 12, 27 + offsetX, 12, selectedMainmenuItem == i ? YELLOW : BLACK);
        for (int j = 0; j < 22; j++) {
            display.drawLine(6 + offsetX, 13 + j, 29 + offsetX, 13 + j, selectedMainmenuItem == i ? YELLOW : BLACK);
        }
        display.drawLine(8 + offsetX, 35, 27 + offsetX, 35, selectedMainmenuItem == i ? YELLOW : BLACK);
    }

    uint8_t iconTempX = 14;
    uint8_t iconTempY = 14;
    for (int i = 0; i < iconTempSize; i++) {
        uint16_t val = iconTemp[i];
        display.drawPixel(iconTempX + (val >> 8), iconTempY + (val & 0xFF), selectedMainmenuItem == 0 ? BLACK : YELLOW);
    }

    uint8_t iconClockX = 39;
    uint8_t iconClockY = 15;
    for (int i = 0; i < iconClockSize; i++) {
        uint16_t val = iconClock[i];
        display.drawPixel(iconClockX + (val >> 8), iconClockY + (val & 0xFF), reflowRunning ? DARK_YELLOW : (selectedMainmenuItem == 1 ? BLACK : YELLOW));
    }

    if (reflowRunning) {
        uint8_t iconHeatX = 71;
        uint8_t iconHeatY = 15;
        for (int i = 0; i < iconHeatOnSize; i++) {
            uint16_t val = iconHeatOn[i];
            display.drawPixel(
                iconHeatX + ((val >> 8) * (flicker ? -1 : 1) + (flicker ? 13 : 0)),
                iconHeatY + (val & 0xFF),
                heatingOn ? RED : (selectedMainmenuItem == 2 ? BLACK : YELLOW)
            );
        }
    } else {
        uint8_t iconHeatX = 71;
        uint8_t iconHeatY = 15;
        for (int i = 0; i < iconHeatOffSize; i++) {
            uint16_t val = iconHeatOff[i];
            display.drawPixel(iconHeatX + (val >> 8), iconHeatY + (val & 0xFF), selectedMainmenuItem == 2 ? BLACK : YELLOW);
        }
    }
}

void drawSetTemp(void) {
    // display.fillScreen(BLACK);
    display.fillRect(0, 0, 40, 10, BLACK);
    display.fillRect(21, 20, 52, 22, BLACK);
    display.fillRect(11, 27, 8, 8, BLACK);
    display.fillRect(76, 27, 8, 8, BLACK);

    String temperatureString = "";
    if (targetTemperature < 10) {
        temperatureString += "0";
    }
    if (targetTemperature < 100) {
        temperatureString += "0";
    }
    temperatureString += String(targetTemperature);

    display.setTextSize(3);
    display.setTextColor(YELLOW);
    display.setCursor(22, 21);
    display.print(temperatureString);

    for (int y = 27; y < 35; y++) {
        if (targetTemperature > 0) {
            display.drawLine(11, 31, 18, y, YELLOW);
        }
        if (targetTemperature < MAX_TEMP) {
            display.drawLine(83, 31, 76, y, YELLOW);
        }
    }

    uint8_t iconButtonX = 2;
    uint8_t iconButtonY = 0;
    if (!flicker) {
        for (int i = 0; i < iconButtonSize; i++) {
            uint16_t val = iconButton[i];
            display.drawPixel(iconButtonX + (val >> 8), iconButtonY + (val & 0xFF), YELLOW);
        }
    } else {
        for (int i = 0; i < iconButtonPressedSize; i++) {
            uint16_t val = iconButtonPressed[i];
            display.drawPixel(iconButtonX + (val >> 8), iconButtonY + (val & 0xFF), YELLOW);
        }
    }

    display.setTextSize(1);
    display.setTextColor(YELLOW);
    display.setCursor(13, 0);
    display.print("BACK");
}

void drawSetTime(void) {
    display.fillRect(0, 0, 40, 10, BLACK);
    display.fillRect(13, 24, 22, 14, BLACK);

    String timeString = "";
    if (targetTimeMins < 10) {
        timeString += "0";
    }
    timeString += String(targetTimeMins);
    timeString += " MIN";

    display.setTextSize(2);
    display.setTextColor(YELLOW);
    display.setCursor(13, 24);
    display.print(timeString);

    uint8_t iconButtonX = 2;
    uint8_t iconButtonY = 0;
    if (!flicker) {
        for (int i = 0; i < iconButtonSize; i++) {
            uint16_t val = iconButton[i];
            display.drawPixel(iconButtonX + (val >> 8), iconButtonY + (val & 0xFF), YELLOW);
        }
    } else {
        for (int i = 0; i < iconButtonPressedSize; i++) {
            uint16_t val = iconButtonPressed[i];
            display.drawPixel(iconButtonX + (val >> 8), iconButtonY + (val & 0xFF), YELLOW);
        }
    }

    display.setTextSize(1);
    display.setTextColor(YELLOW);
    display.setCursor(13, 0);
    display.print("BACK");
}