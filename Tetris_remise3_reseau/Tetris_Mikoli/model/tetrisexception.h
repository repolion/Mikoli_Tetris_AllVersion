#ifndef TETRISEXCEPTION_H
#define TETRISEXCEPTION_H

#include <iostream>
#include <sstream>
#include <exception>

namespace mikoli{

/*!
 * \brief The TetrisException class
 * This is the exception class used for the game .
 */
class TetrisException : public std::exception{
private:
    std::string msg;

public:
    TetrisException( const char * Msg){
        std::ostringstream output;
        output << Msg;
        this->msg = output.str();
    }

    virtual ~TetrisException() throw(){}

    const char * what() const throw(){
        return msg.c_str();
    }
};

}
#endif // TETRISEXCEPTION_H
