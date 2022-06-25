//
// Created by Zhong on 2022/6/25.
//

#ifndef STUDENT_CHOOSE_CLASS_SYSTEM_MANAGE_H
#define STUDENT_CHOOSE_CLASS_SYSTEM_MANAGE_H

#include "head.h"
#include "Student.h"
#include "ClassInfor.h"
#include <windows.h>

#pragma once

class Manage {
public:
    bool
    new_class(const std::string &Course_name, unsigned int Course_nature, unsigned int Total_hours,
              unsigned int Credits,
              unsigned int Semester);

    bool remove_class(const int &course_id);

    void class_list_show();

    void target_class_list_show(const int &course_id);

    void who_choose_this_class(const unsigned int &course_id);

    long long how_many_student_choose_this_class(const long long &course_id);

    long long how_many_class();

//学生
    bool new_student(const long long &student_id, const std::string &student_name, bool gender, unsigned int ages,
                     unsigned int major, unsigned int classroom_id, long long phone_number);

    bool remove_student(const long long &student_id);

    void student_list_show();

    void target_student_show(const long long &student_id);

    bool student_choose_class(const long long &student_id, const int &course_id);

    bool student_remove_class(const long long &student_id, const int &course_id);

    void student_change_information(const long long &student_id);

    long long how_many_student();

//专业操作
    unsigned int new_major(const std::string &major_name);

    void major_list_show();

//课程性质操作
    void course_nature_list_show();

//交互功能
    void welcome();

    unsigned long long input_solution(const std::string &a);

    void init();

    void save();
};


#endif //STUDENT_CHOOSE_CLASS_SYSTEM_MANAGE_H
