cmake_minimum_required(VERSION 3.5)
project(vuln)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "gcc")


set(CMAKE_CXX_FLAGS "-fno-stack-protector")  # Disable canary
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -no-pie -fno-pic")  # Disable PIE
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -z execstack")  # Disable DEP
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_FORTIFY_SOURCE=0") # Disable Foritify
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcf-protection=none") # Disable Intel CET
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-asynchronous-unwind-tables -fno-dwarf2-cfi-asm") # ETC
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32") # 32-bit

# #
# -no-pie \ # Disable PIE
# -fno-pic
# -z execstack \ Disable DEP
# -D_FORTIFY_SOURCE=0 \ Disable Foritify
# -fcf-protection=none \ Disable Intel CET
# -fno-asynchronous-unwind-tables -fno-dwarf2-cfi-asm")

# "-fno-pie -fstack-protector -lcrypto -Wall -Wl,-z,relro -Wl,-z,now -Wl,-no-pie")
set(CMAKE_CXX_FLAGS_RELEASE)
set(CMAKE_CXX_FLAGS_DEBUG "-Og -g  -DCTF_DEBUG=1")

if(${CMAKE_BUILD_TYPE} MATCHES Debug)
    set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG}")
else()
    set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE}")
endif()

message("CMAKE_BUILD_TYPE is ${CMAKE_BUILD_TYPE}")
message("CMAKE_C_FLAGS is ${CMAKE_C_FLAGS}")
add_executable(vuln vuln.c)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
