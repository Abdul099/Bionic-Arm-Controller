/*
  Author: Abdullatif Hassan <abdullatif.hassan@mail.mcgill.ca>
  Source Repository: https://github.com/Abdul099/Bionic-Arm-Controller
  Last Updated: May 26, 2020
*/
#include <Arm_Screen.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Arm_Settings.h>

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Arm_Screen::Arm_Screen()
{
	_started = 0;
};

void Arm_Screen::prepare()
{
	//Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	display.clearDisplay();
	display.setTextSize(2);   
    display.setTextColor(WHITE); 
	display.setCursor(0, 0);
}

void Arm_Screen::setTextSize(int size)
{
	display.setTextSize(size);
}

void Arm_Screen::printToScreen(String str)
{
	//Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
	//display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	String cpy = str;
	display.clearDisplay();
	//display.setTextSize(2);   
    display.setTextColor(WHITE); 
	display.setCursor(0, 0);
	display.println(cpy);
	display.display();
}

void Arm_Screen::printToScreen(int val)
{
	// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
	// display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	display.clearDisplay();
	//display.setTextSize(2);   
    display.setTextColor(WHITE); 
	display.setCursor(0, 0);
	display.println(val);
	display.display();
}

void Arm_Screen::printToScreen(String s, int v)
{
	String c = s;
	display.clearDisplay();
	//display.setTextSize(2);   
    display.setTextColor(WHITE); 
	display.setCursor(0, 0);
	display.println(c);
	display.println(v);
	display.display();
}

void Arm_Screen::clearScreen()
{
	display.clearDisplay();
}