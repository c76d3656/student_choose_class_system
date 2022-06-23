//
// Created by Zhong on 2022/6/23.
//

#ifndef STUDENT_CHOOSE_CLASS_SYSTEM_CLASSINFOR_H
#define STUDENT_CHOOSE_CLASS_SYSTEM_CLASSINFOR_H
#include <string>
#include <map>
#pragma once

class ClassInformation {
public:
    int course_id;//课程代码
    std::string course_name;//课程名称
    std::string course_nature;//课程性质
    unsigned int total_hours;//总学时
    unsigned int credits;//学分
    unsigned int semester;//开课学期
    unsigned int choose_number;//选修人数
    std::map<long long, std::string> choose_student_list;//选该门课的学生列表

    ClassInformation(const std::string &Course_name, unsigned int Course_nature, unsigned int Total_hours,unsigned int Credits, unsigned int Semester);

    ClassInformation(int Course_id, const std::string &Course_name, std::string Course_nature, unsigned int Total_hours,unsigned int Credits, unsigned int Semester, unsigned int Choose_number) ;

    void class_show() const ;

    void choose_student_show();
};

extern std::map<long long, ClassInformation *> total_class_list;
extern int COURSE_LIST_NUMBER;
extern std::map<unsigned int, std::string> course_nature_list ;

#endif //STUDENT_CHOOSE_CLASS_SYSTEM_CLASSINFOR_H
