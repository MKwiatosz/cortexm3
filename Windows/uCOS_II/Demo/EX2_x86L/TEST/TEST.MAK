###############################################################################
#                                  uC/OS-II
#                            The Real-Time Kernel
#                         
#              (c) Copyright 2002, Jean J. Labrosse, Weston, FL
#                             All Rights Reserved
#
#
# Filename    : TEST.MAK
###############################################################################
#
#/*$PAGE*/
###############################################################################
#                                   TOOLS
###############################################################################
#

BORLAND=C:\BC45

CC=$(BORLAND)\BIN\BCC
ASM=$(BORLAND)\BIN\TASM
LINK=$(BORLAND)\BIN\TLINK
TOUCH=$(BORLAND)\BIN\TOUCH

###############################################################################
#                                DIRECTORIES
###############################################################################
#

LST=..\LST
OBJ=..\OBJ
SOURCE=..\SOURCE
TARGET=..\TEST
WORK=..\WORK

BaseDir=..\..\..\..\..
OS=$(BaseDir)\uCOS_II_V2.52
PC=$(BaseDir)\Windows\uCOS_II\uC_Port\PC
PORT=$(BaseDir)\Windows\uCOS_II\uC_Port\Ix86L

###############################################################################
#                               COMPILER FLAGS
#
# -1                 Generate 80186 code
# -B                 Compile and call assembler
# -c                 Compiler to .OBJ
# -f                 Use the Borland Floating-Point Emulation Library (default)
# -G                 Select code for speed
# -I                 Path to include   directory
# -k-                Standard stack frame
# -L                 Path to libraries directory
# -ml                Large memory model
# -N-                Do not check for stack overflow
# -n                 Path to object directory
# -O                 Optimize jumps
# -Ob                Dead code elimination
# -Oe                Global register allocation
# -Og                Optimize globally
# -Ol                Loop optimization
# -Om                Invariant code motion
# -Op                Copy propagation
# -Ov                Induction variable
# -v                 Source debugging ON
# -vi                Turn inline expansion ON
# -wpro              Error reporting: call to functions with no prototype
# -Z                 Suppress redundant loads
###############################################################################
#

C_FLAGS=-c -f -ml -1 -G -O -Ogemvlbpi -Z -d -n..\obj -k- -v -vi- -wpro -I$(BORLAND)\INCLUDE -L$(BORLAND)\LIB

###############################################################################
#                               ASSEMBLER FLAGS
#
# /MX                Case sensitive on globals
# /ZI                Full debug info
# /O                 Generate overlay code
###############################################################################
#

ASM_FLAGS=/MX /ZI /O 

###############################################################################
#                                LINKER FLAGS
###############################################################################
#
LINK_FLAGS= 

###############################################################################
#                               MISCELLANEOUS
###############################################################################
#
INCLUDES=      $(SOURCE)\INCLUDES.H  \
               $(SOURCE)\OS_CFG.H    \
               $(PORT)\OS_CPU.H      \
               $(PC)\PC.H            \
               $(OS)\uCOS_II.H               

###############################################################################
#                          CREATION OF .EXE FILE
###############################################################################

$(TARGET)\TEST.EXE:                  \
               $(WORK)\INCLUDES.H    \
               $(OBJ)\OS_CPU_A.OBJ   \
               $(OBJ)\OS_CPU_C.OBJ   \
               $(OBJ)\PC.OBJ         \
               $(OBJ)\TEST.OBJ       \
               $(OBJ)\uCOS_II.OBJ    \
               $(SOURCE)\TEST.LNK
               COPY    $(SOURCE)\TEST.LNK
               $(LINK) $(LINK_FLAGS)     @TEST.LNK
               COPY    $(OBJ)\TEST.EXE   $(TARGET)\TEST.EXE
               COPY    $(OBJ)\TEST.MAP   $(TARGET)\TEST.MAP
               DEL     TEST.MAK


###############################################################################
#                        CREATION OF .OBJ (Object) FILES
###############################################################################

$(OBJ)\OS_CPU_A.OBJ:                  \
               $(PORT)\OS_CPU_A.ASM   

               COPY   $(PORT)\OS_CPU_A.ASM  OS_CPU_A.ASM
	           $(ASM) $(ASM_FLAGS)  $(PORT)\OS_CPU_A.ASM,$(OBJ)\OS_CPU_A.OBJ


$(OBJ)\OS_CPU_C.OBJ:                  \
               $(PORT)\OS_CPU_C.C     \

               COPY   $(PORT)\OS_CPU_C.C    OS_CPU_C.C
               $(CC)  $(C_FLAGS)            OS_CPU_C.C


$(OBJ)\PC.OBJ:                        \
               $(PC)\PC.C             \
               $(INCLUDES)

               COPY   $(PC)\PC.C            PC.C
               $(CC)  $(C_FLAGS)            PC.C


$(OBJ)\TEST.OBJ:                      \
               $(SOURCE)\TEST.C       \
               $(INCLUDES)

               COPY   $(SOURCE)\TEST.C      TEST.C
               $(CC)  $(C_FLAGS)            TEST.C


$(OBJ)\uCOS_II.OBJ:                   \
               $(OS)\uCOS_II.C        \
               $(INCLUDES)

               COPY   $(OS)\os_core.c       os_core.c
               COPY   $(OS)\os_flag.c       os_flag.c 
               COPY   $(OS)\os_mbox.c       os_mbox.c 
               COPY   $(OS)\os_mem.c        os_mem.c 
               COPY   $(OS)\os_mutex.c      os_mutex.c
               COPY   $(OS)\os_q.c          os_q.c    
               COPY   $(OS)\os_sem.c        os_sem.c  
               COPY   $(OS)\os_task.c       os_task.c
               COPY   $(OS)\os_time.c       os_time.c 
               COPY   $(OS)\uCOS_II.H       uCOS_II.H
               COPY   $(OS)\uCOS_II.C       uCOS_II.C
               $(CC)  $(C_FLAGS)            uCOS_II.C


$(WORK)\INCLUDES.H:                   \
               $(INCLUDES)

               COPY   $(SOURCE)\INCLUDES.H  INCLUDES.H
               COPY   $(SOURCE)\OS_CFG.H    OS_CFG.H
               COPY   $(PC)\PC.H            PC.H
               COPY   $(PORT)\OS_CPU.H      OS_CPU.H
               COPY   $(OS)\uCOS_II.H       uCOS_II.H
