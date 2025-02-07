// General utils
#include <stdlib.h>
#include <ctype.h>

// Util to validate string as valid int
int is_int(char str[]) {
  for (int i = 0; str[i] != 0; i++) {
    if (!isdigit(str[i])) {
      return 0;
    }
  }
  return 1;
}
