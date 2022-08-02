#ifndef EXCEPTIONS_HPP
# define EXCEPTIONS_HPP

# include <exception>
# include <string>

# include "Server.hpp"

class ircException : public std::exception
{
    protected:
        std::string code;
        std::string rpl;
    public:
        virtual         ~ircException() throw() {}
        virtual void    reply(Server *srv, const int &fd) const throw();
};

class grammarException : public ircException
{ 
    private:
        const char  *msg;
    public:
        virtual         ~grammarException() throw() {}
        grammarException(const char *msg = NULL) : msg(msg) {}
        virtual const char *what() const throw();
};

class nosuchnickException : public ircException
{ public: nosuchnickException(std::string nickname, std::string code = "401");};

class norecipientException : public ircException
{ public: norecipientException(std::string command, std::string code = "411");};

class notexttosendException : public ircException
{ public: notexttosendException(std::string code = "412"); };

class toomanytargetsException : public ircException
{ public: toomanytargetsException(std::string target, std::string errcode, \
                                std::string abortmsg, std::string code = "407");
};

class notoplevelException : public ircException
{ public: notoplevelException(std::string mask, std::string code = "413");};

class wildtoplevelException : public ircException
{ public: wildtoplevelException(std::string mask, std::string code = "414");};

class cannotsendtochanException : public ircException
{ public: cannotsendtochanException(std::string channame, \
                                                      std::string code = "404");
};

#endif
