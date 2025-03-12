// #include <Wire.h>
// #include <LiquidCrystal_I2C.h>
// #include <DHT.h>

// // Define DHT sensor
// #define DHTPIN 2
// #define DHTTYPE DHT22
// DHT dht(DHTPIN, DHTTYPE);

// // Initialize I2C LCD
// LiquidCrystal_I2C lcd(0x3F, 16, 2); // Replace 0x27 with your LCD's I2C address


//  #include <RTClib.h>
// RTC_DS3231 rtc;

// // DateTime now = rtc.now();
// //             Serial.print(now.year());
// //             Serial.print('/');
// //             Serial.print(now.month());
// //             Serial.print('/');
// //             Serial.print(now.day());
// //             Serial.print(" ");
// //             Serial.print(now.hour());
// //             Serial.print(':');
// //             Serial.print(now.minute());
// //             Serial.print(':');
// //             Serial.println(now.second());



// void setup() {
//     Serial.begin(9600);
//     dht.begin();
    
//     // Initialize LCD
//     lcd.init();
//     lcd.backlight();
//     lcd.setCursor(0, 0);
//     lcd.print("Initializing...");
//        if (!rtc.begin()) {
//         Serial.println("Couldn't find RTC");
//         while (1);
//      }
//     delay(2000);
// }

// void loop() {
//     float temperature = dht.readTemperature();
//     float humidity = dht.readHumidity();
// lcd.clear();
//     if (!isnan(temperature) && !isnan(humidity)) {
//         // Print values to Serial Monitor
//         Serial.print("T: ");
//         Serial.print(temperature);
//         Serial.print("C, H: ");
//         Serial.print(humidity);
//         Serial.println("%");
//         DateTime now = rtc.now();
//             // Serial.print(now.year());
//             // Serial.print('/');
//             // Serial.print(now.month());
//             // Serial.print('/');
//             // Serial.print(now.day());
//             // Serial.print(" ");
//             // Serial.print(now.hour());
//             // Serial.print(':');
//             // Serial.print(now.minute());
//         Serial.print(':');
//         Serial.println(now.second());

//         // Print values to LCD
//         lcd.clear();
//         lcd.setCursor(0, 0);
//         lcd.print(now.second());
//         //   lcd.setCursor(0, 0);
//         lcd.print(" T: ");
//         lcd.print(temperature);
//         lcd.print("C    ");
        
//         lcd.setCursor(0, 1);
//         lcd.print("H: ");
//         lcd.print(humidity);
//         lcd.print("% ");
//     } else {
//         Serial.println("Failed to read from DHT sensor!");
        
//         // Display error on LCD
//         lcd.clear();
//         lcd.setCursor(0, 0);
//         lcd.print("Sensor Error!");
//     }
// lcd.setCursor(0, 0);
//     delay(2000); // Wait before next reading
// }