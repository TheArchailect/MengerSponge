#include "Application/MengerSponge.h"
int main(int argc, char** argv)
{
    Application* app = new MengerSponge(1000, 800);
    if (!app->Init()) 
    {
        std::cout << "." << std::endl;
        return EXIT_FAILURE;
    };
    app->Run();
    return EXIT_SUCCESS;
}