import time
import board
import numpy as np
import pandas as pd
from datetime import datetime
import matplotlib.pyplot as plt
# import digitalio # For use with SPI
import adafruit_bmp280
from tqdm import tqdm

from atmosphere import calc_delta_height

# Create sensor object, communicating over the board's default I2C bus
i2c = board.I2C()   # uses board.SCL and board.SDA
bmp280 = adafruit_bmp280.Adafruit_BMP280_I2C(i2c)

# OR Create sensor object, communicating over the board's default SPI bus
# spi = board.SPI()
# bmp_cs = digitalio.DigitalInOut(board.D10)
# bmp280 = adafruit_bmp280.Adafruit_BMP280_SPI(spi, bmp_cs)

# change this to match the location's pressure (hPa) at sea level
bmp280.sea_level_pressure = 1013.25
# bmp280.mode = adafruit_bmp280.MODE_NORMAL
# bmp280.standby_period = adafruit_bmp280.STANDBY_TC_500
bmp280.iir_filter = adafruit_bmp280.IIR_FILTER_X16
bmp280.overscan_pressure = adafruit_bmp280.OVERSCAN_X16
bmp280.overscan_temperature = adafruit_bmp280.OVERSCAN_X16
# The sensor will need a moment to gather inital readings
time.sleep(1)

start = []
temps = []
i = 0
while i < 100:
    start.append(bmp280.pressure)
    temps.append(bmp280.temperature)
    i += 1

start_pressure = np.mean(start)
temp = np.mean(temps)
print("Starting pressure: {}".format(start_pressure))

n = 10000

times = np.empty(n, dtype = object)
res = np.zeros(n)

# plt.axis([0, len(res), -1, 1])
x = 0
for x in tqdm(range(len(res))):
    # print(f"Pressure {dps310.pressure}")
    # d_alt = calc_delta_height(bmp280.pressure, temp, start_pressure) 
    # t = datetime.now()
    # plt.scatter(x, d_alt, color = 'C0', s = 1)
    # plt.pause(0.1)
    res[x] = calc_delta_height(bmp280.pressure, temp, start_pressure) 
    times[x] = datetime.now()
    time.sleep(0.1)

times = pd.to_datetime(pd.Series(times))
df = pd.DataFrame(res, index = times)
df.to_csv(f"./data/bmp280-{datetime.now().strftime('%Y-%m-%dT%T')}")