// Include the TaskScheduler library for managing periodic tasks.
#include <TaskScheduler.h> 

// Define the pin number connected to the LED.
#define LED_PIN 12

// Create a Scheduler object to manage tasks.
Scheduler st;

// Function to toggle the LED state.
void blink() {
  // Change the LED state by writing the opposite of its current state.
  digitalWrite(LED_PIN, !digitalRead(LED_PIN)); 
}

// Function to read the analog value from the potentiometer.
void readPot() {

  // Read the analog input value from pin A0.
  int value = analogRead(A0); 

  // Send The Analog Value to serial monitor
  Serial.print("Analog Value = "); 
  Serial.println(value); 
}

// Create a task named `lblink` to run the `blink` function every 500 ms.
// TASK_FOREVER means the task will run indefinitely.
// &st links the task to the Scheduler instance.
Task lblink(500, TASK_FOREVER, blink, &st); 

// Create a task named `pot` to run the `readPot` function every 1000 ms.
Task pot(1000, TASK_FOREVER, readPot, &st); 

void setup() {
  
  // Initialize serial communication at a baud rate of 9600.
  Serial.begin(9600); 
  
  // Set the LED pin as an output pin.
  pinMode(LED_PIN, OUTPUT);
  
  // Enable the `lblink` task. 
  lblink.enable();
  
  // Enable the `pot` task. 
  pot.enable(); 
}

void loop() {
  // Call the Scheduler's `execute` method to run enabled tasks as per their schedules.
  st.execute(); 
}
