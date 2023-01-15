#ifndef EXCEPTION_H_

#include <string>

class Exception{
    private:
        std::string text_;
    public: 
        Exception(const std::string& text);
        Exception(std::string&& text);
        const std::string& what() const;
};

Exception::Exception(const std::string& text){
    text_ = text;
};

Exception::Exception(std::string&& text){
    text_ = text;
};

const std::string& Exception::what() const {
    return text_;
}

class OutOfRangeException : public Exception{
    using Exception::Exception;
};

class EmptyArrayException : public Exception{
    using Exception::Exception;
};

class UnavailableMemoryException : public Exception{
    using Exception::Exception;
};

class NonexistingItemException : public Exception {
    using Exception::Exception;
};
class ConflictingItemException : public Exception {
    using Exception::Exception;
};
class InvalidIdentifierException : public Exception {
    using Exception::Exception;
};
class FileProcessingException : public Exception {
    using Exception::Exception;
};
#endif