# teensy3.6-mk3
teensy 3.6 Software for my cdj 1000 mk3 midi conversion 
If you want to change the digital inputs and outputs used, then change the veriables at the start and also change the pinmodes to match.
The leds are switched on and off in the OnNoteOn and OnNoteOff routines. You have to enter the digital pin numbers direct as the case select will not let you use the veriable names.
I have two arrays buttons and leds, this makes reading all the buttons simple in a for next loop.
if you want to use two midi decks at the same time change the channle veriable in one of them.
the routine to detect if the jog wheel is pressed uses buttonstat[8] to see if it's pressed or not, this needs to match up with the array entry for jogpressb and in my version that is the 8th entry.
