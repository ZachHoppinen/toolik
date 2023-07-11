import numpy as np

def calc_delta_height(pressure, temperature, ref_pressure):
    """
    Calculate an approximate altitude given a pressure and temperature

    Args:
    pressure: pressure value at your location in hPa
    temperature: temperature in C
    sea_pressure: pressure at sea level

    Returns:
    altitude: approximate altitude
    """

    # constants
    g = 9.80665 # m/s
    m = 0.0289644 # kg / mol
    R = 8.3143 # N * m * mol-1 * K-1
    Rs = 287 # J kg k 
    temperature = temperature + 273.15

    h = - R * temperature * np.log(pressure/ref_pressure) / (m * g)

    return h

if __name__ == '__main__':
    import sys
    _, p, t, r_p = sys.argv
    print(calc_delta_height(float(p),float(t),float(r_p)))
