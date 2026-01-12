#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ---------------- EYE CONSTANTS ----------------
#define EXR 35
#define EXL 95
#define VPOS 32

// ---------------- EYE VARIABLES ----------------
int left_eye_x = EXL;
int right_eye_x = EXR;
int left_eye_y = VPOS;
int right_eye_y = VPOS;

int left_eye_width = 30;
int right_eye_width = 30;
int left_eye_height = 30;
int right_eye_height = 30;

int ref_corner_radius = 8;

// ---------------- DRAW EYES ----------------
void draw_eyes(bool update = true) {
  display.clearDisplay();

  int x = left_eye_x - left_eye_width / 2;
  int y = left_eye_y - left_eye_height / 2;
  display.fillRoundRect(x, y, left_eye_width, left_eye_height,
                        ref_corner_radius, SSD1306_WHITE);

  x = right_eye_x - right_eye_width / 2;
  y = right_eye_y - right_eye_height / 2;
  display.fillRoundRect(x, y, right_eye_width, right_eye_height,
                        ref_corner_radius, SSD1306_WHITE);

  if (update) display.display();
}

// ---------------- BASIC STATES ----------------
void center_eyes() {
  left_eye_x = EXL;
  right_eye_x = EXR;
  left_eye_y = VPOS;
  right_eye_y = VPOS;
  left_eye_width = right_eye_width = 30;
  left_eye_height = right_eye_height = 30;
  ref_corner_radius = 8;
  draw_eyes();
}

// ---------------- BLINK ----------------
void blink(int speed = 12) {
  for (int i = 30; i > 2; i -= 2) {
    left_eye_height = right_eye_height = i;
    draw_eyes();
    delay(speed);
  }
  delay(80);
  for (int i = 2; i < 30; i += 2) {
    left_eye_height = right_eye_height = i;
    draw_eyes();
    delay(speed);
  }
}

// ---------------- SLEEP / WAKE ----------------
void sleep() {
  left_eye_height = right_eye_height = 5;
  draw_eyes();
}

void wakeup() {
  for (int i = 5; i <= 30; i += 2) {
    left_eye_height = right_eye_height = i;
    draw_eyes();
    delay(40);
  }
}

// ---------------- EMOTIONS ----------------
void happy() {
  left_eye_height = right_eye_height = 20;
  ref_corner_radius = 12;
  draw_eyes();
}

void sad() {
  left_eye_height = right_eye_height = 12;
  ref_corner_radius = 4;
  draw_eyes();
}

void angry() {
  left_eye_height = right_eye_height = 18;
  left_eye_width = right_eye_width = 34;
  ref_corner_radius = 2;
  draw_eyes();
}

void cute() {
  left_eye_width = right_eye_width = 26;
  left_eye_height = right_eye_height = 26;
  ref_corner_radius = 14;
  draw_eyes();
}

void suspicious() {
  left_eye_height = 12;
  right_eye_height = 24;
  draw_eyes();
}

// ---------------- MOVEMENTS ----------------
void lookLeft() {
  left_eye_x = EXL + 8;
  right_eye_x = EXR + 8;
  draw_eyes();
}

void lookRight() {
  left_eye_x = EXL - 8;
  right_eye_x = EXR - 8;
  draw_eyes();
}

void lookUp() {
  left_eye_y = right_eye_y = VPOS - 6;
  draw_eyes();
}

void lookDown() {
  left_eye_y = right_eye_y = VPOS + 6;
  draw_eyes();
}

void saccade(int dx, int dy) {
  left_eye_x += dx;
  right_eye_x += dx;
  left_eye_y += dy;
  right_eye_y += dy;
  draw_eyes();
  delay(80);
  center_eyes();
}

// ---------------- SETUP ----------------
void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  center_eyes();
}

// ---------------- LOOP (DEMO) ----------------
void loop() {
  blink();
  delay(800);

  lookLeft(); delay(600);
  lookRight(); delay(600);
  lookUp(); delay(600);
  lookDown(); delay(600);

  center_eyes(); delay(500);

  happy(); delay(1000);
  sad(); delay(1000);
  angry(); delay(1000);
  cute(); delay(1000);
  suspicious(); delay(1000);

  sleep(); delay(1200);
  wakeup(); delay(800);
}
