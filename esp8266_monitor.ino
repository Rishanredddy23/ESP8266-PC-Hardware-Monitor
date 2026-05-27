#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

String cpu = "--";
String cpuTemp = "--";

String ram = "--";

String gpu = "--";
String gpuTemp = "--";

void setup() {

  Serial.begin(115200);

  Wire.begin(D2, D1);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.clearDisplay();
  display.setTextColor(WHITE);

  // STARTUP SCREEN
  display.setTextSize(2);
  display.setCursor(8, 22);
  display.println("RAYLYNX");
  display.display();

  delay(2000);
}

void loop() {

  if (Serial.available()) {

    String data = Serial.readStringUntil('\n');

    data.trim();

    int c1 = data.indexOf(',');
    int c2 = data.indexOf(',', c1 + 1);
    int c3 = data.indexOf(',', c2 + 1);
    int c4 = data.indexOf(',', c3 + 1);

    if (c1 > 0 && c2 > 0 && c3 > 0 && c4 > 0) {

      cpu = data.substring(0, c1);

      cpuTemp = data.substring(c1 + 1, c2);

      ram = data.substring(c2 + 1, c3);

      gpu = data.substring(c3 + 1, c4);

      gpuTemp = data.substring(c4 + 1);

      // ================= DISPLAY =================

      display.clearDisplay();

      // ---------- CPU ----------
      display.setTextSize(2);

      display.setCursor(0, 0);

      display.print("C");

      if (cpu.toInt() < 10) display.print(" ");

      display.print(cpu);
      display.print("%");

      display.setTextSize(1);

      display.setCursor(92, 6);

      display.print(cpuTemp);
      display.print("C");

      // ---------- GPU ----------
      display.setTextSize(2);

      display.setCursor(0, 24);

      display.print("G");

      if (gpu.toInt() < 10) display.print(" ");

      display.print(gpu);
      display.print("%");

      display.setTextSize(1);

      display.setCursor(92, 30);

      display.print(gpuTemp);
      display.print("C");

      // ---------- RAM ----------
      display.drawLine(0, 52, 127, 52, WHITE);

      display.setTextSize(1);

      display.setCursor(0, 56);

      display.print("RAM ");

      display.print(ram);
      display.print("%");

      display.display();
    }
  }
}