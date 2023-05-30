#ifndef PROI_23L_101_APTEKA_LOGGER_H
#define PROI_23L_101_APTEKA_LOGGER_H
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>

class Logger {
private:
    inline static const char time_wait = 2;
    std::string pathToOutput;
    std::ofstream outputFile;
    int turn = 0;
    using endl_type = std::ostream&(std::ostream&);
public:
    Logger(std::string& pathToOutput);
    template<typename T>
    Logger& operator<<(const T& value){
        std::string turnStr = "["+std::to_string(turn)+"] ";
        outputFile<<turnStr<<value;
        std::cout<<turnStr<<value;
#ifndef TESTING_ENV
        std::this_thread::sleep_for(std::chrono::seconds(time_wait));
#endif // !TESTING_ENV
        return *this;

    }
    Logger& operator<<(endl_type endl)
    {
        outputFile<<std::endl;
        std::cout<<std::endl;
        return *this;
    }

    Logger& operator++(){
        turn++;
        return *this;
    }

};

#endif //PROI_23L_101_APTEKA_LOGGER_H
