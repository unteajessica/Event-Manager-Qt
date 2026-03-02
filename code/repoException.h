#pragma once
#include <exception>
#include <string>
using namespace std;

class RepoException : public exception {
private:
	string message;
public:
	RepoException(const string& m) : message(m) {}
	const char* what() const noexcept override {
		return message.c_str();
	}
};
