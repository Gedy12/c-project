#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Product class
class Product {
public:
    // Constructor
    Product(string n, double p, int q) {
        name = n;
        price = p;
        quantity = q;
    }

    // Getter methods
    string getName() const {
        return name;
    }

    double getPrice() const {
        return price;
    }

    int getQuantity() const {
        return quantity;
    }

    // Setter methods
    void setPrice(double p) {
        price = p;
    }

    void setQuantity(int q) {
        quantity = q;
    }

private:
    string name;
    double price;
    int quantity;
};

// User class
class User {
public:
    // Constructor
    User(string u, string p) {
        username = u;
        password = p;
    }

    // Getter methods
    string getUsername() const {
        return username;
    }

    string getPassword() const {
        return password;
    }

private:
    string username;
    string password;
};

// Admin class
class Admin {
public:
    // Constructor
    Admin(string u, string p) {
        username = u;
        password = p;
    }

    // Getter methods
    string getUsername() const {
        return username;
    }

    string getPassword() const {
        return password;
    }

private:
    string username;
    string password;
};

// Online shopping system class
class OnlineShoppingSystem {
public:
    // Constructor
    OnlineShoppingSystem() {
        // Add products to the inventory
        inventory.push_back(Product("Hand Sanitizer", 30, 20));
        inventory.push_back(Product("Face Mask", 10, 30));
        inventory.push_back(Product("Soft", 10, 50));
        inventory.push_back(Product("Pasta", 25, 40));
        inventory.push_back(Product("Socks", 50, 30));
        inventory.push_back(Product("Mango Juice", 35, 60));
        inventory.push_back(Product("Eggs", 12, 100));
        inventory.push_back(Product("Milk", 60, 30));
        inventory.push_back(Product("Sugar 1K", 60, 100));
        inventory.push_back(Product("Water 1L", 20, 55));

        // Add administrators to the list
        admins.push_back(Admin("admin", "password"));

        // Open the output file stream for transaction details
        transactionFile.open("transactions.txt");

        // Open the output file stream for remaining products
        remainingFile.open("remaining.txt");
    }

    // Destructor
    ~OnlineShoppingSystem() {
        // Close the output file streams
        transactionFile.close();
        remainingFile.close();
    }

    // Function to display the list of products
    void displayProducts() {
        cout << "List of products:" << endl;
        for (int i = 0; i < inventory.size(); i++) {
            Product product = inventory[i];
            cout << i + 1 << ". " << product.getName() << " (Price: " << product.getPrice() << ", Quantity: " << product.getQuantity() << ")" << endl;
        }
    }

    // Function to allow administrators to add new products to the inventory
    void addProduct() {
        string name;
        double price;
        int quantity;

        cout << "Enter name of the product: ";
        cin >> name;

        cout << "Enter price of the product: ";
        cin >> price;

        cout << "Enter quantity of the product: ";
        cin >> quantity;

        Product product(name, price, quantity);
        inventory.push_back(product);

        cout << "Product added successfully!" << endl;
    }

    // Function to allow administrators to remove products from the inventory
    void removeProduct() {
        displayProducts();

        int index;
        cout << "Enter the number of the product you want to remove: ";
        cin >> index;

        if (index <= 0 || index > inventory.size()) {
            cout << "Invalid product number." << endl;
            return;
        }

        inventory.erase(inventory.begin() + index - 1);

        cout << "Product removed successfully!" << endl;
    }
    // Function to allow administrators to update the price of a product in the inventory
    void updateProductPrice() {
        displayProducts();

        int index;
        cout << "Enter the number of the product you want to update: ";
        cin >> index;

        if (index <= 0 || index > inventory.size()) {
            cout << "Invalid product number." << endl;
            return;
        }

        double price;
        cout<< "Enter the new price of the product: ";
        cin >> price;

        inventory[index - 1].setPrice(price);

        cout << "Product price updated successfully!" << endl;
    }

    // Function to allow administrators to update the quantity of a product in the inventory
    void updateProductQuantity() {
        displayProducts();

        int index;
        cout << "Enter the number of the product you want to update: ";
        cin >> index;

        if (index <= 0 || index > inventory.size()) {
            cout << "Invalid product number." << endl;
            return;
        }

        int quantity;
        cout<< "Enter the new quantity of the product: ";
        cin >> quantity;

        inventory[index - 1].setQuantity(quantity);

        cout << "Product quantity updated successfully!" << endl;
    }

    // Function to allow administrators to view the total transactions
    void viewTransactions() {
        // Print the contents of the transaction file
        ifstream file("transactions.txt");
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }

    // Function to allow users to register
    void registerUser() {
        string username;
        string password;

        cout << "Enter username: ";
        cin >> username;

        cout << "Enter password: ";
        cin >> password;

        User user(username, password);
        users.push_back(user);

        cout << "User registration successful!" << endl;
    }

    // Function to allow administrators to register
    void registerAdmin() {
        string username;
        string password;

        cout << "Enter username: ";
        cin >> username;

        cout << "Enter password: ";
        cin >> password;

        Admin admin(username, password);
        admins.push_back(admin);

        cout << "Admin registration successful!" << endl;
    }

    // Function to allow administrators to log in
    bool adminLogin() {
        string username;
        string password;

        cout << "Enter username: ";
        cin >> username;

        cout << "Enter password: ";
        cin >> password;

        // Check if the entered credentials match with any of the administrators
        for (int i = 0; i < admins.size(); i++) {
            if (admins[i].getUsername() == username && admins[i].getPassword() == password) {
                return true;
            }
        }

        cout << "Invalid username or password." << endl;
        return false;
    }

    // Function to allow users to log in
    bool userLogin() {
        string username;
        string password;

        cout << "Enter username: ";
        cin >> username;

        cout << "Enter password: ";
        cin >> password;

        // Check if the entered credentials match with any of the users
        for (int i = 0; i < users.size(); i++) {
            if (users[i].getUsername() == username && users[i].getPassword() == password) {
                currentUserIndex = i;
                return true;
            }
        }

        cout << "Invalid username or password." << endl;
        return false;
    }

    // Function to allow a user to make a transaction
    void makeTransaction() {
    bool continueTransaction = true;
    while (continueTransaction) {
        displayProducts();
        int index;
        cout << "Enter the number of the product you want to buy: ";
        cin >> index;

        if (index <= 0 || index > inventory.size()) {
            cout << "Invalid product number." << endl;
            return;
        }

        int quantity;
        cout << "Enter the quantity you want to buy: ";
        cin >> quantity;

        Product product = inventory[index - 1];

        if (product.getQuantity() < quantity) {
            cout << "Insufficient quantity." << endl;
            return;
        }

        double totalPrice = product.getPrice() * quantity;

        inventory[index - 1].setQuantity(product.getQuantity() - quantity);

        // Write the transaction details to the transaction file.
        transactionFile << "User: " << users[currentUserIndex].getUsername() 
                        << ", Product: " << product.getName() 
                        << ", Quantity: " << quantity 
                        << ", Total Price: " << totalPrice 
                        << endl;

        // Write the remaining products to the remaining file.
        ofstream remainingFile("remaining.txt");
        
        for (int i = 0; i < inventory.size(); i++) {
            remainingFile << inventory[i].getName() 
                          << "," 
                          << inventory[i].getPrice() 
                          << "," 
                          << inventory[i].getQuantity() 
                          << endl;
         }
         
         remainingFile.close();

         cout <<"Total price is "<<totalPrice<<endl;

         char choice;
         cout<<"Do you want to make another transaction? (Y/N): ";
         cin>>choice;

         if(choice=='N'||choice=='n'){
             continueTransaction=false;
             break;
         }
    }

    cout <<"Transaction successful!"<<endl;    
    }

    // Function to run the online shopping system
    void run() {
        while (true) {
            // Display the main menu
            cout << endl;
            cout << "Main Menu" << endl;
            cout << "1. Display Products" << endl;
            cout << "2. Admin Registration" << endl;
            cout << "3. User Registration" << endl;
            cout << "4. Admin Login" << endl;
            cout << "5. User Login" << endl;
            cout <<  "6.Exit" << endl;

            int choice;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    displayProducts();
                    break;
                case 2:
                    registerAdmin();
                    break;
                case 3:
                    registerUser();
                    break;
                case 4:
                    if (adminLogin()) {
                        // Display the admin menu
                        cout << endl;
                        cout << "Admin Menu" << endl;
                        cout << "1. Add Product" << endl;
                        cout << "2. Remove Product" << endl;
                        cout << "3. Update Product Price" << endl;
                        cout << "4. Update Product Quantity" << endl;
                        cout << "5. View Transactions" << endl;
                        cout << "6. Logout" << endl;

                        int adminChoice;
                        cout << "Enter your choice: ";
                        cin >> adminChoice;

                        switch (adminChoice) {
                            case 1:
                                addProduct();
                                break;
                            case 2:
                                removeProduct();
                                break;
                            case 3:
                                updateProductPrice();
                                break;
                            case 4:
                                updateProductQuantity();
                                break;
                            case 5:
                                viewTransactions();
                                break;
                            case 6:
                                cout << "Logged out successfully!" << endl;
                                break;
                            default:
                                cout << "Invalid choice." << endl;
                                break;
                        }
                    }
                    break;
                case 5:
                    if (userLogin()) {
                        // Display the user menu
                        cout << endl;
                        cout << "User Menu" << endl;
                        cout << "1. Make a Transaction" << endl;
                        cout << "2. Logout" << endl;
                        int userChoice;
                        cout << "Enter your choice: ";
                        cin >> userChoice;

                        switch (userChoice) {
                            case 1:
                                makeTransaction();
                                break;
                            case 2:
                                cout << "Logged out successfully!" << endl;
                                break;
                            default:
                                cout << "Invalid choice." << endl;
                                break;
                        }
                    }
                    break;
                case 6:
                    cout << "Thank you for using the online shopping system!" << endl;
                    return;
                default:
                    cout << "Invalid choice." << endl;
                    break;
            }
        }
    }

private:
    vector<Product> inventory;
    vector<User> users;
    vector<Admin> admins;
    int currentUserIndex;
    ofstream transactionFile;
    ofstream remainingFile;
};

int main() {
    OnlineShoppingSystem system;
    system.run();
    return 0;
}