#pragma once

#include <memory>

#include "Core/Application.hpp"

int main() {
	auto app = Rendurr::CreateApplication();
	app->run();
	return 0;
}