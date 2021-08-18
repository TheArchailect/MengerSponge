#include "Application/MengerSponge.h"
int main(int argc, char** argv)
{
    Application* app = new MengerSponge(1000, 800);
    app->Init();
    app->Run();
    return EXIT_SUCCESS;
}