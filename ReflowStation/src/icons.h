#include <stdint.h>

uint8_t iconTempSize = 62;
uint16_t iconTemp[] = {
    (3 << 8) | 0, (4 << 8) | 0,
    (2 << 8) | 1, (5 << 8) | 1,
    (1 << 8) | 2, (4 << 8) | 2, (5 << 8) | 2, (6 << 8) | 2,
    (1 << 8) | 3, (6 << 8) | 3,
    (1 << 8) | 4, (5 << 8) | 4, (6 << 8) | 4,
    (1 << 8) | 5, (6 << 8) | 5,
    (1 << 8) | 6, (4 << 8) | 6, (5 << 8) | 6, (6 << 8) | 6,
    (1 << 8) | 7, (6 << 8) | 7,
    (1 << 8) | 8, (5 << 8) | 8, (6 << 8) | 8,
    (1 << 8) | 9, (6 << 8) | 9,
    (1 << 8) | 10, (4 << 8) | 10, (5 << 8) | 10, (6 << 8) | 10,
    (1 << 8) | 11, (6 << 8) | 11,
    (1 << 8) | 12, (2 << 8) | 12, (3 << 8) | 12, (4 << 8) | 12, (5 << 8) | 12, (6 << 8) | 12,
    (1 << 8) | 13, (6 << 8) | 13,
    (0 << 8) | 14, (4 << 8) | 14, (5 << 8) | 14, (6 << 8) | 14, (7 << 8) | 14,
    (0 << 8) | 15, (7 << 8) | 15,
    (0 << 8) | 16, (4 << 8) | 16, (5 << 8) | 16, (6 << 8) | 16, (7 << 8) | 16,
    (0 << 8) | 17, (7 << 8) | 17,
    (1 << 8) | 18, (4 << 8) | 18, (5 << 8) | 18, (6 << 8) | 18, (2 << 8) | 18, (3 << 8) | 18, (4 << 8) | 18, (5 << 8) | 18};

uint8_t iconClockSize = 76;
uint16_t iconClock[] = {
    (6 << 8) | 0, (7 << 8) | 0, (8 << 8) | 0, (9 << 8) | 0, (10 << 8) | 0, (11 << 8) | 0,
    (4 << 8) | 1, (5 << 8) | 1, (12 << 8) | 1, (13 << 8) | 1,
    (3 << 8) | 2, (8 << 8) | 2, (9 << 8) | 2, (14 << 8) | 2,
    (2 << 8) | 3, (8 << 8) | 3, (9 << 8) | 3, (15 << 8) | 3,
    (1 << 8) | 4, (8 << 8) | 4, (9 << 8) | 4, (16 << 8) | 4,
    (1 << 8) | 5, (8 << 8) | 5, (9 << 8) | 5, (16 << 8) | 5,
    (0 << 8) | 6, (8 << 8) | 6, (9 << 8) | 6, (17 << 8) | 6,
    (0 << 8) | 7, (8 << 8) | 7, (9 << 8) | 7, (17 << 8) | 7,
    (0 << 8) | 8, (7 << 8) | 8, (8 << 8) | 8, (9 << 8) | 8, (10 << 8) | 8, (11 << 8) | 8, (12 << 8) | 8, (13 << 8) | 8, (17 << 8) | 8,
    (0 << 8) | 9, (7 << 8) | 9, (8 << 8) | 9, (9 << 8) | 9, (10 << 8) | 9, (11 << 8) | 9, (12 << 8) | 9, (13 << 8) | 9, (17 << 8) | 9,
    (0 << 8) | 10, (8 << 8) | 10, (9 << 8) | 10, (17 << 8) | 10,
    (0 << 8) | 11, (17 << 8) | 11,
    (1 << 8) | 12, (16 << 8) | 12,
    (1 << 8) | 13, (16 << 8) | 13,
    (2 << 8) | 14, (15 << 8) | 14,
    (3 << 8) | 15, (14 << 8) | 15,
    (4 << 8) | 16, (5 << 8) | 16, (12 << 8) | 16, (13 << 8) | 16,
    (6 << 8) | 17, (7 << 8) | 17, (8 << 8) | 17, (9 << 8) | 17, (10 << 8) | 17, (11 << 8) | 17};

uint8_t iconHeatOffSize = 42;
uint16_t iconHeatOff[] = {
    (3 << 8) | 8, (4 << 8) | 8, (5 << 8) | 8, (6 << 8) | 8, (7 << 8) | 8, (8 << 8) | 8, (9 << 8) | 8, (10 << 8) | 8,
    (1 << 8) | 9, (2 << 8) | 9, (11 << 8) | 9, (12 << 8) | 9,
    (0 << 8) | 10, (13 << 8) | 10,
    (0 << 8) | 11, (13 << 8) | 11,
    (0 << 8) | 12, (1 << 8) | 12, (2 << 8) | 12, (11 << 8) | 12, (12 << 8) | 12, (13 << 8) | 12,
    (1 << 8) | 13, (2 << 8) | 13, (3 << 8) | 13, (4 << 8) | 13, (5 << 8) | 13, (6 << 8) | 13, (7 << 8) | 13, (8 << 8) | 13, (9 << 8) | 13, (10 << 8) | 13, (11 << 8) | 13, (12 << 8) | 13,
    (3 << 8) | 14, (4 << 8) | 14, (5 << 8) | 14, (6 << 8) | 14, (7 << 8) | 14, (8 << 8) | 14, (9 << 8) | 14, (10 << 8) | 14};

uint8_t iconHeatOnSize = 58;
uint16_t iconHeatOn[] = {
    (5 << 8) | 0, (8 << 8) | 0,
    (5 << 8) | 1, (8 << 8) | 1,
    (4 << 8) | 2, (7 << 8) | 2,
    (3 << 8) | 3, (6 << 8) | 3,
    (3 << 8) | 4, (6 << 8) | 4,
    (3 << 8) | 5, (6 << 8) | 5,
    (4 << 8) | 6, (7 << 8) | 6,
    (5 << 8) | 7, (8 << 8) | 7,
    (3 << 8) | 8, (5 << 8) | 8, (8 << 8) | 8, (10 << 8) | 8,
    (1 << 8) | 9, (2 << 8) | 9, (5 << 8) | 9, (8 << 8) | 9, (11 << 8) | 9, (12 << 8) | 9,
    (0 << 8) | 10, (5 << 8) | 10, (8 << 8) | 10, (13 << 8) | 10,
    (0 << 8) | 11, (13 << 8) | 11,
    (0 << 8) | 12, (1 << 8) | 12, (2 << 8) | 12, (11 << 8) | 12, (12 << 8) | 12, (13 << 8) | 12,
    (1 << 8) | 13, (2 << 8) | 13, (3 << 8) | 13, (4 << 8) | 13, (5 << 8) | 13, (6 << 8) | 13, (7 << 8) | 13, (8 << 8) | 13, (9 << 8) | 13, (10 << 8) | 13, (11 << 8) | 13, (12 << 8) | 13,
    (3 << 8) | 14, (4 << 8) | 14, (5 << 8) | 14, (6 << 8) | 14, (7 << 8) | 14, (8 << 8) | 14, (9 << 8) | 14, (10 << 8) | 14};

uint8_t iconButtonSize = 21;
uint16_t iconButton[] = {
    (4 << 8) | 2, (5 << 8) | 2, (6 << 8) | 2,
    (3 << 8) | 3, (7 << 8) | 3,
    (3 << 8) | 4, (7 << 8) | 4,
    (2 << 8) | 5, (3 << 8) | 5, (4 << 8) | 5, (5 << 8) | 5, (6 << 8) | 5, (7 << 8) | 5, (8 << 8) | 5,
    (2 << 8) | 6, (3 << 8) | 6, (4 << 8) | 6, (5 << 8) | 6, (6 << 8) | 6, (7 << 8) | 6, (8 << 8) | 6,
};

uint8_t iconButtonPressedSize = 25;
uint16_t iconButtonPressed[] = {
    (4 << 8) | 0, (7 << 8) | 0,
    (2 << 8) | 1, (4 << 8) | 1, (7 << 8) | 1,
    (2 << 8) | 2,
    (4 << 8) | 3, (5 << 8) | 3, (6 << 8) | 3,
    (3 << 8) | 4, (7 << 8) | 4,
    (2 << 8) | 5, (3 << 8) | 5, (4 << 8) | 5, (5 << 8) | 5, (6 << 8) | 5, (7 << 8) | 5, (8 << 8) | 5,
    (2 << 8) | 6, (3 << 8) | 6, (4 << 8) | 6, (5 << 8) | 6, (6 << 8) | 6, (7 << 8) | 6, (8 << 8) | 6,
};