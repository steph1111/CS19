#include "cs19_c_strings.h"

namespace cs19 {

unsigned atoi(const char *str) {
  unsigned len = strlen(str), digit = 0, number = 0;

  for (unsigned i = 0; i < len; i++) {
    digit = 1;
    for (unsigned j = 0; j < len - i - 1; j++) digit *= 10;
    number += digit * (*(str + i) - '0');
  }

  return number;
}

const char *strchr(const char *haystack, const char needle) {
  for (; *haystack; ++haystack) {
    if (*haystack == needle) return haystack;
  }
  return nullptr;
}

int strcmp(const char *str1, const char *str2) {
  unsigned len1 = strlen(str1), len2 = strlen(str2);
  bool equal = true;


  for (; *str1 && *str2; str1++, str2++) {
    if (*str1 > *str2) return 1;
    if (*str1 < *str2) return -1;
    if (*str1 != *str2) equal = false;
  }

  if (equal && len1 != len2) return (len1 < len2) ? -1 : 1;

  return 0;
}

std::size_t strlen(const char *str) {
  size_t count = 0;

  for (; *str; ++str) {
    if (*str != '\0') count++;
  }

  return count;
}

const char *strpbrk(const char *haystack, const char *char_list) {
  const char *begin_list = char_list;

  for (; *haystack; haystack++) {
    char_list = begin_list;
    for (; *char_list; char_list++) {
      if (*char_list == *haystack) {
        return haystack;
      }
    }
  }
  return nullptr;
}

const char *strrchr(const char *haystack, const char needle) {
  const char *end = haystack + strlen(haystack) - 1;

  for (; haystack <= end; end--) {
    if (*end == needle) {
      return end;
    }
  }

  return nullptr;
}

char *strrev(char *str) {
  char *end = str + strlen(str) - 1;
  char *begin = str;
  for (; begin < end; begin++, end--) {
    char temp = *end;
    *end = *begin;
    *begin = temp;
  }
  return str;
}

const char *strstr(const char *haystack, const char *needle) {
  const char *orig_needle = needle, *pos_haystack = haystack;

  for (; *haystack; haystack++) {
    if (*haystack == *needle) {
      pos_haystack = haystack;
      pos_haystack++; needle++;
      for (; *pos_haystack && *needle; pos_haystack++, needle++) {
        if (*pos_haystack != *needle) break;
      }
      if (!(*needle)) {
        return haystack;
      } else {
        needle = orig_needle;
      }
    }
  }

  return nullptr;
}

void strzip(const char *str1, const char *str2, char *output) {
  unsigned len1 = strlen(str1), len2 = strlen(str2);

  for (; *str1 && *str2; str1++, str2++) {
    *output = *str1;
    output++;
    *output = *str2;
    output++;
  }

  if (len1 > len2) {
    for (; *str1; str1++, output++) *output = *str1;
  } else if (len2 > len1) {
    for (; *str2; str2++, output++) *output = *str2;
  }
  *output = '\0';
}

char *str_rot13(char *str) {
  char *begin = str;

  for (; *str; str++) {
    if ((*str >= 'a' && *str <= 'm') || (*str >= 'A' && *str <= 'M')) {
      *str += 13;
    } else if ((*str >= 'n' && *str <= 'z') || (*str >= 'N' && *str <= 'Z')) {
      *str -= 13;
    }
  }
  str = begin;

  return str;
}

}  // namespace cs19