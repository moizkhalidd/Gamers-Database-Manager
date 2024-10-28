#include <iostream>
using namespace std;
struct GamesPlayed 
{
    string gameID;
    float hoursPlayed;
    int achievementsUnlocked;

    GamesPlayed(string id, float hours, int achievements)
    {
       gameID = id;
       hoursPlayed = hours;
       achievementsUnlocked = achievements; 
    }
        
};

struct Game 
{
    int gameID;
    string gameName;
    Game *left = nullptr, *right = nullptr;

    Game(int id, string name) 
    {
       gameID = id; 
       gameName = name; 
    }
};

struct Player 
{
    int playerID;
    string playerName;
    string phoneNumber;
    string email;
    string password;
    Player *left = nullptr, *right= nullptr;
    GamesPlayed *gamesHead = nullptr;

    Player(int id, string name, string phone, string mail, string pass)
    {
       playerID = id; 
       playerName = name;
       phoneNumber = phone; 
       email = mail; 
       password = pass;
    }
        
    void addGame(string gameID, float hours, int achievements) 
    {
        GamesPlayed *newGame = new GamesPlayed(gameID, hours, achievements);
        gamesHead = newGame;
    }
};
int main()
{

  return 0;
}
