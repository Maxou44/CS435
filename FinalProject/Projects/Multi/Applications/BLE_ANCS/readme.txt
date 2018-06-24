/**
  @page BlueNRG Expansion Board for STM32 Nucleo Boards ANCS
  
  @verbatim
  ******************** (C) COPYRIGHT 2014 STMicroelectronics *******************
  * @file    readme.txt 
  * @author  CL/AST  
  * @version V0.0.1
  * @date    01-December-2016
  * @brief   Description of the BlueNRG ANCS application.
  ******************************************************************************
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  @endverbatim

@par Example Description 

This is a demo of the Apple Notification Center Service (ANCS) showing how to
configure the BlueNRG-MS chip as a Notification Consumer device.
The purpose of the ANCS profile (BLE Notification Consumer role)
is to give Bluetooth accessories a simple and convenient way to access
many kinds of notifications that are generated on a Notification Provider.
The BLE_ANCS demo, after the reset, puts the BlueNRG-MS in advertising
with device name "ANCSdemo", and it sets the BlueNRG-MS authentication
requirements for enabling bonding.
When the device is connected and bonded with a Notification Provider,
the demo configures the BlueNRG-MS Notification Consumer device
to discover the service and the characteristics of the Notification Provider.
When the setup phase is completed, the BlueNRG-MS device is configured
as a Notification Consumer and is able to receive every notification
sent from the Notification Provider.
 
@par Hardware and Software environment

  - This example runs on STM32 Nucleo devices with BlueNRG-MS STM32 expansion board
    (X-NUCLEO-IDB05A1)
  - This example has been tested with STMicroelectronics:
    - NUCLEO-L053R8 RevC board
    - NUCLEO-F401RE RevC board
    - NUCLEO-L476RG RevC board
    and can be easily tailored to any other supported device and development board.
    This example runs also on the NUCLEO-F411RE RevC board, even if the chip could
    be not exploited at its best since the projects are configured for the
    NUCLEO-F401RE target board.
    

@par How to use it? 

In order to make the program work, you must do the following:
 - WARNING: before opening the project with any toolchain be sure your folder
   installation path is not too in-depth since the toolchain may report errors
   after building.
 - Open IAR toolchain (this firmware has been successfully tested with
   Embedded Workbench V7.80.4).
   Alternatively you can use the Keil uVision toolchain (this firmware
   has been successfully tested with V5.24.2).
   Alternatively you can use the System Workbench for STM32 (this firmware
   has been successfully tested with Version 2.4.0).
 - Rebuild all files and load your image into target memory.
 - Run the example.
 - Alternatively, you can download the pre-built binaries in "Binary" 
   folder included in the distributed package.


 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
