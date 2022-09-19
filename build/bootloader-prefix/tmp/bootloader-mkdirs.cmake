# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/vitorlamego/esp/esp-idf/components/bootloader/subproject"
  "/Users/vitorlamego/esp/Trabalho_Final/build/bootloader"
  "/Users/vitorlamego/esp/Trabalho_Final/build/bootloader-prefix"
  "/Users/vitorlamego/esp/Trabalho_Final/build/bootloader-prefix/tmp"
  "/Users/vitorlamego/esp/Trabalho_Final/build/bootloader-prefix/src/bootloader-stamp"
  "/Users/vitorlamego/esp/Trabalho_Final/build/bootloader-prefix/src"
  "/Users/vitorlamego/esp/Trabalho_Final/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/vitorlamego/esp/Trabalho_Final/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/vitorlamego/esp/Trabalho_Final/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
