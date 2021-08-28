#include "Application/MengerSponge.h"
int main(int argc, char** argv)
{
    Application* app = new MengerSponge(1920, 1080);
    app->Init();
    app->Run();
    return EXIT_SUCCESS;
}