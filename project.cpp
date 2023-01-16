#include <iostream>
#include <vector>
#include <algorithm>
#include <unistd.h> //for linux
// #include<windows.h> //windows
using namespace std;

// Registration

string u_name, u_password, confirm_password;

bool login()
{
    string name, password;
    int counter = 0;
    cout << " Enter the username:";
    cin >> name;
    cout << "Enter the password:";
    cin >> password;
    if (u_name == name && u_password == password)
    {
        return true;
    }
    else
    {
        cout << "Wrong Creditionals";
        cout << endl;
        return false;
    }
    return false;
}

void takeSignUp()
{
    cout << "Enter your username:";
    cin >> u_name;
    cout << "Enter your password:";
    cin >> u_password;
    cout << "Enter confirm password:";
    cin >> confirm_password;
}
void signup()
{
    takeSignUp();
    int counter = 0;
    if (u_password != confirm_password)
    {
        cout << "Password and Confirm Password doesn't match!\n";
        cout << "Retry" << endl;
        while (true)
        {
            if (counter == 3)
            {
                break;
            }
            if (counter == 1)
            {
                cout << "You have left one chance to type write password otherwise you will have to wait run the program again\n";
            }
            takeSignUp();
            counter++;
        }
    }
    else
    {
        cout << "Registered Successfully" << endl;
    }
}

// Structure to represent a tile
struct Tile
{
    int width;
    int length;
    int height;
    int value;
};

class ContainerLoading : public Tile
{
private:
public:
    ContainerLoading()
    {
        width = length = height = value = 0;
    }

    // Function to add tiles in the container
    void addTile(vector<Tile> &tiles, int width, int length, int height, int value)
    {
        Tile newTile;
        newTile.width = width;
        newTile.length = length;
        newTile.height = height;
        newTile.value = value;
        tiles.push_back(newTile);
    }

    // Function to validate the container size
    bool validateContainerSize(int containerWidth, int containerLength, int containerHeight, int minContainerWidth, int minContainerLength, int minContainerHeight)
    {
        if (containerWidth < minContainerWidth || containerLength < minContainerLength || containerHeight < minContainerHeight)
        {
            cout << "Container size is less than minimum required size. No tiles can be stacked." << endl;
            return false;
        }
        return true;
    }

    // Function to find the maximum value of tiles that can be stacked in a container
    int containerLoading(vector<Tile> &tiles, int containerWidth, int containerLength, int containerHeight, int minContainerWidth, int minContainerLength, int minContainerHeight)
    {
        if (!validateContainerSize(containerWidth, containerLength, containerHeight, minContainerWidth, minContainerLength, minContainerHeight))
        {
            return 0;
        }
        // Create a 4D array to store the results of subproblems
        vector<vector<vector<vector<int>>>> dp(tiles.size() + 1, vector<vector<vector<int>>>(containerWidth + 1, vector<vector<int>>(containerLength + 1, vector<int>(containerHeight + 1))));
        for (int i = 0; i <= tiles.size(); i++)
        {
            for (int w = 0; w <= containerWidth; w++)
            {
                for (int l = 0; l <= containerLength; l++)
                {
                    for (int h = 0; h <= containerHeight; h++)
                    {
                        dp[i][w][l][h] = 0;
                    }
                }
            }
        }

        // Fill in the dp array
        for (int i = 1; i <= tiles.size(); i++)
        {
            for (int w = 1; w <= containerWidth; w++)
            {
                for (int l = 1; l <= containerLength; l++)
                {
                    for (int h = 1; h <= containerHeight; h++)
                    {
                        if (tiles[i - 1].width <= w && tiles[i - 1].length <= l && tiles[i - 1].height <= h)
                        {
                            dp[i][w][l][h] = max(dp[i - 1][w][l][h], dp[i - 1][w - tiles[i - 1].width][l - tiles[i - 1].length][h - tiles[i - 1].height] + tiles[i - 1].value);
                        }
                        else
                        {
                            dp[i][w][l][h] = dp[i - 1][w][l][h];
                        }
                    }
                }
            }
        }

        int maxValue = dp[tiles.size()][containerWidth][containerLength][containerHeight];
        return maxValue;
    }
};

int main()
{
    ContainerLoading project;
    cout << "--------------------------------------------------------------------"
         << endl;
    cout << "\t\t\t"
         << "Container Loading\n"
         << "---------------------------------------------------------------------"
         << "\n\n";
    vector<Tile> tiles;
    int containerWidth, containerLength, containerHeight;
    int minContainerWidth, minContainerLength, minContainerHeight;
    int maxValue = 0;
    unsigned int microsecond = 1000000; // for linux
    usleep(2 * microsecond);            // sleeps for 3 second //for unix or linux
    //  Sleep(milliseconds); windows
    system("clear"); // for linux
    // system("cls")

    while (true)
    {
        cout << "⚠ To Use This Application You mush have to sign in" << endl;
        cout << endl
             << "Press 1 to Sign In" << endl
             << "Press 2 to Sign Up" << endl
             << "Press 3 to Exit" << endl;
        int option;
        cout << "Enter your choice:";
        cin >> option;
        if (option == 3)
        {
            break;
        }
        switch (option)
        {
        case 1:

            if (login() == 1)
            {
                system("clear"); // for linux
                // system("cls"); //for windows
                cout << "\n\t\t\t"
                     << "Welcome to my Project Container made by Suleiman Sani"
                     << "\n\n";
                int ch;
                while (true)
                {
                    cout << "Press 1 to Add the tile in the Container" << endl;
                    cout << "Press 2 to Choose the Container Size" << endl;
                    cout << "Press 3 to Choose the Minimum Container Size" << endl;
                    cout << "Press 4 to Optimize the Container Loading and Display the Maximum value of tiles that can be stacked in the container" << endl;
                    cout << "Press 5 to Back" << endl;
                    cout << endl;
                    cout << "Enter Your Choice:";
                    cin >> ch;
                    if (ch == 5)
                    {
                        break;
                    }
                    switch (ch)
                    {
                    case 1:
                        cout << endl;
                        int width, length, height, value;
                        cout << "Enter the width:";
                        cin >> width;
                        cout << "Enter the length:";
                        cin >> length;
                        cout << "Enter the height:";
                        cin >> height;
                        cout << "Enter the weight of the tile or value of the tile:";
                        cin >> value;
                        project.addTile(tiles, width, length, height, value);
                        break;

                    case 2:
                        cout << endl;
                        cout << "Enter the Container Width:";
                        cin >> containerWidth;
                        cout << "Enter the Container Length:";
                        cin >> containerLength;
                        cout << "Enter the Container Height:";
                        cin >> containerHeight;
                        break;
                    case 3:
                        cout << endl;
                        cout << "Enter the Minimum Container Width:";
                        cin >> minContainerWidth;
                        cout << "Enter the Minimum Container Length:";
                        cin >> minContainerLength;
                        cout << "Enter the Minimum Container Height:";
                        cin >> minContainerHeight;
                        break;
                    case 4:
                        cout << endl;
                        maxValue = project.containerLoading(tiles, containerWidth, containerLength, containerHeight, minContainerWidth, minContainerLength, minContainerHeight);
                        cout << "Maximum value of tiles that can be stacked in the container: " << maxValue << endl;
                        break;
                    default:
                        break;
                    }
                }
            }
            break;
        case 2:
            signup();
            break;
        case 3:
            break;
        default:
            cout << "Invalid option" << endl;
            break;
        }
    }

    return 0;
}