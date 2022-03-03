#pragma once
#include <chrono>
#include "LoxCallable.hpp"
using namespace std::chrono;

struct ClockCallable : LoxCallable {
	int arity() override { return 0; }
	LoxType call(Interpreter interpreter, vector<LoxType> arguments) {
		return duration_cast<milliseconds>(
			time_point_cast<milliseconds>(system_clock::now()).time_since_epoch()).count();
		//return (double)system_clock::now();
	}
};
