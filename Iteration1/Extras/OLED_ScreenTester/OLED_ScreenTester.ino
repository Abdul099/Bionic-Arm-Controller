#include <Arm_Screen.h>
#include <Wire.h>

String a = "hello";
String b = "hi";
String c = "val";
Arm_Screen screen = Arm_Screen();
  
void setup() {
  screen.prepare();
  screen.printToScreen(a);
  delay(1000);
  screen.printToScreen(b);
  delay(1000);
  screen.printToScreen(c, 10);
  delay(1000);
  screen.printToScreen("three", 3);
  delay(1000);
  screen.printToScreen("abdul");
}
void loop() {
  // put your main code here, to run repeatedly:

}
