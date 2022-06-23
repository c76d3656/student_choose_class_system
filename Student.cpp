//
// Created by Zhong on 2022/6/23.
//

#include "Student.h"
#include "ClassInfor.h"


static void dropInput() {
    while (std::cin && std::cin.get() != '\n')continue;
    std::cin.clear();
}

static void major_list_show() {
    int i=0;
    for (const auto &major: major_list) {
        std::cout <<i<<":"<< major << " ";
        ++i;
    }
    printf("\n");
}


void Student::detail_show() const {
    printf("\t%lld\t%s\t%s\t%d\t%lld\t%d\t%s\n", this->student_id, this->student_name.c_str(),
           this->major.c_str(), this->classroom_id, this->phone_number, this->age,
           (this->gender ? "man" : "girl"));
}

std::map<int, std::string> Student::get_class_list() {
    return this->choose_class_list;
}

void Student::change_info() {
    printf("input something if change，or Enter to jump it\n");
    //修改学号(禁止)
//        printf("change student id as:  ");
//        {
//            int tmp_int =-1;
//            std::cin>>tmp_int;
//            if(tmp_int>0){
//                if(!total_student_list.count(tmp_int)){
//                    int tmp= this->student_id;
//                    remove_student(tmp);
//                    this->student_id=tmp_int;
//                    printf("change student id success!\n");
//                } else{
//                    printf("this student id have been exist\n");
//                    return;
//                }
//            }
//        }
    //修改姓名
    printf("change student name as:  ");
    [&](){
        std::string tmp_string;
        if(std::cin >> tmp_string){
            if(std::cin.get()=='\n'){
                return ;
            }
            if(!std::cin){
                dropInput();
                return;
            }
            dropInput();
        }

        if (!tmp_string.empty()) {
            this->student_name = tmp_string;
            {
                for (const auto &cour: this->choose_class_list) {
                    auto course = total_class_list.find(cour.first);
                    auto stu = course->second->choose_student_list.find(this->student_id);
                    stu->second = tmp_string;
                }
            }
            printf("change student name success!\n");
        }
    }();
    //修改性别
    printf("1 is man,0 is girl\n");
    printf("change student gender as:  ");
    [&](){
        int tmp_gender = -1;
        if(std::cin >> tmp_gender){
            if(std::cin.get()=='\n'){
                return;
            }
            if(!std::cin){
                dropInput();
                return;
            }
            dropInput();
        }
        if (tmp_gender == 1) {
            this->gender = true;
            printf("change student gender success!\n");
        } else if (tmp_gender == 0) {
            this->gender = false;
            printf("change student gender success!\n");
        }
    }();
    //修改年龄
    printf("change student age as:  ");
    [&](){
        double tmp_dou = -1;
        if(std::cin >> tmp_dou){
            if(std::cin.get()=='\n'){
                return;
            }
            if(!std::cin){
                dropInput();
                return;
            }
            dropInput();
        }
        int tmp_int = (int)tmp_dou;
        if (tmp_int > 0) {
            this->age = tmp_int;
            printf("change student age success!\n");
        } else if (tmp_int == 0) {
            printf("hey hey hey guys.He or she is a baby?\n");
        }
    }();
    //修改系别
    printf("change student major as:  ");
    [&](){
        major_list_show();
        int tmp_int = -1;
        if(std::cin >> tmp_int){
            if(std::cin.get()=='\n'){
                return;
            }
            if(!std::cin){
                dropInput();
                return;
            }
            dropInput();
        }
        if(tmp_int>=0&&tmp_int<major_list.size()-1){
            this->major=major_list[tmp_int];
        } else{
            printf("this major isn't exist");
        }
    }();
    //修改班级
    printf("change student classroom id as:  ");
    [&](){
        int tmp_int = -1;
        if(std::cin >> tmp_int){
            if(std::cin.get()=='\n'){
                return;
            }
            if(!std::cin){
                dropInput();
                return;
            }
            dropInput();
        }
        if (tmp_int > 0) {
            this->classroom_id = tmp_int;
            printf("change student classroom id success!\n");
        }
    }();
    //修改联系方式
    printf("change student phone number as:  ");
    [&](){
        long long tmp_int = -1;
        if(std::cin >> tmp_int){
            if(std::cin.get()=='\n'){
                return;
            }
            if(!std::cin){
                dropInput();
                return;
            }
            dropInput();
        }
        if (tmp_int > 0) {
            this->phone_number = tmp_int;
            printf("change student phone number success!\n");
        }
    }();
}

void Student::choose_class_list_show() {
    printf("student choose this class\n");
    printf("\tclass_is\tclass_name\n");
    for (auto &it: choose_class_list) {
        printf("\t%d\t%s\n", it.first, it.second.c_str());
    }
    printf("the end\n");
}

bool Student::remove_class(const int &course_id) {
    if (this->choose_class_list.erase(course_id)) {
        printf("remove %d success\n", course_id);
        {
            auto course = total_class_list.find(course_id);
            course->second->choose_number -= 1;
            course->second->choose_student_list.erase(this->student_id);
        }
        return true;
    } else {
        printf("remove %d fail\n", course_id);
        return false;
    }
}

bool Student::choose_class(const int &course_id) {
    auto course = total_class_list.find(course_id);
    bool ok = this->choose_class_list.insert({course_id, course->second->course_name}).second;
    if (ok) {
        printf("choose %d success\n", course_id);
        course->second->choose_number += 1;
        course->second->choose_student_list.insert({this->student_id, this->student_name});
        return true;
    } else {
        return false;
    }
}

Student::Student(long long Student_id, const std::string &Student_name, bool Gender, unsigned int Years,
        std::string Major, unsigned int Classroom_id, long long Phone_number) {
    student_id = Student_id;
    student_name = Student_name;
    gender = Gender;
    age = Years;
    major = std::move(Major);
    classroom_id = Classroom_id;
    phone_number = Phone_number;
}

Student::Student(long long Student_id, const std::string &Student_name, bool Gender, unsigned int Years,
                 unsigned int Major, unsigned int Classroom_id, long long Phone_number) {
    student_id = Student_id;
    student_name = Student_name;
    gender = Gender;
    age = Years;
    major = major_list[Major];
    classroom_id = Classroom_id;
    phone_number = Phone_number;
}