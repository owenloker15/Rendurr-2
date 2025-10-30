#include <Rendurr.hpp>

#include "EditurrLayer.hpp"

#include <memory>

int main()
{
	Rendurr::Application app;
	app.pushLayer<Editurr::EditurrLayer>("Editurr");
	app.run();
	return 0;
}