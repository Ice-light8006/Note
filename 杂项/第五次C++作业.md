# 题目
（1）学生类：一个学生类，有学号、姓名、年龄、专业。函数有入学、升级、换专业、毕业。`main` 函数能够创建多个学生，实现学生的各种信息处理，并能够统计每个专业的学生人数和学生总数。
（2）课程类：在上述学生类的基础上，添加课程类，有课程名、课程号、选课人数。函数包括选课和退选功能。`main` 函数实现各种处理，并统计课程数以及每门课的选课人数。
（3）教室类：在上述两个类的基础上，添加教室类，实现每个课程的教室分配。要求每个课程可以有多个教室，学生在选课时要考虑教室的选择以及上课时间不要冲突。
# 代码实现
```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

enum Weekday { Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday };
enum Major { WLW, JK, RG };
enum TeachingBuilding { A, B, C, D };

struct TimeSlot
{
    Weekday weekday;
    int start, end;
};

class Classroom_HYC
{
public:
    Classroom_HYC(TeachingBuilding building, const string &roomId, int capacity);
    Classroom_HYC(const Classroom_HYC &) = delete;
    Classroom_HYC &operator=(const Classroom_HYC &) = delete;
    ~Classroom_HYC();
    string getLabel() const;
    int getCapacity() const;
    static int getCount();

private:
    TeachingBuilding building;
    string roomId;
    int capacity;
    static int count;
};

struct ClassroomOption
{
    Classroom_HYC *classroom;
    int selectedCount;
};

class Student_HYC;
class SchoolManager;

class Course_HYC
{
public:
    Course_HYC(const string &name, const string &id, const vector<TimeSlot> &times);
    Course_HYC(const Course_HYC &) = delete;
    Course_HYC &operator=(const Course_HYC &) = delete;
    ~Course_HYC();
    const string &getName() const;
    const string &getId() const;
    int getSelectedCount() const;
    static int getCount();
    bool validTimes() const;
    void printInfo() const;

private:
    string name, id;
    vector<TimeSlot> times;
    vector<ClassroomOption> classrooms;
    int count_selected;
    static int count;

    friend class Student_HYC;
    friend class SchoolManager;
};

struct CourseSelection
{
    Course_HYC *course;
    Classroom_HYC *classroom;
};

class Student_HYC
{
public:
    Student_HYC(const string &stuId, const string &name, Major major, int age);
    Student_HYC(const Student_HYC &) = delete;
    Student_HYC &operator=(const Student_HYC &) = delete;
    static Student_HYC enroll(const string &stuId, const string &name, Major major, int age);
    void upgrade();
    void switchMajor(Major newMajor);
    void graduate();
    ~Student_HYC();
    const string &getName() const;
    int getGrade() const;
    static int getCount();
    static int getMajorCount(Major major);
    void printCourses() const;

private:
    string stuId, name;
    Major major;
    int age, grade;
    bool graduated;
    vector<CourseSelection> selected_course;
    static int count;
    static int count_major[3];

    friend class SchoolManager;
};

class SchoolManager
{
public:
    SchoolManager(const vector<Course_HYC *> &courseList);
    bool assignClassroom(Course_HYC &course, Classroom_HYC &classroom);
    bool selectCourse(Student_HYC &student, Course_HYC &course, Classroom_HYC &classroom);
    bool unselectCourse(Student_HYC &student, Course_HYC &course);

private:
    vector<Course_HYC *> courses;
};

TimeSlot makeTime(Weekday weekday, int start, int end);
bool isConflict(const TimeSlot &a, const TimeSlot &b);
bool isConflict(const vector<TimeSlot> &a, const vector<TimeSlot> &b);
void printResult(const string &operation, bool result);
void printStatistics();

int Classroom_HYC::count = 0;
int Course_HYC::count = 0;
int Student_HYC::count = 0;
int Student_HYC::count_major[3] = {0, 0, 0};

TimeSlot makeTime(Weekday weekday, int start, int end)
{
    return {weekday, start, end};
}

bool isConflict(const TimeSlot &a, const TimeSlot &b)
{
    return a.weekday == b.weekday && a.start < b.end && b.start < a.end;
}

bool isConflict(const vector<TimeSlot> &a, const vector<TimeSlot> &b)
{
    for (const auto &x : a)
        for (const auto &y : b)
            if (isConflict(x, y)) return true;
    return false;
}

Classroom_HYC::Classroom_HYC(TeachingBuilding building, const string &roomId, int capacity)
    : building(building), roomId(roomId), capacity(capacity)
{
    count++;
}

Classroom_HYC::~Classroom_HYC()
{
    count--;
}

string Classroom_HYC::getLabel() const
{
    char buildingName = 'A' + static_cast<int>(building);
    return string(1, buildingName) + roomId;
}

int Classroom_HYC::getCapacity() const
{
    return capacity;
}

int Classroom_HYC::getCount()
{
    return count;
}

Course_HYC::Course_HYC(const string &name, const string &id, const vector<TimeSlot> &times)
    : name(name), id(id), times(times), count_selected(0)
{
    count++;
}

Course_HYC::~Course_HYC()
{
    count--;
}

const string &Course_HYC::getName() const
{
    return name;
}

const string &Course_HYC::getId() const
{
    return id;
}

int Course_HYC::getSelectedCount() const
{
    return count_selected;
}

int Course_HYC::getCount()
{
    return count;
}

bool Course_HYC::validTimes() const
{
    if (times.empty()) return false;
    for (size_t i = 0; i < times.size(); i++)
    {
        if (times[i].weekday < Monday || times[i].weekday > Sunday ||
            times[i].start < 1 || times[i].end <= times[i].start)
            return false;

        for (size_t j = i + 1; j < times.size(); j++)
            if (isConflict(times[i], times[j])) return false;
    }
    return true;
}

void Course_HYC::printInfo() const
{
    const string days[7] = {"一", "二", "三", "四", "五", "六", "日"};
    cout << id << " " << name << " | ";
    for (size_t i = 0; i < times.size(); i++)
    {
        if (i > 0) cout << "、";
        cout << "周" << days[times[i].weekday] << "第"
             << times[i].start << "-" << times[i].end - 1 << "节";
    }
    cout << " | 选课人数: " << count_selected << "\n";

    for (const auto &option : classrooms)
        cout << "    " << option.classroom->getLabel()
             << "  已选: " << option.selectedCount << "/"
             << option.classroom->getCapacity() << "\n";
}

Student_HYC::Student_HYC(const string &stuId, const string &name, Major major, int age)
    : stuId(stuId), name(name), major(major), age(age), grade(1), graduated(false)
{
    count++;
    if (major >= WLW && major <= RG) count_major[major]++;
}

Student_HYC Student_HYC::enroll(const string &stuId, const string &name, Major major, int age)
{
    return Student_HYC(stuId, name, major, age);
}

void Student_HYC::upgrade()
{
    if (graduated || grade >= 4) return;
    grade++;
    age++;
}

void Student_HYC::switchMajor(Major newMajor)
{
    if (graduated || newMajor < WLW || newMajor > RG || major == newMajor) return;
    if (major >= WLW && major <= RG) count_major[major]--;
    major = newMajor;
    count_major[major]++;
}

void Student_HYC::graduate()
{
    if (graduated) return;

    for (const auto &selection : selected_course)
    {
        Course_HYC *course = selection.course;
        course->count_selected--;
        for (auto &option : course->classrooms)
        {
            if (option.classroom == selection.classroom)
            {
                option.selectedCount--;
                break;
            }
        }
    }

    selected_course.clear();
    graduated = true;
    count--;
    if (major >= WLW && major <= RG) count_major[major]--;
}

Student_HYC::~Student_HYC()
{
    if (!graduated) graduate();
}

const string &Student_HYC::getName() const
{
    return name;
}

int Student_HYC::getGrade() const
{
    return grade;
}

int Student_HYC::getCount()
{
    return count;
}

int Student_HYC::getMajorCount(Major major)
{
    if (major < WLW || major > RG) return 0;
    return count_major[major];
}

void Student_HYC::printCourses() const
{
    cout << name << "(" << stuId << "): ";
    if (selected_course.empty())
    {
        cout << "无选课记录\n";
        return;
    }

    for (const auto &selection : selected_course)
        cout << selection.course->getId() << "["
             << selection.classroom->getLabel() << "] ";
    cout << "\n";
}

SchoolManager::SchoolManager(const vector<Course_HYC *> &courseList)
    : courses(courseList)
{
}

bool SchoolManager::assignClassroom(Course_HYC &course, Classroom_HYC &classroom)
{
    if (find(courses.begin(), courses.end(), &course) == courses.end()) return false;
    if (!course.validTimes() || classroom.getCapacity() <= 0) return false;

    for (const auto &option : course.classrooms)
        if (option.classroom == &classroom) return false;

    for (Course_HYC *other : courses)
        for (const auto &option : other->classrooms)
            if (option.classroom == &classroom &&
                isConflict(course.times, other->times)) return false;

    course.classrooms.push_back({&classroom, 0});
    return true;
}

bool SchoolManager::selectCourse(Student_HYC &student, Course_HYC &course, Classroom_HYC &classroom)
{
    if (student.graduated) return false;
    if (find(courses.begin(), courses.end(), &course) == courses.end()) return false;

    auto roomIt = find_if(course.classrooms.begin(), course.classrooms.end(),
        [&](const ClassroomOption &option) { return option.classroom == &classroom; });

    if (roomIt == course.classrooms.end()) return false;

    for (const auto &selection : student.selected_course)
    {
        if (selection.course == &course || selection.course->name == course.name)
            return false;
        if (isConflict(selection.course->times, course.times)) return false;
    }

    if (roomIt->selectedCount >= classroom.getCapacity()) return false;

    student.selected_course.push_back({&course, &classroom});
    roomIt->selectedCount++;
    course.count_selected++;
    return true;
}

bool SchoolManager::unselectCourse(Student_HYC &student, Course_HYC &course)
{
    if (student.graduated) return false;

    auto it = find_if(student.selected_course.begin(), student.selected_course.end(),
        [&](const CourseSelection &selection) { return selection.course == &course; });

    if (it == student.selected_course.end()) return false;

    for (auto &option : course.classrooms)
    {
        if (option.classroom == it->classroom)
        {
            option.selectedCount--;
            break;
        }
    }

    course.count_selected--;
    student.selected_course.erase(it);
    return true;
}

void printResult(const string &operation, bool result)
{
    cout << "  " << operation << " -> " << (result ? "成功" : "失败") << "\n";
}

void printStatistics()
{
    cout << "学生总数: " << Student_HYC::getCount() << "\n";
    cout << "  物联网: " << Student_HYC::getMajorCount(WLW)
         << "  计科: " << Student_HYC::getMajorCount(JK)
         << "  软工: " << Student_HYC::getMajorCount(RG) << "\n";
    cout << "课程总数: " << Course_HYC::getCount() << "\n";
    cout << "教室总数: " << Classroom_HYC::getCount() << "\n";
}

int main()
{
    cout << "============================================\n";
    cout << "         学生选课与教室管理系统\n";
    cout << "============================================\n\n";

    Classroom_HYC r1(A, "101", 2), r2(A, "102", 1), r3(B, "201", 2);

    vector<TimeSlot> cppATimes, cppBTimes, pythonTimes, stm32Times, mathTimes;
    cppATimes.push_back(makeTime(Monday, 1, 3));
    cppATimes.push_back(makeTime(Wednesday, 1, 3));
    cppBTimes.push_back(makeTime(Tuesday, 1, 3));
    cppBTimes.push_back(makeTime(Thursday, 1, 3));
    pythonTimes.push_back(makeTime(Monday, 1, 3));
    pythonTimes.push_back(makeTime(Thursday, 3, 5));
    stm32Times.push_back(makeTime(Monday, 3, 5));
    mathTimes.push_back(makeTime(Friday, 1, 3));

    Course_HYC cppA("C++程序设计", "C001-A", cppATimes);
    Course_HYC cppB("C++程序设计", "C001-B", cppBTimes);
    Course_HYC python("Python程序设计", "C002", pythonTimes);
    Course_HYC stm32("STM32开发", "C003", stm32Times);
    Course_HYC math("高等数学", "C004", mathTimes);

    Student_HYC s1 = Student_HYC::enroll("2026001", "张三", WLW, 19);
    Student_HYC s2 = Student_HYC::enroll("2026002", "李四", JK, 20);
    Student_HYC s3 = Student_HYC::enroll("2026003", "王五", WLW, 19);
    Student_HYC s4 = Student_HYC::enroll("2026004", "赵六", RG, 20);

    vector<Course_HYC *> allCourses;
    allCourses.push_back(&cppA);
    allCourses.push_back(&cppB);
    allCourses.push_back(&python);
    allCourses.push_back(&stm32);
    allCourses.push_back(&math);
    SchoolManager manager(allCourses);

    cout << "【一】初始数据统计\n";
    printStatistics();

    cout << "\n【二】教室分配测试\n";
    printResult("C++ A班 -> A101", manager.assignClassroom(cppA, r1));
    printResult("C++ A班 -> A102", manager.assignClassroom(cppA, r2));
    printResult("C++ B班 -> A101", manager.assignClassroom(cppB, r1));
    printResult("Python -> A101 (教室时间冲突)", manager.assignClassroom(python, r1));
    printResult("Python -> B201", manager.assignClassroom(python, r3));
    printResult("STM32 -> A101", manager.assignClassroom(stm32, r1));
    printResult("高等数学 -> B201", manager.assignClassroom(math, r3));
    printResult("C++ B班 -> B201", manager.assignClassroom(cppB, r3));

    cout << "\n【三】学生选课测试\n";
    printResult("张三选 C++ A班 A101", manager.selectCourse(s1, cppA, r1));
    printResult("张三选 Python (时间冲突)", manager.selectCourse(s1, python, r3));
    printResult("张三选 C++ B班 (重复课程)", manager.selectCourse(s1, cppB, r1));
    printResult("张三选 STM32 A101", manager.selectCourse(s1, stm32, r1));
    printResult("李四选 C++ B班 A101", manager.selectCourse(s2, cppB, r1));
    printResult("李四选 Python B201", manager.selectCourse(s2, python, r3));
    printResult("王五选 C++ A班 A102", manager.selectCourse(s3, cppA, r2));
    printResult("赵六选 C++ A班 A102 (教室已满)", manager.selectCourse(s4, cppA, r2));
    printResult("赵六选 Python B201", manager.selectCourse(s4, python, r3));
    printResult("李四重复选择 Python", manager.selectCourse(s2, python, r3));

    cout << "\n【四】当前学生课表\n";
    s1.printCourses();
    s2.printCourses();
    s3.printCourses();
    s4.printCourses();

    cout << "\n【五】退课、升级、转专业、毕业测试\n";
    printResult("张三退选 STM32", manager.unselectCourse(s1, stm32));
    printResult("赵六退选 Python", manager.unselectCourse(s4, python));
    s1.upgrade();
    cout << "  张三升级后年级: " << s1.getGrade() << "\n";
    s2.switchMajor(RG);
    cout << "  李四转专业: 计科 -> 软工\n";
    s4.graduate();
    cout << "  赵六毕业\n";
    s1.graduate();
    cout << "  张三毕业 (自动清除选课记录)\n";

    cout << "\n【六】最终学生统计\n";
    printStatistics();

    cout << "\n【七】最终课程及教室统计\n";
    cppA.printInfo();
    cppB.printInfo();
    python.printInfo();
    stm32.printInfo();
    math.printInfo();

    cout << "\n【八】剩余学生课表\n";
    s2.printCourses();
    s3.printCourses();
    return 0;
}

```