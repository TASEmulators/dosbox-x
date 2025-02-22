/*
 *  Copyright (C) 2002-2021  The DOSBox Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */



#ifndef DOSBOX_MOUSE_H
#define DOSBOX_MOUSE_H

#include <pic.h>

enum MOUSE_EMULATION
{
    MOUSE_EMULATION_NEVER,
    MOUSE_EMULATION_ALWAYS,
    MOUSE_EMULATION_INTEGRATION,
    MOUSE_EMULATION_LOCKED,
};

bool Mouse_SetPS2State(bool use);

void Mouse_ChangePS2Callback(uint16_t pseg, uint16_t pofs);

void Mouse_CursorMoved(float xrel,float yrel,float x,float y,bool emulate);
const char* Mouse_GetSelected(int x1, int y1, int x2, int y2, int w, int h, uint16_t *textlen);
#if defined(WIN32) || defined(MACOSX) || defined(C_SDL2)
void Mouse_Select(int x1, int y1, int x2, int y2, int w, int h, bool select);
#endif
void Mouse_ButtonPressed(uint8_t button);
void Mouse_ButtonReleased(uint8_t button);
void Mouse_WheelMoved(int32_t scroll);

void Mouse_AutoLock(bool enable);
bool Mouse_IsLocked();
void Mouse_BeforeNewVideoMode(bool setmode);
void Mouse_AfterNewVideoMode(bool setmode);

void UpdateMouseReportRate(void);
void ChangeMouseReportRate(unsigned int new_rate);

#define MOUSE_BUTTONS 3
#define QUEUE_SIZE 32
#define CURSORX 16
#define CURSORY 16
#define MOUSE_HAS_MOVED 1
#define MOUSE_LEFT_PRESSED 2
#define MOUSE_LEFT_RELEASED 4
#define MOUSE_RIGHT_PRESSED 8
#define MOUSE_RIGHT_RELEASED 16
#define MOUSE_MIDDLE_PRESSED 32
#define MOUSE_MIDDLE_RELEASED 64
#define MOUSE_WHEEL_MOVED 128
#define MOUSE_ABSOLUTE 256

struct button_event {
    uint8_t type;
    uint8_t buttons;
};

struct mouse_t {
    uint8_t buttons;
    int16_t wheel;
    uint16_t times_pressed[MOUSE_BUTTONS];
    uint16_t times_released[MOUSE_BUTTONS];
    uint16_t last_released_x[MOUSE_BUTTONS];
    uint16_t last_released_y[MOUSE_BUTTONS];
    uint16_t last_pressed_x[MOUSE_BUTTONS];
    uint16_t last_pressed_y[MOUSE_BUTTONS];
    pic_tickindex_t hidden_at;
    uint16_t last_scrolled_x;
    uint16_t last_scrolled_y;
    uint16_t hidden;
    float add_x,add_y;
    int16_t min_x,max_x,min_y,max_y;
    int16_t max_screen_x,max_screen_y;
    int32_t mickey_x,mickey_y;
    float mickey_accum_x, mickey_accum_y;
    float x,y;
    float ps2x,ps2y;
    button_event event_queue[QUEUE_SIZE];
    uint8_t events;//Increase if QUEUE_SIZE >255 (currently 32)
    uint16_t sub_seg,sub_ofs;
    uint16_t sub_mask;

    bool    background;
    int16_t  backposx, backposy;
    uint8_t   backData[CURSORX*CURSORY];
    uint16_t* screenMask;
    uint16_t* cursorMask;
    int16_t  clipx,clipy;
    int16_t  hotx,hoty;
    uint16_t  textAndMask, textXorMask;

    float   mickeysPerPixel_x;
    float   mickeysPerPixel_y;
    float   pixelPerMickey_x;
    float   pixelPerMickey_y;
    uint16_t  senv_x_val;
    uint16_t  senv_y_val;
    uint16_t  dspeed_val;
    float   senv_x;
    float   senv_y;
    int16_t  updateRegion_x[2];
    int16_t  updateRegion_y[2];
    uint16_t  doubleSpeedThreshold;
    uint16_t  language;
    uint16_t  cursorType;
    uint16_t  oldhidden;
    uint8_t  page;
    bool enabled;
    bool inhibit_draw;
    bool timer_in_progress;
    bool first_range_setx;
    bool first_range_sety;
    bool in_UIR;
    uint8_t mode;
    int16_t gran_x,gran_y;
    int scrollwheel;
    uint8_t ps2_type;
    uint8_t ps2_rate; // sampling rate is not really emulated, but needed for switching between protocols
    uint8_t ps2_packet_size;
    uint8_t ps2_unlock_idx;
};

extern mouse_t mouse;
extern void Mouse_AddEvent(uint8_t type);
#endif
