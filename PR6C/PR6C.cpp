#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <Windows.h>

using namespace std;

class Player {
protected:
    string name;
    double score;
public:
    Player(string name, double score) {
        this->name = name;
        this->score = score;
    }
    int health = 100;
    void Attack(int damage) {
        cout << "Вы атакуете и получаете " << damage << " урона и 30 очков" << endl;
        addScore(30);
        health -= damage;
        cout << "Ваше здоровье: " << health << endl;
    }
    void Defend() {
        cout << "Вы защищаетесь и получаете 20 очков" << endl;
        addScore(20);
        cout << "Ваше здоровье: " << health << endl;
    }
    string getName() const {
        return name;
    }

    double getScore() const {
        return score;
    }

    void addScore(double points) {
        score += points;
    }

    void displayInfo() const {
        cout << "Игрок: " << name << ", Здоровье: " << health << ", Очки: " << score << endl;
    }
};

class World {
protected:
    string name;
public:
    World(string name) {
        this->name = name;
    }
    void Weather() {
        string weatherConditions[] = { "Солнечно", "Дождливо", "Облачно", "Ветрено", "Туманно" };
        int randomIndex = rand() % (sizeof(weatherConditions) / sizeof(weatherConditions[0]));
        cout << "Состояние погоды: " << weatherConditions[randomIndex] << endl;
    }
};

class Monster {
protected:
    string nameM;
    int damage;
public:
    Monster(string name, int damage) {
        this->nameM = name;
        this->damage = damage;
    }
    void AttackMonster(int damage) {
        cout << "Монстр " << nameM << " атакует и наносит " << damage << " урона" << endl;
    }

    string getName() const { // Метод для получения имени монстра
        return nameM;
    }

    int getDamage() const { // Метод для получения силы монстра
        return damage;
    }
};


class Game : public Monster, public World 
{
public:
    Game(string monsterName, int monsterDamage, string worldName) : Monster(monsterName, monsterDamage), World(worldName) {}
    void StartGame() {
        cout << "Игра началась!" << endl;
        Weather();
    }

    void EndGame() {
        cout << "Игра завершена!" << endl;
    }

    void EncounterMonster(Monster& monster) {
        cout << "Вы столкнулись с монстром " << monster.getName() << endl;
        monster.AttackMonster(monster.getDamage());
    }
};


int main() {
    srand(time(0));

    SetConsoleCP(1251);
    setlocale(LC_ALL, "Russian");

    int action, b;
    string playerName;
    bool playerCreated = false; // Флаг, указывающий, был ли создан персонаж
    Player player("", 0); // Создаем временного игрока
    Monster monster("Злой монстр", 20); // Обновляем монстра
    World world("Мир"); // Создаем временный мир
    Game game("", 0, ""); // Инициализируем объект game

    do {
        cout << "Выберите действие: \n1. Создать персонажа \n2. Начать игру\n3. Выйти из игры\n\n";
        cin >> action;

        switch (action) {
        case 1: {
            cout << "Введите имя персонажа: ";
            cin >> playerName;
            player = Player(playerName, 0);
            playerCreated = true;
            break;
        }
        case 2: {
            if (playerCreated) {
                game.StartGame(); // Начинаем игру

                game.EncounterMonster(monster);

                int i = 100;
                while (i != 0) {
                    cout << "Выберите действие: \n1. Атаковать \n2. Защищаться\n" << endl;
                    cin >> b;

                    if (b == 1) {
                        player.Attack(monster.getDamage());
                        i = i - 50;
                        cout << "Здоровье монстра: " << i << "HP\n" << endl;
                        
                    }
                    else if (b == 2) {
                        player.Defend();
                    }
                    else {
                        cout << "Введено неправильное действие" << endl;
                    }
                }

                player.displayInfo();
                game.EndGame();

            }
            else {
                cout << "Сначала создайте персонажа!" << endl;
            }
            break;
        }
        }
    } while (action != 3); // Выполнять цикл до тех пор, пока не будет выбрано действие "Выйти из игры"

    return 0;
}

