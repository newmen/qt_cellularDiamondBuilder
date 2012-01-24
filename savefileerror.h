#ifndef SAVEFILEERROR_H
#define SAVEFILEERROR_H

#include "fileerror.h"

class SaveFileError : public FileError
{
public:
    SaveFileError(const std::string &file_name) : FileError(file_name, "File cannot be saved") {}
};

#endif // SAVEFILEERROR_H
