#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
//structure for gamesplayed node
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
//structure for game node
struct Game 
{
    string gameID;
    string gameName;
    string developer;
    string publisher;
    float fileSize;
    int copiesSold;
    Game *left = nullptr, *right = nullptr;

    Game(string id, string name, string dev, string pub, float size, int sold) 
    {
       gameID = id; 
       gameName = name;
       developer = dev;
       publisher = pub;
       fileSize = size;
       copiesSold = sold;
    }
};
//structure for player node
struct Player 
{
    string playerID;
    string playerName;
    string phoneNumber;
    string email;
    string password;
    Player *left = nullptr, *right= nullptr;
    GamesPlayed *gamesHead = nullptr;

    Player(string id, string name, string phone, string mail, string pass)
    {
       playerID = id; 
       playerName = name;
       phoneNumber = phone; 
       email = mail; 
       password = pass;
    }
    
    //function to add game to the game played list for the player 
    //needs fixing by creating a separate tree for games played
    void addGame(string gameID, float hours, int achievements) 
    {   
        if(searchGame(gameID) != nullptr)
        {
         cout<<"ID already exists"<<endl;
         return;
        }
        GamesPlayed *newGame = new GamesPlayed(gameID, hours, achievements);
        if(gamesHead == nullptr)
        gamesHead = newGame;
        else
        {
         GamesPlayed *temp = gamesHead;
         while(temp -> next!= nullptr)
         {
           temp = temp -> next;
         }       
          temp -> next = newGame;
        }
    }
    
    GamesPlayed* searchGame(string id) 
    {
        if (!gamesHead) 
        return gamesHead;
        
        GamesPlayed *temp = gamesHead;
        while(temp != nullptr)
        { 
          if(temp -> gameID == id)
          return temp;
          
          temp = temp -> next;
        }
        
        return temp;
    }
    
};
struct QueueNode {
    Player* treeNode;
    Game* treeNode2;
    int depth;
    QueueNode* next;

    QueueNode(Player* node, int dep) : treeNode(node), depth(dep), next(nullptr) {}
    QueueNode(Game* node, int dep) : treeNode2(node), depth(dep), next(nullptr) {}
};
class Queue {
    QueueNode* front;
    QueueNode* rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    bool isEmpty() {
        return front == nullptr;
    }

    void enqueue(Player* node, int depth) {
        QueueNode* newNode = new QueueNode(node, depth);
        if (rear) {
            rear->next = newNode;
        }
        rear = newNode;
        if (!front) {
            front = newNode;
        }
    }
    
    void enqueue(Game* node, int depth) {
        QueueNode* newNode = new QueueNode(node, depth);
        if (rear) {
            rear->next = newNode;
        }
        rear = newNode;
        if (!front) {
            front = newNode;
        }
    }

    QueueNode* dequeue() {
        if (isEmpty()) return nullptr;
        QueueNode* temp = front;
        front = front->next;
        if (!front) {
            rear = nullptr;
        }
        return temp;
    }
};
//BST for player 
class DatabasePlayer  
{
  private:
    Player *playerRoot = nullptr;
    int skipThreshold;
    
    public:
    //generating custom seed
    DatabasePlayer() 
    {
      // Calculate the skip threshold based on roll number
        int lastTwoDigits = 232552 % 100; 
        skipThreshold = (lastTwoDigits * 10) + 100;
        
        // Seed random number generator with roll number
        srand(232552);
    }  
    private:
    //function to search player in the tree
    Player* searchPlayer(Player* root, string id) 
    {
        if (!root || root->playerID == id) 
        return root;
        
        if (stringToInt(id) < stringToInt(root->playerID)) 
        return searchPlayer(root->left, id);
        
        return searchPlayer(root->right, id);
    }
    
    //function to add player in the tree
    Player* insertPlayerHelper(Player* root, string id, string name, string phone, string email, string password) 
    {
        if (!root)
        { 
          Player* player = new Player(id, name, phone, email, password);
          //string inp;
          //cout<<"Enter yes to add games played details"<<endl;
          //cin>> inp;
          //while(inp == "yes")
          //{
            //string ID;
            //float time;
            //int ach;
            //cout<<"Enter GameID"<<endl;
            //cin>>ID;
            //cout<<"Enter Hours Played"<<endl;
            //cin>>time;
            //cout<<"Enter Achievements"<<endl;
            //cin>>ach;
            //player -> addGame(ID,time,ach);
            //cout<<"Add more?"<<endl;
            //cin>> inp;
          //}
          return player;
        }
        if (stringToInt(id) < stringToInt(root->playerID)) 
        root->left = insertPlayerHelper(root->left, id, name, phone, email, password);
        else if (stringToInt(id) > stringToInt(root->playerID)) 
        root->right = insertPlayerHelper(root->right, id, name, phone, email, password);
        
        return root;
    }
    
    //function to find the minimum id node 
    Player* minValueNode(Player* node) 
    {
        Player* current = node;
        while (current && current->left) 
        current = current->left;
        
        return current;
    }
    
    //function to delete a node 
    Player* deletePlayerHelper(Player* root, string id) 
    {
        if (!root) 
        return nullptr;

        if (stringToInt(id) < stringToInt(root->playerID)) 
        {
            root->left = deletePlayerHelper(root->left, id);
        } 
        else if (stringToInt(id) > stringToInt(root->playerID)) 
        {
            root->right = deletePlayerHelper(root->right, id);
        } 
        else 
        {   
            //if one to zero child nodes are there
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
            
            //if node has 2 children
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
    
    //function to show layer number for the node
    int showLayerNumberHelper(Player* root, string id) 
    {
       int layer = 1;
       while (root) 
       {
          if (root->playerID == id) 
          return layer;

          root = (stringToInt(id) < stringToInt(root->playerID)) ? root->left : root->right;
          layer++;
       }
       cout << "\nPlayer with ID " << id << " does not exist.\n";
       return -1;
    }
    
    //function to print path to the node
    bool showPathHelper(Player* root, string id) 
    {
      if (!root) 
      return false;

      cout << root->playerID << " ";  
      if (root->playerID == id) 
      return true;

      if (id < root->playerID) 
      {
         if (showPathHelper(root->left, id)) 
         return true;
      } 
      else 
      {
         if (showPathHelper(root->right, id)) 
         return true;
      }
      return false;
    }
    
    //function to print details of a player
    void showDetailsHelper(Player* player) 
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
    
    int stringToInt(string& str) {
  
    int result = 0;
    bool isNegative = false;
    int startIndex = 0;

    // Check if the string has a negative sign
    if (str[0] == '-') {
        isNegative = true;
        startIndex = 1; // Start from the next character
    }

    for (int i = startIndex; i < str.length(); ++i) {
        char ch = str[i];
        
        // Ensure the character is a digit
        //if (ch < '0' || ch > '9') {
          //  cout << "Invalid character in input string.\n";
            //return 0;
        //}
        
        // Update result by shifting the existing digits left and adding the new digit
        if (ch >= '0' && ch <= '9')
        result = result * 10 + (ch - '0');
    }

    // Apply negative sign if necessary
    if (isNegative) {
        result = -result;
    }
    
    return result;
   }
    
    
    float stringToFloat(string &str) {
    float result = 0.0f;
    float decimalPlace = 0.1f;
    bool isNegative = false;
    bool isFractionalPart = false;
    
    for (char ch : str) {
        if (ch == '-') {
            isNegative = true;
        }
        else if (ch == '.') {
            isFractionalPart = true;
        }
        else if (ch >= '0' && ch <= '9') {
            if (isFractionalPart) {
                result += (ch - '0') * decimalPlace;
                decimalPlace *= 0.1f;  // Move one place to the right in the decimal
            }
            else {
                result = result * 10 + (ch - '0');  // Build the integer part
            }
        }
    }

    if (isNegative) {
        result = -result;
    }
    
    return result;
}
    
    
    
    // top n playerssssssssssssssss
    struct PlayerGamesCount {
        Player* player;
        int gamesCount;
    };

    void countGamesForPlayer(Player* player, PlayerGamesCount* playerCounts, int& index) {
        int gameCount = 0;
        GamesPlayed* game = player->gamesHead;
        while (game) {
            gameCount++;
            game = game->next;
        }
        playerCounts[index++] = {player, gameCount};
    }

    void inorderCollectPlayers(Player* root, PlayerGamesCount* playerCounts, int& index) {
        if (!root) return;
        inorderCollectPlayers(root->left, playerCounts, index);
        countGamesForPlayer(root, playerCounts, index);
        inorderCollectPlayers(root->right, playerCounts, index);
    }

    void sortPlayersByGames(PlayerGamesCount* playerCounts, int size) {
        // Bubble sort algorithm without std::swap
        for (int i = 0; i < size - 1; ++i) {
            for (int j = i + 1; j < size; ++j) {
                if (playerCounts[i].gamesCount < playerCounts[j].gamesCount) {
                    // Swap manually
                    PlayerGamesCount temp = playerCounts[i];
                    playerCounts[i] = playerCounts[j];
                    playerCounts[j] = temp;
                }
            }
        }
    }
    
    
    
    public: 
    
    void insertPlayer(string id, string name, string phone, string email, string password) 
    {
        if (searchPlayer(playerRoot, id) != nullptr) 
        {
            cout << "Error: Player with ID " << id << " already exists.\n";
            return;
        }
        
        playerRoot = insertPlayerHelper(playerRoot, id, name, phone, email, password);
        cout << "Inserted player with ID: " << id << endl;
    }
    
 
     void searchPlayer(string id) 
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
     
   
     void deletePlayer(string id) 
     {
        playerRoot = deletePlayerHelper(playerRoot, id);
     }
     
     
     int showLayerNumber(string id)
     {
        return showLayerNumberHelper(playerRoot, id);
     }

    
     void showPath(string id)
     {
       bool found;
       
       found = showPathHelper(playerRoot, id);
       
       if(found)
       cout<<"Player Found"<<endl;
       else
       cout<<"Player not Found"<<endl;
     }
    
     void showDetails(string id)
     {
        Player * p = searchPlayer(playerRoot, id);      
        return showDetailsHelper(p);
     }
     
     
     //function to edit an entry in the tree
     void editEntry(string oldID, string newID, string newName, string newEmail, string newPhone, string newPassword) 
     {
        Player* nodeToEdit = searchPlayer(playerRoot, oldID);

        if (!nodeToEdit) 
        {
            cout << "Player with ID " << oldID << " not found." << endl;
            return;
        }

        if (oldID != newID) 
        {
            playerRoot = deletePlayerHelper(playerRoot, oldID);
            playerRoot = insertPlayerHelper(playerRoot, newID, newName, newEmail, newPhone, newPassword);
            Player* newNode = searchPlayer(playerRoot, newID);
            newNode->gamesHead = nodeToEdit->gamesHead;
            delete nodeToEdit;
        } 
        else 
        {
            nodeToEdit->playerName = newName;
            nodeToEdit->email = newEmail;
            nodeToEdit->phoneNumber = newPhone;
        }

        cout << "Player entry updated successfully." << endl;
    }
    
    
    //testttttttttttttttttttttttttttttttttttttttttttttttt
    
    void showNLayersHelper(int N) {
        if (!playerRoot) {
            cout << "Tree is empty." << endl;
            return;
        }

        // Linked list-based queue
        Queue queue;
        queue.enqueue(playerRoot, 1);  // Start with the root node at depth 1
        int currentLayer = 1;
        int maxLayerReached = 0;

        while (!queue.isEmpty()) {
            QueueNode* nodeData = queue.dequeue();
            Player* current = nodeData->treeNode;
            int depth = nodeData->depth;
            delete nodeData; // Free memory

            // Check if we are within the layer limit
            if (depth > N) {
                cout << "\nLayer Limit was Reached, can’t go further" << endl;
                break;
            }

            // Print player info layer by layer
            if (depth > currentLayer) {
                cout << "\nLayer " << depth << ": ";
                currentLayer = depth;
            }

            cout << "[" << current->playerID << ": " << current->playerName << "] ";

            // Add left and right children to the queue
            if (current->left) queue.enqueue(current->left, depth + 1);
            if (current->right) queue.enqueue(current->right, depth + 1);

            maxLayerReached = depth;
        }

        // Warning if the tree depth < N
        if (maxLayerReached < N) {
            cout << "\nLayer Limit was Reached, can’t go further" << endl;
        }

        cout << endl;
    }
    
    
    void topNPlayers(int N) {
        int totalPlayers = countNodes(playerRoot);
        PlayerGamesCount* playerCounts = new PlayerGamesCount[totalPlayers];
        int index = 0;

        // Collect all players with their game counts
        inorderCollectPlayers(playerRoot, playerCounts, index);

        // Sort players by game count in descending order
        sortPlayersByGames(playerCounts, totalPlayers);

        // Display the top N players
        for (int i = 0; i < N && i < totalPlayers; ++i) {
            std::cout << "Player ID: " << playerCounts[i].player->playerID
                      << ", Name: " << playerCounts[i].player->playerName
                      << ", Games Played: " << playerCounts[i].gamesCount << std::endl;
        }

        delete[] playerCounts;
    }

    int countNodes(Player* root) {
        if (!root) return 0;
        return 1 + countNodes(root->left) + countNodes(root->right);
    }
    
    
    
    
    //store in csv
    
    
     void saveDataToCSV(Player* root, ofstream& file) {
        if (root == nullptr) 
        return;

        // Write player details (Player ID, Name, Phone, Email, Password)
        file << root->playerID << "," 
             << root->playerName << "," 
             << root->phoneNumber << "," 
             << root->email << "," 
             << root->password;

        // Write game details (Game ID, Hours Played, Achievements)
        GamesPlayed* game = root->gamesHead;
        while (game != nullptr) {
            file << "," << game->gameID
                 << "," << game->hoursPlayed
                 << "," << game->achievementsUnlocked;
            game = game->next;
        }
        file << endl;

        // Recur for left and right children
        saveDataToCSV(root->left, file);
        saveDataToCSV(root->right, file);
    }

    // Function to save the entire database to a CSV file
    void saveDatabaseToCSV() {
        ofstream file("Playerrr.txt");
        if (!file.is_open()) {
            cout << "Error opening file." << endl;
            return;
        }

        // Save player data to the CSV file
        saveDataToCSV(playerRoot, file);

        file.close();
    }
    
    
    // load from csv
    
    
    
    void loadPlayersFromCSV() 
    {
        ifstream file("Players.txt");
        if (!file.is_open()) {
            cout << "Error opening file." << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            // Generate random number from 0 to 1000 to decide if we should skip this line
            int randomNum = rand() % 1001;
            
            if (randomNum < skipThreshold) {
                // Skip this line (do not insert player)
                continue;
            }

            // Process this line and add the player
            stringstream ss(line);
            string id, name, phone, email, password, gameid, hours, achiev;
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, phone, ',');
            getline(ss, email, ',');
            getline(ss, password, ',');

            // Insert player into the BST
            insertPlayer(id, name, phone, email, password);
            
            Player* player = searchPlayer(playerRoot, id);
            
            while (getline(ss, gameid, ',') && getline(ss, hours, ',') && getline(ss, achiev, ',')) {
            // Convert hours and achievements from strings to int or float as needed
            float hoursPlayed = stringToFloat(hours);
            int achievementsUnlocked = stringToInt(achiev);

            // Add game details to the player's game list
            player->addGame(gameid, hoursPlayed, achievementsUnlocked);
           }
            
        
        }
        
        file.close();
    }
    
};
class DatabaseGame
{
   private:

    Game *gameRoot = nullptr;
    int skipThreshold;
    
    public: 
    //generating custom seed
    DatabaseGame() 
    {
      // Calculate the skip threshold based on roll number
        int lastTwoDigits = 232552 % 100; 
        skipThreshold = (lastTwoDigits * 10) + 100;
        
        // Seed random number generator with roll number
        srand(232552);
    }  
    
    private:
    //function to search game in the tree 
    Game* searchGame(Game* root, string id) 
    {
        if (!root || root->gameID == id) 
        return root;
        
        if (stringToInt(id) < stringToInt(root->gameID)) 
        return searchGame(root->left, id);
        
        return searchGame(root->right, id);
    }
    
    
     //function to insert game in the tree
     Game* insertGameHelper(Game* root,string id, string name, string developer, string publisher, float size, int copiesSold) 
     {
        if (!root) 
        return new Game(id, name, developer, publisher, size, copiesSold);
        
        if (stringToInt(id) < stringToInt(root->gameID)) 
        root->left = insertGameHelper(root->left, id, name, developer, publisher, size, copiesSold);
        else if (stringToInt(id) > stringToInt(root->gameID)) 
        root->right = insertGameHelper(root->right, id, name, developer, publisher, size, copiesSold);
        
        return root;
    }
    
    //function to get min id game node
    Game* minValueNode(Game* node) 
    {
        Game* current = node;
        while (current && current->left) 
        current = current->left;
        
        return current;
    }
    
    //function to delete node 
    Game* deleteGameHelper(Game* root, string id) 
    {
        if (!root) 
        return nullptr;

        if (stringToInt(id) < stringToInt(root->gameID)) 
        {
            root->left = deleteGameHelper(root->left, id);
        } 
        else if (stringToInt(id) > stringToInt(root->gameID)) 
        {
            root->right = deleteGameHelper(root->right, id);
        } 
        else 
        {   
            //if node has 1 or 0 children
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
        
            //if node has 2 children
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
    
    //function to show layer number for a node
    int showLayerNumberHelper(Game* root, string id) 
    {
       int layer = 1;
       while (root) 
       {
          if (root->gameID == id) 
          return layer;

          root = (stringToInt(id) < stringToInt(root->gameID)) ? root->left : root->right;
          layer++;
       }
       cout << "Game with ID " << id << " does not exist.\n";
       return -1;
    }
    
    //function to show path to the node
    bool showPathHelper(Game* root, string id) 
    {
      if (!root) 
      return false;

      cout << root->gameID << " ";  
      if (root->gameID == id) 
      return true;

      if (id < root->gameID) 
      {
         if (showPathHelper(root->left, id)) 
         return true;
      } 
      else 
      {
         if (showPathHelper(root->right, id)) 
         return true;
      }
      return false;
    }
    
    int stringToInt(string& str) {
    int result = 0;
    bool isNegative = false;
    int startIndex = 0;

    // Check if the string has a negative sign
    if (str[0] == '-') {
        isNegative = true;
        startIndex = 1; // Start from the next character
    }

    for (int i = startIndex; i < str.length(); ++i) {
        char ch = str[i];
        
        // Ensure the character is a digit
        if (ch < '0' || ch > '9') {
            std::cerr << "Invalid character in input string.\n";
            return 0;
        }
        
        // Update result by shifting the existing digits left and adding the new digit
        result = result * 10 + (ch - '0');
    }

    // Apply negative sign if necessary
    if (isNegative) {
        result = -result;
    }

    return result;
}
    
    float stringToFloat(string &str) {
    float result = 0.0f;
    float decimalPlace = 0.1f;
    bool isNegative = false;
    bool isFractionalPart = false;
    
    for (char ch : str) {
        if (ch == '-') {
            isNegative = true;
        }
        else if (ch == '.') {
            isFractionalPart = true;
        }
        else if (ch >= '0' && ch <= '9') {
            if (isFractionalPart) {
                result += (ch - '0') * decimalPlace;
                decimalPlace *= 0.1f;  // Move one place to the right in the decimal
            }
            else {
                result = result * 10 + (ch - '0');  // Build the integer part
            }
        }
    }

    if (isNegative) {
        result = -result;
    }
    
    return result;
}
    
    public: 
     
    void insertGame(string id, string name, string developer, string publisher, float size, int copiesSold) 
    {
        if (searchGame(gameRoot, id) != nullptr) 
        {
            cout << "Error: Game with ID " << id << " already exists.\n";
            return;
        }
        
        gameRoot = insertGameHelper(gameRoot, id, name, developer, publisher, size, copiesSold);
        cout << "Inserted game with ID: " << id << endl;
    }
    
     void searchGame(string id) 
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

    void deleteGame(string id) 
    {
        gameRoot = deleteGameHelper(gameRoot, id);
    }
    
    int showLayerNumber(string id)
    {
      return showLayerNumberHelper(gameRoot, id);
    }
      
    void showPath(string id)
     {
       bool found;
       
       found = showPathHelper(gameRoot, id);
       
       if(found)
       cout<<"Game Found"<<endl;
       else
       cout<<"Game not Found"<<endl;
     }
     
     
     void showNLayersHelper(int N) {
        if (!gameRoot) {
            cout << "Tree is empty." << endl;
            return;
        }

        // Linked list-based queue
        Queue queue;
        queue.enqueue(gameRoot, 1);  // Start with the root node at depth 1
        int currentLayer = 1;
        int maxLayerReached = 0;

        while (!queue.isEmpty()) {
            QueueNode* nodeData = queue.dequeue();
            Player* current = nodeData->treeNode;
            int depth = nodeData->depth;
            delete nodeData; // Free memory

            // Check if we are within the layer limit
            if (depth > N) {
                cout << "\nLayer Limit was Reached, can’t go further" << endl;
                break;
            }

            // Print player info layer by layer
            if (depth > currentLayer) {
                cout << "\nLayer " << depth << ": ";
                currentLayer = depth;
            }

            cout << "[" << current->playerID << ": " << current->playerName << "] ";

            // Add left and right children to the queue
            if (current->left) queue.enqueue(current->left, depth + 1);
            if (current->right) queue.enqueue(current->right, depth + 1);

            maxLayerReached = depth;
        }

        // Warning if the tree depth < N
        if (maxLayerReached < N) {
            cout << "\nLayer Limit was Reached, can’t go further" << endl;
        }

        cout << endl;
    }
    
    
     //store in csv
    
    
     void saveDataToCSV(Game* root, ofstream& file) {
        if (root == nullptr) 
        return;

        file << root->gameID << "," 
             << root->gameName << "," 
             << root->developer << "," 
             << root->publisher<< "," 
             << root->fileSize<< ","
             << root -> copiesSold;

        file << endl;

        // Recur for left and right children
        saveDataToCSV(root->left, file);
        saveDataToCSV(root->right, file);
    }

    // Function to save the entire database to a CSV file
    void saveDatabaseToCSV() {
        ofstream file("Gamessss.txt");
        if (!file.is_open()) {
            cout << "Error opening file." << endl;
            return;
        }

        // Save player data to the CSV file
        saveDataToCSV(gameRoot, file);

        file.close();
    }
    
    
    void loadGamesFromCSV() 
    {
        ifstream file("Games.txt");
        if (!file.is_open()) {
            cout << "Error opening file." << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            // Generate random number from 0 to 1000 to decide if we should skip this line
            int randomNum = rand() % 1001;
            
            if (randomNum < skipThreshold) {
                // Skip this line (do not insert game)
                continue;
            }

            // Process this line and add the game
            stringstream ss(line);
            string id, name, develop, publish, size, download;
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, develop, ',');
            getline(ss, publish, ',');
            getline(ss, size, ',');
            getline(ss, download, ',');

            // Insert game into the BST
            insertGame(id, name, develop, publish, stringToFloat(size), stringToInt(download));
            
        }
        
        file.close();
    }
    
    
    
};
int main()
{
   DatabasePlayer db;
   DatabaseGame db2;
    // Insert some players
    //db.insertPlayer("P001", "Alice", "1234567890", "alice@example.com", "password123");
    //db.insertPlayer("P002", "Bob", "0987654321", "bob@example.com", "password456");
    //db.insertPlayer("P003", "Charlie", "5555555555", "charlie@example.com", "password789");
    db.loadPlayersFromCSV();
    db.saveDatabaseToCSV();
   
    db2.loadGamesFromCSV();
    db2.saveDatabaseToCSV();
    // Show details of a player
    //cout << "\nShowing details of player P001:" << endl;
    //db.showDetails("P001");

    return 0;
}
