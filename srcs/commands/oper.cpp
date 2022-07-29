#include "../../includes/commands.hpp"
#include "../../includes/utils.hpp"

bool isOperHost(User *user) {
	char			*configFile = OPERCONF;
	std::ifstream	input;
	std::string		str;

	input.open(configFile, std::ios::in);
	try {input.is_open(); } 
    catch (std::ifstream::failure e)
        { printError(e.what(), 1, true); return; }
	while (getline(input, str)) {
		if (str == user->getHostname())
			return true;
	}
	return false;
}

void	oper(const int &fd, const std::vector<std::string> &params, const std::string &prefix, 
		Server *srv) {

	std::string replyMsg;
	User *user = srv->getUserByFd(fd);

	if (params.empty() || params.size() < 2 || emptyParams(params)) {
		replyMsg = numericReply(srv, fd, "461", ERR_NEEDMOREPARAMS(prefix));
	}
	// else if (isOperHost(user->getHostname()))
	// 	replyMsg = numericReply(srv, fd, "491", ERR_NOOPERHOST);
	else if (params[1] != srv->getPassword())
		replyMsg = numericReply(srv, fd, "464", ERR_PASSWDMISMATCH);
	else {
		std::vector<std::string> nickname;
		nickname.push_back(user->getNickname());
		user->addMode(MOD_OPER);
		mode(fd, nickname, "MODE", srv);
	}
}