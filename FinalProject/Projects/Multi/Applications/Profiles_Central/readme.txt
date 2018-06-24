/**
  @page BlueNRG Expansion Board for STM32 Nucleo Boards BLE Profiles Application
   
  @verbatim
  ******************** (C) COPYRIGHT 2015 STMicroelectronics *******************
  * @file    readme.txt
  * @author  CL/AST
  * @version V1.0.0
  * @date    15-May-2015
  * @brief   BLE Central Profiles Sample Application
  ******************************************************************************
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  @endverbatim

@par Example Description 

This sample application shows how to use BlueNRG Bluetooth Low Energy 
stack.

To test this application you need:
- two STM32 Nucleo boards with their BlueNRG STM32 expansion boards
- the Java tool profileCentral.jar running on a Win/Lin/OSX PC
The Java tool profileCentral.jar can be found in this package at:
$PATH_TO_THIS_PACKAGE$\Utilities\PC_Software\ProfileCentralTool

On one STM32 Nucleo board the Heart Rate Peripheral BLE Profile must be running.
On the other STM32 Nucleo board this sample application for the Heart Rate Central
BLE Profile must be running. This board must be connected through a mini USB cable to the PC
where the Java tool profileCentral.jar will be launched.

The Heart Rate Peripheral BLE Profile project is part of the
$PATH_TO_THIS_PACKAGE$\Projects\Multi\Applications\Profiles_LowPower application.

The Heart Rate Central BLE Profile project is part of the
$PATH_TO_THIS_PACKAGE$\Projects\Multi\Applications\Profiles_Central application.

To set/change the BLE Peripheral to test, change the value of the macro BLE_CURRENT_PROFILE_ROLES
(in the "active profile" section) in file:
$PATH_TO_THIS_PACKAGE$\Middlewares\ST\STM32_BlueNRG\Prof_Periph\includes\host_config.h

To set/change the BLE Central Profile to test, change the value of the macro BLE_CURRENT_PROFILE_ROLES
(in the "active profile" section) in file:
$PATH_TO_THIS_PACKAGE$\Middlewares\ST\STM32_BlueNRG\Prof_Centr\includes\host_config.h

For example, if the HEART_RATE profile is set, after the connection between the
two boards has been established, the Profile Central tool will
show the information (Services and Characteristics discovered along with HR values notifications)
coming from the STM32 Nucleo board running the HR peripheral role.

@par Hardware and Software environment

  - This example runs on STM32 Nucleo devices with BlueNRG STM32 expansion board
    (X-NUCLEO-IDB04A1 or X-NUCLEO-IDB05A1)
  - This example has been tested with STMicroelectronics:
    - NUCLEO-L053R8 RevC board
    - NUCLEO-F401RE RevC board
    - NUCLEO-L476RG RevC board
    and can be easily tailored to any other supported device and development board.
	- WARNING:
		- A bug in current UART driver for NUCLEO-L053R8 could prevent a correct usage of
          Profile Central tool.
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
   
 - IMPORTANT NOTE: To avoid issues with USB connection (mandatory if you have USB 3.0), it is   
   suggested to update the ST-Link/V2 firmware for STM32 Nucleo boards to the latest version.
   Please refer to the readme.txt file in the Applications directory for details.
   
   
   
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
