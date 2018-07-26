/*

  SelectionList.ino


*/

#include <Arduino.h>


// Bounce2 library  // https://github.com/thomasfredericks/Bounce2
// u8g2 fonts       // https://github.com/olikraus/u8g2/wiki/fntlistall#4-pixel-height
// fonts with 'm' mean monospace,
// 'f' means full 256 character set
// no 't' means not transparent! avoids having to rewrite character in reverse in advance

#include <Bounce2.h>

#define BUTTON_PIN_1 0
#define BUTTON_PIN_2 1
#define LED_PIN 13

#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0,  U8X8_PIN_NONE);
Bounce debouncer1 = Bounce();       // Instantiate a Bounce object
Bounce debouncer2 = Bounce();       // Instantiate another Bounce object


const bool INVERT_FLAG = 0;
const bool ON  = 1 ^ INVERT_FLAG;
const bool OFF = 0 ^ INVERT_FLAG;

char str[22] = "\0";

const byte SCRN_W = 128;
const byte SCRN_H = 32;

int barwidth = 10;
int h_ofst = 28;
int v_ofst = barwidth+3;

int tick_space = 16;

int val;
int val_p;

void setup(void) {
    pinMode(LED_PIN,OUTPUT);
    splashLED(3);

    // Set up the first button with an internal pull-up :
    pinMode(BUTTON_PIN_1,INPUT_PULLUP);
    pinMode(BUTTON_PIN_2,INPUT_PULLUP);
    debouncer1.attach(BUTTON_PIN_1); // After setting up the button, setup the Bounce instance :
    debouncer2.attach(BUTTON_PIN_2);
    debouncer1.interval(20); // interval in ms
    debouncer2.interval(20); // interval in ms

    oledInit();
    sprintf(str, "%s","NTD BarGraph v0.1");
    u8g2.setFont(u8g2_font_5x8_mf);
    oledPrintMsg(28,30, str, 0);    // xy text angle 0

    serialInit();   // set up usb serial port

    randomSeed(analogRead(A1));

    oledDrawTicks(tick_space, h_ofst, v_ofst);
    delay(100);

    u8g2.setFont(u8g2_font_7x14_mf);
    u8g2.setFontDirection(1);   // 1=90

    while(1) {
        for(int j=1; j<299; j++) {
            // leave space for numbers at lf/btm
            // val = random(1,SCRN_W);
            val = SCRN_W/2 * (0.8*sin(0.2*j) + 1);
            Serial.println(String(j) + "\t" + String(val));    // temp
            digitalWrite(LED_PIN,1);
            oledDrawBarGraph(val,h_ofst,barwidth);         // value, offset, barwidth

            // write numerical value
            u8g2.setDrawColor(ON);
            sprintf(str, "%3d ", val);
            u8g2.drawStr(6, 0, str);
            u8g2.sendBuffer();
            delay(100);
            digitalWrite(LED_PIN,0);
            delay(10);
        }

        // temp: wait here
    };
    // u8g2.setFont(u8g2_font_6x12_tr);
}


void loop(void) {

    // Update the Bounce instances :
    debouncer1.update();
    debouncer2.update();

    // Get the updated value :
    int value1 = debouncer1.read();
    int value2 = debouncer2.read();

    if(value1 == LOW)
        doAlpha();
    if(value2 == LOW)
        doBeta();
    // Turn on the LED if either button is pressed :
    if ( value1 == LOW || value2 == LOW ) {
        digitalWrite(LED_PIN, HIGH );
    }
    else {
        digitalWrite(LED_PIN, LOW );
    }
}

void doAlpha() {

}

void doBeta() {

}



void splashLED(byte n) {
    for (byte i=0; i<n; i++) {
        digitalWrite(LED_PIN,1);
        delay(15);
        digitalWrite(LED_PIN,0);
        delay(200);
    }
    delay(300);
}


void serialInit() {
    Serial.begin(57600); // rate doesn't matter for teensy routed to USB console
    while (!Serial && (millis() < 5000)) {} // include timeout if print console isn't opened
    Serial.println(" USB Serial Print initialized.");
}



