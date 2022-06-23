//
// Created by Zhong on 2022/6/23.
//

#include "ClassInfor.h"

int class_id_create(const std::string &course_name) {
    int class_id_now = COURSE_LIST_NUMBER;
    ++COURSE_LIST_NUMBER;
    auto ok = total_class_list.find(class_id_now);
    if (ok == total_class_list.end()) {
        return class_id_now;
    } else {
        return -1;
    }
}

void ClassInformation::choose_student_show() {
    for (const auto &student: this->choose_student_list) {
        printf("\t\t%lld\t%s\n", student.first, student.second.c_str());
    }
}

void ClassInformation::class_show() const {
    printf("\t%d\t%s\t%s\t%d\t%d\t%d\t%d\n", this->course_id, this->course_name.c_str(),
           this->course_nature.c_str(), this->total_hours, this->credits,
           this->semester, this->choose_number);
}

ClassInformation::ClassInformation(int Course_id, const std::string &Course_name, std::string Course_nature,
                                   unsigned int Total_hours, unsigned int Credits, unsigned int Semester,
                                   unsigned int Choose_number) {
    course_id = Course_id;
    course_name = Course_name;
    course_nature = std::move(Course_nature);
    total_hours = Total_hours;
    credits = Credits;
    semester = Semester;
    choose_number = Choose_number;
}

ClassInformation::ClassInformation(const std::string &Course_name, unsigned int Course_nature, unsigned int Total_hours,
                                   unsigned int Credits, unsigned int Semester) {
    course_id = class_id_create(Course_name);
    course_name = Course_name;
    course_nature = course_nature_list.find(Course_nature)->second;
    total_hours = Total_hours;
    credits = Credits;
    semester = Semester;
    choose_number = 0;
}