// /* DHT-22 sensor with 12c 16x2 LCD with Arduino uno
//    Temperature  and humidity sensor displayed in LCD
//    based on: http://www.ardumotive.com/how-to-use-dht-22-sensor-en.html  and
//    https://www.ardumotive.com/i2clcden.html for the i2c LCD library by Michalis  Vasilakis
//    Recompile by adhitadhitadhit
//    Notes: use LCD i2c Library from  link above, i'm not sure why but new Liquidcristal library from Francisco Malpartida  isn't working for me
//    other thing, check your */

// //Libraries
// #include <DHT22.h> // sensor library using lib from https://www.ardumotive.com/how-to-use-dht-22-sensor-en.html
// #include  <LiquidCrystal_I2C.h> // LCD library using from  https://www.ardumotive.com/i2clcden.html  for the i2c LCD library 
// #include <Wire.h> 

// //Constants
// #define pinDATA 2 // SDA, or almost any other I/O pin
// DHT22 dht22(pinDATA); 


// LiquidCrystal_I2C lcd(0x3F, 16, 2);
// //Variables
// float h= -1;  //Stores  humidity value
// float t= -1; //Stores temperature value

// void setup()
// {

//     Serial.begin(9600);
//     Wire.begin();
//     lcd.init();                      // initialize the  lcd 
//   // Print a message to the LCD.
//   lcd.backlight();
//   lcd.setBacklight(HIGH);
// }

// void  loop()
// {
  
//           t = dht22.getTemperature();
//           h = dht22.getHumidity();

//           if (dht22.getLastError() != dht22.OK) {
//             Serial.print("last error :");
//             Serial.println(dht22.getLastError());
//           }
//           Serial.print("h=");Serial.print(h,1);Serial.print("\t");
//           Serial.print("t=");Serial.println(t,1);
//     //Print temp and humidity values to LCD
//     lcd.setCursor(0,0);
//     lcd.print("H: ");
//     lcd.print(h);
//     lcd.print("%");
//     lcd.setCursor(0,1);
//     lcd.print("T: "); 
//     lcd.print(t);
//     lcd.print("'C ");
//     lcd.setCursor(0,0);
//     delay(2000);
// }