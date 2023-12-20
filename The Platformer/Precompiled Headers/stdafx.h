#pragma once
#include <initializer_list>
#include <functional>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <stack>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


constexpr int WINDOW_WIDTH  = 1600;
constexpr int WINDOW_HEIGHT = 900;

constexpr float PHYSICS_STEP = 0.01f;



template <typename Arg, typename... Args>
constexpr static void DEBUG_MESSAGE_LOG(Arg&& arg, Args&&... args)
{
	std::cerr << std::forward<Arg>(arg);
	((std::cerr << std::forward<Args>(args)), ...);
}

/* This here makes sounds and music work */
FILE _iob[] = { *stdin, *stdout, *stderr };
extern "C" FILE * __cdecl __iob_func(void) { return _iob; }