#include <algorithm>
#include <iostream>
#include <vector>
#include <cassert>

#include <bits/stdc++.h>

using namespace std; // ugly as h*ll, hackerrank does this

using std::min_element;
using std::for_each;

vector<string> split_string(string);

// Nr of ops to reduce val to 0.
int num_ops(int val)
{
  //cout << "Num ops for " << val;

  int result = 0;
  int quot = 0;
  // First, subtract as many 5:s as possible:
  quot = val/5;
  result += quot;
  val -= quot*5;

  // Now, subtract as many 2:s as possible
  quot = val/2;
  result += quot;
  val -= quot*2;

  assert(val <= 1);
  // Now, add the remaining 1 if it is there:
  result += val;

  //cout << " is " << result << '\n';

  return result;
}

int equal(vector<int> arr) {
  auto sz = arr.size();

  auto it = min_element(arr.begin(), arr.end());
  auto val = *it;
  auto decreaser = [val](int& elem) { elem -= val; };
  for_each(arr.begin(), arr.end(), decreaser);

  int total_nr_ops[5] {0, 0, 0, 0, 0};

  for (int i = 0; i < 5; i++) {
    auto totalops = [&total_nr_ops, i](int elem) { total_nr_ops[i] += num_ops(elem+i); };
    for_each(arr.begin(), arr.end(), totalops);
  }

  //cout << "Result: ";

  //for (int i = 0; i < 5; i++) cout << ' ' << total_nr_ops[i] << ' ';
  //cout << '\n';

  return *min_element(&total_nr_ops[0], (&total_nr_ops[4]) + 1);
}


int main()
{
  ofstream fout(getenv("OUTPUT_PATH"));

  int t;
  cin >> t;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  for (int t_itr = 0; t_itr < t; t_itr++) {
    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split_string(arr_temp_temp);

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
      int arr_item = stoi(arr_temp[i]);

      arr[i] = arr_item;
    }

    int result = equal(arr);

    fout << result << "\n";
  }

  fout.close();

  return 0;
}

vector<string> split_string(string input_string) {
  string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
                                                                                return x == y and x == ' ';
                                                                              });

  input_string.erase(new_end, input_string.end());

  while (input_string[input_string.length() - 1] == ' ') {
    input_string.pop_back();
  }

  vector<string> splits;
  char delimiter = ' ';

  size_t i = 0;
  size_t pos = input_string.find(delimiter);

  while (pos != string::npos) {
    splits.push_back(input_string.substr(i, pos - i));

    i = pos + 1;
    pos = input_string.find(delimiter, i);
  }

  splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

  return splits;
}
