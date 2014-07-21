#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

using std::string;
using std::unordered_map;
const int kmaxlength = 8;
unordered_map<string,int> dict;
string MMSS(string instring) {
  int stringinlen = instring.length();
  int i = 0;
  int j = i+std::min(kmaxlength,stringinlen-i);
  std::string result;
  while (i<stringinlen) {
    string s = instring.substr(i,j);
    if(j == (i-2) || dict.count(s)) {
        result = result + s + " ";
      i++;
      j = i+std::min(kmaxlength,stringinlen-i);

    }
    else {
      j--;
    }
  }
  return result;
}


int main() {
    dict.insert(std::make_pair("ÄãºÃ", 2));
    std::string in("ÄãºÃÂð");
    auto s = MMSS(in);
    std::cout << s;

}

