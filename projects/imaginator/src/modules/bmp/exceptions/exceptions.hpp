#pragma once

class BitmapCorruptedException : public std::exception {
 public:
  const char* what() const throw() {
    return "Bitmap is corrupted!";
  }
};

class NotBitmapException : public std::exception {
 public:
  const char* what() const throw() {
    return "Provided bitmap doesn't have the right header!";
  }
};

class BitmapNotFoundException : public std::exception {
 public:
  const char* what() const throw() {
    return "Provided bitmap doesn't exist!";
  }
};

class BitmapFilterIllegalArgument : public std::exception {
 public:
  const char* what() const throw() {
    return "Argument you used is not valid.";
  }
};