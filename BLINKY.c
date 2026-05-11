/****/
/* BLINKY.C: LED Flasher for MCB-STR9 Board                                   */
/****/
/* This file is part of the uVision/ARM development tools.                    */
/* Copyright (c) 2005-2006 Keil Software. All rights reserved.                */
/* This software may only be used under the terms of a valid, current,        */
/* end user licence from KEIL for a compatible version of KEIL software       */
/* development tools. Nothing else gives you the right to use this software.  */
/****/

#include <91x_lib.h>
#include <math.h>

#define LED       GPIO7->DR[0x3FC]
#define SW        GPIO3->DR[0x3FC]
#define BTN_UP    (SW & 0x40)
#define BTN_DOWN  (SW & 0x20)
#define lose_light 50
#define LOSE 3

void dly(int i);
int measure(void);
void dly(int i)
{
    int j, k;
    for (j = 1; j < 100; j++)
    {
        for (k = 0; k < i; k++);
    }
}

int measure(void)
{
    ADC->CR &= 0xFF7f;
    ADC->CR = 0x0002;

    ADC->CR |= 0x0001;
    dly(100);

    while (((ADC->CR) & 0x8000) == 0); // wait for end of converge

    return ((ADC->DR0) & 0x03FF);
}

void blink(int blink_num, int place, int line) {
    int i, j;
    for (i = 0; i < blink_num; i++) {
        LED = 0xff;
        set_cursor(place, line);
        lcd_putchar('*');
        set_cursor(20, 20);
        for (j = 0; j < lose_light; j++)
            dly(100);
        LED = 0;
        set_cursor(place, line);
        lcd_putchar(' ');
        set_cursor(20, 20);
        for (j = 0; j < lose_light; j++)
            dly(100);
    }
}

int main(void)
{
    unsigned int i = 0, td, place = -1, line = 1, length = 3, time_print = 0, time_press = 0, time_point = 200, time_led = 0, score = 0, point_loction[] = {50,50}, lose = LOSE;
    Intio();
    Int_a2d();
    lcd_init(); // initial the LCD display
    lcd_clear();
    while (1) {
        td = 1023 - measure();
        if (time_print == 0) { // print snake and delete tail
            time_print = 40;
            place++;
            if (place == 16)
                place = 0;
            set_cursor(place, line);
            lcd_putchar('_');
            set_cursor((place - length + 16) % 16, 0);
            lcd_putchar(' ');
            set_cursor(20, 20);
            set_cursor((place - length + 16) % 16, 1);
            lcd_putchar(' ');
            set_cursor(20, 20);
        }

        if (time_press == 0 && (BTN_UP == 0)) { // button up
            time_press = 60;
            if (line > 0) line--;
            place++;
            if (place == 16)
                place = 0;
            set_cursor(place, line);
            lcd_putchar('|');
            set_cursor(20, 20);
            set_cursor((place - length + 16) % 16, 0);
            lcd_putchar(' ');
            set_cursor(20, 20);
            set_cursor((place - length + 16) % 16, 1);
            lcd_putchar(' ');
            set_cursor(20, 20);
        }

        if (time_press == 0 && (BTN_DOWN == 0)) { // button down
            time_press = 60;
            if (line < 1) line++;
            place++;
            if (place == 16)
                place = 0;
            set_cursor(place, line);
            lcd_putchar('|');
            set_cursor(20, 20);
            set_cursor((place - length + 16) % 16, 0);
            lcd_putchar(' ');
            set_cursor(20, 20);
            set_cursor((place - length + 16) % 16, 1);
            lcd_putchar(' ');
            set_cursor(20, 20);
        }

        if (time_point == 0 && point_loction[0] == 50) { // food
            set_cursor((place + 7) % 16, (line + 1) % 2);
            lcd_putchar('*');
            set_cursor(20, 20);
            point_loction[0] = (place + 7) % 16;
            point_loction[1] = (line + 1) % 2;
        }

        if (place == point_loction[0]) { // arrive to point
            if (line == point_loction[1]) { // hit point
                score++;
                if (length < 8)
                    length++;
                if ((BTN_UP == 0) || (BTN_DOWN == 0)) { // special situation
                    set_cursor(point_loction[0], point_loction[1]);
                    lcd_putchar(' ');
                }
            }
            else { // miss point
                lose--;
                blink(5, point_loction[0], point_loction[1]);
                set_cursor(point_loction[0], point_loction[1]);
                lcd_putchar(' ');
            }
            point_loction[0] = 50;
            point_loction[1] = 50;
            time_point = 200;
        }

        if (time_led == 0) { // LED RUN
            time_led = 10;
            LED = pow(2, i);
            if (i == 8)
                i = -1;
            i++;
        }

        if (lose == 0) {
            break;
        }

        time_led--;
        time_point--;
        if (time_press) {
            time_press--;
        }
        time_print--;
        dly(td);
    }

    lcd_clear(); // GAME OVER
    LED = 0xff;
    set_cursor(3, 0);
    lcd_print("GAME OVER!");
    set_cursor(1, 1);
    lcd_print("YOUR SCORE:");
    lcd_putchar(0x30 + score / 10);
    lcd_putchar(0x30 + score % 10);
    while (1) {}
}
