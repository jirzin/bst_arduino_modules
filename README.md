bst_arduino_modules
===================
codes and circuits for instalation in Bedrich Smetana Muzeum

bst_receiver is the 4 channel IR signal receiver that expects 0xFFFFBEDA sequence in NEC coding on more than two of its TSOP receivers with demodulation...

bst_emmittor is 1 channel IR signal generator that emmits 0xFFFFBEDA sequence in NEC coding...
flashing hex to board via avr dragon
# avrdude -v -p m328p -c dragon_isp -P usb -U flash:w:bst_emittor_000.cpp.hex
fuses setup for emittor that provides functional circuit 
# avrdude -v -p m328p -c dragon_isp -P usb -U lfuse:w:0xFF:m -U hfuse:w:0xDE:m -U efuse:w:0x05:m 

bst_dimmer is 1 channel LED dimmer that converts sudden changes in controll signal to ramps...

