# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/nicolekaldus/esp/esp-idf/components/bootloader/subproject"
  "/Users/nicolekaldus/esp/wired-528-final/Wired-Gesture-Controlled-Drone-Flight/build/bootloader"
  "/Users/nicolekaldus/esp/wired-528-final/Wired-Gesture-Controlled-Drone-Flight/build/bootloader-prefix"
  "/Users/nicolekaldus/esp/wired-528-final/Wired-Gesture-Controlled-Drone-Flight/build/bootloader-prefix/tmp"
  "/Users/nicolekaldus/esp/wired-528-final/Wired-Gesture-Controlled-Drone-Flight/build/bootloader-prefix/src/bootloader-stamp"
  "/Users/nicolekaldus/esp/wired-528-final/Wired-Gesture-Controlled-Drone-Flight/build/bootloader-prefix/src"
  "/Users/nicolekaldus/esp/wired-528-final/Wired-Gesture-Controlled-Drone-Flight/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/nicolekaldus/esp/wired-528-final/Wired-Gesture-Controlled-Drone-Flight/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/nicolekaldus/esp/wired-528-final/Wired-Gesture-Controlled-Drone-Flight/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
