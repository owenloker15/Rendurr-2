#include <Rendurr.hpp>

#include "EditurrLayer.hpp"

int main()
{
	Rendurr::Application app;
	app.pushLayer<Editurr::EditurrLayer>("Editurr");
	app.run();
	return 0;
}