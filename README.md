# SunRiseAlarm

This Arduino Script is based on a Script by Austin Tarango (YouTube). For further information, watch his video.
It can control an (external) LED(-strip) with a transistor to wake you up easily in the morning, just like a real sunrise.
I have improved Austin's script by making it able to change the wake-up time by turning the arduino on and off, furthermore, you can now use the LEDs also as nightlight.

Code:
To change output PIN - change the "uled" variable to desired pin
To change wakeup-times (Start of LEDs) - change times in "timeMatrix" - not at setHour and setMin!!!! - "timeMatrix" can also be extended with additional Wakup-Options if required
To change fade-time (until you wake up) - change variable "fadeTime"

User Instructions:
The Arduino basically has 3 states: "Nightlight on", "Show Wakup-Time" and "Change Wakeup-Time"

By switching the arduino OFF and ON again, it either turns the Night-Light on or it shows the Wakup-Time by blinking:
1 Blink = Time Setting with Index 0 in "timeMatrix"
2 Blinks = Time Setting with Index 1 in "timeMatrix"
3 Blinks = Time Setting with Index 2 in "timeMatrix"
...

If you turn OFF the Arduino within 3 seconds after the nightlight began to shine or after the last blink in "Show Wakeup-time" mode - your Arduino will be in "Change Wakeup-Time" mode, the LED now will blink fast for approx. 4 seconds. If you turn OFF the Arduino within this period, the next Time Setting in "timeMatrix" will be selected. You can turn it on and off as often as you wish in this mode - every time you turn it off, the Wakup-Time Setting will cycle through the preset Times in "timeMatrix" (for ONE index!). If you have the desired Time, just wait for 4 seconds and the fast blinking will change to slow blinking after a short break - this indicates the new Time again, as described in the paragraph above.

EXAMPLE:
Turn ON Arduino
LED shines bright --> Nightlight mode
Wait 3 sec
OFF/ON
LED blinks 3 Times - Time with index 2 is set --> 6:30
Wait 3 sec
OFF/ON
Nightlight burns
OFF/ON immediately
LED blinks fast --> Change Mode
OFF/ON immediately --> Time is now set to index 3
LED blinks fast
OFF/ON immediately --> Time is now set to index 4
Wait ~4 sec
LED stops blinking fast briefly (half sec)
LED blinks 5 Times - Time with index 4 is set --> 7:30
OFF/ON
LEDs start blinking for time indication
OFF/ON immediately
LED blinks fast
OFF/ON --> Index 0
LED blinks fast
OFF/ON --> Index 1
LED blinks fast
OFF/ON --> Index 2
Wait ~4sec
LED blinks slow 3 Times --> 6:30 (back to initial setting)


