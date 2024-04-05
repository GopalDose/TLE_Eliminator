#include<bits/stdc++.h>
using namespace std;

class Artist {
public:
    string ArtistName;
    vector<int> MusicId;

    Artist(string name, vector<int> id) {
        ArtistName = name;
        MusicId = id;
    }
};

class SongNode {
public:
    string SongName;
    int Aartist;
    string Genre;

    SongNode(string name, int art, string gen) {
        SongName = name;
        Aartist = art;
        Genre = gen;
    }
};

unordered_map<int, SongNode*> songmp;    // Song Id, Song Node Info
unordered_map<int, Artist*> atmp;    // Aritst Id, Aritst Node Info
unordered_map<string, int> artId;

void loadSongsFromCSV() {
    int vars = 1;
    vector<string> row;
    string line, word, temp;
    fstream fin;
    fin.open("data.csv", ios::in);
    int var = 0;
    while (fin >> temp) {
        row.clear();
        getline(fin, line);
        stringstream s(line);
        while (getline(s, word, ',')) {
            row.push_back(word);
        }

        for(auto it : row){
            cout << it << " ";
        }
        cout << endl;
        // Assign the Artist an ID
        if (artId.find(row[2]) == artId.end()) {
            artId[row[2]] = var++;
        }
        // Create a song Node with songName, ArtId, Genre
        SongNode* sn = new SongNode(row[1], artId[row[2]], row[3]);

        songmp[vars] = sn;

        if (atmp.find(artId[row[2]]) == atmp.end()) {
            vector<int> temp;
            temp.push_back(vars);
            Artist* ar = new Artist(row[2], temp);
            atmp[artId[row[2]]] = ar;
        }
        else {
            atmp[artId[row[2]]]->MusicId.push_back(vars);
        }
        vars++;
    }
}

void print(int id) {
    for (auto i : atmp[id]->MusicId) {
        cout << i << " " << songmp[i]->SongName << endl;
    }
}

int main() {
    loadSongsFromCSV();
    print(1);
    return 0;
}
