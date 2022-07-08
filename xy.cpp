#include <iostream>
#include <fstream>
#include <algorithm>
#include "ini/INIReader.h"

class args {
  public:
    int argc;
    char**argv;
    args(int argc,char**argv) {
      this->argc=argc,
      this->argv=argv;
    }
    char* get(const std::string&option) {
      char**end=this->argv+this->argc;
      char**itr=std::find(this->argv,end,option);
      if (itr!=end&&++itr!=end)return*itr;
      return 0;
    }
    bool exists(const std::string&option) {
      char**end=this->argv+this->argc;
      return std::find(this->argv,end,option)!=end;
    }
};

int writeini() {
  std::string name;
  std::cout << "Project Name: (proj-name) ";
  std::getline(std::cin, name);
  if (name.empty()) name = "proj-name";
  std::ofstream xyini("xy.ini");
  xyini << "; XY Config file\n\n[info]\nname = "+name+"\n\n[commands]\ntest = echo test\n";
  xyini.close();
  std::cout << "Initialized a minimal xy configuration" << std::endl;
  return 0;
};

int main(int argc, char * argv[]) {
  INIReader xy("xy.ini");
  args args(argc, argv);

  // Help
  if (args.exists("-h")) {
    std::cout << "Usage : xy <command> [options]\n"
    "   xy init                  : Initialize and create a minimal `xy.ini` file or reinitialize an existing one\n"
    "Options:\n"
    "   --quiet, -q              : Quiet operation, do not output messages (default false)\n"
    "   --version, -v            : Display xy version\n"
    "   --help, -h               : Display help message" << std::endl;
    return 0;
  }

  // xy init
  if (argv[1] ? std::string(argv[1]) == "init" : false) {
    if (xy.ParseError() < 0) {
      return writeini();
    } else {
      if (xy.GetString("commands", "init", "UNKNOWN") == "UNKNOWN") {
        return writeini();
      } else {
        std::cout << "error: usage of `init` command in 'xy.ini' not allowed" << std::endl;
        return 1;
      }
    }
  } else if (xy.ParseError() < 0) {
    std::cout << "error: no 'xy.ini' file found" << std::endl;
    return 1;
  } else if (argc < 2) {
    std::cout << "error: no command arguments" << std::endl;
    return 1;
  }

  // xy <command>
  std::string cmd = xy.GetString("commands", argv[1], "UNKNOWN");
  if (cmd == "UNKNOWN") {
    std::cout << "error: no command named `" << argv[1] << "` found" << std::endl;
    return 0;
  }

  // Pretty output
  std::string name = xy.GetString("info", "name", "UNKNOWN");
  std::cout << "\n> " << (name != "UNKNOWN" ? name : "") << "@" << argv[1] << std::endl;
  std::cout << "> " << cmd << "\n" << std::endl;

  // Runner
  system(('"'+cmd+'"').c_str());

  return 0;
};