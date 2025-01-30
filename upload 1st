#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

void calculateNetDebts(const unordered_map<string, unordered_map<string, int>>& debts) {
    unordered_map<string, int> netDebts;

    // Tinh toan no rong cho moi nguoi choi
    for (const auto& player : debts) {
        for (const auto& other : player.second) {
            if (player.first != other.first) {
                netDebts[player.first] += other.second; // Nguoi choi no
                netDebts[other.first] -= other.second; // Nguoi choi duoc no
            }
        }
    }

    // Hien thi ket qua can no
    cout << "\nKet qua can no:\n";
    for (const auto& netDebt : netDebts) {
        if (netDebt.second > 0) {
            cout << netDebt.first << " no tong cong: " << netDebt.second << " VND\n";
        } else if (netDebt.second < 0) {
            cout << netDebt.first << " duoc no tong cong: " << -netDebt.second << " VND\n";
        }
    }

    // Hien thi chi tiet ai con no ai bao nhieu
    cout << "\nChi tiet ai con no ai bao nhieu:\n";
    for (const auto& player : debts) {
        for (const auto& other : player.second) {
            if (other.second > 0) {
                cout << player.first << " no " << other.first << ": " << other.second << " VND\n";
            }
        }
    }
}

int main() {
    vector<string> players;
    string input;

    // Nhap danh sach nguoi choi
    cout << "Nhap ten cac nguoi choi (cach nhau boi dau phay): ";
    getline(cin, input);

    size_t pos;
    while ((pos = input.find(",")) != string::npos) {
        players.push_back(input.substr(0, pos));
        input.erase(0, pos + 1);
    }
    players.push_back(input);

    for (auto &player : players) {
        player.erase(remove(player.begin(), player.end(), ' '), player.end());
    }

    if (players.size() < 4) {
        cout << "Can it nhat 4 nguoi choi.\n";
        return 0;
    }

    cout << "So luong nguoi choi: " << players.size() << endl;

    int numRounds;
    cout << "Nhap so van bai da choi: ";
    cin >> numRounds;
    cin.ignore();

    unordered_map<string, unordered_map<string, int>> debts;
    for (const auto &player : players) {
        for (const auto &other : players) {
            if (player != other) {
                debts[player][other] = 0;
            }
        }
    }

    for (int roundNum = 1; roundNum <= numRounds; ++roundNum) {
        cout << "\nNhap thong tin cho van " << roundNum << ":\n";

        vector<string> selectedPlayers(4);
        while (true) {
            cout << "Chon 4 nguoi choi (cach nhau boi dau phay): ";
            getline(cin, input);
            size_t pos;
            int count = 0;
            while ((pos = input.find(",")) != string::npos && count < 4) {
                selectedPlayers[count++] = input.substr(0, pos);
                input.erase(0, pos + 1);
            }
            selectedPlayers[count++] = input;

            for (auto &player : selectedPlayers) {
                player.erase(remove(player.begin(), player.end(), ' '), player.end());
            }

            if (selectedPlayers.size() == 4 && all_of(selectedPlayers.begin(), selectedPlayers.end(), [&](const string &p) {
                return find(players.begin(), players.end(), p) != players.end();
            })) {
                break;
            }
            cout << "Vui long chon dung 4 nguoi.\n";
        }

        vector<string> positions(4);
        cout << "Nhap thu tu ve nhat, nhi, ba, tu:\n";
        for (int i = 0; i < 4; ++i) {
            while (true) {
                cout << "Nguoi ve " << (i + 1) << ": ";
                getline(cin, positions[i]);
                positions[i].erase(remove(positions[i].begin(), positions[i].end(), ' '), positions[i].end());

                if (find(selectedPlayers.begin(), selectedPlayers.end(), positions[i]) != selectedPlayers.end() &&
                    count(positions.begin(), positions.end(), positions[i]) == 1) {
                    break;
                }
                cout << "Nguoi choi khong hop le hoac da nhap truoc.\n";
            }
        }

        debts[positions[3]][positions[0]] += 2000; // 4th owes 2000 to 1st
        debts[positions[2]][positions[1]] += 1000; // 3rd owes 1000 to 2nd

        // Nhap thong tin ve nguoi chat heo va nguoi bi chat heo
        string chopper;
        cout << "Ai la nguoi chat heo (bo qua neu khong co): ";
        getline(cin, chopper);
        chopper.erase(remove(chopper.begin(), chopper.end(), ' '), chopper.end());
        if (!chopper.empty()) {
            string victim;
            cout << "Ai bi chat heo: ";
            getline(cin, victim);
            victim.erase(remove(victim.begin(), victim.end(), ' '), victim.end());
            if (find(selectedPlayers.begin(), selectedPlayers.end(), victim) != selectedPlayers.end() &&
                find(selectedPlayers.begin(), selectedPlayers.end(), chopper) != selectedPlayers.end()) {
                cout << "Heo den (1) hay heo do (2): ";
                int pigType;
                cin >> pigType;
                cin.ignore();
                if (pigType == 1) {
                    debts[victim][chopper] += 1000;
                } else if (pigType == 2) {
                    debts[victim][chopper] += 2000;
                }
            }
        }

        string skunkedPlayer;
        cout << "Ai thui heo (bo qua neu khong co): ";
        getline(cin, skunkedPlayer);
        skunkedPlayer.erase(remove(skunkedPlayer.begin(), skunkedPlayer.end(), ' '), skunkedPlayer.end());
        if (!skunkedPlayer.empty() && find(selectedPlayers.begin(), selectedPlayers.end(), skunkedPlayer) != selectedPlayers.end()) {
            cout << "Heo den (1) hay heo do (2): ";
            int pigType;
            cin >> pigType;
            cin.ignore();
            if (pigType == 1) {
                debts[skunkedPlayer][positions[0]] += 1000;
            } else if (pigType == 2) {
                debts[skunkedPlayer][positions[0]] += 2000;
            }
        }
    }

    // Tinh toan va hien thi ket qua can no
    calculateNetDebts(debts);

    return 0;
}
