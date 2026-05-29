#pragma once
#include <chrono>
#include <random>
#include <iostream>

inline std::mt19937 gen(std::random_device{}());

inline int random_nbr(int min, int max) {
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

inline bool timer(float sec, auto& last) {
    auto curTime = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration<float>(curTime - last).count();
    return elapsed >= sec;
}

inline void time_converter(int sec) {
    int h = sec / 3600;
    sec = sec % 3600;
    int min = sec / 60;
    sec = sec % 60;

    if (h == 0) {
        std::cout << min << "m:" << sec << "s";
    } else {
        std::cout << h << "h:" << min << "m:" << sec << "s";
    }
}

inline int input_check(int max) {
    int input;

    do {
        std::cout << "to chouse type the convinient int : ";
        std::cin >> input;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');

            std::cout << "invalid input!\n";
            input = -1;
        }
    } while (input <= 0 || input > max);

    return input;
}