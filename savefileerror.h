#ifndef SAVEFILEERROR_H
#define SAVEFILEERROR_H

#include "fileerror.h"

class SaveFileError : public FileError
{
public:
    SaveFileError(const std::string &file_name) : FileError(file_name, "File cannot be saved") {}

private:
    SaveFileError &operator= (const SaveFileError &);
};

#endif // SAVEFILEERROR_H
