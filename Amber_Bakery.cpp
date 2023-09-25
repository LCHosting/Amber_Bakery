#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

// Define a structure for bakery items
struct BakeryItem {
	std::string name;
	std::string category;
	double price = 10;
	int qty = 1;
};
//FileName
const std::string filename = "items.txt";
//Cache Variable
std::vector<BakeryItem> bakerycache;

// Function to display the main menu
void displayMenu() {
	cout << "\nAmber Bakery Automated Billing System\n";
	cout << "1. View Bakery Items\n";
	cout << "2. Add Bakery Items\n";
	cout << "3. Manage Item Packages\n";
	cout << "4. Manage Sales Details\n";
	cout << "5. View Company Details\n";
	cout << "6. Logout\n";
	cout << "7. Exit\n";
	cout << "Enter your choice: ";
}

//Save Data In to TXT
void SaveDataTxt(const std::vector<BakeryItem>& bakerycache) {
	std::ofstream outFile(filename);
	if (outFile.is_open()) {
		for (const BakeryItem& item : bakerycache)
		{
			outFile << "Name: " <<  item.name << ", Category: " << item.category << ", Price: " << item.price << ", QTY: " << item.qty << "\n";

		}
		outFile.close();
		std::cout << "Bakery Items Saved to " << filename << ". \n";
	}
	else
	{
		std::cerr << "Unable to Open file for writing. \n";
	}
}

//Read Data 
void ReadDataTxt() {
	std::string line;
	ifstream file(filename);
	cout << "\n";
	while (getline(file, line)) {
		cout << line << "\n";	
	}
	file.close();
}

//Exit System
void ExitSystem() {
	cout << "Exiting the Amber Bakery Automated Billing System.\n";
	exit(0);
}

//ManageSalesDetails
void ManageSales() {
	int getchoice;
	cout << "1. View Sales Details\n";
	cout << "2. Go Back\n";
	cout << "3. Exit\n";
	cin >> getchoice;

	switch (getchoice)
	{
	case 1:
		cout << "Sales Details\n";
		cout << "--------------------------\n";
		cout << "Sales: 2000 Items\n";
		cout << "Profit: 25000LKR\n";
		cout << "--------------------------\n";
		break;
	case 2:
		break;
	case 3:
		ExitSystem();
	default:
		std::cout << "Invalid choice. Please try again.\n";
		break;
	}
}
//Define a structure for User 
struct User {
	std::string username;
	std::string password;
};

//View Company Details
void ViewCompanyDetails() {
	int getchoice;
	cout << "Company Details\n";
	cout << "--------------------------\n";
	cout << "Name: Amber Bakery\n";
	cout << "Location: UK\n";
	cout << "About: We offer different kinds of cakes, desserts, breads, cookies like delicious bakery products and other wonderful items\n";
	cout << "--------------------------\n";
	cout << "1. Go Back\n";
	cout << "2. Exit\n";
	cin >> getchoice;

	switch (getchoice)
	{
	case 1:
		break;
	case 2:
		ExitSystem();
	default:
		std::cout << "Invalid choice. Please try again.\n";
		break;
	}

}

//Function to display available bakery item details 
void displayBakeryItems() {
	std::cout << "Available Bakery Items:\n";
	ReadDataTxt();
}

// Function to add a new bakery item
void addBakeryItem(std::vector<BakeryItem>& bakerycache) {
	BakeryItem newItem;
	std::cout << "Enter Item name: ";
	std::cin >> newItem.name;
	std::cout << "Enter Item category: ";
	std::cin >> newItem.category;
	std::cout << "Enter Item Price: ";
	std::cin >> newItem.price;
	std::cout << "Enter Item Qty: ";
	std::cin >> newItem.qty;
	//items.push_back(newItem);
	bakerycache.push_back(newItem);

	SaveDataTxt(bakerycache);

	std::cout << "Item Added and System Updated Successfully. \n";

}

bool loggedIn = false;
void login() {
	//Define Username And Password (Replace with a  proper authentication system)
	std::string correctUsername = "admin";
	std::string correctPassword = "123";
	string username, password;
	User currentUser;
	cout << "Welcome To the Amber Bakery Login System!\n";
	cout << "Username: ";
	cin >> currentUser.username;
	cout << "Password: ";
	cin >> currentUser.password;
	//Check if the provided username and password match the correct ones
	if (currentUser.username == correctUsername && currentUser.password == correctPassword) {
		cout << "Login Successfull. Welcome, " << currentUser.username << "!\n";
		loggedIn = true;
	}
	else
	{
		loggedIn = false;
		cout << "Login Failed. Please Check your username and password\n";
		login();
	}

}

//User Logout
void logout() {
	bool loggedIn = false;
	cout << "Logged out.\n";
	login();
}



// Function to remove a bakery item by name from a text file
void removeBakeryItemByName(const std::string& itemName) {
	std::ifstream inFile(filename);
	bool found = false;

	if (!inFile.is_open()) {
		std::cerr << "Unable to open file for reading.\n";
		return;
	}

	BakeryItem item;
	while (inFile >> item.name) {
		if (item.name == itemName) {
			bakerycache.push_back(item);
		}
		else {
			found = true;
		}
	}

	inFile.close();

	if (!found) {
		std::cout << "Item not found in the file.\n";
		return;
	}

	std::ofstream outFile(filename);
	if (!outFile.is_open()) {
		std::cerr << "Unable to open file for writing.\n";
		return;
	}

	for (const BakeryItem& newItem : bakerycache) {
		outFile << newItem.name << " " << newItem.category << " " << newItem.price << " " << newItem.qty << "\n";
	}

	outFile.close();

	std::cout << "Item removed successfully.\n";
	return;
}

//Function to ManageBakeryItem
void ManageBakeryItem(std::vector<BakeryItem> bakerycache) {
	int getchoice;
	cout << "1. Remove Items\n";
	cout << "2. Go Back\n";
	cout << "3. Exit\n";
	std::cout << "Enter Your Choice: ";
	cin >> getchoice;
	std::string itemName;
	switch (getchoice)
	{
	case 1:
		std::cout << "Enter Item Name: ";
		cin >> itemName;
		removeBakeryItemByName(itemName);
		break;
	case 2:
		break;
	case 3:
		ExitSystem();
	default:
		std::cout << "Invalid choice. Please try again.\n";
		ManageBakeryItem(bakerycache);
	}
}

int main() {
	std::vector<BakeryItem> bakerycache;
	while (true) {
		if (loggedIn == true) {
			//std::vector<SalesTransaction> salesTransactions;

			int choice;


			displayMenu();
			cin >> choice;

			switch (choice) {
			case 1:
				// View Bakery Items
				displayBakeryItems();
				break;
			case 2:
				// Add Bakery Items
				addBakeryItem(bakerycache);
				break;
			case 3:
				// Manage Item Packages
				ManageBakeryItem(bakerycache);
				break;
			case 4:
				// Manage Sales Details
				ManageSales();
				break;
			case 5:
				// View Company Details
				ViewCompanyDetails();
				break;
			case 6:
				// Logout
				logout();
				break;
			case 7:
				// Exit the program
				ExitSystem();
				break;
			default:
				cout << "Invalid choice. Please try again.\n";
			}
		}
		else
		{
			login();
		}
	}
	return 0;
}