# Arduino-Bluetooth-Car-With-Speaker

This was the project for CSE331L. Code was written by me, Rafifa Jahir, Rahman Mushfiq (Mushfiqqq), and Rafiul Hasan (Helkite). Car was assembled by me.

Install Adafruit Motor Shield V2 Library, Adafruit Motor Shield library from the arduino IDE library
And download Timer Free Tone from here https://bitbucket.org/teckel12/arduino-timer-free-tone/downloads/

Timer free tone is used instead of the already available tone function because the tone function uses the built-in timer in the Arduino which disturbs the communication between the Arduino and the motor shield, causing bugs (which in my case was the left motors not receiving any output after playing the song).

HC-05 bluetooth module was used along with the L-293D motor shield to make the car.
