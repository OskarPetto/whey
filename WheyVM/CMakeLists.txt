cmake_minimum_required(VERSION 3.13.0 FATAL_ERROR)

enable_testing()

option(TIMING "Enableds instruction timing" OFF)

project(whey VERSION 0.1 LANGUAGES C)

set(WC_FILE_SOURCES WcFile/src/Constant.c WcFile/src/Function.c WcFile/src/WcFile.c)

set(OPERAND_SOURCES 
    Operand/src/Array.c
    Operand/src/Double.c
    Operand/src/Gc.c
    Operand/src/Integer.c
    Operand/src/Map.c
    Operand/src/Object.c
    Operand/src/String.c
    Operand/src/Pair.c)

add_executable(whey 
  ${OPERAND_SOURCES}
  ${WC_FILE_SOURCES}
  src/Frame.c
  src/InstructionSet.c
  src/main.c
  src/WheyVM.c)

if(TIMING)
  target_compile_definitions(whey PRIVATE INSTRUCTION_TIMING)
endif()

add_executable(operand_test ${OPERAND_SOURCES} Operand/test/ObjectTest.c)

add_executable(wcfile_test
  ${WC_FILE_SOURCES}
  WcFile/test/WcFileTest.c)

add_test(NAME wcfile
         COMMAND wcfile_test 
         WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/WcFile/test)

add_test(NAME operand
         COMMAND operand_test 
         WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/Operand/test/)