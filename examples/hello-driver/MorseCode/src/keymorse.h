/***************************************************************************
 * Copyright (C) 2008 by Benjamin Hadorn (b_hadorn@bluewin.ch)             *
 ***************************************************************************
 * Projekt : Operation System Project
 * Module  : keymorse
 * Package : Drivers
 * Author  : Benjamin Hadorn
 * Datum   : $Date$
 * Ablage  : $File$
 * System  : Zeus C++ Framework
 ***************************************************************************
 * Licence:                                                                *
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version             *
 *   2.1 of the License, or (at your option) any later version.            *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the          *
 *   GNU Lesser General Public License for more details.                   *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110, USA  *
 ***************************************************************************/

/***************************************************************************
 Changes :
 $Log$
***************************************************************************/

#ifndef keymorseH 
#define keymorseH


#include <linux/fs.h>
#include <linux/kernel.h>

//Definitions
///Mayor number of the device (auto detect = 0)
#define KEYMORSE_MAJOR    0
///Name of the device
#define KEYMORSE_NAME     "keymorse"

///Define needed to generate the test code
#define TEST_DRIVER

//forward
struct TypeMorseDevice;

static int  initModule(void);
static void exitModule(void); 
static int  setup_cdev(struct TypeMorseDevice* rData, int iIndex);
static void release_cdev(struct TypeMorseDevice* rData);


//Main functions of the morse device
static ssize_t main_write(struct file *, const char __user*, size_t, loff_t *);
static int     main_open(struct inode *, struct file *);
static int     main_release(struct inode *, struct file *);
static int     read_morsemem(char* pcBuffer, char** ppcStart, off_t iOffset, int iCount, int* piEOF, void* pData);

#ifdef TEST_DRIVER
static int     read_morsetest(char* pcBuffer, char** ppcStart, off_t iOffset, int iCount, int* piEOF, void* pData);
#endif


#endif
