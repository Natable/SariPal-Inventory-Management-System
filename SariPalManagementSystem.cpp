#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <iomanip>

using namespace std;

const int CONSOLE_WIDTH = 80;

struct Product{
    string name;
    double price;
    int stock;

    Product(string n, double p, int s) : name(n), price(p), stock(s) {}
};

struct Order{
    string productName;
    int quantity;
    double totalPrice;
};

void displayProducts(const vector<Product>& products);
void buyDisplayProducts(const vector<Product>& buyPrices);
void sellProducts(vector<Product>& products, double& totalSales, double& balance);
void buyProducts(vector<Product>& products, double& balance, const vector<Product>& buyPrices);
void salesHistory(double& totalSales);
void showHistory(const vector<Order>& orderHistory);
void centerText (const string& text);
vector <Order> buyHistory;
vector <Order> sellHistory;

int main (){

    vector <Product> products = {
        {"Coke", 35.0, 100},
        {"Piattos", 15.0, 50},
        {"Hany", 10.0, 75},
        {"Water", 20.0, 200}
    };

    vector <Product> buyPrices = {
        {"Coke", 30.0, 0},
        {"Piattos", 10.0, 0},
        {"Hany", 5.0, 0},
        {"Water", 15.0, 0}
    };

    bool systemOn = true;
    double balance = 5000;
    double totalSales = 0;
    int select;

    while (systemOn){
    system("CLS");
    centerText("-- SARI-PAL MANAGEMENT SYSTEM --\n");
    centerText("Balance: " + to_string(static_cast<int>(balance)) + "\n");
    centerText("1. Display Inventory\n");
    centerText("2. Sell Products\n");
    centerText("3. Buy Products\n");
    centerText("4. Transaction History\n");
    centerText("5. Exit Program\n");
    centerText("Enter choice: ");
    cin >> select;
    cin.get();

    switch (select){
        case 1:
            system("CLS");
            displayProducts(products);
            centerText("Press enter to continue...");
            cin.get();
            break;
        case 2:
            system("CLS");
            sellProducts(products, totalSales, balance);
            cin.get();
            centerText("Press enter to continue...");
            cin.get();
            break;
        case 3:
            system("CLS");
            buyProducts(products, balance, buyPrices);
            cin.get();
            centerText("Press enter to continue...");
            cin.get();
            break;
        case 4:
            system("CLS");
            salesHistory (totalSales);
            centerText("-- SELL HISTORY --\n");
            showHistory(sellHistory);
            centerText("-- BUY HISTORY --\n");
            showHistory(buyHistory);
            centerText("Press enter to continue...");
            cin.get();
            break;
        case 5:
            system("CLS");
            centerText("Thank you for using the Sari-Pal Management System! Goodbye! Exiting program...\n");
            systemOn = false;
            break;
        default:
            centerText("Invalid choice. Please try again.\n");
            centerText("Press enter to continue...");
            cin.get();
            break;
    }
    }
    return 0;
}

void centerText(const string& text) {
    int spaces = (CONSOLE_WIDTH - text.length()) / 2;
    for (int i = 0; i < spaces; ++i) {
        cout << " ";
    }
    cout << text;
}

void displayProducts(const vector<Product>& products) {
    centerText("--- AVAILABLE PRODUCTS ---\n");
    for (size_t i = 0; i < products.size(); i++) {
        string productInfo = to_string(i + 1) + ". " + products[i].name + " - Price: " + to_string(static_cast<int>(products[i].price)) + " - Stock: " + to_string(products[i].stock);
        centerText(productInfo + "\n");
    }
}

void buyDisplayProducts (const vector<Product>& buyPrices){
    centerText("-- PRODUCTS TO BUY --\n");
    for (size_t i = 0; i < buyPrices.size(); i++){
        string buyProductInfo = to_string(i + 1) + ". " + buyPrices[i].name + " - Price: " + to_string(static_cast<int>(buyPrices[i].price));
        centerText(buyProductInfo + "\n");
    }
}

void sellProducts (vector <Product>& products, double& totalSales, double& balance){

    int sellChoice, sellQuantity;
    double saleAmount;
    displayProducts (products);
    centerText("Enter product number (or 0 to exit): ");
    cin >> sellChoice;

    if (sellChoice == 0) {
        return;
    }

    if (sellChoice < 1 || sellChoice > products.size()){
        centerText("Invalid product choice\n");
        return;
    }

    Product& selectedProduct = products[sellChoice - 1];

    centerText("Enter quantity: ");
    cin >> sellQuantity;

    if (sellQuantity <= 0){
        centerText("Invalid quantity amount\n");
    }
    else if (sellQuantity > selectedProduct.stock){
        centerText("Not enough stock available\n");
    }
    else {
        centerText("Selected product price: " + to_string(static_cast<int>(selectedProduct.price)) + "\n");


        selectedProduct.stock -= sellQuantity;
        saleAmount = sellQuantity * selectedProduct.price;
        totalSales += saleAmount;
        balance += saleAmount;
        centerText("Sold " + to_string(sellQuantity) + " of " + products[sellChoice - 1].name + " for " + to_string(static_cast<int>(saleAmount)) + "\n");

        Order product = {selectedProduct.name, sellQuantity, saleAmount};
        sellHistory.push_back(product);
    }
}

void buyProducts (vector <Product>& products, double& balance, const vector <Product>& buyPrices){

    int buyChoice, buyQuantity;
    double buySaleAmount;
    buyDisplayProducts (buyPrices);
    centerText("Enter product number (or 0 to exit): ");
    cin >> buyChoice;

    if (buyChoice == 0) {
        return;
    }

    if (buyChoice < 1 || buyChoice > buyPrices.size()){
        centerText("Invalid product choice\n");
        return;
    }

    Product& selectedProduct = products[buyChoice - 1];

    centerText("Enter quantity: ");
    cin >> buyQuantity;

    if (buyQuantity < 1){
        centerText("Invalid quantity amount\n");
    }
    else{
        buySaleAmount = buyPrices[buyChoice - 1].price * buyQuantity;

        if (balance < buySaleAmount) {
            centerText("Insufficient balance to complete the purchase\n");
            return;
        }

        balance -= buySaleAmount;
        selectedProduct.stock += buyQuantity;

        Order order = {selectedProduct.name, buyQuantity, buySaleAmount};
        buyHistory.push_back(order);

        centerText("You have purchased " + to_string(buyQuantity) + " " + selectedProduct.name + "(s) for " + to_string(static_cast<int>(buySaleAmount)) + ".\n");
        
        centerText("Your current balance is " + to_string(static_cast<int>(balance)) +".\n");
    }
}

void salesHistory (double& totalSales){
    centerText("-- TOTAL SALES --\n");
    centerText(to_string(static_cast<int>(totalSales)) + "\n");

}

void showHistory (const vector <Order>& v_showHistory) {
    for (size_t i = 0; i < v_showHistory.size(); i++) {
        // cout << "Product: " << v_showHistory[i].productName
        //      << " - Quantity: " << v_showHistory[i].quantity
        //      << " - Total Price: " << v_showHistory[i].totalPrice << "\n";

        centerText("Product: " + v_showHistory[i].productName + " - Quantity: " + to_string(v_showHistory[i].quantity) + " - Total Price: " + to_string(static_cast<int>(v_showHistory[i].totalPrice)) + "\n");
    }
}