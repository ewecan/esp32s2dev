#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "stdint.h"
#include "string.h"

// According to your need to modify the constants.
#define TICKS_INTERVAL 20 // ms
#define DEBOUNCE_TICKS 3  // MAX 8
#define SHORT_TICKS (100 / TICKS_INTERVAL)
#define LONG_TICKS (800 / TICKS_INTERVAL)

typedef void (*BtnCallback)(void *, uint8_t);

typedef enum
{
    BTN_UNPRESS = 0X00,
    BTN_PRESSED = 0x01,
    PRESS_DOWN = 0x02,
    PRESS_UP = 0x04,
    PRESS_REPEAT = 0x08,
    SINGLE_CLICK = 0x10,
    DOUBLE_CLICK = 0x20,
    LONG_RRESS_START = 0x40,
    LONG_PRESS_HOLD = 0x80,
    number_of_event = 9,
} PressEvent;

typedef struct Button
{
    struct Button *next;
    uint16_t ticks;
    uint8_t event;
    uint8_t repeat : 4;
    uint8_t state : 3;
    uint8_t debounce_cnt : 3;
    uint8_t button_level : 1;
    uint8_t (*hal_button_Level)(void);
    BtnCallback cb;
} Button;

void button_init(void);
/**
 * @brief  Button driver core function, driver state machine.
 * @param  handle: the button handle strcut.
 * @param  pin_level: the button status 0:NONE_PRESS 1:BTN_PRESSED.
 * @param  cb: the button press call function.
 * @param  event: the button event trigger mask.
 * @retval None
 */
void button_attach(struct Button *handle, uint8_t (*pin_level)(), BtnCallback cb, PressEvent event);
PressEvent get_button_event(struct Button *handle);
int button_start(struct Button *handle);
void button_stop(struct Button *handle);
void button_ticks(void);

#endif // __BUTTON_H__
