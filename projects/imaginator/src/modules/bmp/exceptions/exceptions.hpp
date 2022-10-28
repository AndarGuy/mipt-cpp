class BitmapCorruptedException : public std::exception {
   public:
    char* what() { return "Bitmap is corrupted!"; }
};

class NotBitmapException : public std::exception {
   public:
    char* what() { return "Provided bitmap doesn't have the right header!"; }
};

class BitmapNotFoundException : public std::exception {
   public:
    char* what() { return "Provided bitmap doesn't exist!"; }
};