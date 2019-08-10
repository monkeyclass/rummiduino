# Rummiduino
A arduino project for a countdown "clock" with board games in mind.\

The clock does not display how much time is left, but rather indicates it using a green, yellow and red LED to blink 1/3 of the time each, to keep information simple in the situation. When the time is up a speaker beeps for five seconds.

## Functionality
The code enables the following functionality to the rummiduino:
1. Button no. 1 (start button) to start countdown of time (1 minute by default).
2. Button no. 2 (pause button) to pause the time (disagreements happens in board games where I come from).
3. Button no. 3 (stop button) stop and resets the timer.
4. Pressing start button while the timer is running will restart the timer.
5. Pressing pause and stop button simultaneously enables setting the countdown timer.
  * each lit LED indicates 30 seconds, e.g. red + yellow = 1 minute.
  * More or less time is controlled with pause and stop buttons.
  * Exit and set time by pressing start button.



## Design
Breadboard layout for the rummiduino. Made with Tinkercad.
![alt text](https://raw.githubusercontent.com/monkeyclass/rummiduino/master/circuitDrawing.png)
