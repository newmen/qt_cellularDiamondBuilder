#ifndef LOADFILEERROR_H
#define LOADFILEERROR_H

#include "fileerror.h"

class LoadFileError : public FileError
{
public:
    LoadFileError(const std::string &file_name) : FileError(file_name, "File cannot be loaded") {}

private:
    LoadFileError &operator= (const LoadFileError &);
};

#endif // LOADFILEERROR_H
