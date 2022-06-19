#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <utility>
#include <vector>
#include <direct.h>

//类的声明
class ClassInformation;
class Student;

//变量定义
int COURSE_LIST_NUMBER = 10001;
//公共必修、学科必修、学科选修、专业必修 、专业选修、实践必修、实践选修
const std::map<unsigned int, std::string> course_nature_list = {{1, "公共必修"},{2, "学科必修"},{3, "学科选修"},{4, "专业必修"},{5, "专业选修"},{6, "实践必修"},{7, "实践选修"}};
//0是英语，1是数学，2是计算机专业
std::vector<std::string> major_list = {"major"};
std::map<unsigned int, ClassInformation*> total_class_list;
std::map<unsigned int, Student*> total_student_list;

//函数声明
//课程
int class_id_create(const std::string &course_name);
bool new_class(const std::string &Course_name, unsigned int Course_nature, unsigned int Total_hours, unsigned int Credits,unsigned int Semester);
bool remove_class(const int &course_id);
void class_list_show();
void target_class_list_show(const int & course_id);
void who_choose_this_class(const unsigned int &course_id);
unsigned int how_many_student_choose_this_class(const unsigned int &course_id);
unsigned int how_many_class();
//学生
bool new_student(const unsigned int &student_id, const std::string &student_name, bool gender, unsigned int ages, unsigned int major, unsigned int classroom_id, long long phone_number);
bool remove_student(const unsigned int &student_id);
void student_list_show();
void target_student_show(const unsigned int &student_id);
bool student_choose_class(const unsigned int &student_id, const int &course_id);
bool student_remove_class(const unsigned int &student_id, const int &course_id);
void student_change_information(const unsigned int &student_id);
unsigned int how_many_student();
//专业操作
unsigned int new_major(const std::string & major_name);
void major_list_show();
//交互功能
void welcome();


//类的定义
class ClassInformation {
public:
    int course_id;//课程代码
    std::string course_name;//课程名称
    std::string course_nature;//课程性质
    unsigned int total_hours;//总学时
    unsigned int credits;//学分
    unsigned int semester;//开课学期
    unsigned int choose_number;//选修人数
    std::map<unsigned int, std::string> choose_student_list;//选该门课的学生列表

    ClassInformation(const std::string &Course_name, unsigned int Course_nature, unsigned int Total_hours, unsigned int Credits, unsigned int Semester) {
        course_id = class_id_create(Course_name);
        course_nature = course_nature_list.find(Course_nature)->second;
        total_hours = Total_hours;
        credits = Credits;
        semester = Semester;
        choose_number = 0;
    }

    ClassInformation(int Course_id, const std::string &Course_name, std::string Course_nature, unsigned int Total_hours, unsigned int Credits, unsigned int Semester, unsigned int Choose_number) {
        course_id = Course_id;
        course_nature = std::move(Course_nature);
        total_hours = Total_hours;
        credits = Credits;
        semester = Semester;
        choose_number = Choose_number;
    }

    void class_show() const{
        printf("\t%d\t%s\t%s\t%d\t%d\t%d\t%d\n", this->course_id, this->course_name.c_str(),
               this->course_nature.c_str(), this->total_hours, this->credits,
               this->semester, this->choose_number);
    }

    void choose_student_show(){
        for (const auto &student: this->choose_student_list) {
            printf("\t\t%d\t%s\n", student.first, student.second.c_str());
        }
    }
};
class Student {
private:
    unsigned int student_id;
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
    Student(unsigned int Student_id, const std::string &Student_name, bool Gender, unsigned int Years,
            unsigned int Major, unsigned int Classroom_id, long long Phone_number) {
        student_id = Student_id;
        student_name = Student_name;
        gender = Gender;
        age = Years;
        major = major_list[Major];
        classroom_id = Classroom_id;
        phone_number = Phone_number;
    }

    Student(unsigned int Student_id, const std::string &Student_name, bool Gender, unsigned int Years,
            std::string Major, unsigned int Classroom_id, long long Phone_number) {
        student_id = Student_id;
        student_name = Student_name;
        gender = Gender;
        age = Years;
        major = std::move(Major);
        classroom_id = Classroom_id;
        phone_number = Phone_number;
    }

    bool choose_class(const int &course_id) {
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

    bool remove_class(const int &course_id) {
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

    void choose_class_list_show() {
        printf("he choose this class\n");
        printf("\tclass_is\tclass_name\n");
        for (auto &it: choose_class_list) {
            printf("\t%d\t%s\n", it.first, it.second.c_str());
        }
        printf("the end\n");
    }

    void change_info() {
        printf("input something if change，or Enter to jump it");
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
        {
            std::string tmp_string;
            std::cin >> tmp_string;
            if (!tmp_string.empty()) {
                this->student_name = tmp_string;
                {
                    for(const auto& cour : this->choose_class_list){
                        auto course = total_class_list.find(cour.first);
                        auto stu = course->second->choose_student_list.find(this->student_id);
                        stu->second=tmp_string;
                    }
                }
                printf("change student name success!\n");
            }
        }
        //修改性别
        printf("1 is man,0 is girl\n");
        printf("change student gender as:  ");
        {
            int tmp_gender = -1;
            std::cin >> tmp_gender;
            if (tmp_gender == 1) {
                this->gender = true;
                printf("change student gender success!\n");
            } else if (tmp_gender == 0) {
                this->gender = false;
                printf("change student gender success!\n");
            }
        }
        //修改年龄
        printf("change student age as:  ");
        {
            int tmp_int = -1;
            std::cin >> tmp_int;
            if (tmp_int > 0) {
                this->age = tmp_int;
                printf("change student age success!\n");
            } else if (tmp_int == 0) {
                printf("hey hey hey guys.He or she is a baby?\n");
            }
        }
        //修改系别
        printf("change student major as:  ");
        {
            //I haven't done the major system
        }
        //修改班级
        printf("change student classroom id as:  ");
        {
            int tmp_int = -1;
            std::cin >> tmp_int;
            if (tmp_int > 0) {
                this->classroom_id = tmp_int;
                printf("change student classroom id success!\n");
            }
        }
        //修改联系方式
        printf("change student phone number as:  ");
        {
            long long tmp_int = -1;
            std::cin >> tmp_int;
            if (tmp_int > 0) {
                this->phone_number = tmp_int;
                printf("change student phone number success!\n");
            }
        }

    }

    void detail_show() const {
        printf("\t%d\t%s\t%s\t%d\t%lld\t%d\t%s\n", this->student_id, this->student_name.c_str(),
               this->major.c_str(), this->classroom_id, this->phone_number, this->age,
               (this->gender ? "man" : "girl"));
    }

    std::map<int, std::string> get_class_list(){
        return this->choose_class_list;
    }


};


//函数操作
//课程
int class_id_create(const std::string &course_name) {
    int class_id_now = COURSE_LIST_NUMBER;
    ++COURSE_LIST_NUMBER;
    bool ok = total_class_list.count(class_id_now);
    if (!ok) {
        return class_id_now;
    } else {
        return -1;
    }
}
bool remove_class(const int &course_id) {
    auto cour = total_class_list.find(course_id);
    if(cour != total_class_list.end()){
        auto course = cour->second;
        for(const auto& student_id_name : course->choose_student_list){
            auto student = total_student_list.find(student_id_name.first);
            student->second->remove_class(course_id);
        }
        total_class_list.erase(course_id);
        printf("remove %d success\n", course_id);
        return true;
    } else {
        printf("remove %d fail\n", course_id);
        return false;
    }
}
bool new_class(const std::string &Course_name, unsigned int Course_nature, unsigned int Total_hours, unsigned int Credits,unsigned int Semester) {
    auto *tmp_class = new ClassInformation(Course_name, Course_nature, Total_hours, Credits, Semester);
    if (tmp_class->course_id == -1) {
        printf("new class error,can't not add total_class_list\n");
        delete (tmp_class);
        return false;
    } else {
        total_class_list.insert({tmp_class->course_id, tmp_class});
        return true;
    }
}
void class_list_show() {
    printf("\tclass id\tclass name\tclass nature\ttotal hour\tcredit\tsemester\tchoose number\n");
    for (const auto &course: total_class_list) {
        const auto &  course_data = course.second;
        course_data->class_show();
    }
    printf("the end\n");
}
void target_class_list_show(const int & course_id) {
    const auto &course = total_class_list.find(course_id);
    if(course != total_class_list.end()){
        printf("\tclass id\tclass name\tclass nature\ttotal hour\tcredit\tsemester\tchoose number\n");
        course->second->class_show();
    }
    who_choose_this_class(course_id);
    printf("the end\n");
}
void who_choose_this_class(const unsigned int &course_id) {
    auto course = total_class_list.find(course_id);
    printf("choose %s 's student\t\tstudent id\tstudent name\n", course->second->course_name.c_str());
    course->second->choose_student_show();
    printf("the end\n");
}
unsigned int how_many_student_choose_this_class(const unsigned int &course_id) {
    unsigned int number = total_class_list.size();
    return number;
}
unsigned int how_many_class() {
    unsigned int number = total_class_list.size();
    printf("there are %d class", number);
    return number;
}
//学生
bool new_student(const unsigned int &student_id, const std::string &student_name, bool gender, unsigned int ages, unsigned int major, unsigned int classroom_id, long long phone_number) {
    if (total_student_list.count(student_id)) {
        printf("student id have existed\n");
        return false;
    }
    auto *tmp_student = new Student(student_id, student_name, gender, ages, major, classroom_id, phone_number);
    total_student_list.insert({student_id, tmp_student});
    return true;
}
bool remove_student(const unsigned int &student_id) {
    auto stu=total_student_list.find(student_id);
    if(stu != total_student_list.end()){
        auto student = stu->second;
        for(const auto& course_id : student->get_class_list()){
            student->remove_class(course_id.first);
        }
        total_student_list.erase(student_id);
        printf("remove %d success\n", student_id);
        return true;
    } else {
        printf("remove %d fail,this student isn't exist\n", student_id);
        return false;
    }
}
void student_list_show() {
    printf("\tstudent id\tstudent name\tmajor\tclassroom\tphone number\tage\tgender\n");
    for (const auto &s: total_student_list) {
        s.second->detail_show();
    }
}
void target_student_show(const unsigned int &student_id){
    printf("\tstudent id\tstudent name\tmajor\tclassroom\tphone number\tage\tgender\n");

    const auto &s = total_student_list.find(student_id);\
    if(s!=total_student_list.end())
    {
        s->second->detail_show();
    }else{
        printf("error");
    }

}
bool student_choose_class(const unsigned int &student_id, const int &course_id) {
    auto s = total_student_list.find(student_id);
    if (s == total_student_list.end()) {
        printf("student id is wrong\n");
        return false;
    }
    if (!total_class_list.count(course_id)) {
        printf("this class id is wrong\n");
        return false;
    }
    auto student = s->second;
    if (student->get_class_list().count(course_id)) {
        printf("have chosen\n");
        return true;
    }
    if (student->choose_class(course_id)) {
        return true;
    } else {
        return false;
    }
}
bool student_remove_class(const unsigned int &student_id, const int &course_id) {
    auto s = total_student_list.find(student_id);
    if (s == total_student_list.end()) {
        printf("student id is wrong\n");
        return false;
    }
    if (!total_class_list.count(course_id)) {
        printf("this class id is wrong\n");
        return true;
    }
    auto student = s->second;
    if (!student->get_class_list().count(course_id)) {
        printf("haven't chosen\n");
        return true;
    }
    if (student->remove_class(course_id)) {
        return true;
    } else {
        return false;
    }
}
void student_change_information(const unsigned int &student_id) {
    auto s = total_student_list.find(student_id);
    if (s == total_student_list.end()) {
        printf("student id is wrong\n");
        return;
    }
    s->second->change_info();
}
unsigned int how_many_student() {
    unsigned int number = total_student_list.size();
    printf("there are %d students", number);
    return number;
}




//保存与读取初始化
void save() {

    std::string dir;
    {
        char _tmp[256];
        getcwd(_tmp,256);
        for(auto &c:_tmp){
            if(c=='\\')
                c='/';
        }
        std::string tmp(_tmp);
        auto tmp_dir = tmp+"/data/";
        if(0 != access(tmp_dir.c_str(),0)){
            mkdir(tmp_dir.c_str());
        }
        dir=tmp_dir;
    }
    std::ofstream out1(dir+"class_data.txt");
    if (out1.is_open()) {
        for (const auto &course: total_class_list) {
            auto course_data = course.second;
            out1 << course_data->course_id << " ";//课程代码
            out1 << course_data->course_name << " ";//课程名称
            out1 << course_data->course_nature << " ";//课程性质
            out1 << course_data->total_hours << " ";//总学时
            out1 << course_data->credits << " ";//学分
            out1 << course_data->semester << " ";//开课学期
            out1 << course_data->choose_number << "\n";//选修人数
            std::ofstream out2((dir+"class_choose_student_" + std::to_string(course_data->course_id) + ".txt"));
            for (const auto &i: course_data->choose_student_list) {
                out2 << i.first << " " << i.second << "\n";
            }
            out2.close();
        }
        out1.close();
    }
    std::ofstream out3(dir+"student_data.txt");
    if (out3.is_open()) {
        for (const auto &student: total_student_list) {
            auto student_data = student.second;
            out3 << student_data->student_id << " ";
            out3 << student_data->student_name << " ";
            out3 << student_data->gender << " ";
            out3 << student_data->age << " ";
            out3 << student_data->major << " ";
            out3 << student_data->classroom_id << " ";
            out3 << student_data->phone_number << "\n";
            std::ofstream out4((dir+"student_choose_class_" + std::to_string(student_data->student_id) + ".txt"));
            for (const auto &i: student_data->choose_class_list) {
                out4 << i.first << " " << i.second << "\n";
            }
            out4.close();
        }
        out3.close();
    }
    std::ofstream out5((dir+"major_list.txt"));
    if(out5.is_open()){
        for(const auto &major : major_list){
            out5 << major <<"\n";
        }
        out5.close();
    }
    out1.close();
    out3.close();
    out5.close();
}
void init() {
    std::string dir;
    {
        char _tmp[256];
        getcwd(_tmp, 256);
        for (auto &c: _tmp) {
            if (c == '\\')
                c = '/';
        }
        std::string tmp(_tmp);
        auto tmp_dir = tmp + "/data/";
        if (0 != access(tmp_dir.c_str(), 0)) {
            mkdir(tmp_dir.c_str());
        }
        dir = tmp_dir;
    }
    std::ifstream in1(dir+"class_data.txt");
    if(in1.is_open()){
        int course_id;//课程代码
        std::string course_name;//课程名称
        std::string course_nature;//课程性质
        unsigned int total_hours;//总学时
        unsigned int credits;//学分
        unsigned int semester;//开课学期
        unsigned int choose_number;//选修人数
        while (!in1.eof()) {
            in1 >> course_id >> course_name >> course_nature >> total_hours >> credits >> semester>> choose_number;
            auto *temp_class = new ClassInformation(course_id, course_name, course_nature, total_hours, credits, semester, choose_number);
            std::ifstream in2(dir+"class_choose_student_" + std::to_string(course_id) + ".txt");
            if(in2.is_open()){
                std::map<unsigned int, std::basic_string<char>> list;
                unsigned int student_id;
                std::string student_name;
                while (in2 >> student_id >> student_name) {
                    list.insert({student_id, student_name});
                }
                temp_class->choose_student_list = list;
            }
            in2.close();
            total_class_list.insert({course_id, temp_class});
        }
        in1.close();
    }
    std::ifstream in3(dir+"student_data.txt");
    if(in3.is_open()){
        unsigned int student_id;
        std::string student_name;
        bool gender;
        unsigned int years;
        std::string major;
        unsigned int classroom_id;
        long long phone_number;
        while (!in3.eof()) {
            in3 >> student_id >> student_name>> gender >> years>> major>> classroom_id>> phone_number;
            auto *temp_student = new Student(student_id, student_name, gender, years, major, classroom_id,phone_number);
            std::ifstream in4(dir+"student_choose_class_" + std::to_string(student_id) + ".txt");
            if(in4.is_open()){
                std::map<int, std::string> list;
                unsigned int class_id;
                std::string class_name;
                while (in4 >> class_id >> class_name) {
                    list.insert({class_id, class_name});
                }
                temp_student->choose_class_list = list;
            }
            in4.close();
            total_student_list.insert({student_id, temp_student});
        }
        in3.close();
    }
    std::ifstream in5(dir+"major_list.txt");
    if(in5.is_open()){
        std::string tmp_major;
        while (in5>>tmp_major){
            major_list.push_back(tmp_major);
        }
        in5.close();
    }
    //初始化时更改COURSE_ID
    if(total_class_list.size()!=0){
        auto last = --total_class_list.end();
        COURSE_LIST_NUMBER = last->first;
    }
}
//专业操作
unsigned int new_major(const std::string & major_name){
    major_list.push_back(major_name);
    if(major_list.empty()){
        return 0;
    } else{
        return major_list.size()-1;
    }
}
void major_list_show(){
    for(const auto &major:major_list){
        std::cout<<major<<" ";
    }
    printf("\n");
}

void course_nature_list_show(){
    for(const auto& i:course_nature_list){
        printf("%d: %s  ",i.first,i.second.c_str());
    }
}


void welcome(){
    system("cls");
    std::cout<<"1. show all class"<<std::endl;
    std::cout<<"2. show all student"<<std::endl;
    std::cout<<"3. new student"<<std::endl;
    std::cout<<"4. new class"<<std::endl;
    std::cout<<"5. show target class"<<std::endl;
    std::cout<<"6. show target student"<<std::endl;
    std::cout<<"7. remove class"<<std::endl;
    std::cout<<"8. remove student"<<std::endl;
    std::cout<<"9. change student information"<<std::endl;
    std::cout<<"10. statistical function"<<std::endl;
    std::cout<<"0. save and exit"<<std::endl;
}


int main() {
    init();

    while (true){
        welcome();
        int choice;
        std::cin >> choice;
        switch (choice) {
            case 1:
                system("cls");
                class_list_show();
                system("pause");
                break;
            case 2:
                system("cls");
                student_list_show();
                system("pause");
                break;
            case 3:
            {
                system("cls");
                std::cout<<"input id,name,gender ,age,major,classroom_id,phone number "<<std::endl;
                std::cout<<"gender 1 is man,0 is girl."<<std::endl;
                major_list_show();
                unsigned int student_id;
                std::string student_name;
                bool gender;
                unsigned int years;
                unsigned int major;
                unsigned int classroom_id;
                long long phone_number;
                std::cin >>student_id >> student_name >> gender >> years >> major >> classroom_id >> phone_number;
                if(new_student(student_id,student_name,gender,years,major,classroom_id,phone_number)){
                    printf("success");
                }
                save();
                system("pause");
                break;
            }
            case 4:
            {
                system("cls");
                std::cout<<"input ,name,nature ,total hours ,credits,semester "<<std::endl;
                std::cout<<"course_nature is number";
                course_nature_list_show();
                std::string course_name;//课程名称
                int course_nature;//课程性质
                unsigned int total_hours;//总学时
                unsigned int credits;//学分
                unsigned int semester;//开课学期
                std::cin >> course_name >> course_nature >> total_hours >> credits >> semester;
                if(new_class(course_name,course_nature,total_hours,credits,semester)){
                    printf("success");
                }
                save();
                system("pause");
                break;
            }
            case 5:
            {
                system("cls");
                std::cout<<"target class_id"<<std::endl;
                int class_id;
                std::cin>>class_id;
                target_class_list_show(class_id);
                system("pause");
                break;
            }
            case 6:
            {
                system("cls");
                std::cout<<"target student_id"<<std::endl;
                int student_id;
                std::cin>>student_id;
                target_student_show(student_id);
                system("pause");
                break;
            }
            case 7:
            {
                system("cls");
                std::cout<<"target class_id"<<std::endl;
                int class_id;
                std::cin>>class_id;
                if(remove_class(class_id)){
                    printf("success");
                }
                save();
                system("pause");
                break;
            }
            case 8:
            {
                system("cls");
                std::cout<<"target student_id"<<std::endl;
                int student_id;
                std::cin>>student_id;
                if(remove_student(student_id)){
                    printf("success");
                }
                save();
                system("pause");
                break;
            }
            case 9:
            {
                system("cls");
                std::cout<<"target student_id"<<std::endl;
                int student_id;
                std::cin>>student_id;
                student_change_information(student_id);
            }
            case 10:
            {
                system("cls");
                std::cout<<"there are"<<how_many_class()<<"class"<<std::endl;
                std::cout<<"there are"<<how_many_student()<<"student"<<std::endl;
                system("pause");
                break;
            }
            case 0:
            {
                save();
                return 0;
            }
            default:
            {
                printf("error input");
                system("pause");
                break;
            }
        }
    }
    return 0;
}
