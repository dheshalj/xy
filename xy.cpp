#include <iostream>
#include <algorithm>
#include "ini/INIReader.h"

class args {
  public:
    int argc;
    char** argv;
    args(int argc, char ** argv) {
      this->argc = argc,
      this->argv = argv;
    }
    char* get(const std::string & option) {
      char** end = this->argv+this->argc;
      char** itr = std::find(this->argv, end, option);
      if (itr != end && ++itr != end) return *itr;
      return 0;
    }
    bool exists(const std::string& option) {
      char** end = this->argv+this->argc;
      return std::find(this->argv, end, option) != end;
    }
};

int main(int argc, char * argv[]) {
  INIReader xy("xy.ini");
  args args(argc, argv);
  
  if (xy.ParseError() < 0) {
    std::cout << "error: no 'xy.ini' file found" << std::endl;
    return 1;
  }

  if (args.exists("-h")) {
    std::cout << "Usage : xy [cmd] [options]\n\n"
    "Options:\n"
    "   --quiet, -q              : Quiet operation, do not output messages (default false)\n"
    "   --version, -v            : Display xy version\n"
    "   --help, -h               : Display help message" << std::endl;
    return 0;
  }

  if (argc < 2) {
    std::cout << "error: no command arguments" << std::endl;
    return 1;
  }

  std::string cmd = xy.GetString("commands", argv[1], "UNKNOWN");
  if (cmd == "UNKNOWN") {
    std::cout << "error: no command named `" << argv[1] << "` found" << std::endl;
    return 0;
  }

  std::string name = xy.GetString("info", "name", "UNKNOWN");
  std::cout << "\n> " << (name != "UNKNOWN" ? name : "") << "@" << argv[1] << std::endl;
  std::cout << "> " << cmd << "\n" << std::endl;

  system(('"'+cmd+'"').c_str());

  return 0;
};