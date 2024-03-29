/*
Water Flow Sensor
Water Flow Sensor output processed to read in litres/hour
*/

volatile int flow_frequency; // Measures flow sensor pulses
unsigned int l_hour; // Calculated litres/hour
unsigned char flowsensor = 2; // Sensor Input
unsigned long currentTime;
unsigned long cloopTime;
  int piezoPin = 8;
  int sum=0;
void flow () // Interrupt function
{
   flow_frequency++;
}
void setup()
{
   pinMode(flowsensor, INPUT);
   digitalWrite(flowsensor, HIGH); // Optional Internal Pull-Up
   Serial.begin(9600);
   attachInterrupt(0, flow, RISING); // Setup Interrupt
   sei(); // Enable interrupts
   currentTime = millis();
   cloopTime = currentTime;
}
void loop ()
{
   currentTime = millis();
   // Every second, calculate and print litres/hour
   if(currentTime >= (cloopTime + 1000))
   {
      cloopTime = currentTime; // Updates cloopTime
      // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
      l_hour = (flow_frequency * 60 / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flowrate in L/hour
      flow_frequency = 0; // Reset Counter
      sum=sum+l_hour;
      Serial.print(l_hour, DEC); // Print litres/hour
      Serial.println(" L/hour");
      Serial.print(sum);
      Serial.println(" L/hour");
   }
   if(sum>300||(l_hour>5&&l_hour<10))
   {
     tone(piezoPin, 1000, 500);
     if(sum>300)
     {
     sum=0;
     }

  //tone(piezoPin, 1000, 500);
 
  noTone(20000000);
  }
   }
