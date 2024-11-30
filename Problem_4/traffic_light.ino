#include <TaskScheduler.h>  // Include the TaskScheduler library for multitasking
Scheduler sc;               // Create a scheduler instance to manage tasks

// Define task indices for readability
#define RED_TASK    0
#define GRN_TASK    1
#define YELLOW_TASK 2
#define BTN_TASK    3

// Define pin numbers for the LEDs and button
#define RED_LED    7
#define YELLOW_LED 6
#define GRN_LED    5
#define BTN        3

// Function prototypes for task callbacks and interrupt handler
void red_led();
void green_led();
void yellow_led();
void button();
void btnHandler();

// Array to store the periods (delays) for each task in milliseconds
unsigned int tasksPeroid[] = {5000, 5000, 2000, 100};

// Flag to track if the button was pressed
bool pushed = false;

// Task objects for each LED and the button
Task redTask(tasksPeroid[RED_TASK], TASK_FOREVER, red_led, &sc);   // Red LED task
Task greenTask(tasksPeroid[GRN_TASK], TASK_FOREVER, green_led, &sc); // Green LED task
Task yellowTask(tasksPeroid[YELLOW_TASK], TASK_FOREVER, yellow_led, &sc); // Yellow LED task
Task buttonTask(tasksPeroid[BTN_TASK], TASK_FOREVER, button, &sc);  // Button task

void setup() {
    // Configure LED pins as outputs
    pinMode(RED_LED, OUTPUT);
    pinMode(GRN_LED, OUTPUT);
    pinMode(YELLOW_LED, OUTPUT);

    // Configure built-in LED and button pin
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(BTN, INPUT);

    // Attach an interrupt to the button pin (rising edge triggers the interrupt)
    attachInterrupt(digitalPinToInterrupt(BTN), btnHandler, RISING);

    // Ensure all LEDs are initially OFF
    digitalWrite(RED_LED, LOW);
    digitalWrite(GRN_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);

    // Enable the green light task and button task at startup
    greenTask.enable();
    buttonTask.enable();
}

void loop() {
    // Execute tasks managed by the scheduler
    sc.execute();
}

// Callback function for the red LED task
void red_led() {
    // Disable tasks for yellow and green LEDs while red is active
    yellowTask.disable();
    greenTask.disable();

    // Turn ON the red LED and turn OFF the others
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GRN_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);

    // Wait for the red task period
    delay(tasksPeroid[RED_TASK]);

    // Enable the green LED task after red finishes
    greenTask.enable();

    // Reset the pushed flag as the cycle is restarting
    pushed = false;
}

// Callback function for the green LED task
void green_led() {
    unsigned long start = millis(); // Record the start time for the task

    // Disable tasks for yellow and red LEDs while green is active
    yellowTask.disable();
    redTask.disable();

    // Turn ON the green LED and turn OFF the others
    digitalWrite(RED_LED, LOW);
    digitalWrite(GRN_LED, HIGH);
    digitalWrite(YELLOW_LED, LOW);

    // Keep the green LED ON for the specified period or until the button is pressed
    while ((tasksPeroid[GRN_TASK] >= millis() - start) && !pushed);

    // Enable the yellow LED task after green finishes
    yellowTask.enable();
}

// Callback function for the yellow LED task
void yellow_led() {
    // Disable tasks for red and green LEDs while yellow is active
    redTask.disable();
    greenTask.disable();

    // Turn ON the yellow LED and turn OFF the others
    digitalWrite(RED_LED, LOW);
    digitalWrite(GRN_LED, LOW);
    digitalWrite(YELLOW_LED, HIGH);

    // Wait for the yellow task period
    delay(tasksPeroid[YELLOW_TASK]);

    // Enable the red LED task after yellow finishes
    redTask.enable();

    // Reset the pushed flag as the cycle is restarting
    pushed = false;
}

// Callback function for the button task
void button() {
    // Check if the button is pressed and the green task is active
    if (digitalRead(BTN) == HIGH && greenTask.isEnabled()) {
        // Delete and disable the green task
        sc.deleteTask(greenTask);
        greenTask.disable();

        // Turn OFF all LEDs
        digitalWrite(RED_LED, LOW);
        digitalWrite(GRN_LED, LOW);
        digitalWrite(YELLOW_LED, HIGH);

        // Restart the yellow LED task immediately
        yellowTask.enable();

        buttonTask.disable();           // Disable the button task
    }
}

// Interrupt Service Routine (ISR) for the button
void btnHandler() {
    pushed = true;                 // Set the flag to indicate the button was pressed
    buttonTask.enable();           // Enable the button task to process the event
}
