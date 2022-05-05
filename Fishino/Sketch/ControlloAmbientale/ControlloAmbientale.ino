//Libraries
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>
#include <DHT.h>
#include <Fishino.h>

// SD chip select pin
#ifdef SDCS
const uint8_t chipSelect = SDCS;
#else
const uint8_t chipSelect = SS;
#endif

//Constants and Sensors
#define DHTPIN 2 // what pin the DHT22 is connected to
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor

// SD values (hard coded)
#define CHIP_NAME "eevee" // Fishino's name
#define SERVER "controlloambientale.pythonanywhere.com" // server's address
// WIFI Parameters
#define SSID "M306"
#define PASSWORD "306piccoleonde"

//Variables

//Fishino values

// Sensor values
float humidity;	   // Stores humidity value
float temperature; // Stores temperature value
float decibel;	   // Stores decibel value
int airQuality;	   // Stores air quality value
int light;		   // Stores light value

Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);

/**
 * Configures the gain and integration time for the TSL2561
 */
void configureSensor() {
	tsl.enableAutoRange(true); // Auto-gain ... switches automatically between 1x and 16x 

	// Changing the integration time gives you better sensor resolution (402ms = 16-bit data)
	tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS); /// fast but low resolution

	Serial.println("TSL configuration");
	Serial.println("------------------------------------");
	Serial.print("Gain:         ");
	Serial.println("Auto");
	Serial.print("Timing:       ");
	Serial.println("13 ms");
	Serial.println("------------------------------------");
}

void readCo2() {
	// Store the value into the variable
	airQuality = analogRead(0); // Read analog input pin A0 (raw data)
}

void readDecibels() {
	int sample;					 // Sample used by max4466 sensor
	const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
	long startMillis = millis(); // Start of sample window
	int peakToPeak = 0;			 // peak-to-peak level

	int signalMax = 0;
	int signalMin = 1024;

	// collect data for 50 mS
	while (millis() - startMillis < sampleWindow) {
		sample = analogRead(A1);
		if (sample < 1024) { // toss out spurious readings
			if (sample > signalMax) {
				signalMax = sample; // save just the max levels
			} else
				if (sample < signalMin) {
					signalMin = sample; // save just the min levels
				}
		}
	}
	peakToPeak = signalMax - signalMin;	// max - min = peak-peak amplitude
	double volts = ((peakToPeak * 3.3) / 1024); // 3.3V
	double first = log10(volts / .00631) * 20;

	// Store the value into the variable
	decibel = first;
}

void readLight() {
	sensors_event_t event; // Get a new sensor event
	tsl.getEvent(&event);

	if (event.light) {
		// Store the value into the variable
		light = (int)event.light;
	} else {
		/* If event.light = 0 lux the sensor is probably saturated
		   and no reliable data could be generated! */
		Serial.println("Sensor overload");
	}
}

void readHumidity() {
	// Store the value into the variable
	humidity = dht.readHumidity();
}

void readTemperature() {
	temperature = dht.readTemperature();
}

String createPacket() {
	String json_data = "{";
	json_data = json_data + "\"name\": \"" + CHIP_NAME +
				"\", \"humidity\": " + String(humidity) +
				", \"brightness\": " + String(light) +
				", \"noise\": " + String(decibel) +
				", \"co2\": " + String(airQuality)+
				", \"temperature\": " + String(temperature) + "}";
	
	return json_data;
}

void sendData(String json_data) {
	FishinoClient client;

	if (client.status()) {
		client.stop();
	}

	client.connect(SERVER, 80); // connect to server on HTTP port
	client.println("POST /fishino/data HTTP/1.1");
	client.print("Host: ");
	client.println(SERVER);
	client.println("User-Agent: FISHINO_CA");
	client.println("Content-Type: application/json");
	client.print("Content-Length: ");
	client.println(json_data.length());
	client.println();
	client.print(json_data);

	client.flush();
	client.stop();
}

void testPacket(String json_data) {
	Serial.println("POST /fishino/data HTTP/1.1");
	Serial.print("Host: ");
	Serial.println(SERVER);
	Serial.println("User-Agent: FISHINO_CA");
	Serial.println("Content-Type: application/json");
	Serial.print("Content-Length: ");
	Serial.println(json_data.length());
	Serial.println();
	Serial.print(json_data);
}

void connectWiFi() {
	while (!Fishino.begin(SSID, PASSWORD)) {}
	Fishino.staStartDHCP();
	Serial.print("Connecting to WIFI..");
	while (Fishino.status() != STATION_GOT_IP) {
		Serial.print(".");
		delay(300);
	}
}

void setup(void) {
	Serial.begin(9600);

	//WIFI
	Fishino.setMode(STATION_MODE);
	connectWiFi();

	Serial.println("Init sensors");
	Serial.println("");

	/* Initialise the sensor */
	if (!tsl.begin()) {
		Serial.print("ERROR: no TSL2561 detected");

		while (!tsl.begin()) { // waits until the sensor is connected
			Serial.print(".");
			delay(2000);
		}
	}

	/* Setup the sensor gain and integration time */
	configureSensor();

	Serial.println();
	dht.begin();
}

void loop(void) {
	readCo2();
	readDecibels();
	readLight();
	readHumidity();
	readTemperature();
	Serial.println("\n");
	String packet = createPacket();
	sendData(packet);
	testPacket(packet);

	Serial.println("\n\n\n");
	delay(300000);
}
