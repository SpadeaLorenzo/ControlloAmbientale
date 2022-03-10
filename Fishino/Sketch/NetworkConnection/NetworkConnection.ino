// Project : 'NetworkConnection'
// Created by FishIDE application 
#include <Fishino.h>


#define MIO_SSID "Ciscom"
#define MIA_PASSWORD "dio ladro"


void setup(){
	// apre la porta seriale e ne attende l’apertura
// consigliabile da eseguire come primo comando per poter visualizzare
// eventuali messaggi di errore sul monitor seriale
Serial.begin(9600);
// attende l’apertura della porta seriale.
// Necessario solo per le boards Leonardo
while (!Serial) ;
// inizializza il modulo SPI
/*SPI.begin();
SPI.setClockDivider(SPI_CLOCK_DIV2);
// resetta e testa il modulo WiFi
if(Fishino.reset())
 Serial.println("Fishino WiFi reset OK");
else
{
 Serial.println("Fishino WiFi reset FAILED");

 // attende per sempre 
 while(true);
}*/
Serial.println("Qui ci sono");
	while(!Fishino.begin(MIO_SSID, MIA_PASSWORD));
}

void loop()
{
	Fishino.setMode(STATION_MODE);
	
	while(true)
	{
	 if(Fishino.begin(MIO_SSID,MIA_PASSWORD)) {
	 Serial.print("Connected to "); 
	 Serial.println(MIO_SSID);
	 break; 
	 } 
	 else { 
	 Serial.println("Failed connecting to ");
	 Serial.println(MIO_SSID);
	 Serial.println("Retrying....."); 
	 }
	}

	
	delay(10000);
}
