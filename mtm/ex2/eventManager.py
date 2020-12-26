#### IMPORTS ####
import event_manager as EM

class Student:
    def __init__(self, ID, name, age, birth, semester):
        self.ID = ID
        self.name = name
        self.age = age
        self.birth = birth
        self.semester = semester
    def __repr__(self):
        return str(self.ID) + ', ' + self.name + ', ' + str(self.age) + ', ' \
            + str(self.birth) + ', ' + str(self.semester)

def validID(ID: int):
    ID_str = str(ID)
    if (ID_str[0] == 0):
        return False
    if (len(ID_str) != 8):
        return False
    return True

def validName(name: str):
    for letter in name:
        if ('a' <= letter and letter <= 'z'):
            continue
        elif ('A' <= letter and letter <= 'Z'):
            continue
        elif (letter == ' '):
            continue
        else:
            return False
    return True

def validAge(age: int):
    if (16 <= age <= 120): #define
        return True
    return False

def validBirth(birth: int, age: int):
    if (2020 - age != birth): #define
        return False
    return True

def validSemester(semester: int):
    if (semester < 1):
        return False
    return True

def validStudent(student):
    if (validID(student.ID) and validName(student.name) and validAge(student.age) and \
            validBirth(student.birth, student.age) and validSemester(student.semester)):
        return True
    return False

def createStudentObjects(src_file_path: str):
    src_file = open(src_file_path, 'r')
    student_objects = []
    for line in src_file:
        student = [e.strip() for e in line.split(',')]
        student[1] = " ".join(student[1].split())
        student = Student(int(student[0]), student[1], int(student[2]), int(student[3]), int(student[4]))
        #validation check
        if (validStudent(student) is False):
            continue
        exists = False
        for i, e in enumerate(student_objects):
            if (e.ID == student.ID):
                student_objects[i] = student
                exists = True
                break
        if (exists):
            continue
        student_objects.append(student)
    src_file.close()
    return student_objects

#### PART 1 ####
# Filters a file of students' subscription to specific event:
#   orig_file_path: The path to the unfiltered subscription file
#   filtered_file_path: The path to the new filtered file
def fileCorrect(orig_file_path: str, filtered_file_path: str):
    student_objects = createStudentObjects(orig_file_path)
    student_objects = sorted(student_objects, key=lambda student: student.ID)
    dest_file = open(filtered_file_path, 'w') 
    for e in student_objects: 
        dest_file.write(repr(e) + '\n')
    dest_file.close()
    pass


# Writes the names of the K youngest students which subscribed 
# to the event correctly.
#   in_file_path: The path to the unfiltered subscription file
#   out_file_path: file path of the output file
def printYoungestStudents(in_file_path: str, out_file_path: str, k: int) -> int:
    if (k <= 0):
        return -1
    student_objects = createStudentObjects(in_file_path)
    student_objects = sorted(student_objects, key=lambda student: (student.age, student.ID))
    dest_file = open(out_file_path, 'w')
    students_num = len(student_objects)
    if (students_num < k):
        k = students_num
    for i in range(k): 
        dest_file.write((student_objects[i]).name + '\n')
    dest_file.close()
    return k

    
# Calculates the avg age for a given semester
#   in_file_path: The path to the unfiltered subscription file
#   retuns the avg, else error codes defined.
def correctAgeAvg(in_file_path: str, semester: int) -> float:
    if (semester < 1):
        return -1
    student_objects = createStudentObjects(in_file_path)
    age_sum = 0
    students = 0
    for e in student_objects: 
        if (e.semester == semester):
            age_sum += e.age
            students += 1
    if (students == 0):
        return students
    return age_sum/students
    

#### PART 2 ####
# Use SWIG :)
# print the events in the list "events" using the functions from hw1
#   events: list of dictionaries
#   file_path: file path of the output file
#em, event_names: list, event_id_list: list, day: int, month: int, year: int):
def printEventsList(events :list, file_path :str): 
    if (len(events) == 0):
        return
    earliest_date = EM.dateCopy((events[0])["date"])
    for event in events:
        if (EM.dateCompare(earliest_date, event["date"]) > 0):
            earliest_date = event["date"]
    events_lists = EM.createEventManager(earliest_date)
    for event in events:
        EM.emAddEventByDate(events_lists, event["name"], event["date"], event["id"])
    EM.emPrintAllEvents(events_lists, file_path)
    EM.dateDestroy(earliest_date)
    return events_lists  
    
    
def testPrintEventsList(file_path :str):
    events_lists=[{"name":"New Year's Eve","id":1,"date": EM.dateCreate(30, 12, 2020)},\
                    {"name" : "annual Rock & Metal party","id":2,"date":  EM.dateCreate(21, 4, 2021)}, \
                                 {"name" : "Improv","id":3,"date": EM.dateCreate(13, 3, 2021)}, \
                                     {"name" : "Student Festival","id":4,"date": EM.dateCreate(13, 5, 2021)},    ]
    em = printEventsList(events_lists,file_path)
    for event in events_lists:
        EM.dateDestroy(event["date"])
    EM.destroyEventManager(em)

#### Main #### 
# feel free to add more tests and change that section. 
# sys.argv - list of the arguments passed to the python script
if __name__ == "__main__":
    import sys
    if len(sys.argv)>1:
        testPrintEventsList(sys.argv[1])
