#include <iostream>

struct Product
{
    int id;
    int price;
    int stock;
};

void ShowProduct(const Product &product) {
    std::cout << "ID: " << product.id << std::endl;
    std::cout << "Price: " << product.price << std::endl;
    std::cout << "Stock: " << product.stock << std::endl;
}

int main() {
    Product pen = {
        0,
        100,
        200,
    };

    ShowProduct(pen);

    pen.price *= 0.8;
    pen.stock--;

    ShowProduct(pen);

    Product* ptr_pen = &pen;

    ptr_pen->price = 200;
    ptr_pen->stock = 300;

    ShowProduct(pen);

    return 0;
}
