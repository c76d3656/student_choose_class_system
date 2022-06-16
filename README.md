# student_choose_class_system
# 学生选修课程系统设计(目前无交互)
## 问题描述
  1. 高校中学生信息包括：学号、姓名、性别、年龄、系别、班级、联系方式等信息。
  2. 课程信息包括：课程代码、课程名称、课程性质、总学时、学分、开课学期、选修人数等信息。学生可对课程信息进行查询，选修符合要求的课程。
  3. 根据课程信息和学生信息完成对课程的选修，需要专门的一个管理类来完成选修工作。
## 功能要求
  - [ ] 1. 添加功能：程序能够任意添加课程和学生记录，可提供选择界面供用户选择所要添加的类别，要求编号要唯一，如果添加了重复编号的记录时，则提示数据添加重复并取消添加。
  - [ ] 2. 查询功能：可根据编号、姓名等信息对已添加的学生和课程记录进行查询，如果未找到，给出相应的提示信息，如果找到，则显示相应的记录信息。
  - [ ] 3. 显示功能：可显示当前系统中所有学生和课程的记录，每条记录占据一行。
  - [ ] 4. 编辑功能：可根据查询结果对相应的记录进行修改，修改时注意编号的唯一性。
  - [ ] 5. 删除功能：主要实现对已添加的学生和课程记录进行删除。如果当前系统中没有相应的记录，则提示“记录为空！”并返回操作。
  - [ ] 6. 统计功能：能根据多种参数进行统计。能统计学生人数、课程的门数、选修某门课程的学生的相关信息。
  - [ ] 7. 保存功能：可将当前系统中各类记录存入文件中，存入方式任意。
  - [ ] 8. 读取功能：可将保存在文件中的信息读入到当前系统中，供用户进行使用。
## 问题的解决方案  
根据系统功能要求，可以将问题解决分为以下步骤：
  1. 应用系统分析，建立该系统的功能模块框图以及界面的组织和设计；
  2. 分析系统中的各个实体及它们之间的关系；
  3. 根据问题描述，设计系统的类层次；
  4. 完成类层次中各个类的描述；
  5. 完成类中各个成员函数的定义；
  6. 完成系统的应用模块；
  7. 功能调试；
  8. 完成系统总结报告。