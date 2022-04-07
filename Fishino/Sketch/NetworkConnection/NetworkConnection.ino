// Project : 'NetworkConnection'
// Created by FishIDE application
#include <Fishino.h>


#define MIO_SSID "Ciscom"
#define MIA_PASSWORD "fishino32"


void setup() {
	// apre la porta seriale e ne attende l’apertura
// consigliabile da eseguire come primo comando per poter visualizzare
// eventuali messaggi di errore sul monitor seriale
	Serial.begin(9600);
// attende l’apertura della porta seriale.
// Necessario solo per le boards Leonardo
	while (!Serial)
		;
	Serial.println("Serial passato");
// inizializza il modulo SPI
	SPI.begin();
	SPI.setClockDivider(SPI_CLOCK_DIV2);
// resetta e testa il modulo WiFi
	if (Fishino.reset())
		Serial.println("Fishino WiFi reset OK");
	else {
		Serial.println("Fishino WiFi reset FAILED");

// attende per sempre
		while (true)
			;
	}
	Serial.println("Qui ci sono");
	while (!Fishino.begin(MIO_SSID, MIA_PASSWORD))
		;
}

void loop() {
	Fishino.setMode(STATION_MODE);

	// se la connessione riesce, allora si esce dal loop
	// se no continua a provarsi a connettere.
	while (true) {
		if (Fishino.begin(MIO_SSID,MIA_PASSWORD)) {
			Serial.print("Connected to ");
			Serial.println(Fishino.SSID());
			break;
		} else {
			Serial.println("Failed connecting to ");
			Serial.println(MIO_SSID);
			Serial.println("Retrying.....");
		}

	}
	
	Serial.print("IP: ");
	Serial.println(Fishino.localIP());
	
	uint8_t const *mac = Fishino.macAddress();
	Serial.print("MAC ");
	for (int i = 0; i < WL_MAC_ADDR_LENGTH; i++) {
		Serial.print(":");
		Serial.print(mac[i], HEX);
	}
	Serial.println();
	delay(10000);
}
