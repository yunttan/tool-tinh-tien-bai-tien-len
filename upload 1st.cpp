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

    unordered_map<string, unordered_map<string, int>> debts;
    for (const auto &player : players) {
        for (const auto &other : players) {
            if (player != other) {
                debts[player][other] = 0;
            }
        }
    }

    // Nhap so lan dung thu hạng cho moi nguoi
    for (const auto& player : players) {
        int first, second, third, fourth;
        cout << "Nhap so lan " << player << " dung thu 1: ";
        cin >> first;
        cout << "Nhap so lan " << player << " dung thu 2: ";
        cin >> second;
        cout << "Nhap so lan " << player << " dung thu 3: ";
        cin >> third;
        cout << "Nhap so lan " << player << " dung thu 4: ";
        cin >> fourth;

        // Cap nhat no dua tren thu tu
        debts[players[3]][players[0]] += 2000 * first; // 4th owes 2000 to 1st
        debts[players[2]][players[1]] += 1000 * second; // 3rd owes 1000 to 2nd
    }
    cin.ignore();

    // Nhap thong tin ve nguoi chat heo cho tung nguoi
    for (const auto& player : players) {
        string victim;
        cout << "Ai bi chat heo (bo qua neu khong co) cho " << player << ": ";
        getline(cin, victim);
        victim.erase(remove(victim.begin(), victim.end(), ' '), victim.end());
        if (!victim.empty()) {
            string chopper;
            cout << "Ai la nguoi chat heo: ";
            getline(cin, chopper);
            chopper.erase(remove(chopper.begin(), chopper.end(), ' '), chopper.end());
            if (find(players.begin(), players.end(), victim) != players.end() &&
                find(players.begin(), players.end(), chopper) != players.end()) {
                cout << "Heo den (1) hay heo do (2): ";
                int pigType;
                cin >> pigType;
                if (pigType == 1) {
                    debts[victim][chopper] += 1000;
                } else if (pigType == 2) {
                    debts[victim][chopper] += 2000;
                }
            }
        }

        string skunkedPlayer;
        cout << "Ai la nguoi thui heo (bo qua neu khong co) cho " << player << ": ";
        getline(cin, skunkedPlayer);
        skunkedPlayer.erase(remove(skunkedPlayer.begin(), skunkedPlayer.end(), ' '), skunkedPlayer.end());
        if (!skunkedPlayer.empty()) {
            string firstPlayer;
            cout << "Ai la nguoi ve nhat: ";
            getline(cin, firstPlayer);
            firstPlayer.erase(remove(firstPlayer.begin(), firstPlayer.end(), ' '), firstPlayer.end());
            if (find(players.begin(), players.end(), firstPlayer) != players.end() &&
                find(players.begin(), players.end(), skunkedPlayer) != players.end()) {
                cout << "Heo den (1) hay heo do (2): ";
                int pigType;
                cin >> pigType;
                if (pigType == 1) {
                    debts[firstPlayer][skunkedPlayer] += 1000;
                } else if (pigType == 2) {
                    debts[firstPlayer][skunkedPlayer] += 2000;
                }
            }
        }
        cin.ignore(); // Để xử lý việc nhập dòng tiếp theo
    }

    // Tinh toan va hien thi ket qua can no
    calculateNetDebts(debts);

    return 0;
}
