/*
Copyright 2021 Sadek Baroudi <sadekbaroudi@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

//#define ONESHOT_TAP_TOGGLE 5 // Tapping this numver of times holds the key until tapped once again
#define ONESHOT_TIMEOUT 5000 // time in ms before the one shot key is released

#define TAPPING_TERM 500

#ifndef XOIVIOX_RGBMATRIX
#define XOIVIOX_RGBMATRIX
#endif

#ifndef XOIVIOX_EVQ
#define XOIVIOX_EVQ
#endif

#define ENCODERS_A_REVERSE true
#define ENCODERS_B_REVERSE true

#pragma once
#include "config_common.h"
