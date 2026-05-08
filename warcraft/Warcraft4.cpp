#include <bits/stdc++.h>
using namespace std;

enum Side { RED = 0, BLUE = 1, NONE = 2 };

string sideName(Side s) {
	return s == RED ? "red" : "blue";
}

string typeName(int t) {
	static const char* names[] = {"dragon", "ninja", "iceman", "lion", "wolf"};
	return names[t];
}

string formatTime(int minutes) {
	int h = minutes / 60;
	int m = minutes % 60;
	ostringstream oss;
	oss << setw(3) << setfill('0') << h << ":" << setw(2) << setfill('0') << m;
	return oss.str();
}

struct Warrior {
	int id = 0;
	Side side = NONE;
	int type = 0;
	int hp = 0;
	int atk = 0;
	int city = 0;
	bool alive = true;

	bool hasSword = false;
	int sword = 0;
	bool hasBomb = false;
	bool hasArrow = false;
	int arrowUses = 0;

	double morale = 0.0;
	int loyalty = 0;
	int steps = 0;

	bool killedByArrow = false;

	int swordPower() const { return hasSword ? sword : 0; }

	void degradeSword() {
		if (!hasSword) return;
		sword = (sword * 8) / 10;
		if (sword == 0) {
			hasSword = false;
		}
	}
};

struct City {
	int index = 0;
	int elements = 0;
	Side flag = NONE;
	Side lastWinner = NONE;
	Warrior* red = nullptr;
	Warrior* blue = nullptr;
	bool hadBothBeforeArrow = false;
	bool bombed = false;

	City() = default;
	explicit City(int idx) : index(idx) {}
};

struct Headquarter {
	Side side = NONE;
	int elements = 0;
	int cityIndex = 0;
	vector<int> order;
	int nextIndex = 0;
	int warriorCount = 0;
	vector<Warrior*> warriors;
};

struct WinnerInfo {
	Warrior* w = nullptr;
	int city = 0;
};

struct Game {
	int M = 0, N = 0, R = 0, K = 0, T = 0;
	vector<int> initHp;
	vector<int> initAtk;
	Headquarter redHQ, blueHQ;
	vector<City> cities;
	vector<Warrior*> allWarriors;
	bool warEnded = false;

	void setup() {
		cities.assign(N + 1, City());
		for (int i = 1; i <= N; ++i) cities[i] = City(i);

		redHQ.side = RED;
		redHQ.elements = M;
		redHQ.cityIndex = 0;
		redHQ.order = {2, 3, 4, 1, 0};
		redHQ.nextIndex = 0;
		redHQ.warriorCount = 0;

		blueHQ.side = BLUE;
		blueHQ.elements = M;
		blueHQ.cityIndex = N + 1;
		blueHQ.order = {3, 0, 1, 2, 4};
		blueHQ.nextIndex = 0;
		blueHQ.warriorCount = 0;
	}

	void addWeapon(Warrior* w, int weaponId) {
		if (weaponId == 0) {
			int power = (w->atk * 2) / 10;
			if (power > 0) {
				w->hasSword = true;
				w->sword = power;
			}
		} else if (weaponId == 1) {
			w->hasBomb = true;
		} else if (weaponId == 2) {
			w->hasArrow = true;
			w->arrowUses = 3;
		}
	}

	Warrior* createWarrior(Headquarter& hq, int type) {
		Warrior* w = new Warrior();
		w->id = ++hq.warriorCount;
		w->side = hq.side;
		w->type = type;
		w->hp = initHp[type];
		w->atk = initAtk[type];
		w->city = hq.cityIndex;
		w->alive = true;

		if (type == 0) {
			addWeapon(w, w->id % 3);
		} else if (type == 1) {
			addWeapon(w, w->id % 3);
			addWeapon(w, (w->id + 1) % 3);
		} else if (type == 2) {
			addWeapon(w, w->id % 3);
		}

		if (type == 0) {
			w->morale = static_cast<double>(hq.elements) / initHp[type];
		} else if (type == 3) {
			w->loyalty = hq.elements;
		}

		hq.warriors.push_back(w);
		allWarriors.push_back(w);
		return w;
	}

	void produce(int time) {
		string t = formatTime(time);
		for (Headquarter* hq : {&redHQ, &blueHQ}) {
			int type = hq->order[hq->nextIndex];
			int cost = initHp[type];
			if (hq->elements < cost) continue;
			hq->elements -= cost;
			Warrior* w = createWarrior(*hq, type);
			cout << t << " " << sideName(hq->side) << " " << typeName(type) << " "
				 << w->id << " born\n";
			if (type == 0) {
				cout << "Its morale is " << fixed << setprecision(2) << w->morale << "\n";
			} else if (type == 3) {
				cout << "Its loyalty is " << w->loyalty << "\n";
			}
			hq->nextIndex = (hq->nextIndex + 1) % 5;
		}
	}

	void lionEscape(int time) {
		string t = formatTime(time);
		auto runAway = [&](Warrior* w, City* c) {
			cout << t << " " << sideName(w->side) << " lion " << w->id << " ran away\n";
			w->alive = false;
			if (c) {
				if (w->side == RED) c->red = nullptr;
				else c->blue = nullptr;
			}
		};

		for (Warrior* w : allWarriors) {
			if (!w->alive || w->type != 3 || w->side != RED || w->city != 0) continue;
			if (w->loyalty <= 0) runAway(w, nullptr);
		}

		for (int i = 1; i <= N; ++i) {
			City& c = cities[i];
			if (c.red && c.red->alive && c.red->type == 3 && c.red->loyalty <= 0) {
				runAway(c.red, &c);
			}
			if (c.blue && c.blue->alive && c.blue->type == 3 && c.blue->loyalty <= 0) {
				runAway(c.blue, &c);
			}
		}

		for (Warrior* w : allWarriors) {
			if (!w->alive || w->type != 3 || w->side != BLUE || w->city != N + 1) continue;
			if (w->loyalty <= 0) runAway(w, nullptr);
		}
	}

	void move(int time) {
		string t = formatTime(time);
		vector<Warrior*> movedRed(N + 2, nullptr);
		vector<Warrior*> movedBlue(N + 2, nullptr);

		int prevBlueInRedHQ = 0;
		int prevRedInBlueHQ = 0;
		for (Warrior* w : allWarriors) {
			if (!w->alive) continue;
			if (w->side == BLUE && w->city == 0) prevBlueInRedHQ++;
			if (w->side == RED && w->city == N + 1) prevRedInBlueHQ++;
		}

		for (int i = 1; i <= N; ++i) {
			cities[i].red = nullptr;
			cities[i].blue = nullptr;
		}

		for (Warrior* w : allWarriors) {
			if (!w->alive) continue;
			int oldCity = w->city;
			int newCity = oldCity;
			bool moved = false;
			if (w->side == RED) {
				if (oldCity != N + 1) {
					newCity = oldCity + 1;
					moved = true;
				}
			} else {
				if (oldCity != 0) {
					newCity = oldCity - 1;
					moved = true;
				}
			}
			if (moved) {
				w->city = newCity;
				if (w->type == 2) {
					w->steps++;
					if (w->steps % 2 == 0) {
						w->hp -= 9;
						if (w->hp <= 0) w->hp = 1;
						w->atk += 20;
					}
				}
				if (w->side == RED) movedRed[newCity] = w;
				else movedBlue[newCity] = w;
			}
			if (w->city >= 1 && w->city <= N) {
				City& c = cities[w->city];
				if (w->side == RED) c.red = w;
				else c.blue = w;
			}
		}

		int blueInRedHQ = prevBlueInRedHQ;
		int redInBlueHQ = prevRedInBlueHQ;
		bool redTakenPrinted = false;
		bool blueTakenPrinted = false;

		for (int i = 0; i <= N + 1; ++i) {
			if (movedRed[i]) {
				Warrior* w = movedRed[i];
				if (i == N + 1) {
					cout << t << " red " << typeName(w->type) << " " << w->id
						 << " reached blue headquarter with " << w->hp
						 << " elements and force " << w->atk << "\n";
					redInBlueHQ++;
					if (!blueTakenPrinted && redInBlueHQ >= 2) {
						cout << t << " blue headquarter was taken\n";
						blueTakenPrinted = true;
						warEnded = true;
					}
				} else {
					cout << t << " red " << typeName(w->type) << " " << w->id
						 << " marched to city " << i << " with " << w->hp
						 << " elements and force " << w->atk << "\n";
				}
			}
			if (movedBlue[i]) {
				Warrior* w = movedBlue[i];
				if (i == 0) {
					cout << t << " blue " << typeName(w->type) << " " << w->id
						 << " reached red headquarter with " << w->hp
						 << " elements and force " << w->atk << "\n";
					blueInRedHQ++;
					if (!redTakenPrinted && blueInRedHQ >= 2) {
						cout << t << " red headquarter was taken\n";
						redTakenPrinted = true;
						warEnded = true;
					}
				} else {
					cout << t << " blue " << typeName(w->type) << " " << w->id
						 << " marched to city " << i << " with " << w->hp
						 << " elements and force " << w->atk << "\n";
				}
			}
		}
	}

	void produceElements() {
		for (int i = 1; i <= N; ++i) {
			cities[i].elements += 10;
		}
	}

	void collectElements(int time) {
		string t = formatTime(time);
		for (int i = 1; i <= N; ++i) {
			City& c = cities[i];
			bool redAlive = c.red && c.red->alive;
			bool blueAlive = c.blue && c.blue->alive;
			if (redAlive && !blueAlive) {
				redHQ.elements += c.elements;
				cout << t << " red " << typeName(c.red->type) << " " << c.red->id
					 << " earned " << c.elements << " elements for his headquarter\n";
				c.elements = 0;
			} else if (blueAlive && !redAlive) {
				blueHQ.elements += c.elements;
				cout << t << " blue " << typeName(c.blue->type) << " " << c.blue->id
					 << " earned " << c.elements << " elements for his headquarter\n";
				c.elements = 0;
			}
		}
	}

	void arrowAttack(int time) {
		string t = formatTime(time);
		struct Shot { Warrior* shooter; Warrior* target; int city; Side side; };
		vector<Shot> shots;

		for (int i = 1; i <= N; ++i) {
			City& c = cities[i];
			bool redAlive = c.red && c.red->alive;
			bool blueAlive = c.blue && c.blue->alive;
			c.hadBothBeforeArrow = redAlive && blueAlive;
		}

		for (int i = 1; i <= N; ++i) {
			City& c = cities[i];
			if (c.red && c.red->alive && c.red->hasArrow) {
				int targetCity = i + 1;
				if (targetCity >= 1 && targetCity <= N) {
					City& next = cities[targetCity];
					if (next.blue && next.blue->alive) {
						shots.push_back({c.red, next.blue, i, RED});
					}
				}
			}
			if (c.blue && c.blue->alive && c.blue->hasArrow) {
				int targetCity = i - 1;
				if (targetCity >= 1 && targetCity <= N) {
					City& prev = cities[targetCity];
					if (prev.red && prev.red->alive) {
						shots.push_back({c.blue, prev.red, i, BLUE});
					}
				}
			}
		}

		sort(shots.begin(), shots.end(), [](const Shot& a, const Shot& b) {
			if (a.city != b.city) return a.city < b.city;
			return a.side < b.side;
		});

		for (const Shot& s : shots) {
			if (s.shooter->hasArrow) {
				s.shooter->arrowUses -= 1;
				if (s.shooter->arrowUses <= 0) {
					s.shooter->hasArrow = false;
				}
			}

			s.target->hp -= R;
			if (s.target->hp < 0) s.target->hp = 0;
			bool killed = s.target->hp == 0;
			if (killed) {
				s.target->alive = false;
				s.target->killedByArrow = true;
			}

			cout << t << " " << sideName(s.shooter->side) << " " << typeName(s.shooter->type)
				 << " " << s.shooter->id << " shot";
			if (killed) {
				cout << " and killed " << sideName(s.target->side) << " "
					 << typeName(s.target->type) << " " << s.target->id;
			}
			cout << "\n";
		}
	}

	Side attackerSide(const City& c) const {
		if (c.flag == RED) return RED;
		if (c.flag == BLUE) return BLUE;
		return (c.index % 2 == 1) ? RED : BLUE;
	}

	void bombAttack(int time) {
		string t = formatTime(time);
		for (int i = 1; i <= N; ++i) {
			City& c = cities[i];
			c.bombed = false;
			if (!(c.red && c.blue)) continue;
			if (!(c.red->alive && c.blue->alive)) continue;

			Side atkSide = attackerSide(c);
			Warrior* attacker = (atkSide == RED) ? c.red : c.blue;
			Warrior* defender = (atkSide == RED) ? c.blue : c.red;

			int attackDamage = attacker->atk + attacker->swordPower();
			bool defenderDies = attackDamage >= defender->hp;
			bool attackerDies = false;
			if (!defenderDies && defender->type != 1) {
				int counterDamage = (defender->atk / 2) + defender->swordPower();
				attackerDies = counterDamage >= attacker->hp;
			}

			Warrior* bomber = nullptr;
			Warrior* other = nullptr;
			if (attackerDies && attacker->hasBomb) {
				bomber = attacker;
				other = defender;
			} else if (defenderDies && defender->hasBomb) {
				bomber = defender;
				other = attacker;
			}

			if (bomber) {
				cout << t << " " << sideName(bomber->side) << " " << typeName(bomber->type)
					 << " " << bomber->id << " used a bomb and killed "
					 << sideName(other->side) << " " << typeName(other->type)
					 << " " << other->id << "\n";
				bomber->alive = false;
				other->alive = false;
				bomber->hasBomb = false;
				c.bombed = true;
				c.red = nullptr;
				c.blue = nullptr;
			}
		}
	}

	void wolfCapture(Warrior* wolf, Warrior* enemy) {
		if (wolf->type != 4 || !enemy) return;
		if (!wolf->hasSword && enemy->hasSword && enemy->sword > 0) {
			wolf->hasSword = true;
			wolf->sword = enemy->sword;
		}
		if (!wolf->hasBomb && enemy->hasBomb) {
			wolf->hasBomb = true;
		}
		if (!wolf->hasArrow && enemy->hasArrow && enemy->arrowUses > 0) {
			wolf->hasArrow = true;
			wolf->arrowUses = enemy->arrowUses;
		}
	}

	void battle(int time) {
		string t = formatTime(time);
		vector<vector<string>> lines(N + 1);
		vector<WinnerInfo> redWinners;
		vector<WinnerInfo> blueWinners;
		vector<int> earned(N + 1, 0);
		vector<bool> hasWinner(N + 1, false);
		vector<Side> winnerSide(N + 1, NONE);

		for (int i = 1; i <= N; ++i) {
			City& c = cities[i];
			if (c.bombed) {
				c.hadBothBeforeArrow = false;
				continue;
			}
			Warrior* red = c.red;
			Warrior* blue = c.blue;
			bool redAlive = red && red->alive;
			bool blueAlive = blue && blue->alive;

			bool arrowWin = c.hadBothBeforeArrow && (redAlive ^ blueAlive);
			if (redAlive && blueAlive) {
				Side atkSide = attackerSide(c);
				Warrior* attacker = (atkSide == RED) ? red : blue;
				Warrior* defender = (atkSide == RED) ? blue : red;
				int attackerPreHp = attacker->hp;
				int attackerPreAtk = attacker->atk;
				int defenderPreHp = defender->hp;
				int defenderPreAtk = defender->atk;

				{
					ostringstream oss;
					oss << t << " " << sideName(attacker->side) << " "
						<< typeName(attacker->type) << " " << attacker->id
						<< " attacked " << sideName(defender->side) << " "
						<< typeName(defender->type) << " " << defender->id
						<< " in city " << i << " with " << attackerPreHp
						<< " elements and force " << attackerPreAtk;
					lines[i].push_back(oss.str());
				}

				int attackDamage = attacker->atk + attacker->swordPower();
				defender->hp -= attackDamage;
				if (defender->hp < 0) defender->hp = 0;
				attacker->degradeSword();

				Warrior* winner = nullptr;
				Warrior* loser = nullptr;
				bool tie = false;

				if (defender->hp == 0) {
					defender->alive = false;
					if (defender->type == 3) attacker->hp += defenderPreHp;
					{
						ostringstream oss;
						oss << t << " " << sideName(defender->side) << " "
							<< typeName(defender->type) << " " << defender->id
							<< " was killed in city " << i;
						lines[i].push_back(oss.str());
					}
					winner = attacker;
					loser = defender;
				} else {
					if (defender->type != 1) {
						{
							ostringstream oss;
							oss << t << " " << sideName(defender->side) << " "
								<< typeName(defender->type) << " " << defender->id
								<< " fought back against " << sideName(attacker->side) << " "
								<< typeName(attacker->type) << " " << attacker->id
								<< " in city " << i;
							lines[i].push_back(oss.str());
						}
						int counterDamage = (defender->atk / 2) + defender->swordPower();
						attacker->hp -= counterDamage;
						if (attacker->hp < 0) attacker->hp = 0;
						defender->degradeSword();
						if (attacker->hp == 0) {
							attacker->alive = false;
							if (attacker->type == 3) defender->hp += attackerPreHp;
							{
								ostringstream oss;
								oss << t << " " << sideName(attacker->side) << " "
									<< typeName(attacker->type) << " " << attacker->id
									<< " was killed in city " << i;
								lines[i].push_back(oss.str());
							}
							winner = defender;
							loser = attacker;
						} else {
							tie = true;
						}
					} else {
						tie = true;
					}
				}

				if (winner) {
					if (winner->type == 0) winner->morale += 0.2;
					wolfCapture(winner, loser);
				} else if (tie) {
					if (attacker->alive && attacker->type == 0) attacker->morale -= 0.2;
					if (defender->alive && defender->type == 0) defender->morale -= 0.2;
					if (attacker->alive && attacker->type == 3) attacker->loyalty -= K;
					if (defender->alive && defender->type == 3) defender->loyalty -= K;
				}

				if (winner && winner->type == 0) {
					// morale already updated above
				}

				if (attacker->alive && attacker->type == 0 && attacker->morale > 0.8) {
					ostringstream oss;
					oss << t << " " << sideName(attacker->side) << " "
						<< typeName(attacker->type) << " " << attacker->id
						<< " yelled in city " << i;
					lines[i].push_back(oss.str());
				}

				if (winner) {
					hasWinner[i] = true;
					earned[i] = c.elements;
					if (winner->side == RED) redWinners.push_back({winner, i});
					else blueWinners.push_back({winner, i});
					winnerSide[i] = winner->side;

					ostringstream oss;
					oss << t << " " << sideName(winner->side) << " "
						<< typeName(winner->type) << " " << winner->id
						<< " earned " << earned[i] << " elements for his headquarter";
					lines[i].push_back(oss.str());

					if (c.lastWinner == winner->side && c.flag != winner->side) {
						c.flag = winner->side;
						ostringstream f;
						f << t << " " << sideName(winner->side) << " flag raised in city " << i;
						lines[i].push_back(f.str());
					}
					c.lastWinner = winner->side;
				} else if (tie) {
					c.lastWinner = NONE;
				}
			} else if (arrowWin) {
				Warrior* winner = redAlive ? red : blue;
				Warrior* loser = redAlive ? blue : red;
				if (winner && winner->type == 0) winner->morale += 0.2;
				if (winner && winner->type == 4) wolfCapture(winner, loser);

				Side atkSide = attackerSide(c);
				Warrior* attacker = (atkSide == RED) ? red : blue;
				if (attacker && attacker->alive && attacker->type == 0 && attacker->morale > 0.8) {
					ostringstream oss;
					oss << t << " " << sideName(attacker->side) << " "
						<< typeName(attacker->type) << " " << attacker->id
						<< " yelled in city " << i;
					lines[i].push_back(oss.str());
				}

				if (winner) {
					hasWinner[i] = true;
					earned[i] = c.elements;
					if (winner->side == RED) redWinners.push_back({winner, i});
					else blueWinners.push_back({winner, i});
					winnerSide[i] = winner->side;

					ostringstream oss;
					oss << t << " " << sideName(winner->side) << " "
						<< typeName(winner->type) << " " << winner->id
						<< " earned " << earned[i] << " elements for his headquarter";
					lines[i].push_back(oss.str());

					if (c.lastWinner == winner->side && c.flag != winner->side) {
						c.flag = winner->side;
						ostringstream f;
						f << t << " " << sideName(winner->side) << " flag raised in city " << i;
						lines[i].push_back(f.str());
					}
					c.lastWinner = winner->side;
				}
			}

			c.hadBothBeforeArrow = false;
		}

		sort(redWinners.begin(), redWinners.end(), [](const WinnerInfo& a, const WinnerInfo& b) {
			return a.city > b.city;
		});
		sort(blueWinners.begin(), blueWinners.end(), [](const WinnerInfo& a, const WinnerInfo& b) {
			return a.city < b.city;
		});

		for (const auto& w : redWinners) {
			if (redHQ.elements >= 8) {
				redHQ.elements -= 8;
				w.w->hp += 8;
			}
		}
		for (const auto& w : blueWinners) {
			if (blueHQ.elements >= 8) {
				blueHQ.elements -= 8;
				w.w->hp += 8;
			}
		}

		for (int i = 1; i <= N; ++i) {
			for (const string& line : lines[i]) {
				cout << line << "\n";
			}
			if (hasWinner[i]) {
				City& c = cities[i];
				if (winnerSide[i] == RED) redHQ.elements += earned[i];
				if (winnerSide[i] == BLUE) blueHQ.elements += earned[i];
				c.elements = 0;
			}
		}

		for (int i = 1; i <= N; ++i) {
			City& c = cities[i];
			if (c.red && !c.red->alive) c.red = nullptr;
			if (c.blue && !c.blue->alive) c.blue = nullptr;
			c.bombed = false;
		}
	}

	void reportElements(int time) {
		string t = formatTime(time);
		cout << t << " " << redHQ.elements << " elements in red headquarter\n";
		cout << t << " " << blueHQ.elements << " elements in blue headquarter\n";
	}

	string weaponReport(Warrior* w) {
		vector<string> parts;
		if (w->hasArrow) {
			parts.push_back(string("arrow(") + to_string(w->arrowUses) + ")");
		}
		if (w->hasBomb) {
			parts.push_back("bomb");
		}
		if (w->hasSword) {
			parts.push_back(string("sword(") + to_string(w->sword) + ")");
		}
		if (parts.empty()) return "has no weapon";
		string res = "has ";
		for (size_t i = 0; i < parts.size(); ++i) {
			if (i) res += ",";
			res += parts[i];
		}
		return res;
	}

	void reportWeapons(int time) {
		string t = formatTime(time);
		vector<Warrior*> redList, blueList;
		for (Warrior* w : allWarriors) {
			if (!w->alive) continue;
			if (w->side == RED) redList.push_back(w);
			else blueList.push_back(w);
		}

		auto sorter = [](Warrior* a, Warrior* b) {
			if (a->city != b->city) return a->city < b->city;
			return a->id < b->id;
		};
		sort(redList.begin(), redList.end(), sorter);
		sort(blueList.begin(), blueList.end(), sorter);

		for (Warrior* w : redList) {
			cout << t << " red " << typeName(w->type) << " " << w->id << " "
				 << weaponReport(w) << "\n";
		}
		for (Warrior* w : blueList) {
			cout << t << " blue " << typeName(w->type) << " " << w->id << " "
				 << weaponReport(w) << "\n";
		}
	}

	void run() {
		setup();
		for (int base = 0; base <= T && !warEnded; base += 60) {
			if (base <= T) produce(base);
			if (base + 5 <= T && !warEnded) lionEscape(base + 5);
			if (base + 10 <= T && !warEnded) {
				move(base + 10);
				if (warEnded) break;
			}
			if (base + 20 <= T && !warEnded) produceElements();
			if (base + 30 <= T && !warEnded) collectElements(base + 30);
			if (base + 35 <= T && !warEnded) arrowAttack(base + 35);
			if (base + 38 <= T && !warEnded) bombAttack(base + 38);
			if (base + 40 <= T && !warEnded) battle(base + 40);
			if (base + 50 <= T && !warEnded) reportElements(base + 50);
			if (base + 55 <= T && !warEnded) reportWeapons(base + 55);
		}
	}
};

int main() {
	int cases = 0;
	if (!(cin >> cases)) return 0;
	for (int cs = 1; cs <= cases; ++cs) {
		Game game;
		cin >> game.M >> game.N >> game.R >> game.K >> game.T;
		game.initHp.resize(5);
		game.initAtk.resize(5);
		for (int i = 0; i < 5; ++i) cin >> game.initHp[i];
		for (int i = 0; i < 5; ++i) cin >> game.initAtk[i];
		cout << "Case " << cs << ":\n";
		game.run();
	}
	return 0;
}
