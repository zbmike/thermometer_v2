from RPLCD.i2c import CharLCD
from RPi import GPIO
from time import sleep

lcd = CharLCD(i2c_expander='PCF8574', address=0x27, port=1,
              cols=16, rows=2)

lcd.cursor_pos = (0, 0)
lcd.write_string("hello")
lcd.cursor_pos = (1, 0)
lcd.write_string("world")
# lcd.clear()
# lcd.close(clear = True)