// Blink
// Turns the Bootloader LED on for one second, then off for one second, repeatedly.
const int LED = 0;

void setup() {
  // initialize digital pin 13 as an output.
  pinMode(LED, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED, HIGH);
  delay(1000);            
  digitalWrite(LED, LOW); 
  delay(1000);            
}