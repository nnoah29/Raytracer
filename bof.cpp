/*
**  _                                              _      ___    ___  
** | |                                            | |    |__ \  / _ \
** | |_Created _       _ __   _ __    ___    __ _ | |__     ) || (_) |
** | '_ \ | | | |     | '_ \ | '_ \  / _ \  / _` || '_ \   / /  \__, |
** | |_) || |_| |     | | | || | | || (_) || (_| || | | | / /_    / / 
** |_.__/  \__, |     |_| |_||_| |_| \___/  \__,_||_| |_||____|  /_/ 
**          __/ |     on 21/05/25.                                          
**         |___/ 
*/

#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

void work(int id) {
    auto start = std::chrono::steady_clock::now();
    std::cout << "Thread " << id << " started\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    auto end = std::chrono::steady_clock::now();
    std::cout << "Thread " << id << " ended after "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";
}

int main() {
    const int NB_THREADS = 4;
    std::vector<std::thread> threads;

    auto global_start = std::chrono::steady_clock::now();
    for (int i = 0; i < NB_THREADS; ++i)
        threads.emplace_back(work, i);

    for (auto& t : threads)
        t.join();
    auto global_end = std::chrono::steady_clock::now();

    std::cout << "Total time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(global_end - global_start).count()
              << " ms\n";

    return 0;
}