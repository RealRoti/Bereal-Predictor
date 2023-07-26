#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <ctime>
#include <windows.h>

struct EventTime {
    int year, month, day, hour, minute, second;
};

// Function to parse a date/time string in the format "YYYY-MM-DD HH:MM:SS" into an EventTime structure
EventTime parseTime(const std::string& timeStr) {
    EventTime timeInfo;
    sscanf(timeStr.c_str(), "%d-%d-%d %d:%d:%d", &timeInfo.year, &timeInfo.month, &timeInfo.day, &timeInfo.hour, &timeInfo.minute, &timeInfo.second);
    return timeInfo;
}

// Function to calculate the time difference in seconds between two times
long long calculateTimeDifference(const EventTime& time1, const EventTime& time2) {
    std::tm t1 = {0};
    t1.tm_year = time1.year - 1900;
    t1.tm_mon = time1.month - 1;
    t1.tm_mday = time1.day;
    t1.tm_hour = time1.hour;
    t1.tm_min = time1.minute;
    t1.tm_sec = time1.second;

    std::tm t2 = {0};
    t2.tm_year = time2.year - 1900;
    t2.tm_mon = time2.month - 1;
    t2.tm_mday = time2.day;
    t2.tm_hour = time2.hour;
    t2.tm_min = time2.minute;
    t2.tm_sec = time2.second;

    std::time_t time1_seconds = std::mktime(&t1);
    std::time_t time2_seconds = std::mktime(&t2);

    return static_cast<long long>(time2_seconds - time1_seconds);
}

int main() {
    // Read the event times from btime.txt and store them in a vector
    system("Color 06");
    std::cerr << "Welcome to BeReal algorithm predictor" << std::endl;
    std::cerr << "Developed by Roti(C)2023" << std::endl;
    std::cerr << std::endl;
    std::cerr << "This tool is open source. Visit github.com/realroti/bereal-predictor." << std::endl;
    std::cerr << std::endl;
    std::cerr << "Select your timezone:" << std::endl;
    std::cerr << "a) America" << std::endl;
    std::cerr << "b) Europe" << std::endl;
    std::cerr << "c) East Asia" << std::endl;
    std::cerr << "d) West Asia" << std::endl;

    char choose;
    std::cin >> choose;

    std::ifstream inputFile; // Declare the variable here

    if (choose == 'a' || choose == 'b' || choose == 'c' || choose == 'd') {
        if (choose == 'a')
            inputFile.open("data/america.txt");
        else if (choose == 'b')
            inputFile.open("data/europe.txt");
        else if (choose == 'c')
            inputFile.open("data/eastasia.txt");
        else if (choose == 'd')
            inputFile.open("data/westasia.txt");
    } else {
        std::cout << "Invalid input. Please choose 'a', 'b', 'c' or 'd'." << std::endl;
        return 1;
    }

    if (!inputFile.is_open()) {
        system("Color 04");
        std::cerr << std::endl;
        std::cerr << "Unable to open the file" << std::endl;
        return 1;
    }

    std::vector<EventTime> eventTimes;

    std::string line;
    while (std::getline(inputFile, line)) {
        EventTime timeInfo = parseTime(line);
        eventTimes.push_back(timeInfo);
    }
    inputFile.close();

    // Get the current time
    auto currentTime = std::chrono::system_clock::now();
    std::time_t currentTimeSeconds = std::chrono::system_clock::to_time_t(currentTime);
    std::tm* localTime = std::localtime(&currentTimeSeconds);
    EventTime currentEventTime;
    currentEventTime.year = localTime->tm_year + 1900;
    currentEventTime.month = localTime->tm_mon + 1;
    currentEventTime.day = localTime->tm_mday;
    currentEventTime.hour = localTime->tm_hour;
    currentEventTime.minute = localTime->tm_min;
    currentEventTime.second = localTime->tm_sec;

    // Filter valid event times (9:00 - 23:59) from past events
    std::vector<EventTime> validEventTimes;
    for (const EventTime& timeInfo : eventTimes) {
        if (timeInfo.hour >= 9 && timeInfo.hour <= 23) {
            validEventTimes.push_back(timeInfo);
        }
    }

    // Calculate the time difference in seconds between the last event and the current time

    std::cout << std::endl;
    if (!validEventTimes.empty()) {
        EventTime lastEventTime = validEventTimes.back();
        long long timeDifferenceSeconds = calculateTimeDifference(lastEventTime, currentEventTime);
        system("Color 06");
        // Print the result
        if (timeDifferenceSeconds > 0) {
            std::cout << "The next BeReal event may occur ";
            if (timeDifferenceSeconds < 3600) {
                std::cout << "in less than an hour.";
            } else if (timeDifferenceSeconds < 21600) {
                std::cout << "during the morning time frame.";
            } else if (timeDifferenceSeconds < 43200) {
                std::cout << "during the afternoon time frame.";
            } else {
                std::cout << "during the late afternoon time frame.";
            }
            std::cout << std::endl;

        } else {
            system("Color 04");
            std::cout << "There are no valid BeReal events today." << std::endl;
        }
    } else {
        system("Color 04");
        std::cout << "There are no valid BeReal events in the past days." << std::endl;
    }

    return 0;
}
