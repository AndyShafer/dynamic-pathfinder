#include <emscripten/bind.h>
#include "../Solver.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(solver_binding) {
	class_<Solver>("Solver")
		.constructor<Environment*>()
		.function("solve", &Solver::solve);
}
