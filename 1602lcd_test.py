from RPLCD.gpio import CharLCD
from RPi import GPIO
from time import sleep

lcd = CharLCD(cols=16, rows=2, pin_rs=15, pin_e=16, pins_data=[21, 22, 23, 24],
              numbering_mode=GPIO.BOARD, compat_mode=True)

lcd.cursor_pos = (0, 0)
lcd.write_string("hello")
lcd.cursor_pos = (1, 0)
lcd.write_string("world")
# lcd.clear()
# lcd.close(clear = True)