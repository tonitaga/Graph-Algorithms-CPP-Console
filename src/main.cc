#include <iostream>

#include "view.h"

int main() {
    ng::Model model;
    ng::Controller controller(&model);
    ng::View view(&controller);
    view.Start();
    return 0;
}
