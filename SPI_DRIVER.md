# Hexapod SPI Peripheral Driver

## Main parameters

1. Type of communication: Full-Duplex mode
2. Baudrate: 22.5 MBit/s Maximum baudrate for STM32F446 in Full Duplex performing as Master -> 22.5 MBit/s)
3. SPI working in Mode 0 (CPOL=0, CPHA=0) accordingly to the Motorola SPI specification
   1. CPOL (Clock Polarity) - 0 - idle state - LOW (0V) - active state - HIGH (3.3V)
   2. CPHA (Clock Phase) - 0 - (first or rising edge)
4. CRC Generation? To be discussed
5. NSS (probably hardware, but to be tested)

## Types of frames
### Type 1 Frame (sending PWM data for all 18 servomotors)