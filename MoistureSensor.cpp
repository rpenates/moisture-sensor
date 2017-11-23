#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <DHT_U.h>

// 0x3F for Green display 0x27 for the blue one
#define I2C_ADDR 0x3F
#define LED_ON 0
#define LED_OFF 1

DHT_Unified dht (2, 11);
LiquidCrystal_I2C display(I2C_ADDR, 16, 2);

uint32_t delayMS;

void setup() {
	display.init();
	dht.begin();
	display.backlight();
    display.begin (16,2);
    display.setBacklight(LED_OFF);

    sensor_t sensor;
    dht.temperature().getSensor(&sensor);
    dht.humidity().getSensor(&sensor);
    delayMS = sensor.min_delay / 500;
}

void loop() {

	delay(delayMS);
	sensors_event_t event;

    display.backlight();
    display.setCursor(0,0);

    dht.temperature().getEvent(&event);
    if (isnan(event.temperature)){
    	display.print("Temp: ---");
    } else {
    	String str1 = "Temp: ";
    	String str2 = String(int(event.temperature));
    	display.print(str1);
    	display.setCursor(str1.length(), 0);
    	display.print(str2);
    	display.setCursor(str1.length() + str2.length(), 0);
    	display.print("*C");
    }

    dht.humidity().getEvent(&event);
    display.setCursor(0,1);
    if (isnan(event.relative_humidity)){
    	display.print("Humedad: ---");
    } else {
    	String str1 = "Humedad: ";
    	String str2 = String(int(event.relative_humidity));
    	display.print(str1);
    	display.setCursor(str1.length(), 1);
    	display.print(str2);
    	display.setCursor(str1.length() + str2.length(), 1);
    	display.print("%");
    }

}
