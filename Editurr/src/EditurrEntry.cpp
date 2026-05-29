#include <Rendurr.hpp>

#include "EditurrLayer.hpp"

int main()
{
    Rendurr::ApplicationSpecification appSpec;
    appSpec.title = "Editurr";
    appSpec.width = 1280;
    appSpec.height = 720;

    Rendurr::Application app(appSpec);
    app.pushLayer<Editurr::EditurrLayer>("Editurr");
    app.run();

    return 0;
}