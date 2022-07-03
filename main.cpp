#include <iostream>
#include <filesystem>
#include "libachie/Profile.h"


void hello_msg();
void in_profile_work(Profile& profile);
void in_profile_msg();

int main() {
    using std::filesystem::directory_iterator;
    setlocale(LC_ALL, "Russian");
    std::vector<Profile> profiles;
    for (const auto &file : directory_iterator("profiles")) {
        //std::cout << file.path().c_str();
        profiles.emplace_back(load_profile(file.path().c_str()));
    }
    while (true) {
        int cmd = -1;
        hello_msg();
        std::cin >> cmd;
        switch (cmd) {
            case 1: {
                std::string name;
                std::cin >> name;
                profiles.emplace_back(name);
                in_profile_work(profiles[profiles.size() - 1]);
                break;
            }
            case 2: {
                int index = 0;
                int i = 0;
                if (profiles.size() == 0) {
                    std::cout << "Нет доступных профилей!\n";
                } else {
                    for (auto &profile: profiles) {
                        std::cout << i++ << " : " << profile.get_name() << "\n";
                    }
                    std::cout << "Выберите нужный индекс: ";
                    std::cin >> index;
                    in_profile_work(profiles[index]);
                }
                break;
            }
            case 3:
            {
                return 0;
            }
        }
    }
    return 0;
}

void hello_msg() {
    system("clear");
    std::cout << "Привет!\n";
    std::cout << "Выберите действие:\n";
    std::cout << "Чтобы создать профиль, выберите 1\n";
    std::cout << "Чтобы войти в профиль, выберите 2\n";
    std::cout << "Чтобы выйти из программы, выберите 3\n";
}

void in_profile_msg() {
    std::cout << "Привет!\n";
    std::cout << "Чтобы добавить достижение, выберите 1\n";
    std::cout << "Чтобы отобразить достижения, выберите 2\n";
    std::cout << "Чтобы экспортировать достижения из CSV-файла, выберите 3\n";
    std::cout << "Чтобы выйти из профиля, выберите 4\n";
}

void in_profile_work(Profile &profile) {
    while (true) {
        in_profile_msg();
        int cmd;
        std::cin >> cmd;
        switch (cmd) {
            case 1: {
                cmd = -1;
                std::string date;
                std::string object;
                std::string type;
                int value;
                std::cout << "Дата: ";
                std::cin >> date;
                std::cout << "\nПредмет: ";
                std::cin >> object;
                std::cout << "\nТип: ";
                std::cin >> type;
                std::cout << "\nДостижение: ";
                std::cin >> value;
                std::cout << "\n";
                profile.add_achie(date, object, type, value);
                break;
            }
            case 2: {
                cmd = -1;
                for (auto achie: profile.get_achies()) {
                    std::cout << achie.get_date() << "\t" << achie.get_object() << "\t" << achie.get_type() << "\t"
                              << achie.get_value() << "\n";
                }
                std::cin.get();
                break;
            }
            case 3: {
                cmd = -1;
                std::cout << "Введите путь до CSV-файла: ";
                std::string csv_path;
                std::cin >> csv_path;
                profile.load_csv(csv_path);
                break;
            }
            case 4:
            {
                return;
            }
        }
    }
}