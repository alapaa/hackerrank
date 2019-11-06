#include <bits/stdc++.h>
#include <inttypes.h>

#include <cstdio>
#include <iostream>

using namespace std;
using std::cout;

vector<string> split_string(string);

/*
** Using documented GCC type unsigned __int128 instead of undocumented
** obsolescent typedef name __uint128_t.  Works with GCC 4.7.1 but not
** GCC 4.1.2 (but __uint128_t works with GCC 4.1.2) on Mac OS X 10.7.4.
*/
typedef unsigned __int128 uint128_t;

/*      UINT64_MAX 18446744073709551615ULL */
#define P10_UINT64 10000000000000000000ULL   /* 19 zeroes */
#define E10_UINT64 19

#define STRINGIZER(x)   # x
#define TO_STRING(x)    STRINGIZER(x)

const size_t BUFSZ = 30000;


std::ostream&
operator<<( std::ostream& dest, __int128_t value )
{
    std::ostream::sentry s( dest );
    if ( s ) {
        __uint128_t tmp = value < 0 ? -value : value;
        char buffer[ 128 ];
        char* d = std::end( buffer );
        do
        {
            -- d;
            *d = "0123456789"[ tmp % 10 ];
            tmp /= 10;
        } while ( tmp != 0 );
        if ( value < 0 ) {
            -- d;
            *d = '-';
        }
        int len = std::end( buffer ) - d;
        if ( dest.rdbuf()->sputn( d, len ) != len ) {
            dest.setstate( std::ios_base::badbit );
        }
    }
    return dest;
}

static int print_u128_u(uint128_t u128, char* buf, size_t size)
{
  int rc;
  if (u128 > UINT64_MAX)
  {
    uint128_t leading  = u128 / P10_UINT64;
    uint64_t  trailing = u128 % P10_UINT64;
    rc = print_u128_u(leading, buf, size);
    rc += snprintf(buf+rc, size-rc, "%." TO_STRING(E10_UINT64) PRIu64, trailing);
  }
  else
  {
    uint64_t u64 = u128;
    rc = snprintf(buf, size, "%" PRIu64, u64);
  }
  return rc;
}

__int128 fibonacciModified(int t1, int t2, int n) {
  __int128 next;
  __int128 tt1 = t1;
  __int128 tt2 = t2;
  __int128 tmp;
  for (int i = 3; i <= n; i++) {
    if ( tt2 > sqrt(double(0xFFFFFFFFFFFFFFFF)) ) {
      cout << "Intermediate result too large! Exiting\n";
      exit(1);
    }
    next = tt1 + tt2*tt2;
    tt1 = tt2;
    tt2 = next;
  }

  return tt2;
}

int main()
{
  ofstream fout(getenv("OUTPUT_PATH"));

  string t1T2n_temp;
  getline(cin, t1T2n_temp);

  vector<string> t1T2n = split_string(t1T2n_temp);

  int t1 = stoi(t1T2n[0]);

  int t2 = stoi(t1T2n[1]);

  int n = stoi(t1T2n[2]);

  __int128 result = fibonacciModified(t1, t2, n);

  char buf[BUFSZ];
  print_u128_u(result, buf, BUFSZ-1);
  fout << buf << '\n';
  cout << buf << '\n';

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
