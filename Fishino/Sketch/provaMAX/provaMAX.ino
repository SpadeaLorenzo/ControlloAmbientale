/****************************************
Example Sound Level Sketch for the 
Adafruit Microphone Amplifier
****************************************/

const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
int sample;

void setup()
{
   Serial.begin(9600);
}

void getDecibel(String ut)
{
   const int sampleWindow = 50;
   unsigned int sample;
   unsigned long startMillis = millis();
   unsigned int peakToPeak = 0;
   unsigned int signalMax = 0;
   unsigned int signalMin = 1024;

   while (millis() - startMillis < sampleWindow)
   {

      sample = analogRead(0);
      if (sample < 1024)
      {
         if (sample > signalMax)
         {
            signalMax = sample;
         }
         else if (sample < signalMin)
         {
            signalMin = sample;
         }
      }
   }
   peakToPeak = signalMax - signalMin;
   double volts = ((peakToPeak * 3.3) / 1024) * 0.707;
   double first = log10(volts / 0.00631) * 20;
   double decibel = first + 94 - 44;

   /*String data_string = "{";
   data_string = data_string + "\"cn\": \"" + String(chip_number);
   data_string = data_string + "\", \"ut\": " + ut;
   data_string = data_string + ", \"d\": " + String(decibel);
   data_string = data_string + "}";

   Post(data_string);*/
}

void loop()
{
   long startMillis = millis(); // Start of sample window
   int peakToPeak = 0;          // peak-to-peak level
   
   int signalMax = 0;
   int signalMin = 1024;

   // collect data for 50 mS
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(A1);
      if (sample < 1024) // toss out spurious readings
      {
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
   peakToPeak = signalMax - signalMin;      // max - min = peak-peak amplitude
   double volts = ((peakToPeak * 3.3) / 1024) * 0.707; // 3.3V
   double first = log10(volts / 0.00631) * 20;
   double decibel = first /*+ 94 - 44*/;
   Serial.print("Decibels: ");
   Serial.println(decibel);
   delay(251);
}
