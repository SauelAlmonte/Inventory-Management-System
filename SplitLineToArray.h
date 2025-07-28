// SplitLineToArray.h
#ifndef SPLITLINETOARRAY_H
#define SPLITLINETOARRAY_H

#include <string>
using namespace std;

// Splits a line using a delimiter into a string array.
// Returns number of fields extracted.
int splitLineToArray(const string& line, const string& delimiter, string fields[], int maxFields) {
    size_t start = 0;
    size_t end;
    int count = 0;

    while ((end = line.find(delimiter, start)) != string::npos && count < maxFields) {
        fields[count++] = line.substr(start, end - start);
        start = end + delimiter.length();
    }

    if (count < maxFields) {
        fields[count++] = line.substr(start);
    }

    return count;
}

#endif
