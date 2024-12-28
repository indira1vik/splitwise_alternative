#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

// Struct for Product
struct Product {
    string name;
    double price;
    double finalPrice;
};

// Struct for Roommate
struct Roommate {
    string name;
    double amount = 0;
};

// Roommate details
map<int, Roommate> roommates = {
    {1, {"Indira"}}, {2, {"Kavin"}}, {3, {"Srinath"}}, {4, {"Viswa"}}, {5, {"Nijanth"}}
};


// Function to calculate the weighted split for additional charges
void calculateWeightedPrices(vector<Product>& products, double totalSum, double tax, double offer, double tip, double delivery) {
    for (auto& product : products) {
        double weightage = product.price / totalSum;
        double deliveryShare = weightage * delivery;
        double taxShare = weightage * tax;
        double tipShare = weightage * tip;
        double offerShare = weightage * offer;
        product.finalPrice = product.price - offerShare + deliveryShare + taxShare + tipShare;
    }
}

// Function to split product prices among roommates
void splitProductPrices(vector<Product>& products, map<int, Roommate>& roommates) {
    for (const auto& product : products) {
        int splitAmong;
        cout << product.name << " - $" << product.finalPrice << "\nEnter number of roommates to split among: ";
        cin >> splitAmong;

        double share = product.finalPrice / splitAmong;
        if (splitAmong == roommates.size()) {
            for (auto it = roommates.begin(); it != roommates.end(); ++it) {
                it->second.amount += share;
            }
        } else {
            cout << "Select roommates by ID:\n";
            for (auto it = roommates.begin(); it != roommates.end(); ++it) {
                cout << "(" << it->first << ") " << it->second.name << " ";
            }
            cout << endl;
            for (int i = 0; i < splitAmong; i++) {
                int roommateID;
                cin >> roommateID;
                roommates[roommateID].amount += share;
            }
        }
        cout << endl;
    }
}

int main() {
    cout << "-----------------------------------------\n";
    int items;
    cout << "Enter number of items: ";
    cin >> items;

    double tax, offer, tip, delivery;
    cout << "Enter final tax amount: ";
    cin >> tax;
    cout << "Enter any offer amount applied: ";
    cin >> offer;
    cout << "Enter tip amount: ";
    cin >> tip;
    cout << "Enter delivery charges: ";
    cin >> delivery;
    cout << "-----------------------------------------\n";

    vector<Product> products;
    double totalSum = 0;

    for (int i = 0; i < items; i++) {
        Product product;
        product.finalPrice = 0;

        cout << "Enter product name: ";
        cin.ignore();
        getline(cin, product.name);

        cout << "Enter product price: ";
        cin >> product.price;
        cout << endl;

        products.push_back(product);
        totalSum += product.price;
    }
    cout << "-----------------------------------------\n";

    // Calculate weighted prices
    calculateWeightedPrices(products, totalSum, tax, offer, tip, delivery);

    // Display final prices for each product
    for (const auto& product : products) {
        cout << product.name << " (Original Price) = $" << product.price
             << ", (Final Price) = $" << product.finalPrice << endl;
    }
    cout << "-----------------------------------------\n";

    // Split product prices among roommates
    splitProductPrices(products, roommates);
    cout << "-----------------------------------------\n";

    // Display total amount for each roommate
    double totalPaid = 0;
    for (auto it = roommates.begin(); it != roommates.end(); ++it) {
        cout << it->second.name << " owes: $" << it->second.amount << endl;
        totalPaid += it->second.amount;
    }
    cout << "-----------------------------------------\n";

    cout << "Total amount spent: $" << totalPaid << endl;
    cout << "-----------------------------------------\n";
    
    return 0;
}