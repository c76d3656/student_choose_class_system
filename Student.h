//
// Created by Zhong on 2022/6/23.
//

#ifndef STUDENT_CHOOSE_CLASS_SYSTEM_STUDENT_H
#define STUDENT_CHOOSE_CLASS_SYSTEM_STUDENT_H

#include <string>
#include <map>
#include <iostream>
#include <vector>
#pragma once

class Student {
private:
    long long student_id;
    std::string student_name;
    bool gender;//1为男0为女
    unsigned int age;
    std::string major;
    unsigned int classroom_id;
    long long phone_number;
    std::map<int, std::string> choose_class_list;

public:
    friend void save();

    friend void init();

    Student(long long Student_id, const std::string &Student_name, bool Gender, unsigned int Years,
            unsigned int Major, unsigned int Classroom_id, long long Phone_number) ;

    Student(long long Student_id, const std::string &Student_name, bool Gender, unsigned int Years,
            std::string Major, unsigned int Classroom_id, long long Phone_number) ;

    bool choose_class(const int &course_id) ;

    bool remove_class(const int &course_id) ;

    void choose_class_list_show() ;

    void change_info();

    void detail_show() const ;

    std::map<int, std::string> get_class_list() ;
};

extern std::vector<std::string> major_list;
extern std::map<long long, Student *> total_student_list;

#endif //STUDENT_CHOOSE_CLASS_SYSTEM_STUDENT_H
