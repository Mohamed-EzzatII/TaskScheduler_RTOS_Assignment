#include <TaskScheduler.h> 
// Include the TaskScheduler library for managing periodic tasks.

#define LED_PIN 13 
// Define the pin number for the LED.

#define PWM_PIN 9 
// Define the pin number for the PWM output (connected to an LED or motor).

#define THREE_SHOLD 512 
// Define a threshold value for the potentiometer reading (mid-point of a 10-bit ADC).

// Create a Scheduler object to manage all tasks.
Scheduler st; 

// Declare task functions.
void readPot();  // Function to read the potentiometer value.
void blink();    // Function to blink the LED based on the potentiometer value.
void pwmLed();   // Function to control PWM brightness of an LED.

// Create a task for blinking the LED every 500 ms, linked to the Scheduler.
Task lblink(500, TASK_FOREVER, blink, &st); 

// Create a task for reading the potentiometer every 1000 ms, linked to the Scheduler.
Task pot(1000, TASK_FOREVER, readPot, &st); 

// Create a task for controlling PWM brightness every 100 ms, linked to the Scheduler.
Task pwm(100, TASK_FOREVER, pwmLed, &st); 

void setup() {
  // Initialize serial communication at a baud rate of 9600.
  Serial.begin(9600); 
  
  // Set the LED pin as an output pin.
  pinMode(LED_PIN, OUTPUT);

  // Set the PWM pin as an output pin.
  pinMode(PWM_PIN, OUTPUT);
  
  // Enable the blinking task.
  lblink.enable();
  
  // Enable the potentiometer reading task.
  pot.enable(); 

  // Enable the PWM brightness control task.
  pwm.enable();
}

void loop() {
  // Execute all enabled tasks in the scheduler.
  st.execute(); 
}

void blink() {
  // Read the analog value from the potentiometer (pin A0).
  int value = analogRead(A0); 

  // If the potentiometer value is greater than or equal to the threshold, toggle the LED.
  if (value >= THREE_SHOLD) {
    digitalWrite(LED_PIN, !digitalRead(LED_PIN)); 
  }
}

void readPot() {
  // Read the analog value from the potentiometer (pin A0).
  int value = analogRead(A0); 

  // Print the potentiometer value to the serial monitor.
  Serial.print("Analog Value = "); 
  Serial.println(value);
}

void pwmLed() {
  // Disable the potentiometer reading task temporarily.
  pot.disable();

  // Define a static variable to hold the brightness level (0-255).
  static unsigned char brightness = 0;

  // Increment the brightness by 10 each time the function is called.
  brightness += 10;

  // Write the brightness level to the PWM pin.
  analogWrite(PWM_PIN, brightness);

  // Re-enable the potentiometer reading task.
  pot.enable();
}
