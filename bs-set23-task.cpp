#include <iostream>
#include <string>

using namespace std;

class Product {
public:
    Product(string name, double price, string description) : name(name), price(price), description(description) {}

    string getName() const { return name; }
    double getPrice() const { return price; }
    string getDescription() const { return description; }

private:
    string name;
    double price;
    string description;
};

class CartItem {
public:
    CartItem(Product* product, int quantity) : product(product), quantity(quantity) {}

    Product* getProduct() const { return product; }
    int getQuantity() const { return quantity; }

    void setQuantity(int newQuantity) { quantity = newQuantity; }

private:
    Product* product;
    int quantity;
};

class Cart {
public:
    void addItem(CartItem* item) { items[count++] = item; }
    CartItem* getItem(int index) const { return items[index]; }
    int getItemCount() const { return count; }

    double getTotalPrice() const {
        double total = 0;
        for (int i = 0; i < count; i++) {
            total += items[i]->getProduct()->getPrice() * items[i]->getQuantity();
        }
        return total;
    }

private:
    CartItem* items[100];
    int count = 0;
};

class ProductList {
public:
    ProductList() {
        products[0] = new Product("Product 1", 10.99, "This is product 1");
        products[1] = new Product("Product 2", 25.99, "This is product 2");
        products[2] = new Product("Product 3", 14.99, "This is product 3");
    }

    Product* getProduct(int index) const { return products[index]; }
    int getProductCount() const { return 3; }

private:
    Product* products[3];
};

int main() {
    ProductList productList;
    Cart cart;

    while (true) {
        // Show menu
        cout << "Select an option:\n"
             << "1. See available products\n"
             << "2. Add product to cart\n"
             << "3. View cart\n"
             << "4. Edit cart\n"
             << "5. Checkout\n"
             << "6. Exit\n";

        // Get user choice
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                // Show available products
                cout << "Available products:\n";
                for (int i = 0; i < productList.getProductCount(); i++) {
                    Product* product = productList.getProduct(i);
                    cout << i+1 << ". " << product->getName() << " - $" << product->getPrice() << " - " << product->getDescription() << "\n";
                }
                break;
            }

            case 2: {
                // Add product to cart
                cout << "Enter product and quantity (e.g. '1 2' for 2 of Product 1), or enter '0 0' to finish:\n";
                while (true) {
                    int productIndex, quantity;
                    cin >> productIndex >> quantity;
                    if (productIndex == 0 && quantity == 0) {
                        break;
                    }
                    Product* product = productList.getProduct(productIndex-1);
                    CartItem* item = new CartItem(product, quantity);
                    cart.addItem(item);
                    cout << "Added " << quantity << " " << product->getName() << "(s) to cart.\n";
                }
                break;
            }

            case 3: {
                // View cart
                cout << "Cart contents:\n";
                for (int i = 0; i < cart.getItemCount(); i++) {
                    CartItem* item = cart.getItem(i);
                    cout << i+1 << ". " << item->getProduct()->getName() << " - $" << item->getProduct()->getPrice() << " - " << item->getQuantity() << " in cart.\n";
                }
                cout << "Total price: $" << cart.getTotalPrice() << "\n";
                break;
            }

            case 4: {
                // Edit cart
                cout << "Enter item number and new quantity (e.g. '1 2' to set the quantity of the first item to 2), or enter '0 0' to finish:\n";
                while (true) {
                    int itemIndex, newQuantity;
                    cin >> itemIndex >> newQuantity;
                    if (itemIndex == 0 && newQuantity == 0) {
                        break;
                    }
                    CartItem* item = cart.getItem(itemIndex-1);
                    item->setQuantity(newQuantity);
                    cout << "Updated quantity of " << item->getProduct()->getName() << " to " << newQuantity << ".\n";
                }
                break;
            }

            case 5: {
    // Checkout
    double total = cart.getTotalPrice();
    cout << "Order details:\n";
    for (int i = 0; i < cart.getItemCount(); i++) {
        CartItem* item = cart.getItem(i);
        Product* product = item->getProduct();
        int quantity = item->getQuantity();
        double price = product->getPrice();
        double productTotal = price * quantity;
        cout << i+1 << ". " << product->getName() << "\n"
             << product->getDescription() << "\n"
             << "Ordered quantity " << quantity << "\n"
             << "Price per unit $" << price << "\n"
             << "Total price for this product $" << productTotal << "\n";
    }
    cout << "Total price: $" << total << "\n";
    cout << "Checking out..." << "\n";
    break;
}


            case 6: {
                // Exit
                cout << "See you again!\n";
                return 0;
            }

            default: {
                cout << "Invalid choice. Please try again.\n";
                break;
            }
        }
    }
}
