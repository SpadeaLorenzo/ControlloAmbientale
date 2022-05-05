1. [Introduzione](#introduzione)

  - [Informazioni sul progetto](#informazioni-sul-progetto)

  - [Abstract](#abstract)

  - [Scopo](#scopo)

1. [Analisi](#analisi)

  - [Analisi del dominio](#analisi-del-dominio)
  
  - [Analisi dei mezzi](#analisi-dei-mezzi)

  - [Analisi e specifica dei requisiti](#analisi-e-specifica-dei-requisiti)

  - [Use case](#use-case)

  - [Pianificazione](#pianificazione)

    - [Gantt preventivo](#gantt-preventivo)

1. [Progettazione](#progettazione)

  - [Design dell’architettura del sistema](#design-dell’architettura-del-sistema)

  - [Design dei dati e database](#design-dei-dati-e-database)

1. [Implementazione](#implementazione)

  - [Fishino](#fishino)

    - [Protocollo di comunicazione](#Protocollo-di-comunicazione-(non-completato-e-non-utilizzato))

      - [Conversione da float a bytes](#Conversione-da-float-a-bytes)
    
    - [Lettura dati sensori](#lettura-dati-sensori)

      - [MAX4466](#MAX4466-(Sensore-suono))

      - [TSL 2561](#TSL-2561-(Sesore-luminosità))
      
      - [DHT22](#DHT-(Sensore-umidità-e-temperatura))

      - [MQ 135](#MQ-135-(Sensore-qualità-aria))

    - [Connessione alla rete Wireless](#Connessione-alla-rete-Wireless)

    - [ Comunicazione Fishino - Applicazione](#Comunicazione-Fishino---Applicazione)

      - [createPacket](#createPacket)

      - [sendData](#sendData)

      - [Struttura pacchetto HTTP](#Struttura-pacchetto-HTTP)

1. [Test](#test)

  - [Protocollo di test](#protocollo-di-test)

  - [Risultati test](#risultati-test)

  - [Mancanze/limitazioni conosciute](#mancanze/limitazioni-conosciute)

1. [Consuntivo](#consuntivo)

1. [Conclusioni](#conclusioni)

  - [Sviluppi futuri](#sviluppi-futuri)

  - [Considerazioni personali](#considerazioni-personali)

  - [Erik](#Erik)

1. [Sitografia](#sitografia)

1. [Allegati](#allegati) 


## Introduzione

### Informazioni sul progetto
  - Autori: Nicola Anghileri, Erik Pelloni, Lorenzo Spadea.
  - Classe: I3BB
  - Docente responsabile: Geo Petrini, Guido Montalbetti
  - Data inizio: 27.02.2022
  - Data fine: 05.05.2022 

### Abstract

  > *Nowadays it can be important and interesting to know information about the 
  > ambiental situation in workplaces.
  > The "Controllo Ambientale" project allows you to analyse data on temperature, 
  > humidity, air quality, noise and brightness in a very simple way, 
  > also using simple and effective graphics.
  > So there is a website that provides graphs containing this data.
  > Furthermore, it is possible to see the trend of these data over time, also thanks to averages.
  > This data is measured by sensors connected to devices located at various places within the fourth floor of the school.*

### Scopo

  Lo scopo del progetto è quello di creare un applicativo Web, che tramite l'uso di diversi 
  fishino, posizionati all'interno della scuola, andrà a fornire dei dati ambientali (poi mostrati sotto forma di grafici).
  I dati che verrano elaborati riguardano la luminosità dell'ambiente, l'umidità,
  la quantità di CO2 presente nell'aria e la temperatura. Grazie all'interfaccia WEB si 
  potrà intuitivamente controllare lo stato dell'ambiente dove si trova un fishino specifico.


## Analisi

### Analisi del dominio

  In questo momento non sappiamo a cosa sia sottoposto il nostro corpo mentre siamo all'interno della nostra sede scolastica, 
  questo è il motivo per cui esiste il nostro progetto, verranno installati diversi apparecchi che raccolgono 
  dati inerenti alla qualità dell'aria, al rumore, all'umidità e alla temperatura.
  Grazie a questi dati raccolti ogni 5 minuti in diverse posizioni all'interno della nostra sede scolastica, 
  potremo scoprire se esistono dei problemi, come ad esempio la qualità dell'aria troppo bassa ecc...
  Al momento in alcune classi sono già presenti dei sensori che forniscono dei dati riguardo il valore di CO2,
  il tutto però non è facilmente accessibile agli allievi. Questo verrà migliorato e facilitato grazie al nostro progetto, il quale si occuperà di raccogliere i 5 dati importanti, 
  già elencati in precedenza e di renderli accessibili tramite la creazione di grafici intuitivi.

### Analisi e specifica dei requisiti



|**ID**	|**Nome**			                                    |**Priorità**|**Vers**|**Note**  |
|-------|-------------------------------------------------|------------|--------|----------|
|Req-001|Scrivere il codice per la raccolta e trasmissione|1           |1.0     |          |
|Req-002|Protocollo trasmissione                          |1           |1.0     |          |
|Req-003|Progettare e realizzare case                     |3           |1.0     |          |
|Req-004|Salvataggio dati in DB                           |1           |1.0     |          |
|Req-005|Elaborazione dati tempo reale                    |1           |1.0     |          |
|Req-006|Scelta grafici sito                              |1           |1.0     |          |
|Req-007|Sistema amministrazione                          |1           |1.0     |          |
|Req-008|Host separati per Web e DB                       |1           |1.0     |          |
|Req-009|Associazione con MAC Address                     |1           |1.0     |          |


### Use case
<img src="assets/use_case.png" height="400">
<br><br>

|**Tipo**	|**Cosa può fare**			                                    |
|---------|-----------------------------------------------------------|
|User     |Vedere i grafici dell'ambiente attraverso la GUI           |
|Admin    |<ul><li>Aggiungere ed eliminare istanze di fishino dalla lista</li><li>Eliminare dati</li><li>Creare utenti</li></ul>|

<br>

### Pianificazione

Una delle prime attività svolte dal gruppo è stata la pianificazione. Per svolgerla
abbiamo usato Microsoft Project come supporto per creare il diagramma di Gantt.

Abbiamo deciso i diversi ruoli e abbiamo strutturato il diagramma in base a quest'ultimi.
Le attività all'interno dell'implementazione sono divise nei sottogruppi `Fishino`, `Front-End` e `Back-End`.

Un diagramma di Gantt è comodo per la pianificazione di un progetto. 
Con l'ausilio di questo strumento è possibile scomporre un grande progetto in piccole attività utilizzando il metodo 
[top-down](https://it.wikipedia.org/wiki/Progettazione_top-down_e_bottom-up),rendendolo più semplice e chiaro da affrontare.

#### Gantt preventivo

![gantt_preventivo](assets/Gantt_Preventivo_ControlloAmbientale.png)


### Analisi dei mezzi

#### **Descrizione componenti Fishino**

***DHT 22, temperatura e umidità***

<img src="assets/sensori/dht22.jpg" alt="DHT22" height="150"  style="float: left; margin:0 10px 0 0">

Questo sensore misura la temperatura in gradi Celsius e l'umidità in percentuale.

I dati vengono immagazzinati dentro a dei pacchetti di 5 byte composti in questo modo:

Dal più al meno signficativo nell'ordine: Byte alto umidità relativa, Byte basso umidità
relativa, Byte alto temperatura, Byte basso temperatura, Checksum.

I valori decimali vengono moltiplicati per 10, come nell'esempio seguente:

`Se l'umidità è del 59.4%, verrà salvato il numero 594 in questa composizione: il primo byte è 0000 0010 e il secondo è 0101 0010.`

La stessa cosa avviene anche per la temperatura (terzo e quarto byte).
L'ultimo bit (il 16°), però, rappresenta il segno: vale 1 se la temperatura
è negativa e 0 se è postiva.

|Alimentazione|Pin|
|-------------|---|
|5V           |2  |

<br>

***MQ 135, qualità dell'aria***

<img src="assets/sensori/mq135.jpg" alt="MQ135" height="150"  style="float: left; margin:0 10px 0 0">

Questo sensore misura la qualità dell'aria e i gas contenuti in essa.

La lettura analogica ritorna 1023 (valore massimo) se non viene rilevato gas. 
Quando c'è gas, il valore sarà più alto.
Dalle misure che ho preso in classe, in una situazione normale il valore si aggira attorno ai 20-30, facendo analizzare il gas dell'accendino il valore sale fino
anche fino a 920.
I valori analogici sono 0 se c'è gas e 1 se non ce n'è.


|Alimentazione|Pin|
|-------------|---|
|5V           |A0 |

<br>

***TSL 2561, luminosità***

<img src="assets/sensori/tsl2561.jpg" alt="TSL2561" height="150"  style="float: left; margin:0 10px 0 0">

```cpp
tsl.enableAutoRange(true)
``` 
configura il "gain" automaticamente in base all'amiente circostante. 
È utile per non dover cambiare il codice in base al fatto che le misurazioni siano prese
all'interno, all'esterno o con diverse situazioni. Il gain può essere configurato
manualmente con un valore che va da 1x a 16x.

Di default, il sensore ritorna i dati in unità `lux`, cioè il risultato di complessi
calcoli matematici basati sui valori registrati dal sensore.

Questo sensore ritorna valori nel range [0.1; 40'000], castati poi in int siccome vengono
sempre misurati dei numeri interi.



|Alimentazione| Pin      |
|-------------|----------|
|3.3V         |SDA e SCL |

<br>

***MAX 4466, microfono (suono)***

<img src="assets/sensori/max4466.jpg" alt="MAX4466" height="150"  style="float: left; margin:0 10px 0 0">

I suoni misurati possono assumere valori da 0.00 a 3.30, cioè il valore in volt.
Questo valore viene trasformato in decibel utilizzando la formula
`20 * log(Audio output voltage/ Audio input voltage)` 


|Alimentazione|Pin|
|-------------|---|
|3.3V         |A1 |

<br>

#### **Librerie Fishino**

<br>

***Fishino*** Versione 8.0.0

Questa libreria è stata utilizzata per gestire tutta la parte di connessione alla rete e con il server, quindi anche l'invio dei dati.

La documentazione completa è disponibile a questo [link](https://www.fishino.it/libraries.html).

***Wire***

Questa libreria è stata utilizzata per la comunicazione tra il fishino e i sensori.

La documentazione completa è disponibile a questo [link](https://www.arduino.cc/en/reference/wire).

***Adafruit_Sensor*** Versione 1.1.5

Questa libreria è stata utilizzata per leggere nel modo corretto i dati registrati dai sensori.
Sono state utilizzate anche delle librerie specifiche per certi sensori.
Tutte queste implementano metodi e attributi che semplificano la lettura dei dati, ad esempio l'attributo
`light` per la lettura della luminosità del sensore TSL.

La documentazione completa è disponibile a questo [link](https://github.com/adafruit/Adafruit_Sensor).

***Adafruit_TSL2561_U***

Questa libreria è specifica per la lettura dei dati interenti alla luminosità letti dal sensore TSL2561.

La documentazione completa è disponibile a questo [link](https://github.com/adafruit/Adafruit_TSL2561).

***DHT***

Questa libreria è specifica per la lettura dei dati interenti alla temperatura e all'umidità letti dal sensore DHT22.
Sono presenti dei metodi molto comodi come ad esempio
```cpp
readHumidity()

readTemperature()
```
<br>

**Librerie utilizzate ma non implementate completamente**

Queste librerie sono state utilizzate per la stesura del codice, però, purtroppo, le parti di codice dove vengono utilizzate
non sono implementate nel codice finale a causa di problemi (di natura sconosciuta) con la lettura della scheda sd.

***Fishino SdFat*** Versione 8.0.0

Questa libreria mette a disposizione dei metodi utili per ciò che riguarda la lettura dei file presenti all'interno della scheda microSd
integrata nel Fishino.

Il repository originale è disponibile a questo [link](https://github.com/systronix/SdFat_greiman).

***ArduinoJson*** Versione 5.13.5

Questa libreria permette di leggere e scrivere in formato Json.

La documentazione completa è disponibile a questo [link](https://arduinojson.org/v5/doc/).

## Progettazione

### Design dell’architettura del sistema

<!-- DIMENSIONI ORIGINALI 
![schema_di_rete](assets/schema_rete.png)
-->
<img src="assets/schema_rete.png" height="500">

#### Application Design

<!-- DIMENSIONI ORIGINALI 
![application design](../application_design.png)
-->
<img src="assets/application_design.png" height="400">



### Design dei dati e database

Per questo progetto abbiamo deciso di utilizzare un database MySQL.
<!--agiungere le info per il db-->

### Schema E-R, schema logico e descrizione.

### Design delle interfacce

### Design procedurale

## Implementazione

### **FISHINO**

### Protocollo di comunicazione (non completato e non utilizzato)
**Al posto di questo, viene utilizato il protocollo HTTP**

Segue una descrizione del protocollo di comunicazione che è stato creato per permettere ai vari Fishino
di passare i dati all'applicazione web.

#### Conversione da float a bytes
Questi sono i metodi utilizzati per memorizzare il valore delle variabili di tipo long (numeri interi di 32 bit) e
float (numeri a virgola mobile di 32 bit) all'interno di 2 byte.

```cpp
byte *long2bytes(long number)
{
  byte *array = new byte[2];
  long value = (long)(number * 10);
  //shift, mask and put in array
  array[0] = (number & 65280) >> 8;
  array[1] = (byte)number;
  return array;
}

byte *float2bytes(float number)
{
  return long2bytes((long)(number * 10));
}
```

Partendo dal principio: `byte*` significa `puntatore di byte`, in questo caso simile ad un array, cioè
una sequenza di valori all'interno della memoria.

Questi metodi prendono il valore, poi con degli shift e con dei cast li inseriscono all'interno del puntatore.

Lo schema seguente mostra, in modo più dettagliato, il funzionamento di questi metodi.

<img src="./assets/spiegazione_conversione_bytes.png" alt="schema conversione" width="500">

I valori float vengono trasformati in valori interi (nel caso specifico, `long`) semplicemente facendo una moltiplicazione
per 10, poi vengono trattati nello stesso modo in cui vengono trattati i numeri interi.

Come detto in origine, nel progetto, questi metodi non vengono utilizzati, siccome è sato deciso di utilizzare il protocollo HTTP, 
già presente all'interno di librerie per Fishino.

### Lettura dati sensori

#### MAX4466 (Sensore suono)

Per leggere correttamente i dati del sensore MAX4466 bisogna impostare i valori `sample` e `sample window` (finesrta di sample).
Vegono poi letti i dati per un certo lasso di tempo, dato dalla finestra di sample.

Il valore passato come output è la quantità di rumore in volt.
Questo viene convertito in decibel utilizzando la formula già documentata in precedenza (vedi documentazione sensore). 


#### TSL 2561 (Sesore luminosità)

Come prima cosa bisogna generare un evento. Per assegnargli un valore viene poi utilizzata la libreria documentata precedentemente.

```cpp
sensors_event_t event; // creo l'evento
tsl.getEvent(&event); // gli assegno un valore. 
```

la variabile `tsl` è di tipo `Adafruit_TSL2561_Unified`, *per maggiori informazioni leggere il capitolo riguardante le [librerie](#Librerie-Fishino)*.

Se il valore `event.light` è maggiore di 0, allora il valore viene salvato.
Se il valore invece è uguale a 0, significa che molto probabilmente il sensore è andato in overload.

#### DHT (Sensore umidità e temperatura)

La lettura di umidità e temperatura avviene semplicemente utilizzando i metodi messi a disposizione dalla libreria DHT, come nel seguente esempio.

```cpp
void readTemperature() {
  // salvo il valore nella variabile
	temperature = dht.readTemperature();
}
```

`dht` è una variabile di tipo `DHT`, *per maggiori informazioni leggere il capitolo riguardante le [librerie](#Librerie-Fishino)*.

#### MQ 135 (Sensore qualità aria)

Per leggere il  valore misurato dal sensore MQ 135 basta semplicemente leggere il valore sul pin analogico al quale è collegato.

Possono poi essere utilizzate delle formule per calcolare percentuali o altri dati come le parti per milione (ppm).

### Connessione alla rete Wireless

La connessione alla rete viene effettuata all'interno del metodo `connectWiFi()`.

```cpp
void connectWiFi() {
	while (!Fishino.begin(SSID, PASSWORD)) {}
	Fishino.staStartDHCP();
	Serial.print("Connecting to WIFI..");
	while (Fishino.status() != STATION_GOT_IP) {
		Serial.print(".");
		delay(300);
	}
}
```

Si può notare che in questo metodo viene utilizzata la classe `Fishino`, [documentata in precedenza](#Librerie-Fishino).

Questo metodo prova a connettersi alla rete specificata e aspetta finché non riceve un indirizzo IP.
Una volta ricevuto l'indirizzo si è connessi alla rete.

Questo metodo viene richiamato all'interno del metodo `setup` per effettuare la prima connessione e nel metodo `loop` per
permettere la riconnessione nel caso in cui il fishino si scolleghi dalla rete.

**SSID:** nome della rete alla quale ci si deve connettere
**Password:** password della rete alla quale ci si deve connettere

### Comunicazione Fishino - Applicazione

La comunicazione tra i fishino e l'applicazione avviene tramite richieste HTTP 1.1.
La creazione di questi pacchetti è documentata qui sotto:

#### createPacket

Il metodo `createPacket()` si occupa di creare il corpo della richiesta, cioè la parte formattata in Json contenente i dati rilevati.

Questo metodo ritorna una stringa contenente la richiesta da inviare al server.

#### sendData

Il metodo `sendData` si occupa di diverse cose:
1. Stabilire la connessione con il server
1. Inviare il pacchetto HTTP al server*
1. Chiudere la connessione con il server

\* il metodo sendData si occupa anche di completare il pacchetto HTTP nel momento in cui lo invia, aggiungendo l'header.

#### Struttura pacchetto HTTP

I pacchetti HTTP inviati dai fishino hanno la seguente struttura

```http
POST <route> HTTP/1.1
Host: <host>
User-Agent: FISHINO_CA
Content-Type: application/json
Content-Length: <length>

{"chip": <chip_name>, "humidity": ..., "temperature": ..., "airQuality": ..., "decibels": ..., "light": ...}
```

Al posto di `<route>` viene messo il percorso (all'interno del sito) al quale mandare i dati.

È indispensabile lasciare una riga vuota tra l'header e il contenuto della richiesta.

Questo pacchetto viene ricevuto e poi interpretato dal server.

## Test

### Protocollo di test

#### Test Fishino

|Test Case            | TC-001                                         |
|---------------------|------------------------------------------------|
|**Nome**             | Raccolta dati                                  |
|**Riferimento**      | REQ-001                                        |
|**Descrizione**      | I dati inerenti all'ambiente vengono raccolti  |
|**Prerequisiti**     | Fishino, sensori e parte di codice funzionanti |
|**Procedura**        | Far partire un programma che misuri e ritorni (magari stampando a terminale) i valori dell'ambiente (temperatura,...) |
|**Risultati attesi** |I dati vengono raccolti e stampati correttamente|

|Test Case            | TC-002                                         |
|---------------------|------------------------------------------------|
|**Nome**             | Invio dati                                     |
|**Riferimento**      | REQ-001                                        |
|**Descrizione**      | I dati raccolti vengono inviati correttamente al server  |
|**Prerequisiti**     | Fishino, sensori e parte di codice funzionanti |
|**Procedura**        | Far partire un programma che misuri e invii i valori dell'ambiente (temperatura,...). Controllare che siano arrivati correttamente al server |
|**Risultati attesi** |I dati vengono inviati e ricevuti correttamente |

|Test Case            | TC-003                                         |
|---------------------|------------------------------------------------|
|**Nome**             | Protocollo trasmissione                        |
|**Riferimento**      | REQ-002                                        |
|**Descrizione**      | I dati vengono inviati utilizzando un protocollo di trasmissione adeguato  |
|**Prerequisiti**     | Codice sorgente                                |
|**Procedura**        | Controllare che l'invio dei dati avvenga tramite un protocollo adeguato (ad esempio HTTP) |
|**Risultati attesi** | Viene utilizzato un protocollo adeguato        |

|Test Case            | TC-004                                         |
|---------------------|------------------------------------------------|
|**Nome**             | Lettura dati scheda SD                         |
|**Riferimento**      | N/D                                            |
|**Descrizione**      | Dati inerenti al fishino e alla connessione Wi-Fi sono salvati sulla scheda SD. Questi dati vengono letti e utilizzati  |
|**Prerequisiti**     | Fishino, scheda sd e parte dicodice funzionanti|
|**Procedura**        | Controllare che questi dati vengano presi dalla scheda SD e che non siano messi a mano nel codice. |
|**Risultati attesi** | I dati sono scritti e vengono letti sulla/dalla scheda SD|


### Risultati test

| ID Test | Passato | Non Passato | Note                       |
|---------|---------|-------------|----------------------------|
| TC-001  | ✔      |             |                            |
| TC-002  | ✔      |             |                            |
| TC-003  | ✔      |             | Viene utilizzato HTTP 1.1  |
| TC-004  |        | ✘           | Ci sono stati degli errori con la lettura della scheda|

### Mancanze/limitazioni conosciute


## Consuntivo


## Conclusioni


### Sviluppi futuri


### Considerazioni personali


## Bibliografia

### Sitografia

1.  URL del sito (se troppo lungo solo dominio, evt completo nel
    diario),

2.  Eventuale titolo della pagina (in italico),

3.  Data di consultazione (GG-MM-AAAA).

**Esempio:**

-   http://standards.ieee.org/guides/style/section7.html, *IEEE Standards Style Manual*, 07-06-2008.

## Allegati

-   [Diari di lavoro](../Diari)

-   [Codice sorgente fishino](../../Fishino/Sketch/ControlloAmbientale/ControlloAmbientale.ino)

-   [Quaderno dei compiti](../qdc.docx)

-   [Link al sito](https://controlloambientale.pythonanywhere.com)
