/*
  Universal 8bit Graphics Library (https://github.com/olikraus/u8g2/)

  Copyright (c) 2016, olikraus@gmail.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification,
  are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this list
    of conditions and the following disclaimer.

  * Redistributions in binary form must reproduce the above copyright notice, this
    list of conditions and the following disclaimer in the documentation and/or other
    materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS FOR A PARTICUtraLAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 */


// the oled library includes a set of functions to make a hilited menu and detect selections
// may use later
void oledInit() {
    // assign pins for cursor control of SelectionList
    // u8g2.begin(/*Select=*/ A0, /*Right/Next=*/ 5, /*Left/Prev=*/ 9, /*Up=*/ 8, /*Down=*/ 10, /*Home/Cancel=*/ A1); // Arduboy DevKit
    u8g2.begin(/*Select=*/ 7, /*Right/Next=*/ A1, /*Left/Prev=*/ A2, /*Up=*/ 0, /*Down=*/ 1, /*Home/Cancel=*/ 8); // Arduboy 10 (Production)
    u8g2.clearBuffer();          // clear the internal memory
//   u8g2.sendBuffer();
    u8g2.setDrawColor(ON);
    u8g2.setFont(u8g2_font_9x15B_mf);  // 11 pix
    // u8g2.setFont(u8g2_font_6x12_tr);
}


void oledDrawBarGraph(int val, int h_ofst, int barwidth) {
    for (int i = 0; i<SCRN_W; i++) {
        if (i < val) {
            u8g2.setDrawColor((i+h_ofst) % 4 > 0);      // make gaps in bar
        }
        else {
            u8g2.setDrawColor(OFF);                       // erase previous lines
        }

        u8g2.drawLine(i+h_ofst,0, i+h_ofst, barwidth);
    }
    u8g2.sendBuffer();
}


void oledDrawAxis(int len, int h_ofst, int v_ofst) {
    u8g2.drawLine(h_ofst,v_ofst, h_ofst+len,v_ofst);  // horizontal
}


void oledDrawTicks(int tick_space, int h_ofst, int v_ofst) {
    // make scale with ticks; start at h,v
    int tick_length = 2;
    for (int i = h_ofst; i<SCRN_W; i++) {
        u8g2.setDrawColor((i+h_ofst) % tick_space<1); // draw  either black or white pixels
        u8g2.drawLine(i,v_ofst, i, v_ofst+tick_length);
    }
    u8g2.sendBuffer();
}


void oledPrintMsg(byte x, byte y, char msg[22], int angle) {   // font preselected
    char s[22] = "\0";
    byte num_chars;
    if (angle == 1 || angle == 90) u8g2.setFontDirection(1);   // 1=90
    else                           u8g2.setFontDirection(0);   // 0= 0
    u8g2.setDrawColor(ON);
    num_chars = sprintf(s, "%s", msg);
    u8g2.drawStr(x, y, s);
    u8g2.sendBuffer();
}




