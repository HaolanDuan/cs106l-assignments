/*
 * CS106L Assignment 2: Marriage Pact
 * Created by Haven Whitney with modifications by Fabio Ibanez & Jacob Roberts-Baca.
 *
 * Welcome to Assignment 2 of CS106L! Please complete each STUDENT TODO
 * in this file. You do not need to modify any other files.
 *
 */

#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>
#include <cctype>
#include <vector>

std::string kYourName = "Haolan Duan"; // Don't forget to change this!

/**
 * Takes in a file name and returns a set containing all of the applicant names as a set.
 *
 * @param filename  The name of the file to read.
 *                  Each line of the file will be a single applicant's name.
 * @returns         A set of all applicant names read from the file.
 *
 * @remark Feel free to change the return type of this function (and the function
 * below it) to use a `std::unordered_set` instead. If you do so, make sure
 * to also change the corresponding functions in `utils.h`.
 */
std::set<std::string> get_applicants(std::string filename) {
  std::set<std::string> applicants;
  std::ifstream input(filename);
  if (!input) {
    std::cerr << "Error: could not open file" << std::endl;
    return applicants;
  }
  std::string line;
  while (std::getline(input, line)) {
    if (!line.empty() && line.back() == '\r') {
      line.pop_back();
    }
    if (!line.empty()) {
      applicants.insert(line);
    }
  }
  return applicants;
}

/**
 * Takes in a set of student names by reference and returns a queue of names
 * that match the given student name.
 *
 * @param name      The returned queue of names should have the same initials as this name.
 * @param students  The set of student names.
 * @return          A queue containing pointers to each matching name.
 */
std::queue<const std::string*> find_matches(std::string name, std::set<std::string>& students) {
  // Helper to compute the initials (first character of first and last token)
  auto get_initials = [] (const std::string& s) -> std::pair<char, char> {
    size_t i = 0;
    while (i < s.size() && std::isspace(static_cast<unsigned char>(s[i]))) ++i;
    if (i == s.size()) return {'\0', '\0'};
    char first = std::toupper(static_cast<unsigned char>(s[i]));

    size_t end = s.find_last_not_of(' ');
    if (end == std::string::npos) return {first, '\0'};
    size_t last_space = s.find_last_of(' ', end);
    size_t start_last = (last_space == std::string::npos) ? 0 : last_space + 1;
    if (start_last >= s.size()) return {first, '\0'};
    char last = std::toupper(static_cast<unsigned char>(s[start_last]));
    return {first, last};
  };

  std::queue<const std::string*> matches;
  auto target = get_initials(name);

  for (const auto& student : students) {
    if (student == name) continue; // don't match with yourself
    if (get_initials(student) == target) {
      matches.push(&student);
    }
  }

  return matches;
}

/**
 * Takes in a queue of pointers to possible matches and determines the one true match!
 *
 * You can implement this function however you'd like, but try to do something a bit
 * more complicated than a simple `pop()`.
 *
 * @param matches The queue of possible matches.
 * @return        Your magical one true love.
 *                Will return "NO MATCHES FOUND." if `matches` is empty.
 */
std::string get_match(std::queue<const std::string*>& matches) {
  // If no possible matches, return the required message.
  if (matches.empty()) {
    return "NO MATCHES FOUND.";
  }

  // Move queue contents into a vector to allow indexed selection.
  std::vector<const std::string*> vec;
  vec.reserve(matches.size());
  while (!matches.empty()) {
    vec.push_back(matches.front());
    matches.pop();
  }

  // Choose the middle element as a simple deterministic selection strategy.
  size_t idx = vec.size() / 2;
  if (idx >= vec.size()) idx = 0;

  return *vec[idx];
}

/* #### Please don't remove this line! #### */
#include "autograder/utils.hpp"
