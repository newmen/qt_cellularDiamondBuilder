#ifndef LOADFILEERROR_H
#define LOADFILEERROR_H

#include "fileerror.h"

class LoadFileError : public FileError
{
public:
    LoadFileError(const std::string &file_name) : FileError(file_name, "File cannot be loaded") {}
};

#endif // LOADFILEERROR_H
