cmake_minimum_required(VERSION 3.24)
project(PROI_23L_101_Apteka)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(external/Catch2)

add_executable(my_tests  tests/test.cpp src/client.cpp src/inventory.cpp  src/logger.cpp src/file_manager.cpp src/simulation.cpp src/medicine.cpp src/counter.cpp src/windows.cpp  src/clients_queue.cpp  src/transaction.cpp)
target_link_libraries(my_tests PRIVATE Catch2::Catch2WithMain)
add_executable(PROI_23L_101_Apteka main.cpp src/client.cpp src/inventory.cpp  src/logger.cpp src/file_manager.cpp src/simulation.cpp src/medicine.cpp  src/counter.cpp  src/windows.cpp  src/clients_queue.cpp  src/transaction.cpp)
