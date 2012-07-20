#include "execute.h"
#include <config.h>
#include <unistd.h>
#include <sys/wait.h>

#ifdef JUST_PRINT
#include <iostream>
std::string join(const std::vector<std::string> &array, char seperator) {
    if(array.size()) {
      std::string result = array[0];
      for(auto i = array.begin()+1;i!=array.end();++i) {
        result += seperator + *i;
      }
      return result;
    } else {
      return std::string("");
    }
}
#endif

void execCommand(std::string executable, std::vector<std::string> firstArgs, std::vector<std::string> argList) {
  std::vector<std::string> string_args({executable});
  std::copy(firstArgs.begin(), firstArgs.end(), std::back_insert_iterator<std::vector<std::string>>(string_args));
  std::copy(argList.begin(), argList.end(), std::back_insert_iterator<std::vector<std::string>>(string_args));
  if(pid_t pid = fork()) {
    waitpid(pid, NULL, 0);
  } else {
    char **args = new char*[string_args.size()+1];
    auto first = string_args.begin();
    char **current = args;
    while (first != string_args.end())
      *(current++) = (char *)(*(first++)).c_str();
    *current = NULL;
#ifdef JUST_PRINT
    std::cout << join(string_args, ' ') << std::endl;
    std::exit(0);
#else 
    execvp(executable.c_str(), args);
#endif
  }
}
