#pragma once
#include <chrono>
#include "LoxCallable.hpp"
using namespace std::chrono;

struct Clock : LoxCallable {
	int arity() override { return 0; }
	LoxType call(Interpreter interpreter, vector<LoxType> arguments) {
		return (double)duration_cast<milliseconds>(
			time_point_cast<milliseconds>(system_clock::now()
				).time_since_epoch()).count() / 1000;
	}
	string toString() { return "<native fn>"; }
	Clock() {};
}; //clock;