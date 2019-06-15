#include "application.h"

#include <iostream>

using namespace Quite;

int main(int argc, char *argv[]) {
    std::system("pwd");
    return Application::exec(argc, argv);
}
