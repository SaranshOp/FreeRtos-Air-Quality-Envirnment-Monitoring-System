// #include <Arduino_FreeRTOS.h>
// #include <semphr.h>
// #include <RTClib.h>
// #include <Wire.h>
// #include "DHT.h"

// #define DHTTYPE DHT22
// #define DHTPIN 2

// // Global variables
// DHT dht(DHTPIN, DHTTYPE);
// RTC_DS3231 rtc;
// SemaphoreHandle_t serialSemaphore;

// // Task handles
// TaskHandle_t dhtTaskHandle;
// TaskHandle_t rtcTaskHandle;

// void TaskReadRTC(void *pvParameters);
// void TaskReadTempHum(void *pvParameters);

// void setup() {
//     Serial.begin(9600);
//     while(!Serial) { ; }
    
//     // Initialize semaphore before using it
//     serialSemaphore = xSemaphoreCreateMutex();
//     if(serialSemaphore == NULL) {
//         Serial.println("Semaphore creation failed!");
//         while(1);
//     }
    
//     // Initialize sensors
//     Wire.begin();
//     dht.begin();
    
//     if (!rtc.begin()) {
//         Serial.println("Couldn't find RTC");
//         while (1);
//     }
    
//     Serial.println("Creating tasks...");
    
//     // Create tasks with proper error checking
//     BaseType_t xReturned;
    
//     xReturned = xTaskCreate(
//         TaskReadTempHum,
//         "TempHum",
//         256,    // Adjusted stack size
//         NULL,
//         1,      // Same priority
//         &dhtTaskHandle
//     );
    
//     if(xReturned != pdPASS) {
//         Serial.println("DHT Task creation failed!");
//         while(1);
//     }
    
//     // xReturned = xTaskCreate(
//     //     TaskReadRTC,
//     //     "ReadRTC",
//     //     256,    // Adjusted stack size
//     //     NULL,
//     //     1,      // Same priority
//     //     &rtcTaskHandle
//     // );
    
//     if(xReturned != pdPASS) {
//         Serial.println("RTC Task creation failed!");
//         //while(1);
//     }
    
//     Serial.println("Setup complete");
// }

// void loop() {
//     // Empty - handled by FreeRTOS
// }

// void TaskReadTempHum(void *pvParameters) {
//     // Initial delay to ensure proper startup
//     vTaskDelay(pdMS_TO_TICKS(100));
//     for(;;) {

//         if(xSemaphoreTake(serialSemaphore, portMAX_DELAY) == pdTRUE) {
//             Serial.println("DHT Reading...");
//             xSemaphoreGive(serialSemaphore);
//         }
        
//         float temperature = dht.readTemperature();
//         float humidity = dht.readHumidity();
        
//         if(xSemaphoreTake(serialSemaphore, portMAX_DELAY) == pdTRUE) {
//             if (!isnan(temperature) && !isnan(humidity)) {
//                 Serial.print("Temp: ");
//                 Serial.print(temperature);
//                 Serial.print("C, Hum: ");
//                 Serial.print(humidity);
//                 Serial.println("%");
//             } else {
//                 Serial.println("DHT Failed!");
//             }
//             xSemaphoreGive(serialSemaphore);
//         }
        
//         vTaskDelay(pdMS_TO_TICKS(2000));
//     }
// }

// void TaskReadRTC(void *pvParameters) {
//     // Initial delay to ensure proper startup
//     vTaskDelay(pdMS_TO_TICKS(100));
    
//     for(;;) {
//         if(xSemaphoreTake(serialSemaphore, portMAX_DELAY) == pdTRUE) {
//             DateTime now = rtc.now();
//             Serial.print(now.year());
//             Serial.print('/');
//             Serial.print(now.month());
//             Serial.print('/');
//             Serial.print(now.day());
//             Serial.print(" ");
//             Serial.print(now.hour());
//             Serial.print(':');
//             Serial.print(now.minute());
//             Serial.print(':');
//             Serial.println(now.second());
//             xSemaphoreGive(serialSemaphore);
//         }
        
//         vTaskDelay(pdMS_TO_TICKS(5000));
//     }
// }