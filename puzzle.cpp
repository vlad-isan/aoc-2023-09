//
// Created by Vlad Isan on 05/12/2023.
//

#include "puzzle.h"

int puzzle_sample_1(const std::string &base_file_path) {
    std::string file_path = fmt::format("{}/{}", base_file_path, "puzzle-input-sample-1.txt");

    std::ifstream file(file_path);

    if (!file.is_open()) {
        fmt::println("{}", file_path);
        fmt::println("Something happened while opening the file. EAT DEEZNUTS!!!");
        fmt::println("Error {}", strerror(errno));

        return 0;
    }

    return do_puzzle_1(file);
}

int puzzle_sample_2(const std::string &base_file_path) {
    std::string file_path = fmt::format("{}/{}", base_file_path, "puzzle-input-sample-2.txt");

    std::ifstream file(file_path);

    if (!file.is_open()) {
        fmt::println("{}", file_path);
        fmt::println("Something happened while opening the file. EAT DEEZNUTS!!!");
        fmt::println("Error {}", strerror(errno));

        return 0;
    }

    return do_puzzle_2(file);
}

int puzzle_1(const std::string &base_file_path) {
    std::string file_path = fmt::format("{}/{}", base_file_path, "puzzle-input-1.txt");

    std::ifstream file(file_path);

    if (!file.is_open()) {
        fmt::println("{}", file_path);
        fmt::println("Something happened while opening the file. EAT DEEZNUTS!!!");
        fmt::println("Error {}", strerror(errno));

        return 0;
    }

    return do_puzzle_1(file);
}

int puzzle_2(const std::string &base_file_path) {
    std::string file_path = fmt::format("{}/{}", base_file_path, "puzzle-input-2.txt");

    std::ifstream file(file_path);

    if (!file.is_open()) {
        fmt::println("{}", file_path);
        fmt::println("Something happened while opening the file. EAT DEEZNUTS!!!");
        fmt::println("Error {}", strerror(errno));

        return 0;
    }

    return do_puzzle_2(file);
}

int do_puzzle_1(std::ifstream &file) {
    std::string line;

    HistoryList history_list{};

    while (std::getline(file, line)) {
        History history{};
        Sequence sequence{};

        std::istringstream iss(line);
        int64_t value;

        while (iss >> value) {
            sequence.emplace_back(value);
        }

        history.emplace_back(sequence);
        history_list.emplace_back(history);
    }

    int64_t sum = 0;

    for(auto &history : history_list) {
        sum += get_next_value(history);
    }

    return sum;
}

int do_puzzle_2(std::ifstream &file) {
    std::string line;

    HistoryList history_list{};

    while (std::getline(file, line)) {
        History history{};
        Sequence sequence{};

        std::istringstream iss(line);
        int64_t value;

        while (iss >> value) {
            sequence.emplace_back(value);
        }

        history.emplace_back(sequence);
        history_list.emplace_back(history);
    }

    int64_t sum = 0;

    for(auto &history : history_list) {
        sum += get_previous_value(history);
    }

    return sum;
}

int64_t get_next_value(History &history) {
    Sequence &first_sequence = history.front();
    compute_til_zero(history, first_sequence);

    int64_t next_value = 0;

    // iterate history in reverse
    for (auto it = history.rbegin() + 1; it != history.rend(); ++it) {
        next_value += it->back();
    }

    return next_value;
}

int64_t get_previous_value(History &history) {
    Sequence &first_sequence = history.front();
    compute_til_zero(history, first_sequence);

    int64_t next_value = 0;

    // iterate history in reverse
    for (auto it = history.rbegin() + 1; it != history.rend(); ++it) {
        next_value = it->front() - next_value;
    }

    return next_value;
}

void compute_til_zero(History &history, Sequence &sequence) {
    bool all_zero = true;

    Sequence next_sequence{};

    for (size_t i = 1; i < sequence.size(); ++i) {
        int64_t diff = sequence[i] - sequence[i - 1];

        if (diff != 0) {
            all_zero = false;
        }

        next_sequence.emplace_back(diff);
    }

    history.emplace_back(next_sequence);

    if (!all_zero) {
        compute_til_zero(history, next_sequence);
    }
}