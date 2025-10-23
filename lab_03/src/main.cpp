#include <iostream>
#include <vector>
#include "classes.h"

int main() {
    std::vector<Figure*> figures;


    try {
        figures.push_back(new Triangle(
            {0, 0}, {4, 0}, {0, 3}
        ));

        figures.push_back(new Rectangle(
            {1, 1}, {6, 4}
        ));

        // 3. Создаем валидный Квадрат
        figures.push_back(new Square(
            {0, 0}, {5, 5}
        ));

    } catch (const std::invalid_argument& e) {
        std::cout << "Ошибка при создании демонстрационных фигур: " << e.what() << std::endl;
        // Очистка в случае ошибки на старте
        for (Figure* fig : figures) {
            delete fig;
        }
        return 1;
    }

    double total_area = 0.0;

    for (size_t i = 0; i < figures.size(); ++i) {
        std::cout << "\nFigure: " << i << std::endl;

        std::cout << *figures[i];

        std::pair<double, double> center = figures[i]->find_center();
        std::cout << "Center: (" << center.first << ", " << center.second << ")" << std::endl;

        double area = static_cast<double>(*figures[i]);
        std::cout << "Area: " << area << std::endl;

        total_area += area;
    }

    std::cout << "\nTotal area: " << total_area << std::endl;


    if (figures.size() > 1) {
        delete figures[1];
        figures.erase(figures.begin() + 1);
    }

    for (const auto* fig : figures) {
        std::cout << *fig;
    }

    for (Figure* fig : figures) {
        delete fig;
    }
    figures.clear();
    std::cout << "Memory is cleaned" << std::endl;

    return 0;
}