#include <iostream>
#include <iomanip>
#include <string> 

using namespace std;

enum Specialization { // Оголошення перерахування для спеціалізацій студентів
    COMPUTER_SCIENCE,  // Комп'ютерні науки
    INFORMATICS,       // Інформатика
    MATH_ECONOMICS,    // Математика та економіка
    PHYSICS_INFORMATICS, // Фізика та інформатика
    LABOR_EDUCATION    // Трудове навчання
};

struct Student {             // Оголошуємо структуру Student для зберігання даних про студента
    string surname;          // Прізвище студента
    int course;              // Номер курсу студента
    Specialization specialization; // Спеціалізація студента
    int physicsGrade;        // Оцінка з фізики
    int mathGrade;           // Оцінка з математики
    union {                 
        int programmingGrade;    // Оцінка з програмування (для Computer Science)
        int numericMethodsGrade; // Оцінка з чисельних методів (для Informatics)
        int pedagogyGrade;       // Оцінка з педагогіки (для інших спеціалізацій)
    };
};

// Оголошення прототипів функцій
void inputStudents(Student students[], int numStudents);          // Функція для введення даних студентів
void displayStudentsTable(Student students[], int numStudents);   // Функція для відображення таблиці студентів
void sortStudents(Student students[], int numStudents);           // Функція для сортування студентів
void createIndexArray(int indexArray[], int numStudents);         // Прототип функції для створення масиву індексів
int binarySearch(Student students[], int indexArray[], int numStudents, string surname, int course, Specialization specialization); // Прототип функції для бінарного пошуку
void showMenu(Student students[], int& numStudents);              // Функція для відображення меню
int getValidIntInput(string prompt, int min, int max);            // Функція для перевірки та отримання коректного вводу цілого числа

int main() {                             
    int numStudents;                      // Змінна для зберігання кількості студентів
    cout << "Enter the number of students: "; // Виводимо запит на введення кількості студентів
    numStudents = getValidIntInput("", 1, 100); // Зчитуємо та перевіряємо введення кількості студентів

    Student students[100];               // Масив для зберігання даних про 100 студентів
    showMenu(students, numStudents);     // Викликаємо меню для керування програмою
    return 0;                            // Завершення програми
}

void inputStudents(Student students[], int numStudents) { // Функція для введення даних студентів
    for (int i = 0; i < numStudents; i++) {               // Цикл для кожного студента
        cout << "\nEntering data for student #" << (i + 1) << ":\n"; // Виводимо повідомлення про номер студента

        cout << "Surname: ";                              // Запитуємо прізвище студента
        cin >> students[i].surname;                      // Зчитуємо прізвище

        students[i].course = getValidIntInput("Course (1-5): ", 1, 5); // Запитуємо та перевіряємо номер курсу

        cout << "Specialization (0 - Comp. Sci., 1 - Informatics, 2 - Math & Econ, 3 - Physics & Info, 4 - Labor Ed.): ";
        int spec;                                         // Змінна для вибору спеціалізації
        spec = getValidIntInput("", 0, 4);               // Зчитуємо та перевіряємо спеціалізацію

        // Присвоюємо спеціалізацію залежно від введеного значення
        if (spec == 0) students[i].specialization = COMPUTER_SCIENCE;
        else if (spec == 1) students[i].specialization = INFORMATICS;
        else if (spec == 2) students[i].specialization = MATH_ECONOMICS;
        else if (spec == 3) students[i].specialization = PHYSICS_INFORMATICS;
        else students[i].specialization = LABOR_EDUCATION;

        students[i].physicsGrade = getValidIntInput("Physics grade (0-5): ", 0, 5); // Запитуємо оцінку з фізики
        students[i].mathGrade = getValidIntInput("Math grade (0-5): ", 0, 5);       // Запитуємо оцінку з математики

        // Вводимо додаткову оцінку залежно від спеціалізації
        if (students[i].specialization == COMPUTER_SCIENCE) {
            students[i].programmingGrade = getValidIntInput("Programming grade (0-5): ", 0, 5);
        }
        else if (students[i].specialization == INFORMATICS) {
            students[i].numericMethodsGrade = getValidIntInput("Numeric Methods grade (0-5): ", 0, 5);
        }
        else {
            students[i].pedagogyGrade = getValidIntInput("Pedagogy grade (0-5): ", 0, 5);
        }
    }
}

void displayStudentsTable(Student students[], int numStudents) { // Функція для виведення таблиці студентів
    // Виводимо заголовок таблиці
    cout << "\n" << setw(5) << "No" << setw(15) << "Surname" << setw(8) << "Course"
        << setw(15) << "Specialization" << setw(10) << "Physics" << setw(10) << "Math"
        << setw(15) << "Subject\n";
    cout << string(80, '-') << endl; // Рядок розділювача

    for (int i = 0; i < numStudents; i++) { // Цикл по всіх студентах
        cout << setw(5) << (i + 1) // Номер студента
            << setw(15) << students[i].surname // Прізвище
            << setw(8) << students[i].course; // Курс

        // Відображення спеціалізації
        if (students[i].specialization == COMPUTER_SCIENCE) cout << setw(15) << "Comp. Sci.";
        else if (students[i].specialization == INFORMATICS) cout << setw(15) << "Informatics";
        else if (students[i].specialization == MATH_ECONOMICS) cout << setw(15) << "Math & Econ";
        else if (students[i].specialization == PHYSICS_INFORMATICS) cout << setw(15) << "Physics & Info";
        else cout << setw(15) << "Labor Ed.";

        cout << setw(10) << students[i].physicsGrade // Виводимо оцінку з фізики
            << setw(10) << students[i].mathGrade;   // Виводимо оцінку з математики

        // Виводимо третю оцінку залежно від спеціалізації
        if (students[i].specialization == COMPUTER_SCIENCE) {
            cout << setw(15) << students[i].programmingGrade;
        }
        else if (students[i].specialization == INFORMATICS) {
            cout << setw(15) << students[i].numericMethodsGrade;
        }
        else {
            cout << setw(15) << students[i].pedagogyGrade;
        }
        cout << endl; // Перехід на новий рядок
    }
}
void sortStudents(Student students[], int numStudents) { // Функція для сортування студентів
    for (int i = 0; i < numStudents - 1; i++) {          // Зовнішній цикл: перебираємо всіх студентів, крім останнього
        for (int j = i + 1; j < numStudents; j++) {      // Внутрішній цикл: порівнюємо поточного студента з наступними
            // Умови сортування: курс, потім спеціалізація, потім прізвище (в алфавітному порядку)
            if (students[i].course > students[j].course ||
                (students[i].course == students[j].course && students[i].specialization > students[j].specialization) ||
                (students[i].course == students[j].course && students[i].specialization == students[j].specialization && students[i].surname > students[j].surname)) {
                swap(students[i], students[j]); // Якщо умова виконана, міняємо місцями студентів
            }
        }
    }
}

void showMenu(Student students[], int& numStudents) { // Функція для відображення меню програми
    int choice; // Змінна для збереження вибору користувача
    do { // Починаємо цикл меню
        // Виводимо опції меню
        cout << "\nMenu:\n";
        cout << "1. Input student data\n";     // Опція для введення даних студентів
        cout << "2. Display students table\n"; // Опція для виводу таблиці студентів
        cout << "3. Sort students\n";         // Опція для сортування студентів
        cout << "0. Exit\n";                  // Опція для виходу з програми
        cout << "Choose an option: ";         // Запит вибору
        choice = getValidIntInput("", 0, 3);  // Отримуємо вибір користувача і перевіряємо, чи він у діапазоні

        switch (choice) { // Обробляємо вибір
        case 1:
            inputStudents(students, numStudents); // Викликаємо функцію введення даних
            break;
        case 2:
            displayStudentsTable(students, numStudents); // Викликаємо функцію відображення таблиці
            break;
        case 3:
            sortStudents(students, numStudents); // Викликаємо функцію сортування
            cout << "Students sorted.\n"; // Повідомлення про успішне сортування
            break;
        case 0:
            cout << "Exiting program...\n"; // Повідомлення про вихід
            break;
        default:
            cout << "Invalid option. Please try again.\n"; // Повідомлення про помилковий вибір
        }
    } while (choice != 0); // Цикл працює, поки користувач не вибере опцію "0"
}

int getValidIntInput(string prompt, int min, int max) { // Функція для отримання і перевірки цілого числа
    int input; // Змінна для збереження введення
    while (true) { // Починаємо безкінечний цикл для валідації вводу
        if (!prompt.empty()) cout << prompt; // Якщо є повідомлення, виводимо його
        cin >> input; // Зчитуємо введене число

        // Перевіряємо, чи введення коректне
        if (cin.fail() || input < min || input > max) {
            cin.clear();               // Очищаємо стан потоку (помилки)
            cin.ignore(10000, '\n');   // Пропускаємо некоректне введення
            cout << "Invalid input. Please enter a number between " << min << " and " << max << ".\n"; // Виводимо помилку
        }
        else {
            cin.ignore(10000, '\n');   // Пропускаємо залишки після введення
            return input;              // Якщо введення коректне, повертаємо його
        }
    }
}
void createIndexArray(int indexArray[], int numStudents) { // Функція для створення масиву індексів
    for (int i = 0; i < numStudents; i++) { // Перебираємо кожного студента
        indexArray[i] = i; // Заповнюємо масив індексами (0, 1, 2, ..., numStudents - 1)
    }
}
int binarySearch(Student students[], int indexArray[], int numStudents, string surname, int course, Specialization specialization) {
    int left = 0;                      // Ліва границя пошуку
    int right = numStudents - 1;       // Права границя пошуку

    while (left <= right) {            // Виконуємо, поки межі не перетнуться
        int mid = (left + right) / 2;  // Обчислюємо середній індекс
        int midIndex = indexArray[mid]; // Отримуємо індекс студента з масиву індексів

        // Порівнюємо середнього студента з критеріями пошуку
        if (students[midIndex].course == course &&
            students[midIndex].specialization == specialization &&
            students[midIndex].surname == surname) {
            return midIndex; // Якщо знайдено, повертаємо індекс студента
        }

        // Змінюємо межі пошуку залежно від результату порівняння
        if (students[midIndex].course < course ||
            (students[midIndex].course == course && students[midIndex].specialization < specialization) ||
            (students[midIndex].course == course && students[midIndex].specialization == specialization && students[midIndex].surname < surname)) {
            left = mid + 1; // Зсуваємо ліву межу вправо
        }
        else {
            right = mid - 1; // Зсуваємо праву межу вліво
        }
    }
    return -1; // Якщо студент не знайдений, повертаємо -1
}
