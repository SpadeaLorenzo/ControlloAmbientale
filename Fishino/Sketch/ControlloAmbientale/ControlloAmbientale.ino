//Libraries
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>
#include <DHT.h>
#include <FishinoSdFat.h>
#include <ArduinoJson.h>
#include <Fishino.h>

//Constants
#define DHTPIN 2 // what pin the DHT22 is connected to
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor
// SD values
#define CHIP_NAME "dratini" // Fishino's name
#define SERVER "10.20.5.40:5000" // server's address
// WIFI Parameters
#define SSID "Ciscom"
#define PASSWORD "fishino32"

//Variables

StaticJsonBuffer<170> jsonBuffer;
JsonObject &json = jsonBuffer.createObject();

const char *chip_number;
const char *ssid;
const char *password;
const char *server;

//Fishino values

// Sensor values
float humidity;	   // Stores humidity value
float temperature; // Stores temperature value
float decibel;	   // Stores decibel value
int airQuality;	   // Stores air quality value
int light;		   // Stores light value

Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);

/**
 * Displays some basic information on the TSL2561 sensor from the unified
 * sensor API sensor_t type.
 */
void displaySensorDetails()
{
	sensor_t sensor;
	tsl.getSensor(&sensor);
	Serial.println("------------------------------------");
	Serial.print("Sensor:       ");
	Serial.println(sensor.name);
	Serial.print("Driver Ver:   ");
	Serial.println(sensor.version);
	Serial.print("Unique ID:    ");
	Serial.println(sensor.sensor_id);
	Serial.print("Max Value:    ");
	Serial.print(sensor.max_value);
	Serial.println(" lux");
	Serial.print("Min Value:    ");
	Serial.print(sensor.min_value);
	Serial.println(" lux");
	Serial.print("Resolution:   ");
	Serial.print(sensor.resolution);
	Serial.println(" lux");
	Serial.println("------------------------------------");
	Serial.println("");
	delay(500);
}

/**
 * Configures the gain and integration time for the TSL2561
 */
/**************************************************************************/
void configureSensor()
{
	/* You can also manually set the gain or enable auto-gain support */
	// tsl.setGain(TSL2561_GAIN_1X);      /* No gain ... use in bright light to avoid sensor saturation */
	// tsl.setGain(TSL2561_GAIN_16X);     /* 16x gain ... use in low light to boost sensitivity */
	tsl.enableAutoRange(true); /* Auto-gain ... switches automatically between 1x and 16x */

	/* Changing the integration time gives you better sensor resolution (402ms = 16-bit data) */
	tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS); /* fast but low resolution */
	// tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_101MS);  /* medium resolution and speed   */
	// tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_402MS);  /* 16-bit data but slowest conversions */

	/* Update these values depending on what you've set above! */
	Serial.println("------------------------------------");
	Serial.print("Gain:         ");
	Serial.println("Auto");
	Serial.print("Timing:       ");
	Serial.println("13 ms");
	Serial.println("------------------------------------");
}

void getSdconfigJson()
{
	SdFat sd;
	while (!sd.begin(SDCS))
	{
	}
	File config_file;
	char config_line[180];
	int char_index = 0;
	char byte_config;

	config_file = sd.open("config.txt", FILE_READ);

	char_index = 0;
	while (config_file.available())
	{
		byte_config = config_file.read();
		if (byte_config >= 32 && byte_config <= 126)
		{
			config_line[char_index] = (char)byte_config;
		}
		char_index++;
	}
	config_file.close();
	jsonBuffer.clear();
	JsonObject &json = jsonBuffer.parseObject(config_line);

	chip_number = json["chip_number"];
	ssid = json["ssid"];
	password = json["password"];
	server = json["server"];

	jsonBuffer.clear();
	Serial.println("SD letta");
}

void readCo2()
{
	airQuality = analogRead(0); // Read analog input pin A0
	//double ppm_percentage = (double)airQuality/100000;

	Serial.print("Air Quality: ");
	Serial.println(airQuality); // Print the value read
	//	Serial.println("\%");
}

void readDecibels()
{
	int sample;					 // Sample used by max4466 sensor
	const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
	long startMillis = millis(); // Start of sample window
	int peakToPeak = 0;			 // peak-to-peak level

	int signalMax = 0;
	int signalMin = 1024;

	// collect data for 50 mS
	while (millis() - startMillis < sampleWindow)
	{
		sample = analogRead(A1);
		if (sample < 1024)
		{ // toss out spurious readings
			if (sample > signalMax)
			{
				signalMax = sample; // save just the max levels
			}
			else if (sample < signalMin)
			{
				signalMin = sample; // save just the min levels
			}
		}
	}
	peakToPeak = signalMax - signalMin;						// max - min = peak-peak amplitude
	double volts = ((peakToPeak * 3.3) / 1024) /** 0.707*/; // 3.3V
	double first = log10(volts / 0.00631) * 20;
	decibel = first /*+ 94 - 44*/;
	Serial.print("Decibels: ");
	Serial.print(decibel);
	Serial.print(" , Light: ");
}

void readLight()
{
	sensors_event_t event; // Get a new sensor event
	tsl.getEvent(&event);

	if (event.light)
	{
		// Display the results (light is measured in lux)
		Serial.print((int)event.light);
		light = (int)event.light;
		Serial.println(" lux");
	}
	else
	{
		/* If event.light = 0 lux the sensor is probably saturated
		   and no reliable data could be generated! */
		Serial.println("Sensor overload");
	}
}

void readHumidity()
{
	humidity = dht.readHumidity();
	Serial.print("Humidity: ");
	Serial.print(humidity);
	Serial.print(" \%");
}

void readTemperature()
{
	temperature = dht.readTemperature();
	Serial.print(", Temperature: ");
	Serial.print(temperature);
	Serial.println(" °C");
}

String createPacket()
{
	String json_data = "{";
	//json_data = json_data + "\"chip\": \"" + String(chip_number);
	json_data = json_data + "\"chip\": \"" + CHIP_NAME;
	json_data = json_data + "\", humidity\": \"" + String(humidity);
	json_data = json_data + "\", \"temperature\": \"" + String(temperature);
	json_data = json_data + "\", \"airQuality\": \"" + String(airQuality);
	json_data = json_data + "\", \"decibels\": \"" + String(decibel);
	json_data = json_data + "\", \"light\": \"" + String(light);
	json_data = json_data + "\"}";

	return json_data;
}

void sendData(String json_data)
{
	/*
	FishinoClient client;

	if (client.status())
	{
		client.stop();
	}

	client.connect(server, 80);*/
	Serial.println("POST /fishino/data HTTP/1.1");
	Serial.print("Host: ");
	//Serial.println(server);
	Serial.println(SERVER);
	Serial.println("User-Agent: FISHINO_CA");
	Serial.println("Content-Type: application/json");
	Serial.print("Content-Length:");
	Serial.println(json_data.length());
	Serial.println();
	Serial.println(json_data);
	//client.flush();
	//client.stop();
}

void setup(void)
{
	Serial.begin(9600);
	Serial.println("Light Sensor Test");
	Serial.println("");

	/* Initialise the sensor */
	// tsl.begin() to default to Wire,
	// tsl.begin(&Wire2) directs api to use Wire2, etc.
	if (!tsl.begin())
	{
		Serial.print("ERROR: no TSL2561 detected");

		while (!tsl.begin())
		{ // waits until the sensor is connected
			Serial.print(".");
			delay(2000);
		}
	}

	/* Display some basic information on this sensor */
	//displaySensorDetails();

	/* Setup the sensor gain and integration time */
	configureSensor();
	Serial.println();

	dht.begin();
	
	//getSdconfigJson();

	//WIFI
	/*
	Fishino.setMode(STATION_MODE);
	while (!Fishino.begin(SSID, PASSWORD)){}
	Fishino.staStartDHCP();
	Serial.print("Connecting..");
	while (Fishino.status() != STATION_GOT_IP)
	{
		Serial.print(".");
		delay(500);
	}*/
}

void loop(void)
{
	readCo2();
	readDecibels();
	readLight();
	readHumidity();
	readTemperature();
	Serial.println("\n");
	sendData(createPacket());

	Serial.println("\n\n\n");
	delay(1500);
}
