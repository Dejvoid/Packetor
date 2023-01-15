/// @file Exception.h
#ifndef EXCEPTION_H_

#include <string>
/// @brief 
class Exception{
    private:
        /// @brief 
        std::string text_;
    public: 
        /// @brief 
        /// @param text 
        Exception(const std::string& text);
        Exception(std::string&& text);
        /// @brief 
        /// @return 
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
/// @brief 
class OutOfRangeException : public Exception{
    using Exception::Exception;
};
/// @brief 
class EmptyArrayException : public Exception{
    using Exception::Exception;
};
/// @brief 
class UnavailableMemoryException : public Exception{
    using Exception::Exception;
};
/// @brief 
class NonexistingItemException : public Exception {
    using Exception::Exception;
};
/// @brief 
class ConflictingItemException : public Exception {
    using Exception::Exception;
};
/// @brief 
class InvalidIdentifierException : public Exception {
    using Exception::Exception;
};
/// @brief 
class FileProcessingException : public Exception {
    using Exception::Exception;
};
#endif