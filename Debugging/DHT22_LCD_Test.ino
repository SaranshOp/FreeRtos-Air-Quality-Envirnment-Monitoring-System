// #include <Arduino_FreeRTOS.h>
// #include <semphr.h>
// #include <Wire.h>
// #include <LiquidCrystal_I2C.h>
// #include <DHT22.h>

// #define DHTPIN 2

// // Initialize LCD (0x27 is the default I2C address, adjust if different)
// LiquidCrystal_I2C lcd(0x3F, 16, 2);
// DHT22 dht22(DHTPIN);
// SemaphoreHandle_t serialSemaphore;

// void TaskReadTempHum(void *pvParameters) {
//     for(;;) {
//         float t = dht22.getTemperature();
//         float h = dht22.getHumidity();
        
//         if(xSemaphoreTake(serialSemaphore, portMAX_DELAY) == pdTRUE) {
//             // Update LCD
//             lcd.clear();
//             lcd.setCursor(0,0);
//             lcd.print("Temp: ");
//             lcd.print(t, 1);
//             lcd.print("C");
            
//             lcd.setCursor(0,1);
//             lcd.print("Hum: ");
//             lcd.print(h, 1);
//             lcd.print("%");
            
//             xSemaphoreGive(serialSemaphore);
//         }
//         vTaskDelay(pdMS_TO_TICKS(2000));
//     }
// }

// void setup() {
//     Wire.begin();
//     lcd.init();
//     lcd.backlight();
    
//     serialSemaphore = xSemaphoreCreateMutex();
    
//     xTaskCreate(
//         TaskReadTempHum,
//         "TempHum",
//         128,
//         NULL,
//         1,
//         NULL
//     );
// }

// void loop() {
//     // Empty - handled by FreeRTOS
// }