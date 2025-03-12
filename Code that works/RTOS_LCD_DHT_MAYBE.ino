// #include <Arduino_FreeRTOS.h>
// #include <semphr.h>
// #include <RTClib.h>
// #include <Wire.h>
// #include <Adafruit_Sensor.h>
// #include <DHT22.h>
// #include <LiquidCrystal_I2C.h> // LCD library using from  https://www.ardumotive.com/i2clcden.html  for the i2c LCD library 
// #include <Wire.h>
// //define pin data
// // code works as expected can see serial output as well as count inc but have'nt tested with LCD screen.


// #define pinDATA 2 // SDA, or almost any other I/O pin

// DHT22 dht22(pinDATA); 


// LiquidCrystal_I2C lcd(0x3F, 16, 2);
// RTC_DS3231 rtc;
// SemaphoreHandle_t serialSemaphore;

// // Task handles
// TaskHandle_t dhtTaskHandle;
// // TaskHandle_t rtcTaskHandle;
// TaskHandle_t ledTaskHandle;

// // void TaskReadRTC(void *pvParameters);
// void TaskReadTempHum(void *pvParameters);
// void TaskLED(void *pvParameters);

// void setup() {
//     Serial.begin(9600);
//     Serial.println("setup running");
//     lcd.init();                      // initialize the  lcd 
//   // Print a message to the LCD.
//     lcd.backlight();
//     lcd.setBacklight(HIGH);
//     while(!Serial) { ; }
    
//     // Initialize semaphore before using it
//     serialSemaphore = xSemaphoreCreateMutex();
//     if(serialSemaphore == NULL) {
//         Serial.println("Semaphore creation failed!");
//         while(1);
//     }
    
//     // Initialize sensors
//     Wire.begin();
//     // delay(2000);
//     // if (!rtc.begin()) {
//     //     Serial.println("Couldn't find RTC");
//     //     while (1);
//     // }
//     // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
//     Serial.println("Creating tasks...");
    
//     // Create tasks with proper error checking
//     BaseType_t xReturned;
//     // xReturned = xTaskCreate(
//     //     TaskReadRTC,
//     //     "ReadRTC",
//     //     128,    // Adjusted stack size
//     //     NULL,
//     //     1,      // Same priority
//     //     &rtcTaskHandle
//     // );
    
//     // if(xReturned != pdPASS) {
//     //     Serial.println("RTC Task creation failed!");
//     //     while(1);
//     // }
    
//     xReturned = xTaskCreate(
//         TaskLED,
//         "",
//         256,    // Adjusted stack size
//         NULL,
//         1,      // Same priority
//         &ledTaskHandle
//     );
    
//     if(xReturned != pdPASS) {
//         Serial.println("LED Task creation failed!");
//         while(1);
//     }
//     xReturned = xTaskCreate(
//         TaskReadTempHum,
//         "",
//         128,    // Adjusted stack size
//         NULL,
//         1,      // Same priority
//         &dhtTaskHandle
//     );
    
//     if(xReturned != pdPASS) {
//         Serial.println("DHT Task creation failed!");
//         while(1);
//     }
    
//     vTaskStartScheduler();
//     Serial.println("Setup complete");
// }

// void loop() {
//     // Empty - handled by FreeRTOS
// }

// void TaskReadTempHum(void *pvParameters) {
//     // Initial delay to ensure proper startup
//     // vTaskDelay(pdMS_TO_TICKS(100));
//     float temperature = -1;
//     float humidity = -1;
//     for(;;) {
//         if(xSemaphoreTake(serialSemaphore, portMAX_DELAY) == pdTRUE) {
//             Serial.println("DHT Reading...");
//             float t = dht22.getTemperature();
//             float h = dht22.getHumidity();

//             if (dht22.getLastError() != dht22.OK) {
//               Serial.print("last error :");
//               Serial.println(dht22.getLastError());
//             }
//             Serial.print("h=");Serial.print(h,1);Serial.print("\t");
//             Serial.print("t=");Serial.println(t,1);
//             // delay(2000); //Collectin
//             xSemaphoreGive(serialSemaphore);
//         }
//         // delay(100);
//         // Serial.println("outside semaphore");
//         // delay(100);
//         // if(xSemaphoreTake(serialSemaphore, portMAX_DELAY) == pdTRUE){
//         //   // Serial.println(dht22.debug()); //optionnal

//         //   float t = dht22.getTemperature();
//         //   float h = dht22.getHumidity();

//         //   if (dht22.getLastError() != dht22.OK) {
//         //     Serial.print("last error :");
//         //     Serial.println(dht22.getLastError());
//         //   }
//         //   Serial.print("h=");Serial.print(h,1);Serial.print("\t");
//         //   Serial.print("t=");Serial.println(t,1);
//         //   // delay(2000); //Collectin
//         //   xSemaphoreGive(serialSemaphore);
//         // }
//         // taskYIELD();
//         vTaskDelay(pdMS_TO_TICKS(3000));
//     }
// }
// void TaskLED(void *pvParameters) {
//     // Initial delay to ensure proper startup
//     // vTaskDelay(pdMS_TO_TICKS(100));
//     auto count = 0x00;
//     for(;;) {
//         if(xSemaphoreTake(serialSemaphore, portMAX_DELAY) == pdTRUE) {
//             // lcd.setCursor(0,0);
//             // lcd.print("t: ");
//             lcd.print(count);
//             Serial.println(count++);
//             // lcd.clear();
//             delay(1000);
//             lcd.clear();
//             lcd.setCursor(0, 0);
//             delay(100);
//             // delay(2000);
//             xSemaphoreGive(serialSemaphore);
//         }
//         // taskYIELD();
//         // delay(100);
//         // Serial.println("outside semaphore");
//         // delay(100);
//         // if(xSemaphoreTake(serialSemaphore, portMAX_DELAY) == pdTRUE){
          
//         //   // lcd.print("H: ");
//         //   // // lcd.print(h);
//         //   // lcd.print("%");
//         //   // lcd.setCursor(0,1);
//         //   // // lcd.print("T: "); 
//         //   // lcd.print(t);
//         //   // lcd.print("'C ");
//         //   // lcd.setCursor(0,0);
//         //   // Serial.println(dht22.debug()); //optionnal
//         //   // delay(2000); //Collectin
//         //   xSemaphoreGive(serialSemaphore);
//         // }
//         // taskYIELD();
//         vTaskDelay(pdMS_TO_TICKS(1000));
//     }
// }

// // void TaskReadRTC(void *pvParameters) {
// //     // Initial delay to ensure proper startup
// //     Serial.println("RTC reading starts");
// //     // vTaskDelay(pdMS_TO_TICKS(100));
    
// //     for(;;) {
// //         if(xSemaphoreTake(serialSemaphore, portMAX_DELAY) == pdTRUE) {
// //             DateTime now = rtc.now();
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
// //             xSemaphoreGive(serialSemaphore);
// //         }
// //         vTaskDelay(pdMS_TO_TICKS(1000));
// //     }
// // }