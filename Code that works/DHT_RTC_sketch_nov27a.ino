// #include <Arduino_FreeRTOS.h>
// #include <semphr.h>  // Add semaphore support
// #include <RTClib.h>
// #include <Wire.h>
// #include "DHT.h"

// #define DHTTYPE DHT22
// #define DHTPIN 2

// // Global variables
// DHT dht(DHTPIN, DHTTYPE);
// RTC_DS3231 rtc;
// SemaphoreHandle_t serialSemaphore;  // For serial port access

// // Task declarations
// void TaskReadRTC(void *pvParameters);
// void TaskReadTempHum(void *pvParameters);

// void setup() {
//     Serial.begin(9600);
//     while(!Serial) { ; }  // Wait for serial port
    
//     // Initialize semaphore
//     serialSemaphore = xSemaphoreCreateMutex();
    
//     // Initialize sensors
//     pinMode(DHTPIN, INPUT);
//     dht.begin();
    
//     if (!rtc.begin()) {
//         Serial.println("Couldn't find RTC");
//         while (1);
//     }
    
//     // Create tasks with larger stack sizes
//     xTaskCreate(
//         TaskReadTempHum,
//         "TempHum",
//         128*4,    // Increased stack size
//         NULL,
//         1,        // Higher priority
//         NULL
//     );
    
//     // xTaskCreate(
//     //     TaskReadRTC,
//     //     "ReadRTC",
//     //     128*3,    // Increased stack size
//     //     NULL,
//     //     1,        // Lower priority
//     //     NULL
//     // );
    
//     Serial.println("Setup complete");
//     vTaskStartScheduler();
// }

// void loop() {
//     // Empty - handled by FreeRTOS
// }

// void TaskReadTempHum(void *pvParameters) {
//   Serial.println("DHT task start ");
//     (void) pvParameters;
//     TickType_t xLastWakeTime;
//     xLastWakeTime = xTaskGetTickCount();
    
//     for (;;) {
//         float temperature = dht.readTemperature();
//         float humidity = dht.readHumidity();
        
//         if (xSemaphoreTake(serialSemaphore, (TickType_t)10) == pdTRUE) {
//             if (!isnan(temperature) && !isnan(humidity)) {
//                 Serial.print("Temperature: ");
//                 Serial.print(temperature);
//                 Serial.print("°C, Humidity: ");
//                 Serial.print(humidity);
//                 Serial.println("%");
//             } else {
//                 Serial.println("DHT Reading Failed!");
//             }
//             xSemaphoreGive(serialSemaphore);
//         }
        
//         // Use absolute timing instead of relative delays
//         vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(2000));
//     }
// }

// void TaskReadRTC(void *pvParameters) {
//   Serial.println("RTC task start ");
//     (void) pvParameters;
//     TickType_t xLastWakeTime;
//     xLastWakeTime = xTaskGetTickCount();
    
//     for (;;) {
//         DateTime now = rtc.now();
        
//         if (xSemaphoreTake(serialSemaphore, (TickType_t)10) == pdTRUE) {
//             Serial.print(now.year(), DEC);
//             Serial.print('/');
//             Serial.print(now.month(), DEC);
//             Serial.print('/');
//             Serial.print(now.day(), DEC);
//             Serial.print(" ");
//             Serial.print(now.hour(), DEC);
//             Serial.print(':');
//             Serial.print(now.minute(), DEC);
//             Serial.print(':');
//             Serial.println(now.second(), DEC);
//             xSemaphoreGive(serialSemaphore);
//         }
        
//         vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(5000));
//     }
// }