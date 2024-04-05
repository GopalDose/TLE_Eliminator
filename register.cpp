#include <bits/stdc++.h>
#include<windows.h>
using namespace std;

/// adarsh code start here

void speak(string a){
    string command = "espeak \"" + a + "\"";
    const char* charCommand = command.c_str();
    system(charCommand);
}



class Artist
{
public:
    string ArtistName;
    vector<int> MusicId;

public:
    Artist()
    {
    }

    Artist(string name, vector<int> id)
    {
        ArtistName = name;
        MusicId = id;
    }
};

class SongNode
{
public:
    string SongName;
    int Aartist;
    string Genre;

public:
    SongNode(string name, int art, string gen)
    {
        SongName = name;
        Aartist = art;
        Genre = gen;
    }
};

unordered_map<int, SongNode *> songmp; // Song Id, Song Node Info
unordered_map<int, Artist *> atmp;     // Aritst Id, Aritst Node Info
unordered_map<string, int> artId;
void loadSongsFromCSV()
{
    int vars = 1;
    vector<string> row;
    string line, word, temp;
    fstream fin;
    fin.open("data.csv", ios::in);
    int var = 0;
    while (getline(fin, line))
    {
        row.clear();
        stringstream s(line);
        while (getline(s, word, ','))
        {
            row.push_back(word);
        }

        // Assign the Artist an ID
        if (artId.find(row[2]) == artId.end())
        {
            artId[row[2]] = var++;
        }
        // Create a song Node with songName, ArtId, Genre

        // cout<<row[0]<<" ";
        SongNode *sn = new SongNode(row[1], artId[row[2]], row[3]);

        songmp[vars] = sn;

        if (atmp.find(artId[row[2]]) == atmp.end())
        {
            vector<int> temp;
            temp.push_back(vars);
            Artist *ar = new Artist(row[2], temp);
            atmp[artId[row[2]]] = ar;
        }
        else
        {
            atmp[artId[row[2]]]->MusicId.push_back(vars);
        }
        vars++;
    }
}

// adarsh code end here

class User
{
public:
    string userName;
    string userEmail;
    string userPass;
    string userMob;

    User()
    {
        userName = "";
        userEmail = "";
        userPass = "";
        userMob = "";
    }

    User(string name, string email, string pass, string mob)
    {
        userName = name;
        userEmail = email;
        userPass = pass;
        userMob = mob;
    }
};

unordered_map<string, User> mp;                  // email and its object of user class
unordered_map<string, set<pair<int, int>>> pref; // user id and artist id + number of views
unordered_map<int, Artist> art;                  // list of artist with its id given by adarsh

string Register()
{
    string name;
    string email;
    string pass;
    string mob;
    cout << "*****************************************" << endl;
    cout << "*            Registration Page          *" << endl;
    cout << "*****************************************" << endl;
    cout << "Enter Name : ";
    cin >> name;

    cout << "Enter email : ";
    cin >> email;

    cout << "Enter Pass : ";
    cin >> pass;

    cout << "Enter Mobile : ";
    cin >> mob;

    if (mp.find(email) != mp.end())
    {
        cout << "User exists" << endl;
        return "";
    }

    User u1(name, email, pass, mob);
    mp[email] = u1;
    cout << "User created successfully" << endl;
    cout << "*****************************************" << endl;
    return email;
}

string Login()
{
    string email;
    string pass;
    cout<<endl;
    cout<<endl;
    cout << "*****************************************" << endl;
    cout << "*               Login Page              *" << endl;
    cout << "*****************************************" << endl;
    cout << "Enter email : ";
    cin >> email;

    cout << "Enter password : ";
    cin >> pass;

    if (mp.find(email) == mp.end())
    {
        cout << "User not found" << endl;
        return "";
    }

    if (mp[email].userPass == pass)
    {
        cout << "Login successful" << endl;
    }
    else
    {
        cout << "Invalid password" << endl;
    }
    cout << "*****************************************" << endl;
    cout<<endl;
    return email;
}

void SelectPreference(string id)
{
    for (auto it : atmp)
    {
        cout << it.second->ArtistName << " : (Yes : 1 , No : 0) : ";
        int num;
        cin >> num;
        if (num == 1)
        {
            pref[id].insert({1, it.first});
        }
    }
}

void dummyArt()
{
    int id = 1;
    string name = "vivek";
    vector<int> musId = {1, 2, 3, 4};

    Artist a1;
    a1.ArtistName = name;
    a1.MusicId = musId;
    art[id] = a1;

    id = 2;
    name = "Gopal";
    musId = {1, 2, 3, 4};

    Artist a2;
    a2.ArtistName = name;
    a2.MusicId = musId;
    art[id] = a2;

    id = 3;
    name = "Harsh";
    musId = {1, 2, 3, 4};

    Artist a3;
    a3.ArtistName = name;
    a3.MusicId = musId;
    art[id] = a3;
}
void ProfilePage(string id)
{
    cout << "*****************************************" << endl;
    cout << "*            Profile Page               *" << endl;
    cout << "*****************************************" << endl;
    cout << "* User Basic Detail                     " << endl;
    cout << "* Name     : " << setw(13) << left << mp[id].userName << endl;
    cout << "* Email    : " << setw(13) << left << mp[id].userEmail << endl;
    cout << "* Password : " << setw(13) << left << mp[id].userPass << endl;
    cout << "* Mobile No: " << setw(13) << left << mp[id].userMob << endl;
    cout << "*****************************************" << endl;
    cout << "* Preferences                           " << endl;
    cout << " Song ID, Artist ID  |  Song Name  |  Genre" << endl;
    cout << "-----------------------------------------" << endl;

    for (auto it : pref[id])
    {
        int artistId = it.second;
        Artist artist = art[artistId];
        cout << setw(13) << left << artist.ArtistName << " | ";

        vector<int> musicIds = atmp[artistId]->MusicId;
        for (int musicId : musicIds)
        {
            SongNode *song = songmp[musicId];
            cout  << musicId<< " "<<artistId  << " | "
                 << setw(11) << left << song->SongName << " | "
                 << setw(9) << left << song->Genre << endl;
        }
    }
    cout << "*****************************************" << endl;

    // Play music
    int songnum = 0, au = 0;
    cout << "Enter Song Number : ";
    cin >> songnum >> au;

    cout << "Listening Song.........." << endl;
    speak("Enjoy Song.");

    set<pair<int, int>> &st = pref[id]; // Get a reference to the set in pref
    for (auto &it : st)
    {
        if (it.second == au)
        {
            int cnt = it.first;
            cnt++;
            st.erase(it);
            st.insert({cnt, au});
            break; // Exit loop once the song is found and updated
        }
    }

    ProfilePage(id);
}

int main()
{
    // dummyArt(); // delete it after some time
    loadSongsFromCSV();

    speak("Welcome");
    string id = "";
    int choice;
    do
    {
        cout << endl
             << endl;
        cout << "*****************************************" << endl;
        cout << "*               Menu Page              *" << endl;
        cout << "*****************************************" << endl;
        cout << "1. Register\n2. Login\n3. User Profile\nEnter your choice: ";
        cin >> choice;
        cout << "*****************************************" << endl<<endl;

        switch (choice)
        {
        case 1:
        {
            id = Register();
            if (id.empty())
            {
                continue;
            }
            SelectPreference(id);
            id = Login();
            break;
        }
        case 2:
        {
            id = Login();
            if (id.empty())
            {
                continue;
            }
            else
            {
                cout << "Profile Page" << endl;
            }
            break;
        }
        case 3:
        {
            if(id == ""){
                choice = 1;
                continue;
            }
            ProfilePage(id);
            break;
        }
        default:
            cout << "Invalid choice" << endl;
        }
    } while (choice != 3);

    return 0;
}
