[WaveShare Docs](https://www.waveshare.com/wiki/RGB-Matrix-P2-64x64)

64x64 WaveShare LED display
| PIN     | Description       | 16PIN CABLE | STM32F401RE PIN |
|---------|-------------------|-------------|-----------------|
| OE      | Output enable     | 2           | PB8             |
| LAT/STB | Latch pin         | 3           | PB9             |
| GND     | Ground            | 13          | GND             |
| CLK     | Clock input       | 4           | PA5             |
| E       | E line selection  | 9           | PA6             |
| D       | D line selection  | 5           | PA7             |
| C       | C line selection  | 6           | PB6             |
| B       | B line selection  | 7           | PC7             |
| A       | A line selection  | 8           | PA9             |
| B2      | B lower bit data  | 10          | PA8             |
| G2      | G lower bit data  | 11          | PB2             |
| R1      | R higher bit data | 16          | PA10            |
| R2      | R lower bit data  | 12          | PC5             |
| B1      | B higher bit data | 14          | PC6             |
| G1      | G higher bit data | 15          | PC8             |
| GND     | Ground            | 1           | GND             |

CHANGES ACK:
R2 PB4  -> PC5
B1 PB5  -> PC6
G1 PB3  -> PC8
G2 PB10 -> PB2

HC-05
| PIN     | Description       | STM32F401RE PIN |
|---------|-------------------|-----------------|
| STATE   |                   | PA13            |
| RXD     |                   | PA3             |
| TXD     |                   | PA2             |
| GND     |                   | GND             |
| VCC     |                   | 3.3             |
| EN      |                   | PA14            |

PICO-RTC-DS3231
| PIN      | Description  | STM32F401RE PIN |
|----------|--------------|-----------------|
| I2C2_SCL | Serial Clock | PB10            |
| I2C2_SDA | Serial Data  | PB3             |
