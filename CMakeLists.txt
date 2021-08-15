
cmake_minimum_required( VERSION 3.5 )

set( AVR_PROGRAMMER usbtiny )
set( AVR_MCU atmega328p )
set( AVR_MCU_SPEED 16000000UL )


set( CMAKE_TOOLCHAIN_FILE $ENV{HOME}/.cmake/avr-gcc-toolchain.cmake )


project( RPNCalc )

set( CMAKE_BUILD_TYPE Release )

enable_language( ASM )

set( Srcs
        KeyPad.cpp
        Lcd.cpp
        DisplayFloat.cpp
        RPNCalcMain.cpp
        RpnStack.cpp
    )


set( AvrUtilsSrcs
#        AVRTools/Analog2Digital.cpp
        AVRTools/InitSystem.cpp
#        AVRTools/MemUtils.cpp
        AVRTools/SystemClock.cpp
#        AVRTools/Pwm.cpp
#        AVRTools/RingBuffer.cpp
        AVRTools/Writer.cpp
#        AVRTools/Reader.cpp
        AVRTools/abi.cpp
        AVRTools/new.cpp
#        AVRTools/I2cMaster.cpp
#        AVRTools/I2cLcd.cpp
#        AVRTools/SimpleDelays.S
#        AVRTools/SPI.cpp
    )


add_avr_executable( RPNCalc ${Srcs} ${AvrUtilsSrcs} )
