#pragma once

#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <cstring>

#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib") // just found out about this: this is great

#define PORT 54000
#define BUFFER_SIZE 4096
//#define _CRT_SECURE_NO_WARNINGS

class Discarder
{
public:
	template<typename T> constexpr inline void operator=(T&) const {}
	template<typename T> constexpr inline void operator=(T&&) const {}
private:
};

constexpr inline Discarder _;