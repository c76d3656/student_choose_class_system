#include "head.h"
#include "ClassInfor.h"
#include "Student.h"
#include<Windows.h>
#include "Manage.h"

void dropInput();

int main() {
    auto manage = new Manage;
    manage->init();
    while (true) {
        manage->welcome();
        std::string _str;
        std::cin >> _str;
        auto choice = manage->input_solution(_str);
        switch (choice) {
            case 1:
                system("cls");
                manage->class_list_show();
                system("pause");
                break;
            case 2:
                system("cls");
                manage->student_list_show();
                system("pause");
                break;
            case 3: {
                system("cls");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                        FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);//设置字体为紫色
                std::cout << "请输入学号，姓名，性别，年龄，专业，班级，电话号码 " << std::endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                        FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);//设置字体为青色
                std::cout << "性别请输入数字：1代表男性，0代表女性" << std::endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                        FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN |
                                        FOREGROUND_BLUE);//设置字体为白色
                std::cout << "专业代号 ";
                manage->major_list_show();
                long long student_id;
                std::string student_name;
                bool gender;
                unsigned int years;
                unsigned int major;
                unsigned int classroom_id;
                long long phone_number;
                std::cin >> student_id >> student_name >> gender >> years >> major >> classroom_id >> phone_number;
                if (!std::cin) {
                    dropInput();
                    break;
                }
                if (major < 0 && major > major_list.size() - 1) {
                    dropInput();
                    break;
                }
                dropInput();
                if (manage->new_student(student_id, student_name, gender, years, major, classroom_id, phone_number)) {
                    printf("成功");
                }
                manage->save();
                system("pause");
                break;
            }
            case 4: {
                system("cls");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                        FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);//设置字体为紫色
                std::cout << "请输入课程名字，课程性质，总学时，学分，开设学期 " << std::endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                        FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);//设置字体为青色
                std::cout << "注意：课程性质请输入数字" << std::endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                        FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN |
                                        FOREGROUND_BLUE);//设置字体为白色
                manage->course_nature_list_show();
                std::string course_name;//课程名称
                int course_nature;//课程性质
                unsigned int total_hours;//总学时
                unsigned int credits;//学分
                unsigned int semester;//开课学期
                std::cin >> course_name >> course_nature >> total_hours >> credits >> semester;
                if (!std::cin) {
                    dropInput();
                    break;
                }
                if (course_nature < 0 && course_nature > course_nature_list.size() - 1) {
                    dropInput();
                    break;
                }
                dropInput();
                if (manage->new_class(course_name, course_nature, total_hours, credits, semester)) {
                    printf("成功");
                }
                manage->save();
                system("pause");
                break;
            }
            case 5: {
                system("cls");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                        FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);//设置字体为紫色
                std::cout << "请输入课程代号" << std::endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                        FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN |
                                        FOREGROUND_BLUE);//设置字体为白色
                long long class_id;
                std::cin >> class_id;
                if (!std::cin) {
                    dropInput();
                    break;
                }
                dropInput();
                manage->target_class_list_show(class_id);
                system("pause");
                break;
            }
            case 6: {
                system("cls");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                        FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);//设置字体为紫色
                std::cout << "请输入学生学号" << std::endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                        FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN |
                                        FOREGROUND_BLUE);//设置字体为白色
                long long student_id;
                std::cin >> student_id;
                if (!std::cin) {
                    dropInput();
                    break;
                }
                dropInput();
                manage->target_student_show(student_id);
                system("pause");
                break;
            }
            case 7: {
                system("cls");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                        FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);//设置字体为紫色
                std::cout << "请输入课程代号" << std::endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                        FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN |
                                        FOREGROUND_BLUE);//设置字体为白色
                int class_id;
                std::cin >> class_id;
                if (!std::cin) {
                    dropInput();
                    break;
                }
                dropInput();
                if (manage->remove_class(class_id)) {
                    printf("成功");
                }
                manage->save();
                system("pause");
                break;
            }
            case 8: {
                system("cls");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                        FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);//设置字体为紫色
                std::cout << "请输入学生学号" << std::endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                        FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN |
                                        FOREGROUND_BLUE);//设置字体为白色
                long long student_id;
                std::cin >> student_id;
                if (!std::cin) {
                    dropInput();
                    break;
                }
                dropInput();
                if (manage->remove_student(student_id)) {
                    printf("成功");
                }
                manage->save();
                system("pause");
                break;
            }
            case 9: {
                system("cls");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                        FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);//设置字体为紫色
                std::cout << "请输入学生学号" << std::endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                        FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN |
                                        FOREGROUND_BLUE);//设置字体为白色
                long long student_id;
                std::cin >> student_id;
                if (!std::cin) {
                    dropInput();
                    break;
                }
                dropInput();
                manage->student_change_information(student_id);
                break;
            }
            case 10: {
                system("cls");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                        FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN |
                                        FOREGROUND_BLUE);//设置字体为白色
                std::cout << "共有" << manage->how_many_class() << "门课" << std::endl;
                std::cout << "共有" << manage->how_many_student() << "个学生" << std::endl;
                system("pause");
                break;
            }
            case 11: {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                        FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);//设置字体为紫色
                std::cout << "请输入学生学号和所选课程代号" << std::endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                        FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN |
                                        FOREGROUND_BLUE);//设置字体为白色
                long long student_id, course_id;
                std::cin >> student_id >> course_id;
                if (!std::cin) {
                    dropInput();
                    break;
                }
                dropInput();
                printf("成功");
                manage->student_choose_class(student_id, course_id);
                break;
            }
            case 12: {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                        FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);//设置字体为紫色
                std::cout << "请输入学生学号和所选课程代号" << std::endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                        FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN |
                                        FOREGROUND_BLUE);//设置字体为白色
                long long student_id, course_id;
                std::cin >> student_id >> course_id;
                if (!std::cin) {
                    dropInput();
                    break;
                }
                dropInput();
                manage->student_remove_class(student_id, course_id);
                break;
            }
            case 13: {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                        FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);//设置字体为紫色
                std::cout << "请输入新建专业名字" << std::endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                        FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN |
                                        FOREGROUND_BLUE);//设置字体为白色
                std::string tmp_major;
                std::cin >> tmp_major;
                if (!std::cin) {
                    dropInput();
                    break;
                }
                dropInput();
                if (!tmp_major.empty()) {
                    manage->new_major(tmp_major);
                    break;
                }
                break;
            }
            case 0: {
                manage->save();
                return 0;
            }
            default: {
                printf("输入错误");
                dropInput();
                system("pause");
                continue;
            }
        }
    }
    return 0;
}

void dropInput() {
    while (std::cin && std::cin.get() != '\n')continue;
    std::cin.clear();
}