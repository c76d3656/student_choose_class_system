cmake_minimum_required(VERSION 3.20)
project(student_choose_class_system)

set(CMAKE_CXX_STANDARD 14)

add_executable(student_choose_class_system main.cpp ClassInfor.cpp ClassInfor.h Student.cpp Student.h head.h Manage.cpp Manage.h)
set(CMAKE_EXE_LINKER_FLAGS "-static")