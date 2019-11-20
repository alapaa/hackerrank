#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using std::cout;
using std::cin;
using std::string;
using std::ofstream;
using std::max;

int mat[5000+1][5000+1];

// See also
// https://www.geeksforgeeks.org/count-common-subsequence-in-two-strings/
// https://www.geeksforgeeks.org/lcs-longest-common-subsequence-three-strings/

int commonChild(string s1, string s2) {
  // mat[i][j] is length of longest common subsequence in s1[0,i-1], s2[0,j-1].

  for (int i = 0; i <= s1.size(); i++) {
    for (int j = 0; j <= s2.size(); j++) {
      if (i == 0 || j == 0)
        mat[i][j] = 0;
      else if (s1[i-1] != s2[j-1])
        mat[i][j] = max(mat[i][j-1], mat[i-1][j]);
      else
        mat[i][j] = mat[i-1][j-1] + 1;
    }
  }

  return mat[s1.size()][s2.size()];
}


int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s1;
    getline(cin, s1);

    string s2;
    getline(cin, s2);

    int result = commonChild(s1, s2);

    fout << result << "\n";
    cout << result << "\n";

    fout.close();

    return 0;
}
