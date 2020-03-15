#/********************************************************************\
# * EyeBoard python listener- Serial port reader from the EOG system *
# * Copyright (C) 2011 Luis Cruz <lcruz@intelsath.com>               *
# * For further information, support, and contributions please visit:*
# *                    http://www.intelsath.com                      * 
# *                                                                  *
# *                                                                  *
# * This program is free software; you can redistribute it and/or    *
# * modify it under the terms of the GNU General Public License as   *
# * published by the Free Software Foundation, either version 3 of   *
# * the License, or (at your option) any later version.              *
# *                                                                  *
# * This program is distributed in the hope that it will be useful,  *
# * but WITHOUT ANY WARRANTY; without even the implied warranty of   *
# * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the    *
# * GNU General Public License for more details.                     *
# *                                                                  *
# * You should have received a copy of the GNU General Public License*
# * along with this program. If not, see                             *
# * <http://www.gnu.org/licenses/>.                                  *
#\********************************************************************/
import serial 
serial = serial.Serial("/dev/ttyUSB0", 115200, timeout=1) #For windows change /dev/ttyUSBx to COMx

while True:

#uses the serial port
 data = serial.read()
#right
 if data == "0": 
  f = open("eog.txt", "w")
  f.write("0")
  f.close()

#center
 if data == "1": 
  f = open("eog.txt", "w")
  f.write("1")
  f.close()

#left
 if data == "2": 
  f = open("eog.txt", "w")
  f.write("2")
  f.close()
