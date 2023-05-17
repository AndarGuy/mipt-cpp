#include <iostream>
#include <sstream>
#include <filesystem>
#include <stack>

#include "modules/bmp/headers/headers.hpp"
#include "modules/bmp/bmp.hpp"
#include "modules/filters/filters.hpp"
#include "modules/localization/localization.hpp"

#define EXAMPLE_PATH "/home/andarguy/courserepo2/Projects/Imaginator/examples/"

class InvalidArgument : public std::exception {
 public:
  const char* what() const throw() {
    return LOCALIZATION::MESSAGE_EXCEPTION_INVALID_ARGUMENT.data();
  }
};

std::vector<std::function<void(Bitmap&)>> parse_filters(std::vector<std::string> arguments) {
  std::vector<std::function<void(Bitmap&)>> filters;
  for (size_t argument = 0; argument < arguments.size(); argument++) {
    if (arguments[argument] == LOCALIZATION::ARGUMENT_NEGATIVE)
      filters.push_back(FILTER_NEGATIVE);
    else if (arguments[argument] == LOCALIZATION::ARGUMENT_REPLACE_COLOR) {
      const int N = 6;
      uint32_t values[N];
      if (argument + N > arguments.size() - 1)
        throw InvalidArgument();
      for (size_t i = 0; i < 6; i++) std::istringstream(arguments[++argument]) >> values[i];
      filters.push_back(
          FILTER_REPLACE_COLOR(PIXEL(values[0], values[1], values[2]), PIXEL(values[3], values[4], values[5])));
    } else if (arguments[argument] == LOCALIZATION::ARGUMENT_SEPIA)
      filters.push_back(FILTER_SEPIA);
    else if (arguments[argument] == LOCALIZATION::ARGUMENT_EDGE_SELECTION)
      filters.push_back(FILTER_EDGE_SELECTION);
    else if (arguments[argument] == LOCALIZATION::ARGUMENT_IMPROVE_QUALITY)
      filters.push_back(FILTER_IMPROVE_QUALITY);
    else if (arguments[argument] == LOCALIZATION::ARGUMENT_NOISE_REMOVE)
      filters.push_back(FILTER_NOISE_REMOVAL(3, 3));
    else if (arguments[argument] == LOCALIZATION::ARGUMENT_GAUSSIAN_BLUR)
      filters.push_back(FILTER_GAUSSIAN_BLUR(5, 5, 1.0));
    else if (arguments[argument] == LOCALIZATION::ARGUMENT_CUT) {
      const int N = 4;
      uint32_t values[N];
      if (argument + N > arguments.size() - 1)
        throw InvalidArgument();
      for (size_t i = 0; i < N; i++) std::istringstream(arguments[++argument]) >> values[i];
      filters.push_back(FILTER_CUT(values[0], values[1], values[2], values[3]));
    } else if (arguments[argument] == LOCALIZATION::ARGUMENT_GRAYSCALE)
      filters.push_back(FILTER_GRAYSCALE);
  }
  return filters;
}

void console(int argv, char* args[]) {
  // COMMAND MODE
  // COMMAND MODE
  // COMMAND MODE
  std::vector<std::string> arguments;
  for (int argument = 1; argument < argv; argument++) arguments.push_back(args[argument]);
  if (std::find(arguments.begin(), arguments.end(), LOCALIZATION::ARGUMENT_HELP) != arguments.end())
    std::cout << LOCALIZATION::MESSAGE_HELP;
  else {
    std::vector<std::function<void(Bitmap&)>> filters = parse_filters(arguments);
    if (filters.size()) {
      std::string path(arguments[arguments.size() - 2]), save(arguments[arguments.size() - 1]);
      Bitmap bitmap(path);
      for (auto filter : filters) bitmap.apply(filter);
      bitmap.save(save);
    }
  }
}

void editor() {
  // EDITOR MODE
  // EDITOR MODE
  // EDITOR MODE

  std::stack<Bitmap> undo_stack, redo_stack;

  auto undo = [&undo_stack, &redo_stack]() {
    redo_stack.push(undo_stack.top());
    undo_stack.pop();
    return redo_stack.top();
  };

  auto redo = [&undo_stack, &redo_stack]() {
    undo_stack.push(redo_stack.top());
    redo_stack.pop();
    return undo_stack.top();
  };

  Bitmap bitmap;
  int is_bitmap_present = false;
  std::string bitmap_path;

  std::string buffer;
  while (!std::cin.eof()) {
    std::cout << "$ " << std::flush;
    std::vector<std::string> arguments;
    getline(std::cin, buffer);
    std::istringstream input(buffer);

    while (!input.eof()) {
      arguments.resize(arguments.size() + 1);
      input >> arguments[arguments.size() - 1];
    }

    if (arguments[0] == "cd") {
      if (arguments.size() == 2)
        std::filesystem::current_path(arguments[1]);
      else if (arguments.size() == 1)
        std::filesystem::current_path("/");
    } else if (arguments[0] == "ls") {
      for (const auto& entry : std::filesystem::directory_iterator(std::filesystem::current_path()))
        std::cout << entry.path() << std::endl;
    } else if (arguments[0] == "redo") {
      if (redo_stack.size())
        bitmap = redo();
      else
        std::cout << LOCALIZATION::MESSAGE_EXCEPTION_NOTHING_TO_REDO << std::endl;
    } else if (arguments[0] == "undo") {
      if (undo_stack.size())
        bitmap = undo();
      else
        std::cout << LOCALIZATION::MESSAGE_EXCEPTION_NOTHING_TO_UNDO << std::endl;
    } else if (arguments[0] == "open") {
      if (arguments.size() == 2) {
        try {
          bitmap = Bitmap(arguments[1]);
          bitmap_path = arguments[1];
          is_bitmap_present = true;
        } catch (...) {
          std::cout << LOCALIZATION::MESSAGE_EXCEPTION_CANNOT_OPEN_BITMAP << std::endl;
        }
      }
    } else if (arguments[0] == "save") {
      if (!is_bitmap_present)
        continue;
      if (arguments.size() == 2) {
        try {
          bitmap.save(arguments[1]);
        } catch (...) {
          std::cout << LOCALIZATION::MESSAGE_EXCEPTION_CANNOT_SAVE_BITMAP << std::endl;
        }
      } else if (arguments.size() == 1) {
        try {
          bitmap.save(bitmap_path);
        } catch (...) {
          std::cout << LOCALIZATION::MESSAGE_EXCEPTION_CANNOT_SAVE_BITMAP << std::endl;
        }
      }
    } else if (arguments[0] == "exit")
      break;
    else if (arguments[0] == "help")
      std::cout << LOCALIZATION::MESSAGE_HELP_INTERACTIVE;
    else if (arguments[0] == "apply") {
      if (!is_bitmap_present)
        continue;
      undo_stack.push(bitmap);
      std::vector<std::function<void(Bitmap&)>> filters = parse_filters(arguments);
      for (auto filter : filters) bitmap.apply(filter);
    }
  }
}

int main(int argv, char* args[]) {
  if (argv == 1)
    editor();
  else
    console(argv, args);

  return 0;
}