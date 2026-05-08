#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

enum WarriorType {
    DRAGON = 0,
    NINJA = 1,
    ICEMAN = 2,
    LION = 3,
    WOLF = 4
};

static const string kWarriorName[5] = {"dragon", "ninja", "iceman", "lion", "wolf"};

class Headquarter {
private:
    int health;
    int totalWarriors;
    int warriorCount[5];
    int warriorHP[5];
    int produceOrder[5];
    int nextStart;
    bool stopped;
    string side;

public:
    Headquarter(int initialHealth, const string& sideName, const int order[5], const int baseHP[5])
        : health(initialHealth), totalWarriors(0), warriorCount{0}, warriorHP{0}, produceOrder{0},
          nextStart(0), stopped(false), side(sideName) {
        for (int i = 0; i < 5; ++i) {
            warriorHP[i] = baseHP[i];
            produceOrder[i] = order[i];
        }
    }

    bool hasStopped() const {
        return stopped;
    }

    void produceOrStop(int timeHour) {
        cout << setw(3) << setfill('0') << timeHour;
        for (int offset = 0; offset < 5; ++offset) {
            int idx = (nextStart + offset) % 5;
            int type = produceOrder[idx];
            if (health >= warriorHP[type]) {
                produce(type);
                nextStart = (idx + 1) % 5;
                return;
            }
        }
        stop();
    }

private:
    void produce(int type) {
        ++warriorCount[type];
        ++totalWarriors;
        health -= warriorHP[type];

        cout << " " << side << " " << kWarriorName[type] << " " << totalWarriors
             << " born with strength " << warriorHP[type] << "," << warriorCount[type]
             << " " << kWarriorName[type] << " in " << side << " headquarter" << endl;
    }

    void stop() {
        stopped = true;
        cout << " " << side << " headquarter stops making warriors" << endl;
    }
};

int main() {
    int T;
    cin >> T;

    const int redOrder[5] = {ICEMAN, LION, WOLF, NINJA, DRAGON};
    const int blueOrder[5] = {LION, DRAGON, NINJA, ICEMAN, WOLF};

    for (int caseId = 1; caseId <= T; ++caseId) {
        cout << "Case:" << caseId << endl;

        int initialHealth;
        int baseHP[5];
        cin >> initialHealth;
        for (int i = 0; i < 5; ++i) {
            cin >> baseHP[i];
        }

        Headquarter red(initialHealth, "red", redOrder, baseHP);
        Headquarter blue(initialHealth, "blue", blueOrder, baseHP);

        for (int timeHour = 0; !red.hasStopped() || !blue.hasStopped(); ++timeHour) {
            if (!red.hasStopped()) {
                red.produceOrStop(timeHour);
            }
            if (!blue.hasStopped()) {
                blue.produceOrStop(timeHour);
            }
        }
    }

    return 0;
}