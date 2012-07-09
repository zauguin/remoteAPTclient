/*
 * remoteAPTclient.cxx
 *
 * Copyright 2012 Marcel Krüger <zauguin@gmail.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above
 *   copyright notice, this list of conditions and the following disclaimer
 *   in the documentation and/or other materials provided with the
 *   distribution.
 * * Neither the name of the Remote Package Management Project nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 */


#include <iostream>
#include <unordered_set>
#include <string>
#include <functional>
#include <algorithm>

#include <cstdlib>

#include <unistd.h>
#include <sys/wait.h>
#include "installed.h"

using std::istream;
using std::cin;
using std::endl;
using std::ostream;
using std::unordered_set;
using std::string;
using std::getline;
using std::function;

string join(const std::vector<string> &array, char seperator) {
  if(array.size()) {
    string result = array[0];
    for(auto i = array.begin()+1;i!=array.end();++i) {
      result += seperator + *i;
    }
    return result;
  } else {
    return string("");
  }
}

unordered_set<string> streamToSet(istream &stream, function<void(string)> helper = [](string){}) {
  unordered_set<string> result;
  string package_name;
  while(getline(stream, package_name)) {
    helper(package_name);
    if(package_name[0]=='-')
      result.erase(package_name.substr(1));
    else
      result.insert(package_name);
  }
  return result;
}

void execCommand(string executable, std::vector<string> firstArgs, std::vector<string> argList) {
  std::vector<string> string_args({executable});
  std::copy(firstArgs.begin(), firstArgs.end(), std::back_insert_iterator<std::vector<string>>(string_args));
  std::copy(argList.begin(), argList.end(), std::back_insert_iterator<std::vector<string>>(string_args));
  if(pid_t pid = fork()) {
    waitpid(pid, NULL, 0);
  } else {
    char **args = new char*[string_args.size()];
    auto first = string_args.begin();
    while (first != string_args.end()) *args++ = (char *)(*first++).c_str();
    std::cout << join(string_args, ' ') << endl;
    std::exit(0);
    //
    //execvp(executable.c_str(), args);
  }
}

int main(int argc, char **argv)
{
  istream &old_file_i = get_istream();
  auto old_set=streamToSet(old_file_i);
#ifdef WRITE_TO_INSTALLED_FILE
  ostream &old_file_o = get_ostream();
  auto new_set=streamToSet(cin, [&old_file_o](string name){old_file_o << name << endl;});
#else
  auto new_set=streamToSet(cin);
#endif
  {
    auto old_set2 = old_set;
    for(auto i:old_set2) {
      if(new_set.erase(i))
        old_set.erase(i);
    }
  }
  std::vector<string> new_vector, old_vector;
  std::copy(new_set.begin(), new_set.end(), std::back_insert_iterator<std::vector<string>>(new_vector));
  std::copy(old_set.begin(), old_set.end(), std::back_insert_iterator<std::vector<string>>(old_vector));
  execCommand("apt-get", {"update"}, {});
  if(old_vector.size())
    execCommand("apt-mark", {"markauto"}, old_vector);
  if(new_vector.size()) {
    execCommand("apt-get", {"install"}, new_vector);
    execCommand("apt-mark", {"unmarkauto"}, new_vector);
  }
  execCommand("apt-get", {"dist_upgrade"}, {});
  execCommand("apt-get", {"autoremove"}, {});
  return 0;
}

