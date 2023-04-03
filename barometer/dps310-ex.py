#!/usr/bin/python

# SPDX-FileCopyrightText: 2021 ladyada for Adafruit Industries
# SPDX-License-Identifier: MIT

import time
import board
import numpy as np
import pandas as pd
from datetime import datetime
import matplotlib.pyplot as plt
from adafruit_dps310.advanced import DPS310_Advanced as DPS310
from adafruit_dps310 import advanced
from atmosphere import calc_delta_height
from tqdm import tqdm


i2c = board.I2C()  # uses board.SCL and board.SDA
dps310 = DPS310(i2c)

dps310.reset()
dps310.pressure_oversample_count = advanced.SampleCount.COUNT_128
dps310.pressure_rate = advanced.Rate.RATE_128_HZ
dps310.temperature_oversample_count = advanced.SampleCount.COUNT_128
dps310.temperature_rate = advanced.Rate.RATE_128_HZ
dps310.mode = advanced.Mode.CONT_PRESTEMP
dps310.wait_temperature_ready()
dps310.wait_pressure_ready()
time.sleep(1)


start = []
temps = []
i = 0
while i < 100:
    start.append(dps310.pressure)
    temps.append(dps310.temperature)
    i += 1

start_pressure = np.mean(start)
temp = np.mean(temps)
print("Starting pressure: {}".format(start_pressure))

n = 10000
times = np.empty(n, dtype = object)
res = np.zeros(n)

# plt.axis([0, len(res), -1, 1])

for x in tqdm(range(len(res))):
    # print(f"Pressure {dps310.pressure}")
    # d_alt = calc_delta_height(dps310.pressure, temp, start_pressure) 
    # t = datetime.now()
    # plt.scatter(x, d_alt, color = 'C0', s = 1)
    # plt.pause(0.1)
    res[x] = calc_delta_height(dps310.pressure, temp, start_pressure) 
    times[x] = datetime.now()
    time.sleep(0.085)

times = pd.to_datetime(pd.Series(times))
df = pd.DataFrame(res, index = times)
df.to_csv(f"./data/dps310-{datetime.now().strftime('%Y-%m-%dT%T')}")