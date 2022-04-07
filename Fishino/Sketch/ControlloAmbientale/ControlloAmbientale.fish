<?xml version="1.0" encoding="UTF-8" standalone="yes" ?>
<!DOCTYPE FishIDE>
<FishIDE>
	<Files>
		<item>ControlloAmbientale.ino</item>
		<item>ArduinoJson.h</item>
	</Files>
	<Libraries>
		<key>DHT sensor library</key>
		<value value="1"/>
		<key>Wire</key>
		<value value="1"/>
		<key>Adafruit Unified Sensor</key>
		<value value="1"/>
		<key>Adafruit TSL2561</key>
		<value value="1"/>
		<key>FishinoSdFat</key>
		<value value="1"/>
		<key>Fishino</key>
		<value value="1"/>
	</Libraries>
	<OtherFiles>
		<item>C:/Users/Admin/Desktop/ads/ads.ino</item>
		<item>C:/Users/Admin/Desktop/ControlloAmbientale/ControlloAmbientale.ino</item>
		<item>[IDEFILES]\BUILD\avr\FISHINO_UNO_R2\ControlloAmbientale\ControlloAmbientale.lst</item>
	</OtherFiles>
	<OpenedFiles>
		<key>[PROJECT]\ControlloAmbientale.ino</key>
		<value>
			<Cursor value="5719"/>
			<ScrollBar value="198"/>
		</value>
	</OpenedFiles>
	<CurrentFile>[PROJECT]\ControlloAmbientale.ino</CurrentFile>
	<SerialMonitor>
		<Port>COM3</Port>
		<Speed value="9600"/>
		<Content>Light Sensor Test

------------------------------------
Gain:         Auto
Timing:       13 ms
------------------------------------

Air Quality: 38
Decibels: 44.07 , Light: 393 lux
Humidity: 32.70 %, Temperature: 26.60 °C


POST /fishino/data HTTP/1.1
Host: 10.20.5.40:5000
User-Agent: FISHINO_CA
Content-Type: application/json
Content-Length:121

{&quot; chip&quot;: &quot;dratini&quot;, humidity&quot;: &quot;32.70&quot;, &quot;temperature&quot;: &quot;26.60&quot;, &quot;airQuality&quot;: &quot;38&quot;, &quot;decibels&quot;: &quot;44.07&quot;, &quot;light&quot;: &quot;393&quot;}




Air Quality: 39
Decibels: 22.12 , Light: 390 lux
Humidity: 32.70 %, Temperature: 26.60 °C


POST /fishino/data HTTP/1.1
Host: 10.20.5.40:5000
User-Agent: FISHINO_CA
Content-Type: application/json
Content-Length:121

{&quot; chip&quot;: &quot;dratini&quot;, humidity&quot;: &quot;32.70&quot;, &quot;temperature&quot;: &quot;26.60&quot;, &quot;airQuality&quot;: &quot;39&quot;, &quot;decibels&quot;: &quot;22.12&quot;, &quot;light&quot;: &quot;390&quot;}




Air Quality: 38
Decibels: 21.77 , Light: 387 lux
Humidity: 33.10 %, Temperature: 26.60 °C


POST /fishino/data HTTP/1.1
Host: 10.20.5.40:5000
User-Agent: FISHINO_CA
Content-Type: application/json
Content-Length:121

{&quot; chip&quot;: &quot;dratini&quot;, humidity&quot;: &quot;33.10&quot;, &quot;temperature&quot;: &quot;26.60&quot;, &quot;airQuality&quot;: &quot;38&quot;, &quot;decibels&quot;: &quot;21.77&quot;, &quot;light&quot;: &quot;387&quot;}




Air Quality: 39
Decibels: 21.40 , Light: 388 lux
Humidity: 33.10 %, Temperature: 26.60 °C


POST /fishino/data HTTP/1.1
Host: 10.20.5.40:5000
User-Agent: FISHINO_CA
Content-Type: application/json
Content-Length:121

{&quot; chip&quot;: &quot;dratini&quot;, humidity&quot;: &quot;33.10&quot;, &quot;temperature&quot;: &quot;26.60&quot;, &quot;airQuality&quot;: &quot;39&quot;, &quot;decibels&quot;: &quot;21.40&quot;, &quot;light&quot;: &quot;388&quot;}




Air Quality: 38
Decibels: 21.77 , Light: 381 lux
Humidity: 34.10 %, Temperature: 26.60 °C


POST /fishino/data HTTP/1.1
Host: 10.20.5.40:5000
User-Agent: FISHINO_CA
Content-Type: application/json
Content-Length:121

{&quot; chip&quot;: &quot;dratini&quot;, humidity&quot;: &quot;34.10&quot;, &quot;temperature&quot;: &quot;26.60&quot;, &quot;airQuality&quot;: &quot;38&quot;, &quot;decibels&quot;: &quot;21.77&quot;, &quot;light&quot;: &quot;381&quot;}




</Content>
	</SerialMonitor>
</FishIDE>