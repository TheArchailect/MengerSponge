#include "Application/MengerSponge.h"
int main(int argc, char** argv)
{
    Application* app = new MengerSponge(800, 600);
    if (!app->Init()) 
    {
        std::cout << 
        "RTR:ERROR: Failed to initialise application. Please see error messages for details..." 
        << std::endl;
        return EXIT_FAILURE;
    };
    app->Run();
    return EXIT_SUCCESS;
}