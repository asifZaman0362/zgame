#include <Application.hpp>

int main() {
    TstBits::Settings settings;
    TstBits::Application app(settings);
    app.Run();
    return 0;
}