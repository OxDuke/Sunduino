/*=====================================================================

Sunduino.cpp - Sunduino Library for STM32F4

Copyright (c) 2016 Weidong Sun.  All right reserved.

Contact information
 -------------------
 Weidong Sun, China
 Web      :  under construction yet
 e-mail   :  swdswd28@gmail.com

This file is part of the Sunduino project

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA .
  or, see <http://www.gnu.org/licenses/>.

======================================================================*/

#include "Sunduino.h"

void Sunduino(void)
{
  Stm32_Clock_Init(336, 8, 2, 7); //set the clock,168Mhz
  sysTickInit(168);
  uart_init(84, 115200);  //serial communication, BAUD=115200
}
