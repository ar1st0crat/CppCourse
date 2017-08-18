#pragma once

#include <cstdio>


class SafeFile
{
public:
    SafeFile(char* filename)
    {
        file_ = fopen(filename, "wt");
    }

    ~SafeFile()
    {
        printf("file was closed!\n");
        fclose(file_);
    }

    void write(char* s) const
    {
        fprintf(file_, s);
    }

private:
    FILE* file_;
};
