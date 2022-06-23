cmake_minimum_required(VERSION 3.22)
project(student_choose_class_system)

set(CMAKE_CXX_STANDARD 23)

add_executable(student_choose_class_system main.cpp ClassInfor.cpp ClassInfor.h Student.cpp Student.h head.h)
