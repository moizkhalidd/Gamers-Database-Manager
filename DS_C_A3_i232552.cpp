#include <iostream>
using namespace std;
struct GamesPlayed 
{
    string gameID;
    float hoursPlayed;
    int achievementsUnlocked;
    GamesPlayed *next = nullptr;

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
    string developer;
    string publisher;
    float fileSize;
    int copiesSold;
    Game *left = nullptr, *right = nullptr;

    Game(int id, string name, string dev, string pub, float size, int sold) 
    {
       gameID = id; 
       gameName = name;
       developer = dev;
       publisher = pub;
       fileSize = size;
       copiesSold = sold;
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
        newGame -> next = gamesHead;
        gamesHead = newGame;
    }
};
class DatabasePlayer  
{
  private:
    Player *playerRoot = nullptr;
    
    int generateSeed(string &rollNumber) 
    {
      int seed = 0;
      for (int i = 0; i < rollNumber.length(); ++i) 
      {
        char ch = rollNumber[i];
        if (ch >= '0' && ch <= '9') 
        {
            seed = seed * 10 + (ch - '0');
        }
      }

      return seed;
    }  
    
    
    Player* searchPlayer(Player* root, int id) 
    {
        if (!root || root->playerID == id) 
        return root;
        
        if (id < root->playerID) 
        return searchPlayer(root->left, id);
        
        return searchPlayer(root->right, id);
    }
    
    Player* insertPlayerHelper(Player* root, int id, string name, string phone, string email, string password) 
    {
        if (!root) 
        return new Player(id, name, phone, email, password);
        
        if (id < root->playerID) 
        root->left = insertPlayerHelper(root->left, id, name, phone, email, password);
        else if (id > root->playerID) 
        root->right = insertPlayerHelper(root->right, id, name, phone, email, password);
        
        return root;
    }

    Player* minValueNode(Player* node) 
    {
        Player* current = node;
        while (current && current->left) 
        current = current->left;
        
        return current;
    }

    Player* deletePlayerHelper(Player* root, int id) 
    {
        if (!root) 
        return nullptr;

        if (id < root->playerID) 
        {
            root->left = deletePlayerHelper(root->left, id);
        } 
        else if (id > root->playerID) 
        {
            root->right = deletePlayerHelper(root->right, id);
        } 
        else 
        {
            if (!root->left) 
            {
                Player* temp = root->right;
                delete root;
                return temp;
            } 
            else if (!root->right) 
            {
                Player* temp = root->left;
                delete root;
                return temp;
            }

            Player* temp = minValueNode(root->right);
            root->playerID = temp->playerID;
            root->playerName = temp->playerName;
            root->phoneNumber = temp->phoneNumber;
            root->email = temp->email;
            root->password = temp->password;

            root->right = deletePlayerHelper(root->right, temp->playerID);
        }
        return root;
    }
    
    
    public: 
    
    void insertPlayer(int id, string name, string phone, string email, string password) 
    {
        if (searchPlayer(playerRoot, id) != nullptr) 
        {
            cout << "Error: Player with ID " << id << " already exists.\n";
            return;
        }
        
        playerRoot = insertPlayerHelper(playerRoot, id, name, phone, email, password);
        cout << "Inserted player with ID: " << id << endl;
    }
    
 
     void searchPlayer(int id) 
     {
        if (searchPlayer(playerRoot, id) == nullptr) 
        {
            cout << "Error: Game with ID " << id << " does not exists.\n";
            return;
        }
        
        Player* player = searchPlayer(playerRoot, id);
        cout<<"Found \n";    
        return;
     }

   
     void deletePlayer(int id) 
     {
        playerRoot = deletePlayerHelper(playerRoot, id);
     }
     
    int showLayerNumber(Player* root, int id) 
    {
       int layer = 1;
       while (root) 
       {
          if (root->playerID == id) 
          return layer;

          root = (id < root->playerID) ? root->left : root->right;
          layer++;
       }
       cout << "Player with ID " << id << " does not exist.\n";
       return -1;
    }

    bool showPath(Player* root, int id) 
    {
      if (!root) 
      return false;

      cout << root->playerID << " ";  
      if (root->playerID == id) 
      return true;

      if (id < root->playerID) 
      {
         if (showPath(root->left, id)) 
         return true;
      } 
      else 
      {
         if (showPath(root->right, id)) 
         return true;
      }
      return false;
    }

    void showDetails(Player* player) 
    {
      if (!player) 
      {
         cout << "Player not found.\n";
         return;
      }

      cout << "Player ID: " << player->playerID << endl;
      cout << "Name: " << player->playerName << endl;
      cout << "Phone: " << player->phoneNumber << endl;
      cout << "Email: " << player->email << endl;

      GamesPlayed* game = player->gamesHead;
      cout << "Games Played:\n";
      while (game) 
      {
          cout << "- Game ID: " << game->gameID
               << ", Hours Played: " << game->hoursPlayed
               << ", Achievements Unlocked: " << game->achievementsUnlocked << endl;
          game = game->next;
      }
    }
};
class DatabaseGame
{
   private:

    Game *gameRoot = nullptr;
    
    int generateSeed(string &rollNumber) 
    {
      int seed = 0;
      for (int i = 0; i < rollNumber.length(); ++i) 
      {
        char ch = rollNumber[i];
        if (ch >= '0' && ch <= '9') 
        {
            seed = seed * 10 + (ch - '0');
        }
      }

      return seed;
    }  
    
    
    Game* searchGame(Game* root, int id) 
    {
        if (!root || root->gameID == id) 
        return root;
        
        if (id < root->gameID) 
        return searchGame(root->left, id);
        
        return searchGame(root->right, id);
    }
    
    
  
     Game* insertGameHelper(Game* root, int id, string name, string developer, string publisher, float size, int copiesSold) 
     {
        if (!root) 
        return new Game(id, name, developer, publisher, size, copiesSold);
        
        if (id < root->gameID) 
        root->left = insertGameHelper(root->left, id, name, developer, publisher, size, copiesSold);
        else if (id > root->gameID) 
        root->right = insertGameHelper(root->right, id, name, developer, publisher, size, copiesSold);
        
        return root;
    }
    

    Game* minValueNode(Game* node) 
    {
        Game* current = node;
        while (current && current->left) 
        current = current->left;
        
        return current;
    }
    
    
    Game* deleteGameHelper(Game* root, int id) 
    {
        if (!root) 
        return nullptr;

        if (id < root->gameID) 
        {
            root->left = deleteGameHelper(root->left, id);
        } 
        else if (id > root->gameID) 
        {
            root->right = deleteGameHelper(root->right, id);
        } 
        else 
        {
            if (!root->left) 
            {
                Game* temp = root->right;
                delete root;
                return temp;
            } 
            else if (!root->right) 
            {
                Game* temp = root->left;
                delete root;
                return temp;
            }

            Game* temp = minValueNode(root->right);
            root->gameID = temp->gameID;
            root->gameName = temp->gameName;
            root->developer = temp->developer;
            root->publisher = temp->publisher;
            root->fileSize = temp->fileSize;
            root->copiesSold = temp->copiesSold;

            root->right = deleteGameHelper(root->right, temp->gameID);
        }
        return root;
    }
    
   
    public: 
     
    void insertGame(int id, string name, string developer, string publisher, float size, int copiesSold) 
    {
        if (searchGame(gameRoot, id) != nullptr) 
        {
            cout << "Error: Game with ID " << id << " already exists.\n";
            return;
        }
        
        gameRoot = insertGameHelper(gameRoot, id, name, developer, publisher, size, copiesSold);
        cout << "Inserted game with ID: " << id << endl;
    }
    
     void searchGame(int id) 
     { 
        if (searchGame(gameRoot, id) == nullptr) 
        {
            cout << "Error: Game with ID " << id << " does not exists.\n";
            return;
        }
        
        Game* game = searchGame(gameRoot, id);
        cout<<"Found \n";    
        return;
     }

    void deleteGame(int id) 
    {
        gameRoot = deleteGameHelper(gameRoot, id);
    }
    
    int showLayerNumber(Game* root, int id) 
    {
       int layer = 1;
       while (root) 
       {
          if (root->gameID == id) 
          return layer;

          root = (id < root->gameID) ? root->left : root->right;
          layer++;
       }
       cout << "Game with ID " << id << " does not exist.\n";
       return -1;
    }
    
    
    bool showPath(Game* root, int id) 
    {
      if (!root) 
      return false;

      cout << root->gameID << " ";  
      if (root->gameID == id) 
      return true;

      if (id < root->gameID) 
      {
         if (showPath(root->left, id)) 
         return true;
      } 
      else 
      {
         if (showPath(root->right, id)) 
         return true;
      }
      return false;
    }
};
int main()
{

  return 0;
}
