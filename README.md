Simple arduino project for an automated watering system
=======================================================

The system reads humidity from a soil humidity sensor, displays a visualization of the humidity using colored LEDs and pumps water when needed.

There is also a distance sensor because running the pump dry damages it.

There are several definitions that change according to setup.

Depending on humidity sensor technology and environment, these should be changed:
 - low: low value for sensor, this means high conductivity so high soil humidity
 - high: high value for sensor, this means low conductivity so low soil humidity

Pumping values:
 - pumpwait: default to 10 minutes, this is the time that the system waits between to pump actions
   This is because the sensor should not be next to the spot that the water is being pumped to, so it takes a while for the soil capillarity to distribute the moisture
 - pumptime: amount of time the pump is activated for each pump action
 - maxdistance: depends on the vessel the water is in, it is the distance at which the pump is not activated to preserve the pump

The pin values should be changed according to setup.

Relay
=====

By far, the hardest was to figure out how to hook up the 12V relay to the arduino. There was no place where the complete information was available. The transistor is needed to upscale the arduino's current to 12V.
I know I could have used a 5V relay and it would have been much simpler, but I was confused as to how relays work and did not want to order a new relay but wanted to work with what I had.

For the relay hookup it is important to connect the two grounds (arduino and 12V power supply).

The 5K1Ω resistor is a "pulldown" resistor. It is important because otherwise, if this is not present, the relay will switch on at every power on of the system.
