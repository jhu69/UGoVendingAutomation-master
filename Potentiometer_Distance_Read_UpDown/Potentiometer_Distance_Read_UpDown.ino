/*
 
***NOTE:
1) LOW -> ON for relay modules 
2) HIGH -> OFF for relay modules
3) ActuatorHot and ActuatorNeutral are controlled by relays

*/



int Read[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};  // Array to hold Actuator Portentiometer Reads
int ValRef = 0;  // Holder value for use during quicksort
const int Potentiometer = A1;    // Actuator Potentiometer Pin


const int pinButtonBlend = 2;   // Button for blending
const int pinButtonClean = 3;   // Button for cleaning 
const int ActuatorHot = 7;   // Actuator rises when the hot line is activated 
const int ActuatorNeutral = 8;   // Actuator lowers when the neutral line is activated 

void setup() {   // Setup for the different pins as either ouput or input/active or non-active 

  pinMode(Potentiometer, INPUT);
  pinMode(pinButtonBlend, INPUT);
  pinMode(pinButtonClean, INPUT);
  pinMode(ActuatorHot, OUTPUT);
  pinMode(ActuatorNeutral, OUTPUT);

  digitalWrite(ActuatorHot, HIGH); // Initializes actuator up to be inactive
  digitalWrite(ActuatorNeutral, HIGH); // Initializes actuator down to be inactive 
  // Put your setup code here, to run once:
  // Initialize serial communications at 9600 bps:
  Serial.begin(9600); // 
  Serial.println();
  /*
  Serial.print("Origonal List: ");
  for(int i = 0; i < 15; i++)
  {
    Serial.print(Read[i]);
    Serial.print(", ");
  }
  
  QuickSort (); 
  Serial.println();
  Serial.println("Sorted List: ");
  for(int i = 0; i < 15; i++)
  {
    Serial.print(Read[i]);
    Serial.print(", ");
  }
  */
  
  
}

int MeasureDistance()  // Measure distance of actuator - takes 15 reads to compensate for inaccuracy
{
  for (int i = 0; i < 15; i++)
  {
    Read [i] = analogRead(Potentiometer); // Runs through the array and sets value
    delay(1); 
  }
  QuickSort();  // Call sort method to sort entries 
  return Read[7];   // Send middle read value which is supposed to be the intended distance
}

void QuickSort ()  // Quick sort algorithm to arrange an array of length 15 in ascending order
{
  for (int i = 0; i < 14; i++)
  {
    for (int j = i+1 ; j>0; j--)
    if (Read[j] < Read[j-1])      // Element out of order
    {
      ValRef = Read[j];  // Tempory hold value j
      Read[j] = Read[j-1];  // Replace j with higher entry
      Read[j-1] = ValRef;  // Replace other entry
    }
  }
}

void loop() {   // Put your main code here, to run repeatedly:
 Serial.println();
 Serial.print("Read: "); // Prints to serial monitor "Read:"
 Serial.print(MeasureDistance()); // Prints to serial monitor what's returned in the MeasureDistance() method, which is the middle value of the array

 digitalWrite(ActuatorHot, HIGH);       // If making sure actuator is inactive for both directions 
 digitalWrite(ActuatorNeutral, HIGH);

 if (digitalRead(pinButtonBlend) == LOW) // If blend button is pressed (LOW) then activate actuator sequence shown below
 {
     digitalWrite(ActuatorHot, LOW);
 }
 
  if (digitalRead(pinButtonClean) == LOW) // If clean button is pressed (LOW) then activate actuator sequence shown below
 {
     digitalWrite(ActuatorNeutral, LOW);
 }
 
 delay(15);
}



