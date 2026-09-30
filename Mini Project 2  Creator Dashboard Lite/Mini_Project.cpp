#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Content class
class Content
{
public:
    string title;
    string platform;
    int views;
    string status;
	
    // Display all details
    void display()
    {
        cout << "Title: " << title << endl;
        cout << "Platform: " << platform << endl;
        cout << "Views: " << views << endl;
        cout << "Status: " << status << endl;
    }
};

// Add new content
void addContent()
{
    Content c;

    cout << "\nEnter Title: ";
    cin.ignore();
    getline(cin, c.title);

    cout << "Enter Platform: ";
    getline(cin, c.platform);

    cout << "Enter Views: ";
    cin >> c.views;

    cout << "Enter Status: ";
    cin.ignore();
    getline(cin, c.status);

    // Open file in append mode
    ofstream file("content_list.txt", ios::app);

    file << c.title << endl;
    file << c.platform << endl;
    file << c.views << endl;
    file << c.status << endl;

    file.close();

    cout << "\nContent added successfully!\n";
}

// Display all content
void showContent()
{
    ifstream file("content_list.txt");

    Content c;
    int number = 1;

    cout << "\n========== CONTENT LIST ==========\n";

    while (getline(file, c.title))
    {
        getline(file, c.platform);
        file >> c.views;
        file.ignore();
        getline(file, c.status);

        cout << number << ". "
             << c.title << " - "
             << c.platform << endl;

        number++;
    }

    file.close();

    if (number == 1)
    {
        cout << "No content found.\n";
    }
}

// Update status
void updateStatus()
{
    int choice;
    int number = 1;

    string newStatus;

    cout << "\n";
    showContent();

    cout << "\nEnter content number to update: ";
    cin >> choice;

    cout << "Enter new status: ";
    cin.ignore();
    getline(cin, newStatus);

    // Open old file
    ifstream file("content_list.txt");

    // Temporary file
    ofstream temp("temp.txt");

    Content c;

    while (getline(file, c.title))
    {
        getline(file, c.platform);
        file >> c.views;
        file.ignore();
        getline(file, c.status);

        if (number == choice)
        {
            c.status = newStatus;
        }

        temp << c.title << endl;
        temp << c.platform << endl;
        temp << c.views << endl;
        temp << c.status << endl;

        number++;
    }

    file.close();
    temp.close();

    // Replace old file with new file
    remove("content_list.txt");
    rename("temp.txt", "content_list.txt");

    cout << "\nStatus updated successfully!\n";
}

// Delete content
void deleteContent()
{
    int choice;
    int number = 1;

    cout << "\n";
    showContent();

    cout << "\nEnter content number to delete: ";
    cin >> choice;

    ifstream file("content_list.txt");
    ofstream temp("temp.txt");

    Content c;

    while (getline(file, c.title))
    {
        getline(file, c.platform);
        file >> c.views;
        file.ignore();
        getline(file, c.status);

        // Write everything except selected content
        if (number != choice)
        {
            temp << c.title << endl;
            temp << c.platform << endl;
            temp << c.views << endl;
            temp << c.status << endl;
        }

        number++;
    }

    file.close();
    temp.close();

    remove("content_list.txt");
    rename("temp.txt", "content_list.txt");

    cout << "\nContent deleted successfully!\n";

    cout << "\nUpdated Content List:\n";
    showContent();
}

int main()
{
    int choice;

    do
    {
        cout << "\n================================\n";
        cout << "     CREATOR DASHBOARD LITE\n";
        cout << "================================\n";
        cout << "1. Add Content\n";
        cout << "2. View Content\n";
        cout << "3. Update Status\n";
        cout << "4. Delete Content\n";
        cout << "5. Exit\n";
        cout << "================================\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addContent();
            break;

        case 2:
            showContent();
            break;

        case 3:
            updateStatus();
            break;

        case 4:
            deleteContent();
            break;

        case 5:
            cout << "\nThank you!\n";
            break;

        default:
            cout << "\nInvalid choice!\n";
        }

    } while (choice != 5);

    return 0;
}