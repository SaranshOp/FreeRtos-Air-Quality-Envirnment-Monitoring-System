#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <RTClib.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <DHT22.h>
//define pin data
#define pinDATA 2 // SDA, or almost any other I/O pin

DHT22 dht22(pinDATA); 


struct SensorData {
  DateTime time;
  float temperature;
  float humidity;
  int mq135_value;
};
SensorData sensorData;

RTC_DS3231 rtc;
SemaphoreHandle_t xsensorDataMutex;

// Task handles
TaskHandle_t dhtTaskHandle;
TaskHandle_t rtcTaskHandle;
TaskHandle_t mq135TaskHandle;
TaskHandle_t printvalHandle;

void TaskReadRTC(void *pvParameters);
void TaskReadTempHum(void *pvParameters);
void TaskReadmq135(void *pvParameters);
void TaskPrintVal(void *pvParameters);

void setup() {
    sensorData.humidity = -1;
    sensorData.temperature = -1;
    Serial.begin(9600);
    Serial.println("setup running");
    while(!Serial) { ; }
    
    // Initialize semaphore before using it
    xsensorDataMutex = xSemaphoreCreateMutex();
    if(xsensorDataMutex == NULL) {
        Serial.println("Semaphore creation failed!");
        while(1);
    }
    
    // Initialize sensors
    Wire.begin();
    // delay(2000);
    if (!rtc.begin()) {
        Serial.println("Couldn't find RTC");
        while (1);
    }
    
    Serial.println("Creating tasks...");
    
    // Create tasks with proper error checking
    BaseType_t xReturned;
    xReturned = xTaskCreate(
        TaskReadRTC,
        "",
        64,    // Adjusted stack size
        NULL,
        2,      // Same priority
        &rtcTaskHandle
    );
    
    if(xReturned != pdPASS) {
        Serial.println("RTC Task creation failed!");
        while(1);
    }
    
    xReturned = xTaskCreate(
        TaskReadTempHum,
        "",
        64,    // Adjusted stack size
        NULL,
        2,      // Same priority
        &dhtTaskHandle
    );
    
    if(xReturned != pdPASS) {
        Serial.println("DHT Task creation failed!");
        while(1);
    }
    
    xReturned = xTaskCreate(
        TaskPrintVal,
        "",
        64,    // Adjusted stack size
        NULL,
        1,      // Same priority
        &printvalHandle
    );
    
    if(xReturned != pdPASS) {
        Serial.println("print Task creation failed!");
        while(1);
    }

    xReturned = xTaskCreate(
        TaskReadmq135,
        "",
        64,    // Adjusted stack size
        NULL,
        2,      // Same priority
        &mq135TaskHandle
    );
    
    if(xReturned != pdPASS) {
        Serial.println("MQ135 Task creation failed!");
        while(1);
    }
    vTaskStartScheduler();
    Serial.println("Setup complete");
}

void loop() {
    // Empty - handled by FreeRTOS
}

void TaskReadTempHum(void *pvParameters) {
    for(;;) {
        if(xSemaphoreTake(xsensorDataMutex, portMAX_DELAY) == pdTRUE){

          if (dht22.getLastError() != dht22.OK) {
            Serial.print("last error :");
            Serial.println(dht22.getLastError());
          }
          sensorData.temperature = dht22.getTemperature();
          sensorData.humidity = dht22.getHumidity();
          xSemaphoreGive(xsensorDataMutex);
        }
        // taskYIELD();
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void TaskReadRTC(void *pvParameters) {
    for(;;) {
        if(xSemaphoreTake(xsensorDataMutex, portMAX_DELAY) == pdTRUE) {
            sensorData.time = rtc.now();
            xSemaphoreGive(xsensorDataMutex);
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
void TaskReadmq135(void *pvParameters) {
    for(;;) {
        if(xSemaphoreTake(xsensorDataMutex, portMAX_DELAY) == pdTRUE){
          sensorData.mq135_value = analogRead(0); 
          xSemaphoreGive(xsensorDataMutex);
        }
        // taskYIELD();
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
void TaskPrintVal(void *pvParameters) {
    for(;;) {
        if(xSemaphoreTake(xsensorDataMutex, portMAX_DELAY) == pdTRUE) {
          Serial.print(sensorData.time.year());
            Serial.print('/');
            Serial.print(sensorData.time.month());
            Serial.print('/');
            Serial.print(sensorData.time.day());
            Serial.print(" ");
            Serial.print(sensorData.time.hour());
            Serial.print(':');
            Serial.print(sensorData.time.minute());
            Serial.print(':');
            Serial.println(sensorData.time.second());

            Serial.print("h=");Serial.print(sensorData.humidity,1);Serial.print("\t");
            Serial.print("t=");Serial.println(sensorData.temperature,1);

            Serial.print(sensorData.mq135_value,  DEC); // prints the value read
            Serial.println(" PPM");
            Serial.println("-------------------");
          xSemaphoreGive(xsensorDataMutex);
        }
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}