# RTOS Assignment 1

## Objectives 
- In this assignment, you will use the TaskScheduler library to implement and manage real-time tasks on an Arduino or ATmega328 microcontroller. The goal is to deepen your understanding of real-time scheduling concepts such as periodic task execution, task prioritization, and task management.

## Assignment Structure
- The assignment is divided into four progressive problems, moving from basic task scheduling to advanced real-time applications.

## Suggested Tools and Resources
- Arduino IDE for development.
- Serial monitor for debugging.
- Libraries: TaskScheduler (https://github.com/arkhipenko/TaskScheduler) for
reference.
- Online Simulation platform using the provided library: https://wokwi.com/playground/task-scheduler.
- Microcontroller: Arduino Uno or similar with ATmega328 chip.

## Problem-1: Getting Started with TaskScheduler
### Objective
- Familiarize yourself with the TaskScheduler library by implementing a simple periodic scheduler.
### Tasks
1. Install the TaskScheduler library from the Arduino IDE Library Manager.
2. Create a program that performs the following:
    - **Task 1:** Blink an LED every 500 milliseconds.
    - **Task 2:** Read an analog input (e.g., from a potentiometer) every 1 second and print the value to the Serial Monitor.
### Deliverables
- A working sketch demonstrating the two tasks.
- Comments in the code explaining how the library schedules and executes tasks.
---
## Problem-2: Adding Task Control and Dependencies
### Objective
- Enhance your understanding of task management by adding task control mechanisms and handling task dependencies.
### Tasks
1. Add a new task:
    - **Task 3:** Generate a PWM signal to control the brightness of an LED every 100 ms.
2. Introduce task control:
    - Pause Task 2 (analog read) when Task 3 (PWM) is running.
    - Resume Task 2 when Task 3 completes.
3. Modify Task 1 (LED blink) to depend on Task 2:
    - Task 1 executes only if the analog input value exceeds a threshold (e.g., 512)
### Deliverables
- Sketch demonstrating task pausing, resuming, and dependencies
- A written explanation of how tasks interact and how dependencies are handled

--- 
## Problem-3: Monitoring and Dynamic Task Addition
### Objective
- Learn how to dynamically manage tasks during runtime and monitor task execution.
### Tasks
1. Add dynamic task management:
    - Dynamically add a task to log the highest analog value observed over a period.
    - The task logs data every 5 seconds and runs only for 3 cycles before being deleted.
2. Add a monitoring feature:
    - Track missed deadlines for all tasks and print the count to the Serial Monitor.
3. Test the dynamic addition/removal of tasks and ensure the scheduler handles them correctly.

### Deliverables
- Sketch demonstrating dynamic task addition/removal and monitoring.
- Explanation of how the library handles dynamic changes and tracks missed deadlines.
---
## Problem-4: Building a Real-Time Application
### Objective
- Apply your knowledge of real-time scheduling to solve a complex problem using multiple tasks.
### Project Options
1. Traffic Light Controller:
    - Simulate a traffic light system with three states: Green (5s), Yellow (2s), and Red (5s).
    - Use a separate task to monitor a pedestrian button and interrupt the traffic light sequence if pressed.
2. Multisensor Logger:
    - Read data from three sensors (e.g., temperature, humidity, light) at different intervals.
    - Aggregate the data every 5 seconds and transmit it over serial.
    - Use a task to alert if any sensor value exceeds a threshold.
3. Interactive LED Game:
    - Implement a reaction-time game:
        - Randomly turn on an LED.
        - Measure how quickly a player presses a button.
        - Display the reaction time on the Serial Monitor.
### Deliverables
- A sketch implementing one of the projects.
- A flowchart or timeline showing task execution.
- A report describing challenges faced and solutions implemented.
- Comments in the code explaining how the library schedules and executes tasks.
### Submission Requirements
- Fully commented sketches for each Task.
- A single PDF file with:
    - Code explanations and flowcharts.
    - Screenshots or photos of the project in action.
    - A brief report summarizing your learning.
---
# Outcome:
- This assignment provides hands-on experience with real-time scheduling concepts, task dependencies, dynamic task management, and applying these principles to real-world applications.