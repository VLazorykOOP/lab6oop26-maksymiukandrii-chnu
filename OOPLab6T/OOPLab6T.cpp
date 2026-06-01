#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ЗАВДАННЯ 1.10. Віртуальне та не віртуальне успадкування [cite: 241, 8, 28]

// --- Не віртуальне успадкування ---
class N1 { protected: int n1; public: N1() : n1(1) {} };
class N2 { protected: int n2; public: N2() : n2(2) {} };

                    // N3 успадковує N1
                    class N3 : public N1 { protected: int n3; public: N3() : n3(3) {} };

                    // N4 успадковує N1 та N2 (Множинне успадкування)
                    class N4 : public N1, public N2 { protected: int n4; public: N4() : n4(4) {} };

                    // N5 успадковує N3 та N4 (Ромбоподібне успадкування, дублювання N1)
                    class N5 : public N3, public N4 { protected: int n5; public: N5() : n5(5) {} };

                    // --- Віртуальне успадкування ---
class V1 { protected: int v1; public: V1() : v1(1) {} };
class V2 { protected: int v2; public: V2() : v2(2) {} };

                    // Віртуальне успадкування для уникнення дублювання
                    class V3 : virtual public V1 { protected: int v3; public: V3() : v3(3) {} };
                    class V4 : virtual public V1, virtual public V2 { protected: int v4; public: V4() : v4(4) {} };

                    // V5 успадковує V3 та V4, але V1 буде лише в одному екземплярі
                    class V5 : public V3, public V4 { protected: int v5; public: V5() : v5(5) {} };

                    // Функція тестування Завдання 1
                    void testTask1() {
                        cout << "\n--- Task 1.10: Inheritance Sizes ---\n";
                        cout << "Non-virtual inheritance sizes:\n";
                        cout << "Size of N1: " << sizeof(N1) << " bytes\n";
                        cout << "Size of N2: " << sizeof(N2) << " bytes\n";
                        cout << "Size of N3: " << sizeof(N3) << " bytes\n";
                        cout << "Size of N4: " << sizeof(N4) << " bytes\n";
                        cout << "Size of N5 (duplicate N1): " << sizeof(N5) << " bytes\n";

                        cout << "\nVirtual inheritance sizes:\n";
                        cout << "Size of V1: " << sizeof(V1) << " bytes\n";
                        cout << "Size of V2: " << sizeof(V2) << " bytes\n";
                        cout << "Size of V3: " << sizeof(V3) << " bytes\n";
                        cout << "Size of V4: " << sizeof(V4) << " bytes\n";
                        cout << "Size of V5 (single V1 due to virtual): " << sizeof(V5) << " bytes\n";
                    }

                    // ЗАВДАННЯ 2.10. Абстрактні класи та віртуальні функції [cite: 287, 288]

                    // Абстрактний базовий клас "Дані"
                    class Data {
                    public:
                        virtual void display() const = 0; // Чисто віртуальна функція відображення
                        virtual void save() const = 0;    // Чисто віртуальна функція збереження
                        virtual void process() = 0;       // Чисто віртуальна функція обробки
                        virtual ~Data() { cout << " [Data destructor called]\n"; }
                    };

                    // Похідний клас: Дані типу сигнал
                    class SignalData : public Data {
                    private:
                        double frequency;
                    public:
                        SignalData(double f = 0.0) : frequency(f) {}

                        // Введення даних з клавіатури
                        void input() {
                            cout << "Enter signal frequency (Hz): ";
                            cin >> frequency;
                        }

                        void display() const override {
                            cout << "Signal Data [Frequency: " << frequency << " Hz]\n";
                        }
                        void save() const override {
                            cout << "Saving Signal Data to file...\n";
                        }
                        void process() override {
                            cout << "Processing Signal Data (Filtering noise)...\n";
                            frequency *= 1.1; // Зміна як результат "обробки"
                        }
                        ~SignalData() { cout << " [SignalData destructor called]\n"; }
                    };

                    // Похідний клас: Результат обробки
                    class ProcessingResultData : public Data {
                    private:
                        string resultStatus;
                    public:
                        ProcessingResultData(string status = "") : resultStatus(status) {}

                        void input() {
                            cout << "Enter processing result status (e.g., Success, Failed): ";
                            cin.ignore();
                            getline(cin, resultStatus);
                        }

                        void display() const override {
                            cout << "Processing Result [Status: " << resultStatus << "]\n";
                        }
                        void save() const override {
                            cout << "Saving Processing Result to database...\n";
                        }
                        void process() override {
                            cout << "Verifying Processing Result...\n";
                        }
                        ~ProcessingResultData() { cout << " [ProcessingResultData destructor called]\n"; }
                    };

                    // Похідний клас: Допоміжні дані
                    class AuxiliaryData : public Data {
                    private:
                        int configCode;
                    public:
                        AuxiliaryData(int code = 0) : configCode(code) {}

                        void input() {
                            cout << "Enter configuration code (integer): ";
                            cin >> configCode;
                        }

                        void display() const override {
                            cout << "Auxiliary Data [Config Code: " << configCode << "]\n";
                        }
                        void save() const override {
                            cout << "Saving Auxiliary Data to temp buffer...\n";
                        }
                        void process() override {
                            cout << "Loading Auxiliary Data into system memory...\n";
                        }
                        ~AuxiliaryData() { cout << " [AuxiliaryData destructor called]\n"; }
                    };

                    // Функція тестування Завдання 2
                    void testTask2() {
                        cout << "\n--- Task 2.10: Abstract Data Classes ---\n";

                        SignalData sig;
                        sig.input();

                        ProcessingResultData res;
                        res.input();

                        AuxiliaryData aux;
                        aux.input();

                        // Масив вказівників на абстрактний клас
                        vector<Data*> dataCollection;
                        dataCollection.push_back(&sig);
                        dataCollection.push_back(&res);
                        dataCollection.push_back(&aux);

                        cout << "\n--- Processing Data Collection ---\n";
                        for (Data* item : dataCollection) {
                            item->display();
                            item->process();
                            item->display(); // Щоб побачити зміни після обробки
                            item->save();
                            cout << "-----------------------\n";
                        }
                    }

                    // ЗАВДАННЯ 3.10. Ієрархія типів та віртуальні базові класи [cite: 354, 355]

                    // Базовий клас: Програмне забезпечення
                    class Software {
                    protected:
                        string name;
                    public:
                        Software(string n = "Unknown") : name(n) {
                            cout << " + Software constructed: " << name << "\n";
                        }
                        virtual ~Software() {
                            cout << " - Software destructed: " << name << "\n";
                        }

                        // Перевантаження операторів введення/виведення
                        friend istream& operator>>(istream& is, Software& s) {
                            cout << "Enter software name: ";
                            is >> ws; // Очищення пробілів
                            getline(is, s.name);
                            return is;
                        }
                        friend ostream& operator<<(ostream& os, const Software& s) {
                            os << "Software Name: " << s.name;
                            return os;
                        }
                    };

                    // Віртуальний похідний клас: Операційна система
                    class OperatingSystem : virtual public Software {
                    protected:
                        double kernelVersion;
                    public:
                        OperatingSystem(string n = "Unknown OS", double kernel = 1.0) : Software(n), kernelVersion(kernel) {
                            cout << " + OperatingSystem constructed\n";
                        }
                        virtual ~OperatingSystem() {
                            cout << " - OperatingSystem destructed\n";
                        }

                        friend istream& operator>>(istream& is, OperatingSystem& os) {
                            // Явне викликання оператора базового класу
                            is >> static_cast<Software&>(os);
                            cout << "Enter kernel version (e.g., 5.15): ";
                            is >> os.kernelVersion;
                            return is;
                        }
                        friend ostream& operator<<(ostream& os, const OperatingSystem& osys) {
                            os << static_cast<const Software&>(osys) << " | Kernel: " << osys.kernelVersion;
                            return os;
                        }
                    };

                    // Віртуальний похідний клас: Прикладне програмне забезпечення
                    class ApplicationSoftware : virtual public Software {
                    protected:
                        string licenseType;
                    public:
                        ApplicationSoftware(string n = "Unknown App", string license = "Free") : Software(n), licenseType(license) {
                            cout << " + ApplicationSoftware constructed\n";
                        }
                        virtual ~ApplicationSoftware() {
                            cout << " - ApplicationSoftware destructed\n";
                        }

                        friend istream& operator>>(istream& is, ApplicationSoftware& app) {
                            is >> static_cast<Software&>(app);
                            cout << "Enter license type (e.g., GPL, Proprietary): ";
                            is >> ws;
                            getline(is, app.licenseType);
                            return is;
                        }
                        friend ostream& operator<<(ostream& os, const ApplicationSoftware& app) {
                            os << static_cast<const Software&>(app) << " | License: " << app.licenseType;
                            return os;
                        }
                    };

                    // Множинне успадкування: Windows (Є і ОС, і прикладною платформою у контексті задачі)
                    class Windows : public OperatingSystem, public ApplicationSoftware {
                    private:
                        bool isActivated;
                    public:
                        // Оскільки Software успадковується віртуально, конструктор Windows повинен ініціалізувати його напряму
                        Windows(string n = "Windows", double kernel = 10.0, string license = "Proprietary", bool active = false)
                            : Software(n), OperatingSystem(n, kernel), ApplicationSoftware(n, license), isActivated(active) {
                            cout << " + Windows constructed\n";
                        }
                        virtual ~Windows() {
                            cout << " - Windows destructed\n";
                        }

                        friend istream& operator>>(istream& is, Windows& win) {
                            cout << "--- Entering Windows Info ---\n";
                            // Вводимо ім'я для базового Software
                            cout << "Enter OS name: ";
                            is >> ws;
                            getline(is, win.name);

                            cout << "Enter kernel version: ";
                            is >> win.kernelVersion;

                            cout << "Enter license type: ";
                            is >> ws;
                            getline(is, win.licenseType);

                            cout << "Is it activated? (1 for Yes, 0 for No): ";
                            is >> win.isActivated;
                            return is;
                        }
                        friend ostream& operator<<(ostream& os, const Windows& win) {
                            os << "Windows System -> Name: " << win.name
                                << " | Kernel: " << win.kernelVersion
                                << " | License: " << win.licenseType
                                << " | Activated: " << (win.isActivated ? "Yes" : "No");
                            return os;
                        }
                    };

                    // Функція тестування Завдання 3
                    void testTask3() {
                        cout << "\n--- Task 3.10: Software Hierarchy ---\n";

                        Windows myWin;
                        cout << "\n[Input Data for Windows System]\n";
                        cin >> myWin;

                        cout << "\n[Output Data for Windows System]\n";
                        cout << myWin << "\n\n";

                        cout << "[Destructors will be called automatically now]\n";
                    }

                    // MAIN FUNCTION

                    int main() {
                        int choice;
                        do {
                            cout << "\n========================================\n";
                            cout << "           MAIN MENU (LAB 6)            \n";
                            cout << "========================================\n";
                            cout << "1. Task 1.10 (Inheritance sizes & Virtual base)\n";
                            cout << "2. Task 2.10 (Abstract Data classes)\n";
                            cout << "3. Task 3.10 (Software hierarchy & Streams)\n";
                            cout << "0. Exit\n";
                            cout << "----------------------------------------\n";
                            cout << "Enter your choice: ";

                            if (!(cin >> choice)) {
                                cin.clear(); // Очищення прапорця помилки
                                cin.ignore(10000, '\n'); // Відкидання некоректного вводу
                                choice = -1;
                            }

                            switch (choice) {
                            case 1:
                                testTask1();
                                break;
                            case 2:
                                testTask2();
                                break;
                            case 3:
                                testTask3();
                                break;
                            case 0:
                                cout << "Exiting program. Goodbye!\n";
                                break;
                            default:
                                cout << "Invalid choice. Please try again.\n";
                            }
                        } while (choice != 0);

                        return 0;
                    }