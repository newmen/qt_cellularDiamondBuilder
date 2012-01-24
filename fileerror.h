#ifndef FILEERROR_H
#define FILEERROR_H

#include <string>

class FileError
{
public:
    const char *message() const { return (_file_name + ": " + _message).c_str(); }

protected:
    FileError(const std::string &file_name, const std::string &message) : _file_name(file_name), _message(message) {}

private:
    FileError &operator= (const FileError &);

    std::string _file_name, _message;
};

#endif // FILEERROR_H
