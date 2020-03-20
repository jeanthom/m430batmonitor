#!/usr/bin/env python3

batteryVoltRange = (6.6, 8.4)
adcValRange = 2**10
adcVoltRange = 2.5
voltageDividerCoefficient = 10/(10+22)

batteryValRange = tuple([x*voltageDividerCoefficient*adcValRange/adcVoltRange for x in batteryVoltRange])
print(batteryValRange)

refPerc = [12.5, 25, 37.5, 50, 62.5, 75, 87.5]

def sigmoidalPercentage(level, min, max):
	tmpRes = 105 - (105 / (1 + (1.724 * (level - min)/(max - min)) ** 5.5))
	return 100 if tmpRes >= 100 else tmpRes

for i in refPerc:
	perc = 0
	lvl = batteryValRange[0]
	while perc < i:
		perc = sigmoidalPercentage(lvl, batteryValRange[0], batteryValRange[1])
		lvl += 1
	print("i = ", lvl)
