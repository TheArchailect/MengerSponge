#include "Application/MengerSponge.h"
int main(int argc, char** argv)
{
    Application* app = new MengerSponge(1920, 1080);
    if (!app->Init()) 
    {
        std::cout << 
        "." 
        << std::endl;
        return EXIT_FAILURE;
    };
    app->Run();
    return EXIT_SUCCESS;
}