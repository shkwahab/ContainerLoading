#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Structure to represent a tile
struct Tile
{
    int width;
    int length;
    int height;
    int value;
};


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

int main()
{
   
    int maxValue;
   
    vector<Tile> tiles = {{2, 2, 2, 20}, {2, 1, 2, 40}, {1, 1, 1, 50}, {1, 1, 1, 50}};
    int containerWidth = 4, containerLength = 4, containerHeight = 4, minContainerWidth = 2, minContainerLength = 2, minContainerHeight = 2;
    vector<vector<vector<vector<int>>>> dp;
    maxValue = containerLoading(tiles, containerWidth, containerLength, containerHeight, minContainerWidth, minContainerLength, minContainerHeight);
    cout << "Maximum value of tiles that can be stacked in the container: " << maxValue << endl;
   
    return 0;
}