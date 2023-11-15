cmake_minimum_required(VERSION 3.26)
project(p3)

set(CMAKE_CXX_STANDARD 17)

add_executable(p3 p3x.cpp
        Patient.h
        PatientPriorityQueuex.h)
