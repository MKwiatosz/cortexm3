/******************** (C) COPYRIGHT 2009 STMicroelectronics ********************
* File Name          : readme.txt
* Author             : MCD Application Team
* Version            : V0.0.6
* Date               : 04/06/2009
* Description        : This sub-directory contains all the Migration Script files
*                      needed to migrate your application code from STM32F10x
*                      FWLib V2.0.3 to STM32F10x Standard Peripherals Library V3.0.0 
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

Directory contents
===================
- MigrationScript.exe: Migration Automatic script binary file
              
- config.ini: Migration script configuration file. It contains all needed and 
              automatic changes that will be applied on your code.              
                      
     
How to use it
=============
- Download and Install the ActivePerl SW from this link:
http://www.activestate.com/activeperl

- Copy the "MigrationScript.exe" and "config.ini" files into the parent directory 
  of the files to be modified.

Note: Please make sure that the target files are in read/write mode.
  
- Launch "MigrationScript.exe"
- A backup folder is created in your work folder. It contains all the old data 
  in your directory. A trace file "trace.log" that summarizes all updated files 
  is also created.
    
******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE******
