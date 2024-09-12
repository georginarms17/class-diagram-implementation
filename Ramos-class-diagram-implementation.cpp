#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

const int max_products = 100;                               //Variable for the maximum number for the products

class Product {
private:
    string prodName;
    string prodID;
    double unitPrice;

public:
    //Constructors to set value for each product details
    Product() : prodID(""), prodName(""), unitPrice(0.0) {}
    Product(string pID, string pname, double pprice) : prodID(pID), prodName(pname), unitPrice(pprice) {}
    
    //Functions to return each product details
    string getProdID() { return prodID; }
    string getProdName() { return prodName; }
    double getPrice() { return unitPrice; }         

    //To display the products in the shop
    void displayProd() {
        cout << prodID << setw(27) << prodName << setw(19) << fixed << setprecision(2) << unitPrice << endl; 
    }
};

class ShoppingCart {
private:
    Product cartProducts[max_products];                     // To hold products in the cart defined by the maximum number of products
    double totalPerProd[max_products];                      // To hold total price per product defined by the maximum number of products
    int prodQty [max_products];                             // To hold quantity per product defined by the maximum number of products                                 
    int prodCount = 0;                                      // To track the number of products in the cart
    
public:
    //Constructor to set the value for product count
    ShoppingCart() : prodCount(0) {}

    // Function to add products to the cart
    void addToCart(const Product& product, int qty) {
        if (prodCount < max_products) {
            cartProducts[prodCount] = product;
            prodQty[prodCount] = qty;
            prodCount++;
        }
        else {
            cout << "Shopping Cart full! Unable to add more products.\n\n";
        }
    }
    
    void displayCart() {
        if (prodCount == 0) {
            cout << "No added product(s) in the shopping cart.\n\n";
            return;                                         // Return here to avoid unnecessary printing
        }

        cout << "PRODUCT ID" << setw(20) << "NAME" << setw(20) << "QUANTITY" << setw(20) << "PRICE\n";
        for (int i = 0; i < prodCount; i++) {
            cout << cartProducts[i].getProdID() << setw(26)
                 << cartProducts[i].getProdName() << setw(20)
                 << prodQty[i] << setw(19)
                 << fixed << setprecision(2) << cartProducts[i].getPrice() * prodQty[i] << endl;
        }
    }

    bool isEmpty() {
        return prodCount == 0;
    }

    void clearCart() {
        prodCount = 0;
    }

    double checkout() {
        double totalPrice = 0;
        int totalQty = 0;
        for (int i = 0; i < prodCount; i++) {
            totalQty += prodQty[i];
            totalPrice += cartProducts[i].getPrice() * prodQty[i];
        }
        cout << "Total Quantity of Products: " << totalQty << endl;
        cout << "Total Price: PHP " << fixed << setprecision(2) << totalPrice << "\n\n";
        return totalPrice;
    }

    int getProductCount() {
        return prodCount;
    }

    Product getCartProduct(int index) {
        return cartProducts[index];
    }

    int getQty(int index) {
        return prodQty[index];
    }
};

class Order {
private:
    Product orderProduct[max_products];                     //To hold the ordered products defined by the maximum number of products
    int orderQty[max_products];                             //To hold the quantity of the ordered products defined by the maximum number of products
    double orderPrice;                                      //To hold the order price
    int orderCount;                                         //To track the number of orders

public:
    //Constructor to set the value for order count and order price
    Order() : orderCount(0), orderPrice(0.0) {}

    void setOrderDetails(ShoppingCart& cart, double orderTotal) {
        orderCount = cart.getProductCount();
        orderPrice = orderTotal;
        for (int i = 0; i < orderCount; i++) {
            orderProduct[i] = cart.getCartProduct(i);
            orderQty[i] = cart.getQty(i);
        }
    }
    
    //Function to show the details of each order
    void displayOrder() {
        cout << "Order Details:\n";
        cout << "PRODUCT ID" << setw(20) << "NAME" << setw(20) << "QUANTITY" << setw(20) << "PRICE" << endl;
        for (int i = 0; i < orderCount; i++) {
            cout << orderProduct[i].getProdID() << setw(26)
                 << orderProduct[i].getProdName() << setw(17)
                 << orderQty[i] << setw(23)
                 << fixed << setprecision(2) << orderProduct[i].getPrice() * orderQty[i] << endl;
        }
        cout << "\nTotal Amount: PHP " << fixed << setprecision(2) << orderPrice << "\n\n";
    }
};

// Function to display the products set into the system
void displayProducts(Product products[], int prodCount) {
    cout << "PRODUCT ID" << setw(20) << "NAME" << setw(20) << "PRICE" << endl;
    for (int i = 0; i < prodCount; i++) {
        products[i].displayProd();
    }
    cout << endl;
}

int main() {
    // Products in the shop
    int prodCount = 10;
    Product products [] = {
        Product("P001", "Apples", 150.00),
        Product("P002", "Bananas", 70.00),
        Product("P003", "Milk (1L)", 60.00),
        Product("P004", "Bread Loaf", 55.00),
        Product("P005", "Eggs", 85.00),
        Product("P006", "Chicken Breasts", 200.00),
        Product("P007", "Rice", 45.00),
        Product("P008", "Tomatoes", 90.00),
        Product("P009", "Potatoes", 80.00),
        Product("P010", "Olive Oil", 150.00),
    };
    
    ShoppingCart cart;                                       //Object for ShoppingCart Class
    Order orders[max_products];                              //Object for Order Class defined by the maximum number of products
    int orderCount = 0;                                      //Initialize to track order count

    int choice;
    do {
        cout << "=============== GROCERY MENU ===============\n";
        cout << "1 - View Products Available in the Grocery\n"
             << "2 - Your Shopping Cart\n"
             << "3 - Your Orders\n"
             << "4 - Exit Grocery\n";
        cout << "Choice: ";
        cin >> choice;
        system("cls");

        switch (choice) {
            case 1:
                displayProducts(products, prodCount);
                
                cout << "Enter the corresponding Product ID to the product that you want to add to your cart.\n\n";
                while (true) {
                    string prodID;
                    int prodQty;
                    
                    cout << "Product ID: ";
                    cin >> prodID;

                    bool found = false;
                    for (int i = 0; i < prodCount; i++) {
                        if (products[i].getProdID() == prodID) {
                            cout << "Enter quantity: ";
                            cin >> prodQty;
                            cart.addToCart(products[i], prodQty);
                            found = true;
                            break;
                        }
                    }

                    if (!found) {
                        cout << "Product ID not found. :(\n";
                    }

                    char addMore;
                    cout << "Would you like to add more products to your shopping cart? (Y/N): ";
                    cin >> addMore;     
                    cout << endl;                   
                    if (toupper(addMore) != 'Y') { 
                        break;
                    }
                }
                cout << "Proceeding to the Grocery Menu...\n";
                system("pause");
                system("cls");
                break;
            
            case 2:
                cart.displayCart();
                if (!cart.isEmpty()) {
                    char choice;
                    cout << "\nWould you like to check out all the products? (Y/N): ";
                    cin >> choice;
                    cout << endl;
                    if (toupper(choice) == 'Y') {
                        double orderPrice = cart.checkout();
                        if (orderCount < max_products) {
                            orders[orderCount].setOrderDetails(cart, orderPrice);
                            orderCount++;
                            cart.clearCart();
                            cout << "Checkout complete! Your order has been placed.\n\n";
                            cout << "Proceeding to the Grocery Menu...\n";
                            system("pause");
                            system("cls");
                        } 
                        else {
                            cout << "Maximum number of orders reached. Unable to place more orders. :(\n";
                            cout << "Proceeding to the Grocery Menu...\n";
                            system("pause");
                            system("cls");
                        }
                    }
                }
                break;

            case 3:
                if (orderCount == 0) {
                    cout << "No order(s) has been placed.\n\n";
                    cout << "Proceeding to the Grocery Menu...\n";
                    system("pause");
                    system("cls");
                } 
                else {
                    for (int i = 0; i < orderCount; i++) {
                        cout << "ORDER ID" << i + 1 << ":\n";
                        orders[i].displayOrder();
                    }
                }
                cout << "Proceeding to the Grocery Menu...\n";
                system("pause");
                system("cls");
                break;

            case 4:
                cout << "Thank you!\n\nExiting from the system...";
                break;
            
            default: 
                cout << "Invalid input. Kindly enter numbers 1 to 4 only.\n\n";
                cout << "Proceeding to the Grocery Menu...\n";
                system("pause");
                system("cls");
        }
    } while (choice != 4);
    return 0;
}