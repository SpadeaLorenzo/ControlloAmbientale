//Libraries
#include <DHT.h>

//Constants
#define DHTPIN 2          // what pin we're connected to
#define DHTTYPE DHT22     // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

//Variables
float humidity;    //Stores humidity value
float temperature; //Stores temperature value

void setup()
{
  Serial.begin(9600);
  dht.begin();
}

void loop()
{
  /**DHT22, TEMPERATURE AND HUMIDITY**/
  //Read data and store it to variables humidiy and temperature
  humidity = dht.readHumidity();       // humidity in percent
  temperature = dht.readTemperature(); // temperature in °C
  //Print temperature and humidity values to serial monitor
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" \%, Temp: ");
  Serial.print(temperature);
  Serial.println(" °C");
  delay(2000); //Delay 2 sec.
}
