# HP9915-Keyboard
Code for the PS2 to HP-9915A/B keyboard adapter

Vassilis Prevelakis <vp2020 .at. aegisresearch.eu>

The HP9915A/B computer is the embedded version of the well known HP-85A/B computer.
More information about these computers from the early 80s may be found at the
www.series80.org web site.

Unlike the other Series80 computers, the 9915 has no keyboard. The base edition
of the 9915 has only 4 function keys on the front panel and 8 LEDs. 

The computer was designed to boot from either an optional internal tape-drive,
or from a set of ROMs that implemented a primitive file system. The 9915 was
thus a trully embedded computer that was compatible with the Series 80 computers
both in terms of hardware and peripherals.

For more interactive applications HP offered an optional adapter card that was
mounted inside the computer and allowed the 9915 to be connected to a monocrome
monitor and an external keyboard. Another connector on the same card allowed 
the lines that drove the front panel LEDs to be accessed so that external 
display  panels could be constructed.

Since the 9915A/B was based on the 85A/B computers (that had 6 inch displays),
the output to the external monitor was of rather low resolution even for the
standards of the time.

The keyboard was also based on the HP-85 keyboard which was a matrix of switches.
Hence the HP-85 keyboard may be connected to the 9915 and used as a fully compatible
external keyboard. HP documented the connector and expected that customers would
connect external switches that the 9915 would read as keyboard input.

The 9915 had a special ROM that provided access to the LEDs, the keyboard and 
the built in ROM-based filesystem. The ROM also included a comprehensive 
self test that complemented the self test included in the standard ROM of
all Series 80 computers.

The keyboard is presented in detail in the HP Journal of July 1981 (pp. 29-30),
and from the description it appears possible to use the GPIO pins of a 
microcontroller to simulate the key presses, thus allowing (a) another 
computer to simulate keyboard input and (b) to connect modern USB keyboards
to the 9915.

In reality connecting a computer to the external keyboard connector of the 9915
turned out to be more complex than anticipated. Tony Duell suggested the use 
of a mux and demux to simulate a keyboard without the need for a microprocessor,
but this does not appear to work. Instead I used a device offerred by 
ZARLINK that fully emulates a 12 x 8 switch matrix using a 40 pin DIP part.

Connecting the 9915 keyboard connector to the ZARLINK MT093 switch array
resulted in a workable keyboard emulator.

To drive the MT093 I used a cheap, but immensly overqualified for the job
on hand, controller the STM32F103C8T6 which contains an ARM Cortex M3 Processor
and lots of other goodies. The part is also known as the "Blue Pill" and
is available for about 3 Euros in small quantities which makes it cheaper 
than the MT093 which is around 5 EUR.

I have used the Arduino IDE with additional support files for the STM-32
chipset.

The adapter uses a PS/2 keyboard (ISO version as standard), to avoid
the need for a USB controller. Alternatively, it can be driven from 
the serial inteface of the STM-32, but, currently, the code does not support
this option. My guess is that it'll be trivial to adapt the code
to support input from the serial interface.

The keyboard had to be remapped to accommodate all the special keys
on the HP-85 keyboard. Even so, a number of keys remain unallocated.
These may be used to send pre-defined series of keystrokes, essentially
allowing frquently used commands (even small programs) to be stored
on the STM-32 and sent to the 9915 at the press of a button.

Using the adapter is plug and play. You plug the adapter to the external
keyboard connector of the 9915, a PS/2 keyboard to the PS/2 connector of
the adapter, and a USB charger to the USB port of the STM-32 to power
the adapter. Then you power up the 9915 and start typing away.

I have included pictures of my prototype, a wiring diagram and a 
PNG file with the key assignments of the PS/2 keyboard.

The parts list for the project is the blue-pill MMC, the Zarlink MT093,
a PS/2 socket (for the keyboard), and the cable to connect the board
to the 9915 external keyboard connector. Depending on how you go about 
connecting the 9915 to the adapter, only a moderate amount of soldering
should be required. 
