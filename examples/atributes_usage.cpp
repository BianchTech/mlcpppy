#include <iostream>

#include "mlcpppy/instances/instances.h"

int main() {
        // Exemplo de uso da classe atribute, instances e instance
        Instance a(Attribute(1), Attribute(2.5), Attribute("Pedro"));
        Instance b(Attribute(1), Attribute(2.5), Attribute("Pedro"));
        Instance c(Attribute(1), Attribute(2.5), Attribute("Pedro"));
        Instances matrix({a, b, c});
        std::cout << matrix << std::endl;
        return 0;
}