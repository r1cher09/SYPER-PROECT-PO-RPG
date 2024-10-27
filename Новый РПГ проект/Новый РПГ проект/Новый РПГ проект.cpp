// РПГ ИГРА.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <chrono>
#include <vector>
#include <string>
#include <conio.h>
using namespace std;

void paths(int a, int b, int defen, int atk, int erud) {
    cout << "______________________________________________\n";
    cout << "    Открыть меню путей прокачки?              \n";
    cout << "  1) Нет                      2) Да           \n";
    cout << "______________________________________________\n";
    cin >> a;
    if (a == 1) {
        cout << "\n";
    }
    if (a == 2) {

        cout << "______________________________________________\n";
        cout << "            Кол-во очков:                     \n";
        cout << b << "\n";
        if (b == 0) {
            cout << "     Вам не хватило очков для прокачки.       \n";
            cout << "   Очки можно получить, сходив в Оптику.      \n";
            this_thread::sleep_for(chrono::nanoseconds(3000000000));
            cout << "          Да ладно, смешно же.                \n";
            cout << "   Очки можно получить  по ходу сюжета.       \n";
            cout << "  После выполнения заданий и побед в боях     \n";
            cout << "  вы будете получать по одному очку.          \n";
            cout << "______________________________________________\n";
            this_thread::sleep_for(chrono::nanoseconds(3000000000));
            return;

        }
        cout << "             1) ЗАЩИТА                       \n";
        cout << "  2)нАПАДЕНИЕ          3)ЭРУДИЦИЯ             \n";
        cout << "                                              \n";
        cout << "______________________________________________\n";
        cin >> a;

        if (a == 1) {
            defen = defen + 20;
            b--;
            cout << "             ЗАЩИТА равна:                    \n";
            cout << defen << "\n";
            cout << "             АТАКА равна:                     \n";
            cout << atk << "\n";
            cout << "             ЭРУДИЦИЯ равна:                  \n";
            cout << erud << "\n";
        }
        if (a == 2) {
            atk = atk + 15;
            b--;
            cout << "             ЗАЩИТА равна:                    \n";
            cout << defen << "\n";
            cout << "             АТАКА равна:                     \n";
            cout << atk << "\n";
            cout << "             ЭРУДИЦИЯ равна:                  \n";
            cout << erud << "\n";
        }
        if (a == 3) {
            erud = erud + 1;
            b--;
            cout << "             ЗАЩИТА равна:                    \n";
            cout << defen << "\n";
            cout << "             АТАКА равна:                     \n";
            cout << atk << "\n";
            cout << "             ЭРУДИЦИЯ равна:                  \n";
            cout << erud << "\n";
        }
    }

}
//Говнокод on
//Механика нвентаря
struct Item {
    string name;
    string description;
    int price;
};

class Inventory {
public:
    void addItem(const Item& item) { items.push_back(item); }
    void removeItem(const string& itemName);
    void viewInventory() const;
    vector<Item> items;
};

void Inventory::removeItem(const string& itemName) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->name == itemName) {
            items.erase(it);
            return;
        }
    }
}

void Inventory::viewInventory() const {
    for (const auto& item : items) {
        cout << "\n" << "Название: " << item.name << "\nОписание: " << item.description << "\nЦена: " << item.price << "\n\n";
    }
}

bool hasRequiredItems(const Inventory& playerInventory) { //Проверка на наличие предметов
    bool hasSword = false;
    bool hasMatchesOrLighter = false;

    for (const auto& item : playerInventory.items) {
        if (item.name == "Меч") {
            hasSword = true;
        }
        if (item.name == "Спички" || item.name == "Зажигалка") {
            hasMatchesOrLighter = true;
        }
    }

    return hasSword && hasMatchesOrLighter;
}
//

//Механика магазина
class Shop {
public:
    void addItem(const Item& item) { shopItems.push_back(item); }
    void viewShop() const;
    bool buyItem(const string& itemName, Inventory& playerInventory, int& playerCoins);
    void initializeItems(); // Новая функция для добавления предметов в магазин
private:
    vector<Item> shopItems;
};

void Shop::viewShop() const {
    for (const auto& item : shopItems) {
        cout << "\n" << "Название: " << item.name << "\nОписание: " << item.description << "\nЦена: " << item.price << "\n\n";
    }
}

bool Shop::buyItem(const string& itemName, Inventory& playerInventory, int& playerCoins) {
    for (const auto& item : shopItems) {
        if (item.name == itemName) {
            if (playerCoins >= item.price) {
                playerInventory.addItem(item);
                playerCoins -= item.price;
                return true;
            }
            else {
                cout << "Недостаточно монет для покупки " << itemName << ".\n";
                return false;
            }
        }
    }
    cout << "Предмет " << itemName << " не найден в магазине.\n";
    this_thread::sleep_for(chrono::nanoseconds(3000000000));
    return false;
}

void Shop::initializeItems() {
    addItem({ "Меч", "Острый меч для сражений", 50 });
    addItem({ "Верёвка", "Крепкая верёвка длиной 10 метров", 20 });
    addItem({ "Зажигалка", "Зажигалка для разведения огня", 10 });
    addItem({ "Спички", "Пачка спичек", 5 });
}
//

//Управление инвентарем и магазином
//Инвентарь
void manageInventory(Inventory& playerInventory, int& playerCoins) {
    bool running = true;
    while (running) {
        cout << "Ваши монеты: " << playerCoins << "\n";
        cout << "1. Посмотреть инвентарь\n";
        cout << "2. Добавить предмет в инвентарь\n";
        cout << "3. Удалить предмет из инвентаря\n";
        cout << "4. Вернуться в главное меню\n";
        cout << "Выберите действие: ";
        int choice;
        cin >> choice;
        cin.ignore(); // Игнорируем оставшиеся символы

        switch (choice) {
        case 1:
            playerInventory.viewInventory();
            break;
        case 2: {
            string itemName, itemDescription;
            int itemPrice;
            cout << "Введите название предмета: ";
            getline(cin, itemName);
            cout << "Введите описание предмета: ";
            getline(cin, itemDescription);
            cout << "Введите цену предмета: ";
            cin >> itemPrice;
            playerInventory.addItem({ itemName, itemDescription, itemPrice });
            break;
        }
        case 3: {
            string itemName;
            cout << "Введите название предмета для удаления: ";
            getline(cin, itemName);
            playerInventory.removeItem(itemName);
            break;
        }
        case 4:
            running = false;
            break;
        default:
            cout << "Неверный выбор!\n";
            break;
        }
    }
}

void checkForInventoryKey(Inventory& playerInventory, int& playerCoins) {
    if (_kbhit()) { // Проверяем, была ли нажата клавиша
        char ch = _getch(); // Получаем нажатую клавишу
        if (ch == 'c' || ch == 'C') { // Проверяем, была ли нажата клавиша "c" или "C"
            manageInventory(playerInventory, playerCoins); // Открываем инвентарь
        }
    }
}

//Магазин
void manageShop(Shop& gameShop, Inventory& playerInventory, int& playerCoins) {
    bool shopping = true;
    while (shopping) {
        cout << "Ваши монеты: " << playerCoins << "\n";
        gameShop.viewShop();
        cout << "Введите номер предмета для покупки:\n";
        cout << "1. Меч\n";
        cout << "2. Верёвка\n";
        cout << "3. Зажигалка\n";
        cout << "4. Спички\n";
        cout << "5. Выход\n";

        int choice;
        cin >> choice;
        string itemName;

        switch (choice) {
        case 1:
            itemName = "Меч";
            break;
        case 2:
            itemName = "Верёвка";
            break;
        case 3:
            itemName = "Зажигалка";
            break;
        case 4:
            itemName = "Спички";
            break;
        case 5:
            shopping = false;
            return; // Выходим из функции
        default:
            cout << "Неверный выбор!\n";
            continue;
        }

        if (gameShop.buyItem(itemName, playerInventory, playerCoins)) {
            cout << "Вы купили " << itemName << "\n";
        }
        else {
            cout << "Недостаточно монет или предмет не найден\n";
        }
        checkForInventoryKey(playerInventory, playerCoins); // Проверяем нажатие клавиши "c"
    }
}
//
void proceedWithStory(Inventory& playerInventory, Shop& gameShop, int& playerCoins);
void proceedWithStory(Inventory& playerInventory, Shop& gameShop, int& playerCoins) {
    while (!hasRequiredItems(playerInventory)) {
        cout << "Для продолжения вам нужно купить меч и спички или зажигалку.\n";
        manageShop(gameShop, playerInventory, playerCoins);
    }
    cout << "Теперь у вас есть необходимые предметы для продолжения.\n";
}
//Говнокод off

int main() {
    setlocale(LC_ALL, "ru_RU");
    int vibor_igroka, vibor_igroka2, vibor_igroka3, vibor_igroka4, vibor_igroka5 = 0, health, atk, enemyhealth, fight, defence = 0, erud = 0, b = 0, a = 0;
    int r;//нужен только для for
    Inventory playerInventory;
    Shop gameShop;
    int playerCoins = 0;
    gameShop.initializeItems();
    atk = 50;
    r = 0;
    for (r = 0; r < 1; r++) {
        do {
            cout << "______________________________________________\n";
            cout << "| ВЫ-король  города и отправились перевозить |\n";
            cout << "| ценные ресурсы, но на вас резко напали     |\n";
            cout << "| бандиты, перевернув вашу повозку они       |\n";
            cout << "| забрали все ресурсы и уехали бросив вас    |\n";
            cout << "| в лесу на растерзание волкам, когда вы     |\n";
            cout << "| проснулись вы забыли все, но то что у вас  |\n";
            cout << "| было все, деньги,слава,популярность. У вас |\n";
            cout << "| это все пропало в один миг, вас это очень  |\n";
            cout << "| очень растроило, и вы решили вернуть себе  |\n";
            cout << "| все что у вас было до этого, но сначало вам|\n";
            cout << "| нужно добыть деньги и популярность чтобы   |\n";
            cout << "| чтобы снова стать королем города           |\n";
            cout << "| (чтобы выбрать свой выбор вам надо ввести  |\n";
            cout << "| цифру выбора и нажать enter, если вы ввели |\n";
            cout << "| не существующую цифру то текст выведеться  |\n";
            cout << "| еще раз и выбор предложиться заного)       |\n";
            cout << "|                                            |\n";
            cout << "|  |1|оглядеться                             |\n";
            cout << "|____________________________________________|\n";
            cin >> vibor_igroka;
        } while (vibor_igroka != 1);
        if (vibor_igroka == 1) {
            do {

                cout << "______________________________________________\n";
                cout << "|   рядом с вами тропинка и сундук           |\n";
                cout << "|                                            |\n";
                cout << "| |1|пойти по тропинке |2|открыть сундук     |\n";
                cout << "|____________________________________________|\n";
                cin >> vibor_igroka5;
            } while (vibor_igroka5 != 1 && vibor_igroka5 != 2);
            vibor_igroka = 0;
            vibor_igroka2 = 0;
            vibor_igroka3 = 0;
            vibor_igroka4 = 0;
        }
        if (vibor_igroka5 == 2) {
            do {

                cout << "______________________________________________\n";
                cout << "|              вы слишком слабы!             |\n";
                cout << "|                                            |\n";
                cout << "|             |1|пойти по тропинке           |\n";
                cout << "|____________________________________________|\n";
                cin >> vibor_igroka5;
            } while (vibor_igroka5 != 1);
            vibor_igroka = 0;
            vibor_igroka2 = 0;
            vibor_igroka3 = 0;
            vibor_igroka4 = 0;
        }
        if (vibor_igroka5 == 1) {//Пойти по тропинке
            do {
                for (int i = 0; i < 1; i++) {
    cout << "______________________________________________\n";
    cout << "    Открыть меню путей прокачки?              \n";
    cout << "  1) Нет                      2) Да           \n";
    cout << "______________________________________________\n";
    cin >> a;
    if (a == 1) {
        break;
    }
    if (a == 2) {

        cout << "______________________________________________\n";
        if (b == 0) {
            cout << "     Вам не хватило очков для прокачки.       \n";
            cout << "   Очки можно получить, сходив в Оптику.      \n";
            this_thread::sleep_for(chrono::nanoseconds(3000000000));
            cout << "          Да ладно, смешно же.                \n";
            cout << "   Очки можно получить  по ходу сюжета.       \n";
            cout << "  После выполнения заданий и побед в боях     \n";
            cout << "  вы будете получать по одному очку.          \n";
            cout << "______________________________________________\n";
            this_thread::sleep_for(chrono::nanoseconds(3000000000));
            break;
        }

    }
    cout << "             1) ЗАЩИТА                       \n";
    cout << "  2)нАПАДЕНИЕ          3)ЭРУДИЦИЯ             \n";
    cout << "                                              \n";
    cout << "______________________________________________\n";
    cin >> a;

    if (a == 1) {
        defence = defence + 20;
        b--;
        cout << "             ЗАЩИТА равна:                    \n";
        cout << defence << "\n";
        cout << "             АТАКА равна:                     \n";
        cout << atk << "\n";
        cout << "             ЭРУДИЦИЯ равна:                  \n";
        cout << erud << "\n";
    }
    if (a == 2) {
        atk = atk + 15;
        b--;
        cout << "             ЗАЩИТА равна:                    \n";
        cout << defence << "\n";
        cout << "             АТАКА равна:                     \n";
        cout << atk << "\n";
        cout << "             ЭРУДИЦИЯ равна:                  \n";
        cout << erud << "\n";
       
    }
    if (a == 3) {
        erud = erud + 1;
        b--;

        cout << "             ЗАЩИТА равна:                    \n";
        cout << defence << "\n";
        cout << "             АТАКА равна:                     \n";
        cout << atk << "\n";
        cout << "             ЭРУДИЦИЯ равна:                  \n";
        cout << erud << "\n";
    }
}

                cout << "______________________________________________\n";
                cout << "| вы пошли по тропинке и наткнулись на       |\n";
                cout << "| странного человека в одежде колдуна, он    |\n";
                cout << "| попросил вас выполнить его задание, он     |\n";
                cout << "| так же сказал вам что задания будут не     |\n";
                cout << "| сложными и их будет всеголишь 9, если ты   |\n";
                cout << "| выполнишь все задания то ты станешь самым  |\n";
                cout << "| богатым, и сможешь купить все что захочешь |\n";
                cout << "|                                            |\n";
                cout << "|  |1|это то что мне и надо! согласиться     |\n";
                cout << "|  |2| пройти мимо                           |\n";
                cout << "|____________________________________________|\n";
                cin >> vibor_igroka2;
            } while (vibor_igroka2 != 1 && vibor_igroka2 != 2);
            if (vibor_igroka2 == 1) {
                do {

                    cout << "______________________________________________\n";
                    cout << "| получив странный конверт вы пошли дальше,  |\n";
                    cout << "| пройдя по тропинке вы видите табличку      |\n";
                    cout << "|   ________________________________________ |\n";
                    cout << "|  | Налево пойдешь - в город попадешь     | |\n";
                    cout << "|  | направо пойдешь - жизнь потеряешь     | |\n";
                    cout << "|  |                                       | |\n";
                    cout << "|  |_______________________________________| |\n";
                    cout << "|                     |                      |\n";
                    cout << "|                                            |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|направо |2|налево                       |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka5;
                } while (vibor_igroka5 != 1 && vibor_igroka5 != 2);
            }
            if (vibor_igroka2 == 2) {
                do {

                    cout << "______________________________________________\n";
                    cout << "| колдун был очень настырным и не дал вам    |\n";
                    cout << "| уйти от него и сказал что убьет вас если   |\n";
                    cout << "| вы не выполните его задание                |\n";
                    cout << "|                                            |\n";
                    cout << "|    |1|согласиться     |2|отказаться        |\n";
                    cout << "|                                            |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka3;
                } while (vibor_igroka3 != 1 && vibor_igroka3 != 2);
                if (vibor_igroka3 == 2) {
                    cout << "______________________________________________\n";
                    cout << "| колдун достает пистолет и стреляет в вас   |\n";
                    cout << "|                                            |\n";
                    cout << "|____________________________________________|\n";
                    this_thread::sleep_for(chrono::nanoseconds(3000000000));
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "___________________________________________________________________________________________________________________________\n";
                    cout << "|Неудача снова достигла тебя? Она не так плоха, как ты думаешь, всё-таки неудача это способ узнать что-то новое, верно?   |\n";
                    cout << "--------------------------------------------------------------------------------------------------------------------------\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    break;
                }
                if (vibor_igroka3 == 1) {
                    vibor_igroka = 1;
                    if (vibor_igroka == 1) {
                        do {

                            cout << "______________________________________________\n";
                            cout << "| получив странный конверт вы пошли дальше,  |\n";
                            cout << "| пройдя по тропинке вы видите табличку      |\n";
                            cout << "|   ________________________________________ |\n";
                            cout << "|  | Налево пойдешь - в город попадешь     | |\n";
                            cout << "|  | направо пойдешь - жизнь потеряешь     | |\n";
                            cout << "|  |                                       | |\n";
                            cout << "|  |_______________________________________| |\n";
                            cout << "|                     |                      |\n";
                            cout << "|                                            |\n";
                            cout << "|                                            |\n";
                            cout << "| |1|направо |2|налево                       |\n";
                            cout << "|____________________________________________|\n";
                            cin >> vibor_igroka5;
                        } while (vibor_igroka5 != 1 && vibor_igroka5 != 2);
                    }
                }
            }
        }


        if (vibor_igroka5 == 1) {//пойти по тропе смерти
            do {

                cout << "______________________________________________\n";
                cout << "| пройдя по тропинке смерти вы замечаете что |\n";
                cout << "| все начинает меняться, листья на деревьях  |\n";
                cout << "| темнеют, трава становиться вся выжженой    |\n";
                cout << "| и так продолжаеться до моста над пропостью |\n";
                cout << "|                                            |\n";
                cout << "| |1|пойти по мосту |2|посмотреть вниз       |\n";
                cout << "|____________________________________________|\n";
                cin >> vibor_igroka2;
            } while (vibor_igroka2 != 1 && vibor_igroka2 != 2);
            if (vibor_igroka2 == 2) {
                do {

                    cout << "______________________________________________\n";
                    cout << "| внизу лава...                              |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|пойти по мосту                          |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka2;
                } while (vibor_igroka2 != 1);
            }
            if (vibor_igroka2 == 1) {
                do {

                    cout << "______________________________________________\n";
                    cout << "| вы ступили на хлипкий деревянный мост имея |\n";
                    cout << "| худшие мысли на уме, пройдя несколько      |\n";
                    cout << "| метро вдали вы увидели окончание моста, вы |\n";
                    cout << "| спокойно дошли до конца и там была лестница|\n";
                    cout << "| вниз, мост сзади как на зло сломался, и вы |\n";
                    cout << "| решили спуститься по лестнице так как пути |\n";
                    cout << "| назад уже не было, спустившись вы увидели  |\n";
                    cout << "| преспешника аида харона, тебя перевести?   |\n";
                    cout << "| спросил харон.                             |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|да, пожалуйста                          |\n";
                    cout << "|                                            |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka5;
                } while (vibor_igroka5 != 1);
            }
        }
        if (vibor_igroka5 == 2) {//ПОЙТИ НА ЛЕВО ПОСЛЕ ТАБЛИЧКИ
            do {

                cout << "______________________________________________\n";
                cout << "| вы спокойно шли но тут <<ПУФ!>> появилась  |\n";
                cout << "| какаято магическая собачка <хей привет,    |\n";
                cout << "| меня зовут альфред, а тебя как? хотя знаешь|\n";//ДОБАВТЕ РАЗГОВОР С СОБАКОЙ
                cout << "| не важно, у меня есть для тебя подарок,    |\n";
                cout << "| знаешь какой? 2 меча, первый это старый    |\n";
                cout << "| дедовский клинок, а второе нож из камня    |\n";
                cout << "|                                            |\n";
                cout << "| |1|выбрать 1 оружие |2|выбрать 2 оружие    |\n";
                cout << "|____________________________________________|\n";
                cin >> vibor_igroka;
            } while (vibor_igroka != 1 && vibor_igroka != 2);
            if (vibor_igroka == 1 or vibor_igroka == 2) {
                if (vibor_igroka == 1 or vibor_igroka == 2) {
                    if (vibor_igroka == 1) {
                        atk = atk + 25;
                    }
                    if (vibor_igroka == 2) {
                        atk = atk + 30;
                    }
                    do {

                        cout << "______________________________________________\n";
                        cout << "| кстати у меня есть еще магазин не хочешь   |\n";
                        cout << "| заглянуть?                                 |\n";
                        cout << "|                                            |\n";
                        cout << "| |1|хочу |2|позже                           |\n";
                        cout << "|____________________________________________|\n";
                        cin >> vibor_igroka2;
                    } while (vibor_igroka2 != 1 && vibor_igroka2 != 2);
                    if (vibor_igroka2 == 1) {
                        manageShop(gameShop, playerInventory, playerCoins); //ДОБАВИЛ МАГАЗИН С СОБАКОЙ
                        vibor_igroka2 = 2;
                    }
                    if (vibor_igroka2 == 2) {

                        cout << "______________________________________________\n";
                        cout << "| ладно, прощай путник, если повезет еще     |\n";
                        cout << "| свидимся. А  главное помни: зло на каждом  |\n";
                        cout << "| шагу. Cмотри под ноги, не вляпайся в него  |\n";
                        cout << "|                                            |\n";
                        cout << "|____________________________________________|\n";
                        this_thread::sleep_for(chrono::nanoseconds(3500000000)); \
                            do {
                                b++;
                                for (int i = 0; i < 1; i++) {
    cout << "______________________________________________\n";
    cout << "    Открыть меню путей прокачки?              \n";
    cout << "  1) Нет                      2) Да           \n";
    cout << "______________________________________________\n";
    cin >> a;
    if (a == 1) {
        break;
    }
    if (a == 2) {

        cout << "______________________________________________\n";
        if (b == 0) {
            cout << "     Вам не хватило очков для прокачки.       \n";
            cout << "   Очки можно получить, сходив в Оптику.      \n";
            this_thread::sleep_for(chrono::nanoseconds(3000000000));
            cout << "          Да ладно, смешно же.                \n";
            cout << "   Очки можно получить  по ходу сюжета.       \n";
            cout << "  После выполнения заданий и побед в боях     \n";
            cout << "  вы будете получать по одному очку.          \n";
            cout << "______________________________________________\n";
            this_thread::sleep_for(chrono::nanoseconds(3000000000));
            break;
        }

    }
    cout << "             1) ЗАЩИТА                       \n";
    cout << "  2)нАПАДЕНИЕ          3)ЭРУДИЦИЯ             \n";
    cout << "                                              \n";
    cout << "______________________________________________\n";
    cin >> a;

    if (a == 1) {
        defence = defence + 20;
        b--;
        cout << "             ЗАЩИТА равна:                    \n";
        cout << defence << "\n";
        cout << "             АТАКА равна:                     \n";
        cout << atk << "\n";
        cout << "             ЭРУДИЦИЯ равна:                  \n";
        cout << erud << "\n";
    }
    if (a == 2) {
        atk = atk + 15;
        b--;
        cout << "             ЗАЩИТА равна:                    \n";
        cout << defence << "\n";
        cout << "             АТАКА равна:                     \n";
        cout << atk << "\n";
        cout << "             ЭРУДИЦИЯ равна:                  \n";
        cout << erud << "\n";
       
    }
    if (a == 3) {
        erud = erud + 1;
        b--;

        cout << "             ЗАЩИТА равна:                    \n";
        cout << defence << "\n";
        cout << "             АТАКА равна:                     \n";
        cout << atk << "\n";
        cout << "             ЭРУДИЦИЯ равна:                  \n";
        cout << erud << "\n";
    }
}
                                cout << "______________________________________________\n";
                                cout << "| <<ПУФ>> собачки как и не было,вы продолжили|\n";
                                cout << "| свой путь, но через несколько десятков     |\n";
                                cout << "| метров вы видите большую стену             |\n";
                                cout << "|                                            |\n";
                                cout << "| |1|пойти налево от стены |2|направо        |\n";
                                cout << "|                                            |\n";
                                cout << "|____________________________________________|\n";
                                cin >> vibor_igroka3;
                            } while (vibor_igroka3 != 1 && vibor_igroka3 != 2);
                        if (vibor_igroka3 == 2) {
                            playerCoins = playerCoins + 200;
                            do {

                                cout << "______________________________________________\n";
                                cout << "| вы пошли направо и вам подвернулась удача, |\n";
                                cout << "| вы нашли пару мемкоинов и желудь на полу, и|\n";
                                cout << "| с ними так же конец дороги и решили пойти  |\n";
                                cout << "| назад и увидели большую надпись ГОРОД, а   |\n";
                                cout << "| так же двух стражников                     |\n";//добавте разговор стражников и главного героя но чтобы героя пропустили
                                cout << "|                                            |\n";
                                cout << "| |1|продолжить  |2|посмотреть количество мем|\n";
                                cout << "| коинов                                     |\n";
                                cout << "|____________________________________________|\n";
                                cin >> vibor_igroka;
                            } while (vibor_igroka != 1 && vibor_igroka != 2);
                        }
                        if (vibor_igroka == 2) {
                            do {

                                cout << "______________________________________________\n";
                                cout << "| у вас " << playerCoins << "                                     | \n";
                                cout << "|                                            |\n";
                                cout << "| |1|продолжить                              |\n";
                                cout << "|____________________________________________|\n";
                                cin >> vibor_igroka;
                            } while (vibor_igroka != 1);
                        }

                        if (vibor_igroka3 == 1) {
                            do {

                                cout << "______________________________________________\n";
                                cout << "| вы увидили большую надпись ГОРОД и двух    |\n";
                                cout << "| стражников                                 |\n";//cюда тоже самое что и в 587 строке
                                cout << "| 1 стражник:Ты кто путник?                  |\n";
                                cout << "| 2 стражник: да полюбому лох какойто        |\n";
                                cout << "|                                            |\n";
                                cout << "| |1|вы должны меня пропустить               |\n";
                                cout << "|____________________________________________|\n";
                                cin >> vibor_igroka;
                            } while (vibor_igroka != 1);
                        }
                        if (vibor_igroka == 1) {
                            do {
                                cout << "______________________________________________\n";
                                cout << "| 1 стражник: Да с чего это вдруг?           |\n";
                                cout << "| 2 стражник: Да-да кто ты?                  |\n";
                                cout << "|                                            |\n";
                                cout << "| |1|соврать |2|сказать правду               |\n";
                                cout << "|____________________________________________|\n";
                                cin >> vibor_igroka;
                            } while (vibor_igroka != 1 && vibor_igroka != 2);
                            if (vibor_igroka == 2) {
                                do {
                                    cout << "______________________________________________\n";
                                    cout << "| <у меня есть писмо для человека>           |\n";
                                    cout << "| 1 стражник: гонец значит?                  |\n";
                                    cout << "| 2 стражник: дада получаеться гонец?        |\n";
                                    cout << "| 1 стражник: а ну покажи письмо             |\n";
                                    cout << "| 2 стражник: да да дай сюда письмо          |\n";
                                    cout << "| *вы протягиваете письмо*                   |\n";
                                    cout << "| *1 стражник отрубает вам руку*             |\n";
                                    cout << "| 1 стражник: а ну катись от сюда! Лгун      |\n";
                                    cout << "| 2 стражник: да да пошел от сюда            |\n";
                                    cout << "|                                            |\n";
                                    cout << "| |1|уйти                                    |\n";
                                    cout << "|____________________________________________|\n";
                                    cin >> vibor_igroka;
                                } while (vibor_igroka != 1);
                                if (vibor_igroka == 1) {
                                    cout << "______________________________________________\n";
                                    cout << "| вы успели уйти не далеко и умерли от потери|\n";
                                    cout << "| крови                                      |\n";
                                    cout << "|____________________________________________|\n";
                                    return 0;
                                }
                            }
                            if (vibor_igroka == 1) {
                                do {
                                    cout << "______________________________________________\n";
                                    cout << "| <я случайно вышел через дырку и вот хочу   |\n";
                                    cout << "| обратно пройти>                            |\n";
                                    cout << "| 1 стражник: ну проходи                     |\n";
                                    cout << "| 2 стражник: да-да проходи                  |\n";
                                    cout << "|                                            |\n";
                                    cout << "| |1|зайти в город                           |\n";
                                    cout << "|____________________________________________|\n";
                                    cin >> vibor_igroka;
                                } while (vibor_igroka != 1);
                            }
                        }
                        if (vibor_igroka == 1) {
                            playerCoins = playerCoins + 500;
                            do {

                                cout << "______________________________________________\n";
                                cout << "| зайдя в город вы сразу увидели много людей,|\n";
                                cout << "| продавцов, пытающихся продать свой товар,  |\n";
                                cout << "| вы начинаете кричать имя человека, которому|\n";
                                cout << "| принесли письмо, тут к вам подбегает       |\n";
                                cout << "| странный мужечек и спрашивает откуда вы его|\n";
                                cout << "| знаете и что вам надо? но вы говоря что это|\n";
                                cout << "| не важно даете ему письмо он вас благодарит|\n";
                                cout << "| дает деньги за задание и уходит в другую   |\n";
                                cout << "| сторону. вы идете дальше вдоль дороги и    |\n";
                                cout << "| видите своего друга Альфреда, который      |\n";
                                cout << "| торговал там                               |\n";
                                cout << "|                                            |\n";
                                cout << "| |1|что то купить |2|посмотреть количество  |\n";
                                cout << "| мемкоинов                                  |\n";
                                cout << "|____________________________________________|\n";
                                cin >> vibor_igroka2;
                            } while (vibor_igroka2 != 1 && vibor_igroka2 != 2);
                            if (vibor_igroka2 == 1)
                                manageShop(gameShop, playerInventory, playerCoins);
                            vibor_igroka2 = 1;
                        }
                        if (vibor_igroka2 == 2) {
                            do {

                                cout << "______________________________________________\n";
                                cout << "| у вас " << playerCoins << "                                  | \n";
                                cout << "|                                            |\n";
                                cout << "| |1|продолжить                              |\n";
                                cout << "|____________________________________________|\n";
                                cin >> vibor_igroka2;
                            } while (vibor_igroka2 != 1);
                            if (vibor_igroka2 == 1) {
                                playerCoins = playerCoins + 500;
                                do {

                                    cout << "______________________________________________\n";
                                    cout << "| зайдя в город вы сразу увидели много людей,|\n";
                                    cout << "| продавцов, пытающихся продать свой товар,  |\n";
                                    cout << "| вы начинаете кричать имя человека, которому|\n";
                                    cout << "| принесли письмо, тут к вам подбегает       |\n";
                                    cout << "| странный мужечек и спрашивает откуда вы его|\n";
                                    cout << "| знаете и что вам надо? но вы говоря что это|\n";
                                    cout << "| не важно даете ему письмо он вас благодарит|\n";
                                    cout << "| дает деньги за задание и уходит в другую   |\n";
                                    cout << "| сторону. вы идете дальше вдоль дороги и    |\n";
                                    cout << "| видите своего друга Альфреда, который      |\n";
                                    cout << "| торговал там                               |\n";
                                    cout << "|                                            |\n";
                                    cout << "| |1|что то купить                           |\n";
                                    cout << "|____________________________________________|\n";
                                    cin >> vibor_igroka2;
                                } while (vibor_igroka2 != 1);
                                if (vibor_igroka2 == 1) {
                                    manageShop(gameShop, playerInventory, playerCoins);
                                    vibor_igroka2 = 1;
                                }
                            }
                        }
                        if (vibor_igroka2 == 1) {
                                do {

                                    cout << "______________________________________________\n";
                                    cout << "| после совершения покупок на улице стало    |\n";
                                    cout << "| темнеть и вам придеться найти ночлег       |\n";
                                    cout << "|                                            |\n";
                                    cout << "| |1|поспать на улице |2|в палатке за деньги |\n";
                                    cout << "|____________________________________________|\n";
                                    cin >> vibor_igroka2;
                                } while (vibor_igroka2 != 1 && vibor_igroka2 != 2);
                                if (vibor_igroka2 == 1) {
                                    do {

                                        cout << "______________________________________________\n";
                                        cout << "| воспав на холодной земле до рассвета вы    |\n";
                                        cout << "| продолжили путь                            |\n";
                                        cout << "|                                            |\n";
                                        cout << "| |1|продолжить путь                         |\n";
                                        cout << "|____________________________________________|\n";
                                        cin >> vibor_igroka3;
                                    } while (vibor_igroka3 != 1);
                                }
                                if (vibor_igroka2 == 2) {
                                    playerCoins = playerCoins - 100;
                                    cout << "______________________________________________\n";
                                    cout << "| проснувшись вы продолжили путь (-100 мем-  |\n";
                                    cout << "| коинов                                     |\n";
                                    cout << "|____________________________________________|\n";
                                    vibor_igroka3 = 1;
                                }
                            }
                            if (vibor_igroka3 == 1) {
                                do {

                                    cout << "______________________________________________\n";
                                    cout << "| пройдясь по улице снова появился колдун    |\n";
                                    cout << "| который так и не представился и сказал вам,|\n";
                                    cout << "| молодец ты прошел одно из моих заданий не  |\n";
                                    cout << "| желаешь продолжить?                        |\n";
                                    cout << "|                                            |\n";
                                    cout << "| |1|звучит как хорошая идея                 |\n";
                                    cout << "|____________________________________________|\n";
                                    cin >> vibor_igroka2;
                                } while (vibor_igroka2 != 1);
                                if (vibor_igroka2 == 1) {
                                    do {
                                        b++;
                                        cout << "______________________________________________\n";
                                        cout << "| хорошая идея стоит продолжить, деньги же   |\n";
                                        cout << "| никогда не бывают лишними, правда? подумали|\n";
                                        cout << "| вы. Хо-хо-хо ну тогда продолжим мой друг!  |\n";
                                        cout << "| второе задание для тебя будет найти и убить|\n";
                                        cout << "| 1 волка возле реки за стеной. Самое легкое |\n";
                                        cout << "| задание за небольшую плату, но есть 1      |\n";
                                        cout << "| условие мой дорогой друг, никто не должен  |\n";
                                        cout << "| знать о том что ты выполняешь мои задания, |\n";
                                        cout << "| а так же если ты откажешься от выполнения  |\n";
                                        cout << "| заданий, то я отправлю тебя в ад и заберу  |\n";
                                        cout << "| все что у тебя есть, это понятно?          |\n";
                                        cout << "|                                            |\n";
                                        cout << "| |1|понятно                                 |\n";
                                        cout << "|____________________________________________|\n";
                                        cin >> vibor_igroka2;
                                    } while (vibor_igroka2 != 1);
                                }
                                if (vibor_igroka2 == 1) {
                                    do {

                                        cout << "______________________________________________\n";
                                        cout << "| <пуф!> И колдуна как и не было. Думая о    |\n";
                                        cout << "| речке вы не знали как лучше к ней пройти   |\n";
                                        cout << "|                                            |\n";
                                        cout << "| |1|пройти через ворота                     |\n";
                                        cout << "| |2|спросить у людей как к ней пройти       |\n";
                                        cout << "| |3|подойти к странному мужику который что  |\n";
                                        cout << "| то бормочет                                |\n";
                                        cout << "|____________________________________________|\n";
                                        cin >> vibor_igroka2;
                                    } while (vibor_igroka2 != 1 && vibor_igroka2 != 2 && vibor_igroka2 != 3);
                                    vibor_igroka = 0;
                                    vibor_igroka3 = 0;
                                    vibor_igroka4 = 0;
                                    vibor_igroka5 = 0;
                                }
                                if (vibor_igroka2 == 3) {
                                    do {

                                        cout << "______________________________________________\n";
                                        cout << "| подойдя к мужчине вы спросили у него, чего |\n";
                                        cout << "| ты бормочешь мужик? <я тут овладел черной  |\n";
                                        cout << "| магией, не хочешь попробовать?>            |\n";
                                        cout << "|                                            |\n";
                                        cout << "| |1|конечно хочу |2|не, спасибо             |\n";
                                        cout << "|____________________________________________|\n";
                                        cin >> vibor_igroka;
                                    } while (vibor_igroka != 1 && vibor_igroka != 2);
                                }
                                if (vibor_igroka == 1) {
                                    do {

                                        cout << "______________________________________________\n";
                                        cout << "| <ну пошли тогда со мной> вы прошли к мужику|\n";
                                        cout << "| в подвал, он вас привязал к стулу и сказал |\n";
                                        cout << "| не двигаться.                              |\n";
                                        cout << "|                                            |\n";
                                        cout << "| |1|а это точно обязательно?                |\n";
                                        cout << "| |2|подвигаться                             |\n";
                                        cout << "| |3|не двигаться                            |\n";
                                        cout << "|                                            |\n";
                                        cout << "|____________________________________________|\n";
                                        cin >> vibor_igroka3;
                                    } while (vibor_igroka3 != 1 && vibor_igroka3 != 2 && vibor_igroka3 != 3);
                                }
                                if (vibor_igroka3 == 1) {
                                    do {

                                        cout << "______________________________________________\n";
                                        cout << "| ну если ты хочешь овладеть черной магией   |\n";
                                        cout << "| то да.                                     |\n";
                                        cout << "|                                            |\n";
                                        cout << "| |1|не двигаться                            |\n";
                                        cout << "| |2|подвигаться                             |\n";
                                        cout << "|____________________________________________|\n";
                                        cin >> vibor_igroka3;
                                    } while (vibor_igroka3 != 1 && vibor_igroka3 != 2);
                                }
                                if (vibor_igroka3 == 3) {
                                    do {

                                        cout << "______________________________________________\n";
                                        cout << "| после успешного излучения он сказал вам    |\n";
                                        cout << "| что похоже не сработало                    |\n";
                                        cout << "|                                            |\n";
                                        cout << "| |1|жалко, ну прощай!                       |\n";
                                        cout << "|____________________________________________|\n";
                                        cin >> vibor_igroka;
                                    } while (vibor_igroka != 1);
                                    vibor_igroka = vibor_igroka + 1;
                                }
                                if (vibor_igroka3 == 2) {
                                    do {

                                        cout << "______________________________________________\n";
                                        cout << "| когда мужик включал апарат вы подвигались  |\n";
                                        cout << "| теперь вы навсегда останетесь лягушкой     |\n";
                                        cout << "|                                            |\n";
                                        cout << "| |1|ква                                     |\n";
                                        cout << "|____________________________________________|\n";
                                        cin >> vibor_igroka3;
                                    } while (vibor_igroka != 1);
                                    if (vibor_igroka3 == 1) {
                                        break;
                                    }
                                }
                                if (vibor_igroka3 == 1) {

                                    do {

                                        cout << "______________________________________________\n";
                                        cout << "| после успешного излучения мужик сказал вам |\n";
                                        cout << "| что похоже не сработало                    |\n";
                                        cout << "|                                            |\n";
                                        cout << "| |1|жалко, ну прощай мужик!                 |\n";
                                        cout << "|____________________________________________|\n";
                                        cin >> vibor_igroka;
                                    } while (vibor_igroka != 1);
                                    vibor_igroka = vibor_igroka + 1;
                                }
                                if (vibor_igroka == 2) {
                                    do {
                                        cout << "______________________________________________\n";
                                        cout << "| поговорив с мужиком вы еще не решили как   |\n";
                                        cout << "| хотите пройти к речке                      |\n";
                                        cout << "|                                            |\n";
                                        cout << "| |1|пройти через ворота                     |\n";
                                        cout << "| |2|спросить у людей как к ней пройти       |\n";
                                        cout << "|____________________________________________|\n";
                                        cin >> vibor_igroka2;
                                    } while (vibor_igroka2 != 1 && vibor_igroka2 != 2);
                                }
                                if (vibor_igroka2 == 1) {

                                    cout << "______________________________________________\n";
                                    cout << "| вы подошли к стражникам и попросили вас    |\n";
                                    cout << "| выпустить, они посмеялись и сказали что без|\n";
                                    cout << "| веской причины вас не выпустят, ясно       |\n";
                                    cout << "| сказали вы, придеться спрашивать у людей   |\n";
                                    cout << "|____________________________________________|\n";
                                    vibor_igroka2 = 2;
                                    this_thread::sleep_for(chrono::nanoseconds(5000000000));
                                }
                                if (vibor_igroka2 == 2) {
                                    do {

                                        cout << "______________________________________________\n";
                                        cout << "| вы подошли к обычному мужику и спросили как|\n";
                                        cout << "| можно пройти к речке? он ответил что его   |\n";
                                        cout << "| зовут стив у него есть жена алекс и дом    |\n";
                                        cout << "| из алмазов, вам стало очень интересно и вы |\n";
                                        cout << "| пошли к нему пообедать, за обедом он       |\n";
                                        cout << "| рассказал вам как пройти к речке, и вы     |\n";
                                        cout << "| направилисчь туда, там оказалась дырка в   |\n";
                                        cout << "| стене, а так же через пару метров волк     |\n";
                                        cout << "|                                            |\n";
                                        cout << "| |1|подкрасться |2|начать бой               |\n";
                                        cout << "|____________________________________________|\n";
                                        cin >> vibor_igroka2;
                                    } while (vibor_igroka2 != 1 && vibor_igroka2 != 2);
                                }
                                if (vibor_igroka2 == 1) {
                                    do {

                                        cout << "______________________________________________\n";
                                        cout << "| вы подкрались и задушили волка             |\n";
                                        cout << "|                                            |\n";
                                        cout << "| |1|зайти обратно в город                   |\n";
                                        cout << "|____________________________________________|\n";
                                        cin >> vibor_igroka2;
                                    } while (vibor_igroka2 != 1);
                                }
                                if (vibor_igroka2 == 2) {
                                    health = 1000;
                                    enemyhealth = 500;
                                    for (int i = 0; i < enemyhealth;) {
                                        int a = 0;
                                        if (health <= 0) {
                                            cout << "|           Вы погибли.                    |\n";
                                            return 0;
                                        }
                                        if (a == 15 + erud) {
                                            cout << "|Ваша защита была пробита и волк вас закрыз.|\n";
                                            return 0;
                                        }
                                        cout << "|        Волк устрашающе рычит.              |\n";
                                        cout << "|    1) Атаковать?     2)Защищаться?         |\n";
                                        cin >> fight;
                                        if (fight == 1) {
                                            cout << "|    Вы бъёте волка,                         |\n";
                                            cout << "|             но получаете несколько царапин.|\n";
                                            enemyhealth = enemyhealth - atk;
                                            health = health - 125 + defence;
                                        }
                                        if (fight == 2) {
                                            cout << "|    Вы отражаете удар волка,                |\n";
                                            cout << "|             и даже бьёте волка по морде.   |\n";
                                            enemyhealth = enemyhealth - 10;
                                            a++;
                                        }
                                        cout << "|        Ваше оставшееся HP = " << health << "             |\n";
                                        cout << "|        Оставшееся HP врага = " << enemyhealth << "            |\n";
                                    }
                                    b++;
                                    cout << "вы убили волка и продолжили ваш путь\n";
                                    vibor_igroka2 = 1;
                                    this_thread::sleep_for(chrono::nanoseconds(3000000000));
                                }
                                if (vibor_igroka2 == 1) {
                                    playerCoins = playerCoins + 500;
                                    do {
                                       for (int i = 0; i < 1; i++) {
    cout << "______________________________________________\n";
    cout << "    Открыть меню путей прокачки?              \n";
    cout << "  1) Нет                      2) Да           \n";
    cout << "______________________________________________\n";
    cin >> a;
    if (a == 1) {
        break;
    }
    if (a == 2) {

        cout << "______________________________________________\n";
        if (b == 0) {
            cout << "     Вам не хватило очков для прокачки.       \n";
            cout << "   Очки можно получить, сходив в Оптику.      \n";
            this_thread::sleep_for(chrono::nanoseconds(3000000000));
            cout << "          Да ладно, смешно же.                \n";
            cout << "   Очки можно получить  по ходу сюжета.       \n";
            cout << "  После выполнения заданий и побед в боях     \n";
            cout << "  вы будете получать по одному очку.          \n";
            cout << "______________________________________________\n";
            this_thread::sleep_for(chrono::nanoseconds(3000000000));
            break;
        }

    }
    cout << "             1) ЗАЩИТА                       \n";
    cout << "  2)нАПАДЕНИЕ          3)ЭРУДИЦИЯ             \n";
    cout << "                                              \n";
    cout << "______________________________________________\n";
    cin >> a;

    if (a == 1) {
        defence = defence + 20;
        b--;
        cout << "             ЗАЩИТА равна:                    \n";
        cout << defence << "\n";
        cout << "             АТАКА равна:                     \n";
        cout << atk << "\n";
        cout << "             ЭРУДИЦИЯ равна:                  \n";
        cout << erud << "\n";
    }
    if (a == 2) {
        atk = atk + 15;
        b--;
        cout << "             ЗАЩИТА равна:                    \n";
        cout << defence << "\n";
        cout << "             АТАКА равна:                     \n";
        cout << atk << "\n";
        cout << "             ЭРУДИЦИЯ равна:                  \n";
        cout << erud << "\n";
       
    }
    if (a == 3) {
        erud = erud + 1;
        b--;

        cout << "             ЗАЩИТА равна:                    \n";
        cout << defence << "\n";
        cout << "             АТАКА равна:                     \n";
        cout << atk << "\n";
        cout << "             ЭРУДИЦИЯ равна:                  \n";
        cout << erud << "\n";
    }
}

                                        cout << "______________________________________________\n";
                                        cout << "| зайдя обратно перед вами появился снова    |\n";
                                        cout << "| колдун который вручил вам маленькую горку  |\n";
                                        cout << "| монет, это была награда за задание, а также|\n";
                                        cout << "| сказал вам 3 задание, вам необходимо пойти |\n";
                                        cout << "| к дому №43 и возле дома будет дерево где   |\n";
                                        cout << "| висит кормушка которую надо сжечь, идя     |\n";
                                        cout << "| по тропинке вы думаете где можно купить    |\n";
                                        cout << "| зажигалку, и видите стива, а также толпу   |\n";
                                        cout << "| людей вы подходите к стиву и спрашиваете у |\n";
                                        cout << "| него почему тут так много людей он отвечает|\n";
                                        cout << "| <тут висит доска объявлений и видимо кто-то|\n";
                                        cout << "| убил соседскую собаку возле реки где ее    |\n";
                                        cout << "| часто выпускают> вы сказали понятно и      |\n";
                                        cout << "| подумали что что-то тут не так и стоит     |\n";
                                        cout << "| прикупить оружие для самозащиты,а также    |\n";
                                        cout << "| спички для задания как тут вам подвернулась|\n";
                                        cout << "| удача и вы увидели собаку альфреда,он стоял|\n";
                                        cout << "| и торговал чем-то, вы решили зайти к нему  |\n";
                                        cout << "| купить что-нибуть                          |\n";
                                        cout << "|____________________________________________|\n";
                                        this_thread::sleep_for(chrono::nanoseconds(43000000000));
                                        proceedWithStory(playerInventory, gameShop, playerCoins);
                                        cout << "1. продолжить\n";
                                        cin >> vibor_igroka2;
                                    } while (vibor_igroka2 != 1);
                                }
                                playerCoins = playerCoins - 200;
                                if (vibor_igroka2 == 1) {
                                    do {

                                        cout << "______________________________________________\n";
                                        cout << "| купив все нужные предметы альфред отвел вас|\n";
                                        cout << "| к дому №43 и увидев кормушку вы подожгли ее|\n";
                                        cout << "| это увидели стражники и начали догонять вас|\n";
                                        cout << "| но из за их тяжелой брони вы легко убежали |\n";
                                        cout << "| и спрятались за домом где уже вас ждал     |\n";
                                        cout << "| колдун с горсткой денег в руке, которые он |\n";
                                        cout << "| протянул вам.                              |\n";
                                        cout << "|                                            |\n";
                                        cout << "| |1|мне не нужны твои грязные деньги я не   |\n";
                                        cout << "| делать плохие вещи!                        |\n";
                                        cout << "| |2|какое твое следующее задание?           |\n";
                                        cout << "| |3|посмотреть количество мемкоинов         |\n";
                                        cout << "|____________________________________________|\n";
                                        cin >> vibor_igroka5;
                                    } while (vibor_igroka5 != 1 && vibor_igroka5 != 2 && vibor_igroka5 != 3);
                                }
                                if (vibor_igroka5 == 3) {
                                    do {

                                        cout << "______________________________________________\n";
                                        cout << "| у вас " << playerCoins << "                                  | \n";
                                        cout << "|                                            |\n";
                                        cout << "| |1|продолжить                              |\n";
                                        cout << "|____________________________________________|\n";
                                        cin >> vibor_igroka2;
                                    } while (vibor_igroka2 != 1);
                                    if (vibor_igroka2 == 1) {
                                        do {
                                            cout << "______________________________________________\n";
                                            cout << "| купив все нужные предметы альфред отвел вас|\n";
                                            cout << "| к дому №43 и увидев кормушку вы подожгли ее|\n";
                                            cout << "| это увидели стражники и начали догонять вас|\n";
                                            cout << "| но из за их тяжелой брони вы легко убежали |\n";
                                            cout << "| и спрятались за домом где уже вас ждал     |\n";
                                            cout << "| колдун с горсткой денег в руке, которые он |\n";
                                            cout << "| протянул вам.                              |\n";
                                            cout << "|                                            |\n";
                                            cout << "| |1|мне не нужны твои грязные деньги я не   |\n";
                                            cout << "| делать плохие вещи!                        |\n";
                                            cout << "| |2|какое твое следующее задание?           |\n";
                                            cout << "|____________________________________________|\n";
                                            cin >> vibor_igroka5;
                                        } while (vibor_igroka5 != 1 && vibor_igroka5 != 2);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        if (vibor_igroka5 == 2) {//выполнять все задания
            do {

                cout << "______________________________________________\n";
                cout << "| следующее твое задание будет найти и убить |\n";
                cout << "| одинокого гуляющего стражника, удачи тебе  |\n";
                cout << "|                                            |\n";
                cout << "| |1|продолжить                              |\n";
                cout << "|____________________________________________|\n";
                cin >> vibor_igroka;
            } while (vibor_igroka != 1);
            if (vibor_igroka == 1) {
                do {

                    cout << "______________________________________________\n";
                    cout << "| вы гуляли по городу и искали одинокого     |\n";
                    cout << "| стражника, как вдруг, он сам вас находит   |\n";
                    cout << "| но почему-то не бьет тревогу, а нападает   |\n";
                    cout << "| на вас один.                               |\n";//БОЙ СО СТРАЖНИКОМ
                    cout << "|                                            |\n";
                    cout << "| |1|продолжить                              |\n";
                    cout << "|                                            |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                    health = 1000;
                    enemyhealth = 1000;
                    for (int i = 0; i < enemyhealth;) {
                        int a = 0;
                        if (health <= 0) {
                            cout << "|           Вы погибли.                    |\n";
                            return 0;
                        }
                        if (a == 15 + erud) {
                            cout << "|Ваша защита была пробита и стражник вас убил.|\n";
                            return 0;
                        }
                        cout << "|        Стражник готовит меч.               |\n";
                        cout << "|    1) Атаковать?     2)Защищаться?         |\n";
                        cin >> fight;
                        if (fight == 1) {
                            cout << "|    Вы бъёте стража,                        |\n";
                            cout << "|               но получаете удар.           |\n";
                            enemyhealth = enemyhealth - atk;
                            health = health - 125 + defence;
                        }
                        if (fight == 2) {
                            cout << "|    Вы отражаете удар стражника,            |\n";
                            cout << "|             и даже бьёте его по морде.     |\n";
                            enemyhealth = enemyhealth - 20;
                            a++;
                        }
                        cout << "|        Ваше оставшееся HP = " << health << "             |\n";
                        cout << "|        Оставшееся HP врага = " << enemyhealth << "            |\n";
                    }
                } while (vibor_igroka != 1);
            }
            if (vibor_igroka == 1) {
                playerCoins = playerCoins + 500;
                do {
                    b++;
                    for (int i = 0; i < 1; i++) {
    cout << "______________________________________________\n";
    cout << "    Открыть меню путей прокачки?              \n";
    cout << "  1) Нет                      2) Да           \n";
    cout << "______________________________________________\n";
    cin >> a;
    if (a == 1) {
        break;
    }
    if (a == 2) {

        cout << "______________________________________________\n";
        if (b == 0) {
            cout << "     Вам не хватило очков для прокачки.       \n";
            cout << "   Очки можно получить, сходив в Оптику.      \n";
            this_thread::sleep_for(chrono::nanoseconds(3000000000));
            cout << "          Да ладно, смешно же.                \n";
            cout << "   Очки можно получить  по ходу сюжета.       \n";
            cout << "  После выполнения заданий и побед в боях     \n";
            cout << "  вы будете получать по одному очку.          \n";
            cout << "______________________________________________\n";
            this_thread::sleep_for(chrono::nanoseconds(3000000000));
            break;
        }

    }
    cout << "             1) ЗАЩИТА                       \n";
    cout << "  2)нАПАДЕНИЕ          3)ЭРУДИЦИЯ             \n";
    cout << "                                              \n";
    cout << "______________________________________________\n";
    cin >> a;

    if (a == 1) {
        defence = defence + 20;
        b--;
        cout << "             ЗАЩИТА равна:                    \n";
        cout << defence << "\n";
        cout << "             АТАКА равна:                     \n";
        cout << atk << "\n";
        cout << "             ЭРУДИЦИЯ равна:                  \n";
        cout << erud << "\n";
    }
    if (a == 2) {
        atk = atk + 15;
        b--;
        cout << "             ЗАЩИТА равна:                    \n";
        cout << defence << "\n";
        cout << "             АТАКА равна:                     \n";
        cout << atk << "\n";
        cout << "             ЭРУДИЦИЯ равна:                  \n";
        cout << erud << "\n";
       
    }
    if (a == 3) {
        erud = erud + 1;
        b--;

        cout << "             ЗАЩИТА равна:                    \n";
        cout << defence << "\n";
        cout << "             АТАКА равна:                     \n";
        cout << atk << "\n";
        cout << "             ЭРУДИЦИЯ равна:                  \n";
        cout << erud << "\n";
    }
}

                    cout << "______________________________________________\n";
                    cout << "| чтобы никто не увидел как вы его убили вы  |\n";
                    cout << "| быстро забежали за угол здания и увидели   |\n";
                    cout << "| снова этого колдуна который предлагает     |\n";
                    cout << "| следующее задание, а так же горстку денег  |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|отказаться |2|согласиться               |\n";
                    cout << "| |3|посмотреть количество мемкоинов         |\n";
                    cout << "|                                            |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka5;
                } while (vibor_igroka5 != 1 && vibor_igroka5 != 2 && vibor_igroka5 != 3);
                if (vibor_igroka5 == 3) {
                    do {

                        cout << "______________________________________________\n";
                        cout << "| у вас " << playerCoins << "                                 | \n";
                        cout << "|                                            |\n";
                        cout << "| |1|продолжить                              |\n";
                        cout << "|____________________________________________|\n";
                        cin >> vibor_igroka2;
                    } while (vibor_igroka2 != 1);
                    if (vibor_igroka2 == 1) {
                        do {

                            cout << "______________________________________________\n";
                            cout << "| чтобы никто не увидел как вы его убили вы  |\n";
                            cout << "| быстро забежали за угол здания и увидели   |\n";
                            cout << "| снова этого колдуна который предлагает     |\n";
                            cout << "| следующее задание, а так же горстку денег  |\n";
                            cout << "|                                            |\n";
                            cout << "| |1|отказаться |2|согласиться               |\n";
                            cout << "|____________________________________________|\n";
                            cin >> vibor_igroka5;
                        } while (vibor_igroka5 != 1 && vibor_igroka5 != 2);
                    }
                }
                if (vibor_igroka5 == 1) {
                    do {

                        cout << "______________________________________________\n";
                        cout << "| ты точно хочешь отказаться?                |\n";
                        cout << "|                                            |\n";
                        cout << "| |1|отказаться |2|согласиться               |\n";
                        cout << "|____________________________________________|\n";
                        cin >> vibor_igroka5;
                    } while (vibor_igroka5 != 1 && vibor_igroka5 != 2);
                }
            }
            if (vibor_igroka5 == 1) {
                vibor_igroka = 0;
                vibor_igroka2 = 0;
                vibor_igroka3 = 0;
                vibor_igroka4 = 0;
                vibor_igroka5 = 1;
            }
            if (vibor_igroka5 == 2) {
                do {

                    cout << "______________________________________________\n";
                    cout << "| следующее твое задание будет, это ограбить |\n";
                    cout << "| богатого рыцаря нашего королевства  Артема |\n";
                    cout << "| украсть у него старинные часы, а так же    |\n";
                    cout << "| картину моно ли... ой я хотел сказать      |\n";
                    cout << "| моно веры, да моно веры.                   |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|согласиться                             |\n";
                    cout << "|                                            |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1);
            }
            if (vibor_igroka == 1) {
                do {
                    cout << "______________________________________________\n";
                    cout << "| он отводит вас к очень красивому белому    |\n";
                    cout << "| дому и говорит что это он и так же быстро  |\n";
                    cout << "| как появился исчез                         |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|пойти через главную дверь               |\n";
                    cout << "| |2|пойти через задний двор                 |\n";
                    cout << "|                                            |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1 && vibor_igroka != 2);
            }
            if (vibor_igroka == 1) {
                do {
                    cout << "______________________________________________\n";
                    cout << "| вы пошли ко входной двери иии о чудо она   |\n";
                    cout << "| была открыта                               |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|пойти на кухню |2|пойти в спальню       |\n";
                    cout << "|                                            |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka2;
                } while (vibor_igroka2 != 1 && vibor_igroka2 != 2);
            }
            if (vibor_igroka == 2) {
                do {
                    cout << "______________________________________________\n";
                    cout << "| на заднем дворе было открыто откно через   |\n";
                    cout << "| которое вы зашли                           |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|пойти на кухню |2|пойти в спальню       |\n";
                    cout << "|                                            |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka2;
                } while (vibor_igroka2 != 1 && vibor_igroka2 != 2);
            }
            if (vibor_igroka2 == 1) {
                cout << "______________________________________________\n";
                cout << "| на кухне не было ничего кроме очень вкусной|\n";
                cout << "| еды которые вы сразу же съели, больше там  |\n";
                cout << "| ничего не было и вы пошли в спальню        |\n";
                cout << "|                                            |\n";
                cout << "|____________________________________________|\n";
                this_thread::sleep_for(chrono::nanoseconds(5000000000));
                do {
                    cout << "______________________________________________\n";
                    cout << "| в спальне была большая двухместная кровать |\n";
                    cout << "| на которой спал охранник, а так же тумбочка|\n";
                    cout << "| и спуск в низ                              |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|пойти вниз по лестнице                  |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1);
            }
            if (vibor_igroka2 == 2) {
                cout << "______________________________________________\n";
                cout << "| в спальне была большая двухмесная кровать  |\n";
                cout << "| на которой спал охранник, а так же тумбочка|\n";
                cout << "| и спуска в низ, и вы пошли на кухню        |\n";
                cout << "|                                            |\n";
                cout << "|____________________________________________|\n";
                this_thread::sleep_for(chrono::nanoseconds(3500000000));
                do {
                    cout << "______________________________________________\n";
                    cout << "| на кухне не было ничего кроме очень вкусной|\n";
                    cout << "| еды которые вы сразу же съели, больше там  |\n";
                    cout << "| ничего не было и вы пошли обратно в спальню|\n";
                    cout << "|                                            |\n";
                    cout << "| |1|пойти вниз по лестнице                  |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1);
            }
            if (vibor_igroka == 1) {
                do {
                    cout << "______________________________________________\n";
                    cout << "| дверь внизу была закрыта, надо найти ключ  |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|поискать в тумбоче возле охранника      |\n";
                    cout << "|                                            |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1);
            }
            if (vibor_igroka == 1) {
                do {
                   for (int i = 0; i < 1; i++) {
    cout << "______________________________________________\n";
    cout << "    Открыть меню путей прокачки?              \n";
    cout << "  1) Нет                      2) Да           \n";
    cout << "______________________________________________\n";
    cin >> a;
    if (a == 1) {
        break;
    }
    if (a == 2) {

        cout << "______________________________________________\n";
        if (b == 0) {
            cout << "     Вам не хватило очков для прокачки.       \n";
            cout << "   Очки можно получить, сходив в Оптику.      \n";
            this_thread::sleep_for(chrono::nanoseconds(3000000000));
            cout << "          Да ладно, смешно же.                \n";
            cout << "   Очки можно получить  по ходу сюжета.       \n";
            cout << "  После выполнения заданий и побед в боях     \n";
            cout << "  вы будете получать по одному очку.          \n";
            cout << "______________________________________________\n";
            this_thread::sleep_for(chrono::nanoseconds(3000000000));
            break;
        }

    }
    cout << "             1) ЗАЩИТА                       \n";
    cout << "  2)нАПАДЕНИЕ          3)ЭРУДИЦИЯ             \n";
    cout << "                                              \n";
    cout << "______________________________________________\n";
    cin >> a;

    if (a == 1) {
        defence = defence + 20;
        b--;
        cout << "             ЗАЩИТА равна:                    \n";
        cout << defence << "\n";
        cout << "             АТАКА равна:                     \n";
        cout << atk << "\n";
        cout << "             ЭРУДИЦИЯ равна:                  \n";
        cout << erud << "\n";
    }
    if (a == 2) {
        atk = atk + 15;
        b--;
        cout << "             ЗАЩИТА равна:                    \n";
        cout << defence << "\n";
        cout << "             АТАКА равна:                     \n";
        cout << atk << "\n";
        cout << "             ЭРУДИЦИЯ равна:                  \n";
        cout << erud << "\n";
       
    }
    if (a == 3) {
        erud = erud + 1;
        b--;

        cout << "             ЗАЩИТА равна:                    \n";
        cout << defence << "\n";
        cout << "             АТАКА равна:                     \n";
        cout << atk << "\n";
        cout << "             ЭРУДИЦИЯ равна:                  \n";
        cout << erud << "\n";
    }
}

                    cout << "______________________________________________\n";
                    cout << "| вы открыли тумбочку но там были лишь 2     |\n";
                    cout << "| книги, <метро 2033> и <метро экзодус> что  |\n";
                    cout << "| это может значить?... ладно не важно, ключа|\n";
                    cout << "| здесь нету. Но это значит осталось лишь    |\n";
                    cout << "| одно место, у охранника, иии ключ! но он на|\n";
                    cout << "| веревочке на шее у охранника.              |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|пойти за ножом на кухню                 |\n";
                    cout << "| |2|дернуть и порвать веревку               |\n";
                    cout << "|                                            |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1 && vibor_igroka != 2);
            }
            if (vibor_igroka == 1) {
                do {

                    cout << "______________________________________________\n";
                    cout << "| вы взяля нож и пока враг беззащитный вы    |\n";
                    cout << "| замахиваетесь иии отрезаете веревку берете |\n";
                    cout << "| ключ                                       |\n";
                    cout << "|                                            |\n";
                    cout << "| |1| открыть дверь внизу лестницы           |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1);
            }
            if (vibor_igroka == 2) {
                do {

                    cout << "______________________________________________\n";
                    cout << "| вы резко дергаете ключ и хлипкая веревка   |\n";
                    cout << "| рвется не разбудив охранника               |\n";
                    cout << "|                                            |\n";
                    cout << "| |1| открыть дверь внизу лестницы           |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1);
            }
            if (vibor_igroka == 1) {
                do {

                    cout << "______________________________________________\n";
                    cout << "| открыв дверь первое что вы видите это доску|\n";
                    cout << "| с разными преступлениями, убийство отряда  |\n";
                    cout << "| стражников, большое ограбление,избил       |\n";
                    cout << "| охранника и сбежал из тюрьмы, что-то очень |\n";
                    cout << "| странные преступления сделанные одним      |\n";
                    cout << "| человеком, надо бы спросить у стива и      |\n";
                    cout << "| колдуна, вы хватаете старинные часы и моно |\n";
                    cout << "| веру, уже собираете бежать, но замечаете   |\n";
                    cout << "| кучу золота.                               |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|бежать через маленькое окошко на улицу  |\n";
                    cout << "| |2|пихать золото по карманам               |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1 && vibor_igroka != 2);
            }
            if (vibor_igroka == 1) {
                vibor_igroka = 1;
            }
            if (vibor_igroka == 2) {
                playerCoins = playerCoins + 150;
                do {

                    cout << "______________________________________________\n";
                    cout << "| вы начинаете пихать золото по карманам, но |\n";
                    cout << "| слышите <так,подожди ка, что-то тут не так,|";
                    this_thread::sleep_for(chrono::nanoseconds(6000000000));
                    cout << "\n| ГДЕ КЛЮЧ?                                  |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|бежать через маленькое окошко на улицу  |\n";
                    cout << "| |2|пихать золото по карманам               |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1 && vibor_igroka != 2);
            }
            if (vibor_igroka == 2) {
                playerCoins = playerCoins + 150;
                do {
                    cout << "______________________________________________\n";
                    cout << "| вы пихаете дальше и уже слышите быстрый    |\n";
                    cout << "| спуск в низ                                |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|бежать через маленькое окошко на улицу  |\n";
                    cout << "| |2|пихать золото по карманам               |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1 && vibor_igroka != 2);
            }
            if (vibor_igroka == 2) {
                cout << "______________________________________________\n";
                cout << "| вы решаете попыпать удачу и пихать дальше  |\n";
                cout << "| но не успеваете убежать и охранник избивает|\n";
                cout << "| вас до смерти, жалко что охранник не знает |\n";
                cout << "| что врагов можно уничтожить сделав их      |\n";
                cout << "| друзьями                                   |\n";
                cout << "|____________________________________________|\n";
                break;
            }
            if (vibor_igroka == 1) {
                do {
                    cout << "______________________________________________\n";
                    cout << "| вы выбиваете решетку и убегаете через      |\n";
                    cout << "| маленькое окошко подальше от сюда и        |\n";
                    cout << "| появляется колдун                          |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|спросить про преступления               |\n";
                    cout << "| |2|посмотреть количество мемкоинов         |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1 && vibor_igroka != 2);
            }
            if (vibor_igroka == 2) {
                do {

                    cout << "______________________________________________\n";
                    cout << "| у вас " << playerCoins << "                                 | \n";
                    cout << "|                                            |\n";
                    cout << "| |1|продолжить                              |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka2;
                } while (vibor_igroka2 != 1);
                if (vibor_igroka2 == 1) {
                    do {
                        cout << "______________________________________________\n";
                        cout << "| вы выбиваете решетку и убегаете через      |\n";
                        cout << "| маленькое окошко подальше от сюда и        |\n";
                        cout << "| появляется колдун                          |\n";
                        cout << "|                                            |\n";
                        cout << "| |1|спросить про преступления               |\n";
                        cout << "|____________________________________________|\n";
                        cin >> vibor_igroka;
                    } while (vibor_igroka != 1);
                }
            }
            if (vibor_igroka == 1) {
                do {
                    cout << "______________________________________________\n";
                    cout << "| я тебе не говорил? по мимо тебя есть еще   |\n";
                    cout << "| участник, и если он выполнит 9 заданий     |\n";
                    cout << "| быстрее тебя то ты отправишься в ад, будешь|\n";
                    cout << "| там вечно ломать не ломаемый камень, ну а  |\n";
                    cout << "| пока иди отдохни на следующий день будут   |\n";
                    cout << "| новые задания. Вы пошли домой и увидели    |\n";
                    cout << "| альфреда который торговал в переулке, и    |\n";
                    cout << "| пока еще совсем не стемнело вы решили      |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|закупаться |2|не закупаться             |\n";
                    cout << "|                                            |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1 && vibor_igroka != 2);
            }
            if (vibor_igroka == 1) {
                manageShop(gameShop, playerInventory, playerCoins);
                cout << "вы продолжили путь\n";
                vibor_igroka = 2;
            }
            if (vibor_igroka == 2) {
                do {
                    cout << "______________________________________________\n";
                    cout << "| вы пошли к стиву переночевать и после ужина|\n";
                    cout << "| спросили у него знает ли он что-то про     |\n";
                    cout << "| ограбление,убийство отряда стражников и то |\n";
                    cout << "| что этот человек сбежал из тюрьмы до этого?|\n";
                    cout << "| стив занервничал и сказал <эээ ну слушай я |\n";
                    cout << "| даже не знаю о чем ты говоришь> что-то тут |\n";
                    cout << "| не так подумали вы и пошли спать. Утром вы |\n";
                    cout << "| проснулись и вышли из дома стива, и тут    |\n";
                    cout << "| снова этот колдун с заданиями, <ну что,    |\n";
                    cout << "| готов к следующему заданию?>               |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|готов                                   |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1);
            }
            if (vibor_igroka == 1) {
                do {
                    cout << "______________________________________________\n";
                    cout << "| ты должен сдаться стражникам               |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|ЧТО?? ты же понимаешь что меня в тюрьму |\n";
                    cout << "| отправят?                                  |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1);
            }
            if (vibor_igroka == 1) {
                do {
                    cout << "______________________________________________\n";
                    cout << "| я прекрасно это понимаю, на это и расчет   |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|ладно, что не сделаешь ради денег       |\n";
                    cout << "| |2|я не буду этого делать                  |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1 && vibor_igroka != 2);
            }
            if (vibor_igroka == 2) {
                vibor_igroka = 0;
                vibor_igroka2 = 0;
                vibor_igroka3 = 0;
                vibor_igroka4 = 0;
                vibor_igroka5 = 1;
            }
            if (vibor_igroka == 1) {
                do {
                    cout << "______________________________________________\n";
                    cout << "| вы пошли и нашли охранника который на вас  |\n";
                    cout << "| набросился и ударил по голове...           |\n";
                    cout << "|____________________________________________|\n";
                    this_thread::sleep_for(chrono::nanoseconds(3500000000));
                    cout << "______________________________________________\n";
                    cout << "| |1|ПРОСНУТЬСЯ!                             |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1);
            }
            if (vibor_igroka == 1) {
                do {
                    cout << "______________________________________________\n";
                    cout << "| вы проснулись в камере, одиночной камере,  |\n";
                    cout << "| осмотрелись и ничего кроме кровати, туалета|\n";
                    cout << "| и железной миски в камере не было... что   |\n";
                    cout << "| дальше? подумали вы и сказали это вслух, но|\n";
                    cout << "| никто ничего так в ответ и не сказал, так  |\n";
                    cout << "| прошел 1..2..3 день пока вы не увидели под |\n";
                    cout << "| кроватью записку <извини что так долго не  |\n";
                    cout << "| было, просто не интересно когда попав в    |\n";
                    cout << "| тюрьму ты выполнил 6 задание, а второй     |\n";
                    cout << "| участник 3, твоим 7 заданием будет выбратся|\n";
                    cout << "| из этой тюрьмы, удачи> Подумав несколько   |\n";
                    cout << "| часов у вас появилось 2 плана побега.      |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|тихий |2|шумный                         |\n";//не дать 1 вариант если не купил напильник
                    cout << "|                                            |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1 && vibor_igroka != 2);
            }
            if (vibor_igroka == 1) {
                cout << "______________________________________________\n";
                cout << "| вы через окно с решеткой попытались позвать|\n";
                cout << "| альфреда.. ии о чудо он услышал.           |\n";
                cout << "|____________________________________________|\n";
                manageShop(gameShop, playerInventory, playerCoins); //не дать 1 вариант если не купил напильник
                playerCoins = playerCoins + 1000;
                cout << playerCoins;
                do {
                    cout << "______________________________________________\n";
                    cout << "| вы распилили решетку и начали бежать как   |\n";
                    cout << "| можно быстрее и дальше, теперь вас будут   |\n";
                    cout << "| искать еще упорнее...                      |\n";
                    cout << "| через несколько часов вы снова встретились |\n";
                    cout << "| с колдуном, который с улыбкой протянул вам |\n";
                    cout << "| мешок с деньгами и сказал что вы выполнили |\n";
                    cout << "| 7 заданий из 9, вашим 8 заданием будет     |\n";
                    cout << "| сразиться с самым величайшим стражником    |\n";
                    cout << "| этого королевства. Он даст вам время       |\n";
                    cout << "| подготовиться.                             |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|согласиться и закупиться у альфреда     |\n";
                    cout << "| |2|отказаться                              |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1 && vibor_igroka != 2);
                if (vibor_igroka == 1) {
                    manageShop(gameShop, playerInventory, playerCoins);
                    vibor_igroka = 1;
                }
                if (vibor_igroka == 2) {
                    vibor_igroka = 0;
                    vibor_igroka2 = 0;
                    vibor_igroka3 = 0;
                    vibor_igroka4 = 0;
                    vibor_igroka5 = 1;
                }
            }
            if (vibor_igroka == 2) {
                do {
                    cout << "______________________________________________\n";
                    cout << "| вы схватились за сердце и стали звать на   |\n";
                    cout << "| помощь, к вам подбежал сторож и начал вам  |\n";
                    cout << "| помогать                                   |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|схватить клинок у стражника на поясе    |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1);
                if (vibor_igroka == 1) {
                    do {
                        cout << "______________________________________________\n";
                        cout << "| вы схватили клинок и ударили охранника     |\n";
                        cout << "| несколько раз.                             |\n";
                        cout << "|                                            |\n";
                        cout << "| |1|убегать                                 |\n";
                        cout << "|____________________________________________|\n";
                        cin >> vibor_igroka;
                    } while (vibor_igroka != 1);
                    if (vibor_igroka == 1) {
                        do {
                            cout << "______________________________________________\n";
                            cout << "| вы бросились бежать через всех охранников  |\n";
                            cout << "| и спокойна убегаете, вас так никто и не    |\n";
                            cout << "| догнал                                     |\n";
                            cout << "|                                            |\n";
                            cout << "| |1|забежать за здание                      |\n";
                            cout << "|____________________________________________|\n";
                            cin >> vibor_igroka;
                        } while (vibor_igroka != 1);
                    }
                }
                if (vibor_igroka == 1) {
                    do {
                        cout << "______________________________________________\n";
                        cout << "| через несколько часов вы снова встретились |\n";
                        cout << "| с колдуном, который с улыбкой протянул вам |\n";
                        cout << "| мешок с деньгами и сказал что вы выполнили |\n";
                        cout << "| 7 заданий из 9, вашим 8 заданием будет     |\n";
                        cout << "| сразиться с самым величайшим стражником    |\n";
                        cout << "| этого королевства. Он даст вам время       |\n";
                        cout << "| подготовиться.                             |\n";
                        cout << "|                                            |\n";
                        cout << "| |1|согласиться и закупиться у альфреда     |\n";
                        cout << "| |2|отказаться                              |\n";
                        cout << "|____________________________________________|\n";
                        cin >> vibor_igroka2;
                    } while (vibor_igroka != 1 && vibor_igroka != 2);
                }

                if (vibor_igroka2 == 2) {
                    vibor_igroka = 0;
                    vibor_igroka2 = 0;
                    vibor_igroka3 = 0;
                    vibor_igroka4 = 0;
                    vibor_igroka5 = 1;
                }
                if (vibor_igroka2 == 1) {//ВОТ ТУТ ЕЩЕ МАГАЗИН
                    do {
                        cout << "______________________________________________\n";
                        cout << "| |1|продолжить                              |\n";
                        cout << "|____________________________________________|\n";
                        cin >> vibor_igroka;
                    } while (vibor_igroka != 1);
                }
            }
            if (vibor_igroka == 1) {
                cout << "______________________________________________\n";
                cout << "| после закупки вы сказали колдуну что вы    |\n";
                cout << "| готовы, он ударил вас по голове и вы       |\n";
                cout << "| появились на арене со стражником, который  |\n";
                cout << "| был около 3 метров ростом в шикарных,      |\n";
                cout << "| больших белых доспехах и очень длинным     |\n";
                cout << "| мечем.                                     |\n";
                cout << "|                                            |\n";
                cout << "|____________________________________________|\n";
                health = 1000;
                enemyhealth = 1500;
                for (int i = 0; i < enemyhealth;) {
                    int a = 0;
                    if (health <= 0) {
                        cout << "|           Вы погибли.                    |\n";
                        return 0;
                    }
                    if (a == 15 + erud) {
                        cout << "|   Ваша защита была пробита              |\n";
                        cout << "|    и стражник проткнул вас насквозь     |\n";
                        return 0;
                    }
                    cout << "|        Стражник готовится атаковать.       |\n";
                    cout << "|    1) Атаковать?     2)Защищаться?         |\n";
                    cin >> fight;
                    if (fight == 1) {
                        cout << "|    Вы бъёте cтража,                         |\n";
                        cout << "|                    но удар в печень.        |\n";
                        enemyhealth = enemyhealth - atk;
                        health = health - 150 + defence;
                    }
                    if (fight == 2) {
                        cout << "|    Вы отражаете удар стража,               |\n";
                        cout << "|             и, пользуясь моментом, бьёте.  |\n";
                        enemyhealth = enemyhealth - 50;
                        a++;
                    }
                    cout << "|        Ваше оставшееся HP = " << health << "             |\n";
                    cout << "|        Оставшееся HP врага = " << enemyhealth << "            |\n";
                }
                if (vibor_igroka == 1) {
                    do {
                        b++;
                        for (int i = 0; i < 1; i++) {
    cout << "______________________________________________\n";
    cout << "    Открыть меню путей прокачки?              \n";
    cout << "  1) Нет                      2) Да           \n";
    cout << "______________________________________________\n";
    cin >> a;
    if (a == 1) {
        break;
    }
    if (a == 2) {

        cout << "______________________________________________\n";
        if (b == 0) {
            cout << "     Вам не хватило очков для прокачки.       \n";
            cout << "   Очки можно получить, сходив в Оптику.      \n";
            this_thread::sleep_for(chrono::nanoseconds(3000000000));
            cout << "          Да ладно, смешно же.                \n";
            cout << "   Очки можно получить  по ходу сюжета.       \n";
            cout << "  После выполнения заданий и побед в боях     \n";
            cout << "  вы будете получать по одному очку.          \n";
            cout << "______________________________________________\n";
            this_thread::sleep_for(chrono::nanoseconds(3000000000));
            break;
        }

    }
    cout << "             1) ЗАЩИТА                       \n";
    cout << "  2)нАПАДЕНИЕ          3)ЭРУДИЦИЯ             \n";
    cout << "                                              \n";
    cout << "______________________________________________\n";
    cin >> a;

    if (a == 1) {
        defence = defence + 20;
        b--;
        cout << "             ЗАЩИТА равна:                    \n";
        cout << defence << "\n";
        cout << "             АТАКА равна:                     \n";
        cout << atk << "\n";
        cout << "             ЭРУДИЦИЯ равна:                  \n";
        cout << erud << "\n";
    }
    if (a == 2) {
        atk = atk + 15;
        b--;
        cout << "             ЗАЩИТА равна:                    \n";
        cout << defence << "\n";
        cout << "             АТАКА равна:                     \n";
        cout << atk << "\n";
        cout << "             ЭРУДИЦИЯ равна:                  \n";
        cout << erud << "\n";
       
    }
    if (a == 3) {
        erud = erud + 1;
        b--;

        cout << "             ЗАЩИТА равна:                    \n";
        cout << defence << "\n";
        cout << "             АТАКА равна:                     \n";
        cout << atk << "\n";
        cout << "             ЭРУДИЦИЯ равна:                  \n";
        cout << erud << "\n";
    }
}
                        cout << "______________________________________________\n";
                        cout << "| ВЫ победили, стражник рухнул на землю, и вы|\n";
                        cout << "| проснулись в доме у стива, где был сам стив|\n";
                        cout << "| колдун и альфред. Колдун дал вам пистолет и|\n";
                        cout << "| сказал <твое задание это выбрать одного из |\n";
                        cout << "| них и убить>                               |\n";
                        cout << "|                                            |\n";
                        cout << "| |1|убить стива |2|убить альфреда           |\n";
                        cout << "| |3|пожертвовать собой |4|спасти обоих      |\n";
                        cout << "|                                            |\n";
                        cout << "|____________________________________________|\n";
                        cin >> vibor_igroka;

                    } while (vibor_igroka != 1 && vibor_igroka != 2 && vibor_igroka != 3 && vibor_igroka != 4);
                }
                if (vibor_igroka == 1) {
                    cout << "______________________________________________\n";
                    cout << "| вы нацеливаетесь на стива, но он делает это|\n";
                    cout << "| быстрее и стреляет в вас попав в сердце, но|\n";
                    cout << "| перед тем как умереть вы успели услышать   |\n";
                    cout << "| <поздравляю вас стив, вы выйграли главный  |\n";
                    cout << "| приз нашей игры>....                       |\n";
                    cout << "|____________________________________________|\n";
                    this_thread::sleep_for(chrono::nanoseconds(10000000000));
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "______________________________________________\n";
                    cout << "|              THE END!                      |\n";
                    cout << "|____________________________________________|\n";
                    this_thread::sleep_for(chrono::nanoseconds(2000000000));
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "______________________________________________\n";
                    cout << "|                  ТИТРЫ                     |\n";
                    cout << "| СЮЖЕТ,ДИАЛОГИ,ДЕНЬГИ-СИЛИННИК ВЛАД         |\n";
                    cout << "| ХАРАКТЕРИСТИКИ,БОИ-АНДРЕЕНКОВ АЛЕКСАНДР    |\n";
                    cout << "| ИНВЕНТАРЬ,МАГАЗИНЫ-СЕРОВ АЛЕКСАНДР         |\n";
                    cout << "|                                            |\n";
                    cout << "| СПАСИБО ЗА ИГРУ! ПРОДОЛЖЕНИЕ СЛЕДУЕТ ЕСЛИ  |\n";
                    cout << "| БУДУТ СПОНСОРЫ!(поставте 12 )              |\n";
                    cout << "|____________________________________________|\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    return 0;
                }
                if (vibor_igroka == 2) {
                    playerCoins = playerCoins = 0;
                    playerCoins = playerCoins + 1000000000;
                    do {
                        cout << "______________________________________________\n";
                        cout << "| вы убили магическую собачку альфреда,      |\n";
                        cout << "| выйграли главный приз несколько миллиардов |\n";
                        cout << "| золотых монет, купили место короля этого   |\n";
                        cout << "| стив и прислужные вас больше не любят, но  |\n";
                        cout << "| место короля этого города вам показалось   |\n";
                        cout << "| мало, поэтому решили                       |\n";
                        cout << "|                                            |\n";
                        cout << "| |1|убить всех богов олимпа (купить на рынке|\n";
                        cout << "| оружие )                                   |\n";
                        cout << "| |2|попытаться скрыться от всех проблем     |\n";
                        cout << "| убежав из города                           |\n";
                        cout << "|____________________________________________|\n";
                        cin >> vibor_igroka5;
                    } while (vibor_igroka5 != 1 && vibor_igroka5 != 2);
                    if (vibor_igroka5 == 1) {
                        manageShop(gameShop, playerInventory, playerCoins); //Добавить в магазин меч за 1000000000 "Убийца Богов 228"
                        vibor_igroka = 0;
                        vibor_igroka2 = 0;
                        vibor_igroka3 = 0;
                        vibor_igroka4 = 0;
                        vibor_igroka5 = vibor_igroka5 + 2;
                    }
                    if (vibor_igroka5 == 2) {
                        cout << "______________________________________________\n";
                        cout << "| вам удалось убежать от всех проблем, но это|\n";
                        cout << "| уже совсем другая история...               |\n";
                        cout << "|____________________________________________|\n";
                        this_thread::sleep_for(chrono::nanoseconds(5000000000));
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "______________________________________________\n";
                        cout << "|              THE END!                      |\n";
                        cout << "|____________________________________________|\n";
                        this_thread::sleep_for(chrono::nanoseconds(2000000000));
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "______________________________________________\n";
                        cout << "|                  ТИТРЫ                     |\n";
                        cout << "| СЮЖЕТ,ДИАЛОГИ,ДЕНЬГИ-СИЛИННИК ВЛАД         |\n";
                        cout << "| ХАРАКТЕРИСТИКИ,БОИ-АНДРЕЕНКОВ АЛЕКСАНДР    |\n";
                        cout << "| ИНВЕНТАРЬ,МАГАЗИНЫ-СЕРОВ АЛЕКСАНДР         |\n";
                        cout << "|                                            |\n";
                        cout << "| СПАСИБО ЗА ИГРУ! ПРОДОЛЖЕНИЕ СЛЕДУЕТ ЕСЛИ  |\n";
                        cout << "| БУДУТ СПОНСОРЫ!(поставте 12 )              |\n";
                        cout << "|____________________________________________|\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        return 0;
                    }
                }
                if (vibor_igroka == 4) {
                    cout << "______________________________________________\n";
                    cout << "| вы спасли обоих убив колдуна, но перед     |\n";
                    cout << "| смертью колдун забрал у вас и у стива все  |\n";
                    cout << "| деньги выйграные до этого и отправил вас в |\n";
                    cout << "| АД! игра продолжаеться!                    |\n";
                    cout << "|____________________________________________|\n";
                    vibor_igroka = 0;
                    vibor_igroka2 = 0;
                    vibor_igroka3 = 0;
                    vibor_igroka4 = 0;
                    vibor_igroka5 = 1;
                }
                if (vibor_igroka5 == 1) {
                    do {
                        cout << "______________________________________________\n";
                        cout << "| в аду вы встречаете харона, преспешника    |\n";
                        cout << "| аида, тебя перевести? спросил у вас харон  |\n";
                        cout << "|                                            |\n";
                        cout << "| |1|да, перевези пожалуйста                 |\n";
                        cout << "|                                            |\n";
                        cout << "|____________________________________________|\n";
                        cin >> vibor_igroka5;
                    } while (vibor_igroka5 != 1);
                }
                if (vibor_igroka == 3) {
                    cout << "______________________________________________\n";
                    cout << "| выстрелив в себя, стив как второй участник |\n";
                    cout << "| побеждает и выигрывает главный приз игры   |\n";
                    cout << "| миллиард монет, покупает новый дом и живет |\n";
                    cout << "| со своей семьей ни в чем себе не отказывая,|\n";
                    cout << "| но каждый день вспоминает о вас...         |\n";
                    cout << "|____________________________________________|\n";
                    this_thread::sleep_for(chrono::nanoseconds(10000000000));
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "______________________________________________\n";
                    cout << "|              THE END!                      |\n";
                    cout << "|____________________________________________|\n";
                    this_thread::sleep_for(chrono::nanoseconds(2000000000));
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "\n";
                    cout << "______________________________________________\n";
                    cout << "|                  ТИТРЫ                     |\n";
                    cout << "| СЮЖЕТ,ДИАЛОГИ,ДЕНЬГИ-СИЛИННИК ВЛАД         |\n";
                    cout << "| ХАРАКТЕРИСТИКИ,БОИ-АНДРЕЕНКОВ АЛЕКСАНДР    |\n";
                    cout << "| ИНВЕНТАРЬ,МАГАЗИНЫ-СЕРОВ АЛЕКСАНДР         |\n";
                    cout << "|                                            |\n";
                    cout << "| СПАСИБО ЗА ИГРУ! ПРОДОЛЖЕНИЕ СЛЕДУЕТ ЕСЛИ  |\n";
                    cout << "| БУДУТ СПОНСОРЫ!(поставте 12 )              |\n";
                    cout << "|____________________________________________|\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    this_thread::sleep_for(chrono::nanoseconds(500000000));
                    cout << "\n";
                    return 0;
                }
            }
        }

        /////////////
        if (vibor_igroka5 == 1) {//попасть в ад
            do {
                cout << "______________________________________________\n";//ТРАТА ЕДЫ И ГОЛОДА НЕ НУЖНА!!!!
                cout << "| харон отвозит вас в царство аида и вы      |\n";
                cout << "| видите большую очередь из умерших душ людей|\n";
                cout << "| вы спросили куда ведет очередь, душа       |\n";
                cout << "| человека из очереди сказала вам что к аиду |\n";
                cout << "| который будет решать их судьбу             |\n";
                cout << "|                                            |\n";
                cout << "| |1|пойти в начало очереди                  |\n";
                cout << "|                                            |\n";
                cout << "|____________________________________________|\n";
                cin >> vibor_igroka;
            } while (vibor_igroka != 1);
        }
        if (vibor_igroka == 1) {
            do {
                for (int i = 0; i < 1; i++) {
    cout << "______________________________________________\n";
    cout << "    Открыть меню путей прокачки?              \n";
    cout << "  1) Нет                      2) Да           \n";
    cout << "______________________________________________\n";
    cin >> a;
    if (a == 1) {
        break;
    }
    if (a == 2) {

        cout << "______________________________________________\n";
        if (b == 0) {
            cout << "     Вам не хватило очков для прокачки.       \n";
            cout << "   Очки можно получить, сходив в Оптику.      \n";
            this_thread::sleep_for(chrono::nanoseconds(3000000000));
            cout << "          Да ладно, смешно же.                \n";
            cout << "   Очки можно получить  по ходу сюжета.       \n";
            cout << "  После выполнения заданий и побед в боях     \n";
            cout << "  вы будете получать по одному очку.          \n";
            cout << "______________________________________________\n";
            this_thread::sleep_for(chrono::nanoseconds(3000000000));
            break;
        }

    }
    cout << "             1) ЗАЩИТА                       \n";
    cout << "  2)нАПАДЕНИЕ          3)ЭРУДИЦИЯ             \n";
    cout << "                                              \n";
    cout << "______________________________________________\n";
    cin >> a;

    if (a == 1) {
        defence = defence + 20;
        b--;
        cout << "             ЗАЩИТА равна:                    \n";
        cout << defence << "\n";
        cout << "             АТАКА равна:                     \n";
        cout << atk << "\n";
        cout << "             ЭРУДИЦИЯ равна:                  \n";
        cout << erud << "\n";
    }
    if (a == 2) {
        atk = atk + 15;
        b--;
        cout << "             ЗАЩИТА равна:                    \n";
        cout << defence << "\n";
        cout << "             АТАКА равна:                     \n";
        cout << atk << "\n";
        cout << "             ЭРУДИЦИЯ равна:                  \n";
        cout << erud << "\n";
       
    }
    if (a == 3) {
        erud = erud + 1;
        b--;

        cout << "             ЗАЩИТА равна:                    \n";
        cout << defence << "\n";
        cout << "             АТАКА равна:                     \n";
        cout << atk << "\n";
        cout << "             ЭРУДИЦИЯ равна:                  \n";
        cout << erud << "\n";
    }
}

                cout << "______________________________________________\n";
                cout << "| вы дошли туда только через минту 30 или час|\n";
                cout << "| в большой комнате по центру сидел сам аид  |\n";
                cout << "| ниже его трона сидел трехглавый цербер на  |\n";
                cout << "| толстой железной цепи который не давал     |\n";
                cout << "| мертвым пройти в обычный мир, слева сидела |\n";
                cout << "| его супруга, а с права два человека, минос |\n";
                cout << "| и радамант они судьи, помогающие аиду      |\n";
                cout << "| выбрать наказание для мертвой души.        |\n";
                cout << "|                                            |\n";
                cout << "| |1|подслушать разговор                     |\n";
                cout << "|                                            |\n";
                cout << "|____________________________________________|\n";
                cin >> vibor_igroka;
            } while (vibor_igroka != 1);

        }
        if (vibor_igroka == 1) {
            do {
                cout << "______________________________________________\n";
                cout << "| <Хо-Хо-Хо друг мой,если ты попал сюда то   |\n";
                cout << "| явно никто не ошибся, как бог подземного   |\n";
                cout << "| царства, сын всемогещего Кратоса и Реи     |\n";
                cout << "| отправляю тебя ломать не ломаемый камень!> |\n";
                cout << "|                                            |\n";
                cout << "| |1|это ужас надо выбираться от сюда        |\n";
                cout << "|____________________________________________|\n";
                cin >> vibor_igroka;
            } while (vibor_igroka != 1);
        }
        if (vibor_igroka == 1) {
            do {
                cout << "______________________________________________\n";
                cout << "| пока вы придумывали план к вас подошел     |\n";
                cout << "| неизвестный мужчина <привет, что делаешь?> |\n";
                cout << "|                                            |\n";
                cout << "| |1|продумываю план как сбежать от сюда     |\n";
                cout << "| |2|неважно                                 |\n";
                cout << "|____________________________________________|\n";
                cin >> vibor_igroka;
            } while (vibor_igroka != 1 && vibor_igroka != 2);
        }
        if (vibor_igroka == 2) {
            do {
                cout << "______________________________________________\n";
                cout << "| <не-не-не, слушай друг, я вижу что ты не   |\n";
                cout << "| стоишь в очереди,ты что-то скрываешь>      |\n";
                cout << "|                                            |\n";
                cout << "| |1|я хочу выбраться от сюда                |\n";
                cout << "|____________________________________________|\n";
                cin >> vibor_igroka;
            } while (vibor_igroka != 1);
        }
        if (vibor_igroka == 1) {
            do {
                cout << "______________________________________________\n";
                cout << "| <выбраться? ты же понимаешь что никто от   |\n";
                cout << "| сюда не выбирался просто так, никто здесь  |\n";
                cout << "| не оказался случайно. Даже если так то что |\n";
                cout << "| ты хочешь сделать?>                        |\n";
                cout << "|                                            |\n";
                cout << "| |1|убить аида |2|попросить харона перевезти|\n";
                cout << "| меня обратно                               |\n";
                cout << "|____________________________________________|\n";
                cin >> vibor_igroka;
            } while (vibor_igroka != 1 && vibor_igroka != 2);
        }
        if (vibor_igroka == 2) {
            cout << "______________________________________________\n";
            cout << "| неа, этот вариант сразу отпадает, харон    |\n";
            cout << "| просто не может перевести обратно умершую  |\n";
            cout << "| душу.                                      |\n";
            cout << "|                                            |\n";
            cout << "|____________________________________________|\n";
            this_thread::sleep_for(chrono::nanoseconds(3000000000));
            do {
                cout << "______________________________________________\n";
                cout << "| вот с убийством аида впринципе возможно,но |\n";
                cout << "| если ты не полу бог хотябы то будет очень, |\n";
                cout << "| ОЧЕНЬ сложно                               |\n";
                cout << "|                                            |\n";
                cout << "| |1|и что мне делать?                       |\n";
                cout << "|____________________________________________|\n";
                cin >> vibor_igroka;
            } while (vibor_igroka != 1);
        }
        if (vibor_igroka == 1) {
            do {
                cout << "______________________________________________\n";
                cout << "| тебе очень повезло, я являюсь гонцом       |\n";
                cout << "| гефеста(гефест-искусный бог кузнец делал   |\n";
                cout << "| оружие для богов). я могу тебе продать     |\n";
                cout << "| оружие и броню с помощью которой ты сможешь|\n";
                cout << "| убить аида                                 |\n";
                cout << "|                                            |\n";
                cout << "| |1|согласиться                             |\n";
                cout << "|____________________________________________|\n";
                cin >> vibor_igroka;
            } while (vibor_igroka != 1);
        }
        if (vibor_igroka == 1) {
            do {
                cout << "______________________________________________\n";
                cout << "| Тогда по рукам, я схожу к гефесту, спрошу  |\n";
                cout << "| сколько будет стоить оружие и броня, а ты  |\n";
                cout << "| пока заработай денег, вот тебе клинок.     |\n";
                cout << "|                                            |\n";
                cout << "| |1|а где еду брать? |2|осмотреть клинок    |\n";
                cout << "|____________________________________________|\n";
                cin >> vibor_igroka;
            } while (vibor_igroka != 1 && vibor_igroka != 2);
        }
        if (vibor_igroka == 1) {
            do {
                cout << "______________________________________________\n";
                cout << "| не беспокойся, ты же <мертвая душа> тебе   |\n";
                cout << "| еда не нужна.                              |\n";
                cout << "|                                            |\n";
                cout << "| |1|осмотреть клинок                        |\n";
                cout << "|____________________________________________|\n";
                cin >> vibor_igroka;
            } while (vibor_igroka != 1);
            vibor_igroka = vibor_igroka + 1;
        }
        if (vibor_igroka == 2) {
            do {
                cout << "______________________________________________\n";
                cout << "| клинок был очень тупым, настолько тупым что|\n";
                cout << "| им только кусты подравнивать...            |\n";
                cout << "|                                            |\n";
                cout << "| |1|Точно,кусты,пойти к садовнику аида аска-|\n";
                cout << "| лафу                                       |\n";
                cout << "|____________________________________________|\n";
                cin >> vibor_igroka;
            } while (vibor_igroka != 1);
        }
        if (vibor_igroka == 1) {
            do {
                cout << "______________________________________________\n";
                cout << "| пройдя в сад вы увидели мужчину с длинными |\n";
                cout << "| волосами который ходил по саду.            |\n";
                cout << "|                                            |\n";
                cout << "| |1|подойти к аскалафу                      |\n";
                cout << "|____________________________________________|\n";
                cin >> vibor_igroka;
            } while (vibor_igroka != 1);
        }
        if (vibor_igroka == 1) {
            do {
                cout << "______________________________________________\n";
                cout << "| когда аскалаф вас увидел он сразу удивился |\n";
                cout << "| и спросил <мертвая душа? ты не должен был  |\n";
                cout << "| тут оказаться>                             |\n";
                cout << "|                                            |\n";
                cout << "| |1|стой погоди! не рассказывай аиду что я  |\n";
                cout << "| не в очереди!                              |\n";
                cout << "| |2|мне нужны деньги                        |\n";
                cout << "|____________________________________________|\n";
            } while (vibor_igroka != 1);

        }
        if (vibor_igroka == 1) {
            do {
                cout << "______________________________________________\n";
                cout << "| я и не собирался ему рассказывать чего ты  |\n";
                cout << "| так испугался?                             |\n";
                cout << "|                                            |\n";
                cout << "| |1|мне нужны деньги                        |\n";
                cout << "|____________________________________________|\n";
                cin >> vibor_igroka;
            } while (vibor_igroka != 1);
        }
        if (vibor_igroka == 2) {
            vibor_igroka = 1;
            vibor_igroka2 = 0;
            vibor_igroka3 = 0;
            vibor_igroka4 = 0;
            vibor_igroka5 = 0;
        }
        if (vibor_igroka == 1) {
            do {
                cout << "______________________________________________\n";
                cout << "| значит тебе нужны деньги? ясно, и что ты   |\n";
                cout << "| собираешься делать с этими деньгами?       |\n";
                cout << "|                                            |\n";
                cout << "| |1|вообще-то я уже договорился с кузнецом  |\n";
                cout << "| гефестом, он скует мне оружие и броню и с  |\n";
                cout << "| помощью них я убью аида                    |\n";
                cout << "|____________________________________________|\n";
                cin >> vibor_igroka;
            } while (vibor_igroka != 1);
        }
        if (vibor_igroka == 1) {
            do {
                cout << "______________________________________________\n";
                cout << "| гефест? ну ладно он и вравду кует отличное |\n";
                cout << "| оружие и броню, ты можешь подстричь кусты и|\n";
                cout << "| я дам тебе немного денег                   |\n";
                cout << "|                                            |\n";
                cout << "| |1|согласиться                             |\n";
                cout << "|                                            |\n";
                cout << "|____________________________________________|\n";
            } while (vibor_igroka != 1);
        }
        if (vibor_igroka == 1) {
            playerCoins = playerCoins + 500;
            do {
                cout << "______________________________________________\n";
                cout << "| потратив несколько десятков минут аскалаф  |\n";
                cout << "| дал вам монет.                             |\n";
                cout << "|                                            |\n";
                cout << "| |1|где еще можно взять денег?              |\n";
                cout << "| |2|посмотреть количество мемкоинов         |\n";
                cout << "|____________________________________________|\n";
                cin >> vibor_igroka;
            } while (vibor_igroka != 1 && vibor_igroka != 2);
            if (vibor_igroka == 2) {
                do {

                    cout << "______________________________________________\n";
                    cout << "| у вас " << playerCoins << "                                  | \n";
                    cout << "|                                            |\n";
                    cout << "| |1|продолжить                              |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka2;
                } while (vibor_igroka2 != 1);
                if (vibor_igroka2 == 1) {
                    do {
                        cout << "______________________________________________\n";
                        cout << "| потратив несколько десятков минут аскалаф  |\n";
                        cout << "| дал вам монет.                             |\n";
                        cout << "|                                            |\n";
                        cout << "| |1|где еще можно взять денег?              |\n";
                        cout << "|____________________________________________|\n";
                        cin >> vibor_igroka;
                    } while (vibor_igroka != 1);
                }
            }
        }
        if (vibor_igroka == 1) {
            do {
                cout << "______________________________________________\n";
                cout << "| ты можешь выполнить еще одно мое задание   |\n";
                cout << "| или пойти выполнить работу харона, а то я  |\n";
                cout << "| знаю что он очень устал выполнять свою     |\n";
                cout << "| работу несколько десятков столетий         |\n";
                cout << "|                                            |\n";
                cout << "| |1|выполнить задание аскалафа              |\n";
                cout << "| |2|выполнить задание харона                |\n";
                cout << "|____________________________________________|\n";
                cin >> vibor_igroka4;
            } while (vibor_igroka4 != 1 && vibor_igroka4 != 2);
        }
        if (vibor_igroka4 == 1) {// ВЫБОР ВЫПОЛНИТЬ СНАЧАЛО ЗАДАНИЕ АСКАЛАФА
            do {
                cout << "______________________________________________\n";
                cout << "| хмм мое, ну давай тогда я тебе дам такое   |\n";
                cout << "| задание... ммм оо, а сходи ка ты к левке   |\n";
                cout << "| (левка-девушка которую любил аид, он ее    |\n";
                cout << "| похитил и после смерти превратил ее в белый|\n";
                cout << "| тополь) левка находиться в елисейских полях|\n";
                cout << "| а в елисейских полях как ты надеюсь знаешь |\n";
                cout << "| вечная весна и она все время опадает, так  |\n";
                cout << "| вот тебе нужно ее срубить.                 |\n";
                cout << "|                                            |\n";
                cout << "| |1|согласиться                             |\n";
                cout << "|____________________________________________|\n";
                cin >> vibor_igroka;
            } while (vibor_igroka != 1);
            if (vibor_igroka == 1) {
                do {
                    cout << "______________________________________________\n";
                    cout << "| аскалаф отвел вас к ней и сказал что ты    |\n";
                    cout << "| можешь выполнять задание, он уже собирался |\n";
                    cout << "| уходить, но вспомнил что вам нечем рубить и|\n";
                    cout << "| вручил топор                               |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|взять топор                             |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1);
            }
            if (vibor_igroka == 1) {
                do {
                    cout << "______________________________________________\n";
                    cout << "| вы взяли топор и подошли к левке           |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|ударить                                 |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1);
            }
            if (vibor_igroka == 1) {
                do {
                    cout << "______________________________________________\n";
                    cout << "| видимо одним ударом тут не обойдешься      |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|ударить                                 |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1);
            }
            if (vibor_igroka == 1) {
                do {
                    cout << "______________________________________________\n";
                    cout << "| дерево плохо поддается ударам, но вы не    |\n";
                    cout << "| хотели останавливаться                     |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|ударить                                 |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1);
            }
            if (vibor_igroka == 1) {
                do {
                    cout << "______________________________________________\n";
                    cout << "|                                            |\n";
                    cout << "| |1|ударить                                 |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1);
            }
            if (vibor_igroka == 1) {
                do {
                    cout << "______________________________________________\n";
                    cout << "|                                            |\n";
                    cout << "| |1|ударить                                 |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1);
            }
            if (vibor_igroka == 1) {
                do {
                    cout << "______________________________________________\n";
                    cout << "| осталось примерно половина подумали вы     |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|ударить                                 |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1);
            }
            if (vibor_igroka == 1) {
                do {
                    cout << "______________________________________________\n";
                    cout << "|                                            |\n";
                    cout << "| |1|ударить                                 |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1);
            }
            if (vibor_igroka == 1) {
                do {
                    cout << "______________________________________________\n";
                    cout << "|                                            |\n";
                    cout << "| |1|ударить                                 |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1);
            }
            if (vibor_igroka == 1) {
                do {
                    cout << "______________________________________________\n";
                    cout << "| осталось чуть-чуть                         |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|ударить                                 |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1);
            }
            if (vibor_igroka == 1) {
                do {
                    cout << "______________________________________________\n";
                    cout << "|                                            |\n";
                    cout << "| |1|ударить                                 |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1);
            }
            if (vibor_igroka == 1) {
                do {
                    cout << "______________________________________________\n";
                    cout << "|                                            |\n";
                    cout << "| |1|ударить                                 |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1);
            }
            if (vibor_igroka == 1) {
                do {
                    cout << "______________________________________________\n";
                    cout << "| дерево упало, вы наконец-то закончили      |\n";
                    cout << "| пора возвращаться                          |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|возвращаться к аскалафу                 |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1);
            }
            if (vibor_igroka == 1) {
                playerCoins = playerCoins + 1000;
                do {
                    cout << "______________________________________________\n";
                    cout << "| вы пришли к аскалафу и он отблагодарил вас |\n";
                    cout << "| деньгами                                   |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|уйти                                    |\n";
                    cout << "| |2|посмотреть количество мемкоинов         |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1 && vibor_igroka != 2);
            }
            if (vibor_igroka == 2) {
                do {

                    cout << "______________________________________________\n";
                    cout << "| у вас " << playerCoins << "                                 | \n";
                    cout << "|                                            |\n";
                    cout << "| |1|продолжить                              |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka2;
                } while (vibor_igroka2 != 1);
                if (vibor_igroka2 == 1) {
                    do {
                        cout << "______________________________________________\n";
                        cout << "| вы пришли к аскалафу и он отблагодарил вас |\n";
                        cout << "| деньгами                                   |\n";
                        cout << "|                                            |\n";
                        cout << "| |1|уйти                                    |\n";
                        cout << "|____________________________________________|\n";
                        cin >> vibor_igroka;
                    } while (vibor_igroka != 1);
                }
            }
            if (vibor_igroka == 1) {
                do {
                    cout << "______________________________________________\n";
                    cout << "| когда вы уходили вы услышали за спиной     |\n";
                    cout << "| Аид: Аскалаф! КТО СРУБИЛ МОЮ ЛЕВКУ? ПОЧЕМУ |\n";
                    cout << "| ТЫ НЕ СЛЕДИЛ ЗА НЕЙ?!?                     |\n";
                    cout << "| Аскалаф: ее никто не срубал мой владыка.   |\n";
                    cout << "| Аид: МНЕ ЧЕРТЫ ДОЛОЖИЛИ ЧТО ОНА СРУБЛЕНА   |\n";
                    cout << "| ГОЛОВУ С ПЛЕЧ!!!                           |\n";
                    cout << "| черты хватают аскалафа и начинают его нести|\n";
                    cout << "|                                            |\n";
                    cout << "| |1|извини аскалаф, я не чем не смогу тебе  |\n";
                    cout << "| помочь.                                    |\n";
                    cout << "| |2|попытаться помочь аскалафу              |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1 && vibor_igroka != 2);
            }
            if (vibor_igroka == 2) {
                cout << "______________________________________________\n";
                cout << "| Эй аид! а ну отпусти аскалафа!             |\n";
                cout << "| Аид: ТЫ! МЕРТВАЯ ДУША, ЭТО ТЫ СРУБИЛ ЛЕВКУ?|\n";
                cout << "| А НУ СХВАТИТЬ ЕГО!                         |\n";
                cout << "| вас хватают черты и теперь вы вечно будете |\n";
                cout << "| падать в вечную яму                        |\n";
                cout << "|____________________________________________|\n";
                return 0;
            }
            if (vibor_igroka == 1) {
                do {
                    cout << "______________________________________________\n";
                    cout << "| вы вспомнили про встречу с гонцом гефеста и|\n";
                    cout << "| пошли на то место встречи, там вас уже он  |\n";
                    cout << "| ждал, вы подошли к нему и спросили узнал ли|\n";
                    cout << "| он цену?                                   |\n";
                    cout << "| гонец: Конечно узнал друг мой, броня и меч |\n";
                    cout << "| будут стоить 3000 мемкоинов                |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|посмотреть количество мемкоинов         |\n";
                    cout << "| |2|огорчиться тому что у вас не хватает    |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1 && vibor_igroka != 2);
                if (vibor_igroka == 1) {
                    do {

                        cout << "______________________________________________\n";
                        cout << "| у вас " << playerCoins << "                                 | \n";
                        cout << "|                                            |\n";
                        cout << "| |1|продолжить                              |\n";
                        cout << "|____________________________________________|\n";
                        cin >> vibor_igroka2;
                    } while (vibor_igroka2 != 1);
                    if (vibor_igroka == 1) {
                        do {
                            cout << "______________________________________________\n";
                            cout << "| вы вспомнили про встречу с гонцом гефеста и|\n";
                            cout << "| пошли на то место встречи, там вас уже он  |\n";
                            cout << "| ждал, вы подошли к нему и спросили узнал ли|\n";
                            cout << "| он цену?                                   |\n";
                            cout << "| гонец: Конечно узнал друг мой, броня и меч |\n";
                            cout << "| будут стоить 3000 мемкоинов                |\n";
                            cout << "|                                            |\n";
                            cout << "| |1|огорчиться тому что у вас не хватает    |\n";
                            cout << "|____________________________________________|\n";
                            cin >> vibor_igroka;
                        } while (vibor_igroka != 1);
                        vibor_igroka = vibor_igroka + 1;
                    }
                }
            }
            if (vibor_igroka == 2) {
                do {
                    cout << "______________________________________________\n";
                    cout << "| слезами делу не поможет подумали вы и пошли|\n";
                    cout << "| к харону чтобы взять задание у него,       |\n";
                    cout << "| харон: тебе нужно перевезти 3 души пока я  |\n";
                    cout << "| буду отдыхать.                             |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|согласиться                             |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1);
            }
            if (vibor_igroka == 1) {//1 душа
                do {
                    cout << "______________________________________________\n";
                    cout << "| вы сели в лодку и посадили туда 1 мертвую  |\n";
                    cout << "| душу.                                      |\n";
                    cout << "| мертвая душа:*американский акцент* привет, |\n";
                    cout << "| я не много говорить по русски, я так  думаю|\n";
                    cout << "| ты есть харон?                             |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|да |2|нет                               |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1 && vibor_igroka != 2);
                if (vibor_igroka == 1) {
                    do {
                        cout << "______________________________________________\n";
                        cout << "| оу ну это очень круто, я так понимаю тебе  |\n";
                        cout << "| надо рассказать свою историю жизни?        |\n";
                        cout << "|                                            |\n";
                        cout << "| |1|необяза...                              |\n";
                        cout << "|____________________________________________|\n";
                        cin >> vibor_igroka;
                    } while (vibor_igroka != 1);
                }
                if (vibor_igroka == 2) {
                    do {
                        cout << "______________________________________________\n";
                        cout << "| оу ну ничего страшного, но я так понимать  |\n";
                        cout << "| тебе надо рассказать свою историю?         |\n";
                        cout << "|                                            |\n";
                        cout << "| |1|необяза...                              |\n";
                        cout << "|____________________________________________|\n";
                        cin >> vibor_igroka;
                    } while (vibor_igroka != 1);
                }
                if (vibor_igroka == 1) {
                    do {
                        cout << "______________________________________________\n";
                        cout << "| я был обычным ребенком, родился в лос-анже-|\n";
                        cout << "| лесе, в 1958, я всемирный певец, меня часто|\n";
                        cout << "| называли <король поп-музыки>, а еще я при- |\n";
                        cout << "| думал лунную походку, ну все я так вижу мы |\n";
                        cout << "| приехали.                                  |\n";
                        cout << "|                                            |\n";
                        cout << "| |1|прощай! мертвая душа                    |\n";
                        cout << "|____________________________________________|\n";
                        cin >> vibor_igroka;
                    } while (vibor_igroka != 1);
                }
            }
            if (vibor_igroka == 1) {//2 душа
                do {
                    cout << "______________________________________________\n";
                    cout << "| вы поехали и взяли вторую мертвую душу     |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|ну расскажи ты свою историю             |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1);
                if (vibor_igroka == 1) {
                    do {
                        cout << "______________________________________________\n";
                        cout << "| мертвая душа:*немецкий акцент* майн история|\n";
                        cout << "| их бин правитель великого и развивающегося |\n";
                        cout << "| государства, вел свой народ к победа, но   |\n";
                        cout << "| наш проигрышь быть неизбежен, айн мужестве-|\n";
                        cout << "| нно сражаться со своии солдат, но майн     |\n";
                        cout << "| окружить, ай делать паф паф эйд айм тут    |\n";
                        cout << "|                                            |\n";
                        cout << "| |1|отличная история, мы приехали           |\n";
                        cout << "|____________________________________________|\n";
                        cin >> vibor_igroka;
                    } while (vibor_igroka != 1);
                }
            }
            if (vibor_igroka == 1) {//3 мертвая душа
                do {
                    cout << "______________________________________________\n";
                    cout << "| вы отвезли вторую мертвую душу и поплыли за|\n";
                    cout << "| 3.                                         |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|поведай мне свою историю                |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1);
                if (vibor_igroka == 1) {
                    playerCoins = playerCoins + 500;
                    do {
                        cout << "______________________________________________\n";
                        cout << "| мертвая душа:*германский акцент* айн был   |\n";
                        cout << "| великий физик-теоретик, майн теория относи-|\n";
                        cout << "| тельности изменить мир, умер я от кровоиз- |\n";
                        cout << "| леяния в мозг а из за этого разорвалась    |\n";
                        cout << "| анеризма аорты.                            |\n";
                        cout << "|                                            |\n";
                        cout << "| |1|отличная история жалко что мы уже       |\n";
                        cout << "| припыли, я бы послушал еще                 |\n";
                        cout << "|____________________________________________|\n";
                        cin >> vibor_igroka;
                    } while (vibor_igroka != 1);
                }
            }
            if (vibor_igroka == 1) {
                do {
                    cout << "______________________________________________\n";
                    cout << "| после выполнения всех заданий вы вспомнили |\n";
                    cout << "| что у аида есть еще и дочка у которой точно|\n";
                    cout << "| есть еще задания                           |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|пойти к макарии                         |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka4 != 1);
                vibor_igroka = 0;
                vibor_igroka2 = 0;
                vibor_igroka3 = 0;
                vibor_igroka5 = 0;
            }
        }
        if (vibor_igroka4 == 2) {//ВЫБОР ВЫПОЛНИТЬ СНАЧАЛО ЗАДАНИЕ ХАРОНА
            do {
                cout << "______________________________________________\n";
                cout << "| вы пошли к харону чтобы взять задание      |\n";
                cout << "| харон: тебе нужно перевезти 3 души пока я  |\n";
                cout << "| буду отдыхать.                             |\n";
                cout << "|                                            |\n";
                cout << "| |1|согласиться                             |\n";
                cout << "|____________________________________________|\n";
                cin >> vibor_igroka;
            } while (vibor_igroka != 1);
        }
        if (vibor_igroka == 1) {//1 душа
            playerCoins = playerCoins + 500;
            do {
                cout << "______________________________________________\n";
                cout << "| вы сели в лодку и посадили туда 1 мертвую  |\n";
                cout << "| душу.                                      |\n";
                cout << "| мертвая душа:*американский акцент* привет, |\n";
                cout << "| я не много говорить по русски, я так  думаю|\n";
                cout << "| ты есть харон?                             |\n";
                cout << "|                                            |\n";
                cout << "| |1|да |2|нет                               |\n";
                cout << "|____________________________________________|\n";
                cin >> vibor_igroka;
            } while (vibor_igroka != 1 && vibor_igroka != 2);
            if (vibor_igroka == 1) {
                do {
                    cout << "______________________________________________\n";
                    cout << "| оу ну это очень круто, я так понимаю тебе  |\n";
                    cout << "| надо рассказать свою историю жизни?        |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|необяза...                              |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1);
            }
            if (vibor_igroka == 2) {
                do {
                    cout << "______________________________________________\n";
                    cout << "| оу ну ничего страшного, но я так понимать  |\n";
                    cout << "| тебе надо рассказать свою историю?         |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|необяза...                              |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1);
            }
            if (vibor_igroka == 1) {
                do {
                    cout << "______________________________________________\n";
                    cout << "| я был обычным ребенком, родился в лос-анже-|\n";
                    cout << "| лесе, в 1958, я всемирный певец, меня часто|\n";
                    cout << "| называли <король поп-музыки>, а еще я при- |\n";
                    cout << "| думал лунную походку, ну все я так вижу мы |\n";
                    cout << "| приехали.                                  |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|прощай! мертвая душа                    |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1);
            }
        }
        if (vibor_igroka == 1) {//2 душа
            do {
                cout << "______________________________________________\n";
                cout << "| вы поехали и взяли вторую мертвую душу     |\n";
                cout << "|                                            |\n";
                cout << "| |1|ну расскажи ты свою историю             |\n";
                cout << "|____________________________________________|\n";
                cin >> vibor_igroka;
            } while (vibor_igroka != 1);
            if (vibor_igroka == 1) {
                do {
                    cout << "______________________________________________\n";
                    cout << "| мертвая душа:*немецкий акцент* майн история|\n";
                    cout << "| их бин правитель великого и развивающегося |\n";
                    cout << "| государства, вел свой народ к победа, но   |\n";
                    cout << "| наш проигрышь быть неизбежен, айн мужестве-|\n";
                    cout << "| нно сражаться со своии солдат, но майн     |\n";
                    cout << "| окружить, ай делать паф паф эйд айм тут    |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|отличная история, мы приехали           |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1);
            }
        }
        if (vibor_igroka == 1) {//3 мертвая душа
            do {
                cout << "______________________________________________\n";
                cout << "| вы отвезли вторую мертвую душу и поплыли за|\n";
                cout << "| 3.                                         |\n";
                cout << "|                                            |\n";
                cout << "| |1|поведай мне свою историю                |\n";
                cout << "|____________________________________________|\n";
                cin >> vibor_igroka;
            } while (vibor_igroka != 1);
            if (vibor_igroka == 1) {
                do {
                    cout << "______________________________________________\n";
                    cout << "| мертвая душа:*германский акцент* айн был   |\n";
                    cout << "| великий физик-теоретик, майн теория относи-|\n";
                    cout << "| тельности изменить мир, умер я от кровоиз- |\n";
                    cout << "| леяния в мозг а из за этого разорвалась    |\n";
                    cout << "| анеризма аорты.                            |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|отличная история жалко что мы уже       |\n";
                    cout << "| припыли, я бы послушал еще                 |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1);
            }
        }
        if (vibor_igroka == 1) {
            do {
                cout << "______________________________________________\n";
                cout << "| вы вспомнили про встречу с гонцом гефеста и|\n";
                cout << "| пошли на то место встречи, там вас уже он  |\n";
                cout << "| ждал, вы подошли к нему и спросили узнал ли|\n";
                cout << "| он цену?                                   |\n";
                cout << "| гонец: Конечно узнал друг мой, броня и меч |\n";
                cout << "| будут стоить 3000 мемкоинов                |\n";
                cout << "|                                            |\n";
                cout << "| |1|посмотреть количество мемкоинов         |\n";
                cout << "| |2|огорчиться тому что у вас не хватает    |\n";
                cout << "|____________________________________________|\n";
                cin >> vibor_igroka;
            } while (vibor_igroka != 1 && vibor_igroka != 2);
            if (vibor_igroka == 1) {
                do {

                    cout << "______________________________________________\n";
                    cout << "| у вас " << playerCoins << "                                 | \n";
                    cout << "|                                            |\n";
                    cout << "| |1|продолжить                              |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka2;
                } while (vibor_igroka2 != 1);
                if (vibor_igroka == 1) {
                    do {
                        cout << "______________________________________________\n";
                        cout << "| вы вспомнили про встречу с гонцом гефеста и|\n";
                        cout << "| пошли на то место встречи, там вас уже он  |\n";
                        cout << "| ждал, вы подошли к нему и спросили узнал ли|\n";
                        cout << "| он цену?                                   |\n";
                        cout << "| гонец: Конечно узнал друг мой, броня и меч |\n";
                        cout << "| будут стоить 3000 мемкоинов                |\n";
                        cout << "|                                            |\n";
                        cout << "| |1|огорчиться тому что у вас не хватает    |\n";
                        cout << "|____________________________________________|\n";
                        cin >> vibor_igroka;
                    } while (vibor_igroka != 1);
                    vibor_igroka = vibor_igroka + 1;
                }
            }
            if (vibor_igroka == 2) {
                do {
                    cout << "______________________________________________\n";
                    cout << "| вы огорчились но решили                    |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|пойти к аскалафу                        |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1);
            }
            if (vibor_igroka == 1) {
                do {
                    cout << "______________________________________________\n";
                    cout << "| хмм мое, ну давай тогда я тебе дам такое   |\n";
                    cout << "| задание... ммм оо, а сходи ка ты к левке   |\n";
                    cout << "| (левка-девушка которую любил аид, он ее    |\n";
                    cout << "| похитил и после смерти превратил ее в белый|\n";
                    cout << "| тополь) левка находиться в елисейских полях|\n";
                    cout << "| а в елисейских полях как ты надеюсь знаешь |\n";
                    cout << "| вечная весна и она все время опадает, так  |\n";
                    cout << "| вот тебе нужно ее срубить.                 |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|согласиться                             |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1);
                if (vibor_igroka == 1) {
                    do {
                        cout << "______________________________________________\n";
                        cout << "| аскалаф отвел вас к ней и сказал что ты    |\n";
                        cout << "| можешь выполнять задание, он уже собирался |\n";
                        cout << "| уходить, но вспомнил что вам нечем рубить и|\n";
                        cout << "| вручил топор                               |\n";
                        cout << "|                                            |\n";
                        cout << "| |1|взять топор                             |\n";
                        cout << "|____________________________________________|\n";
                        cin >> vibor_igroka;
                    } while (vibor_igroka != 1);
                }
                if (vibor_igroka == 1) {
                    do {
                        cout << "______________________________________________\n";
                        cout << "| вы взяли топор и подошли к левке           |\n";
                        cout << "|                                            |\n";
                        cout << "| |1|ударить                                 |\n";
                        cout << "|____________________________________________|\n";
                        cin >> vibor_igroka;
                    } while (vibor_igroka != 1);
                }
                if (vibor_igroka == 1) {
                    do {
                        cout << "______________________________________________\n";
                        cout << "| видимо одним ударом тут не обойдешься      |\n";
                        cout << "|                                            |\n";
                        cout << "| |1|ударить                                 |\n";
                        cout << "|____________________________________________|\n";
                        cin >> vibor_igroka;
                    } while (vibor_igroka != 1);
                }
                if (vibor_igroka == 1) {
                    do {
                        cout << "______________________________________________\n";
                        cout << "| дерево плохо поддается ударам, но вы не    |\n";
                        cout << "| хотели останавливаться                     |\n";
                        cout << "|                                            |\n";
                        cout << "| |1|ударить                                 |\n";
                        cout << "|____________________________________________|\n";
                        cin >> vibor_igroka;
                    } while (vibor_igroka != 1);
                }
                if (vibor_igroka == 1) {
                    do {
                        cout << "______________________________________________\n";
                        cout << "|                                            |\n";
                        cout << "| |1|ударить                                 |\n";
                        cout << "|____________________________________________|\n";
                        cin >> vibor_igroka;
                    } while (vibor_igroka != 1);
                }
                if (vibor_igroka == 1) {
                    do {
                        cout << "______________________________________________\n";
                        cout << "|                                            |\n";
                        cout << "| |1|ударить                                 |\n";
                        cout << "|____________________________________________|\n";
                        cin >> vibor_igroka;
                    } while (vibor_igroka != 1);
                }
                if (vibor_igroka == 1) {
                    do {
                        cout << "______________________________________________\n";
                        cout << "| осталось примерно половина подумали вы     |\n";
                        cout << "|                                            |\n";
                        cout << "| |1|ударить                                 |\n";
                        cout << "|____________________________________________|\n";
                        cin >> vibor_igroka;
                    } while (vibor_igroka != 1);
                }
                if (vibor_igroka == 1) {
                    do {
                        cout << "______________________________________________\n";
                        cout << "|                                            |\n";
                        cout << "| |1|ударить                                 |\n";
                        cout << "|____________________________________________|\n";
                        cin >> vibor_igroka;
                    } while (vibor_igroka != 1);
                }
                if (vibor_igroka == 1) {
                    do {
                        cout << "______________________________________________\n";
                        cout << "|                                            |\n";
                        cout << "| |1|ударить                                 |\n";
                        cout << "|____________________________________________|\n";
                        cin >> vibor_igroka;
                    } while (vibor_igroka != 1);
                }
                if (vibor_igroka == 1) {
                    do {
                        cout << "______________________________________________\n";
                        cout << "| осталось чуть-чуть                         |\n";
                        cout << "|                                            |\n";
                        cout << "| |1|ударить                                 |\n";
                        cout << "|____________________________________________|\n";
                        cin >> vibor_igroka;
                    } while (vibor_igroka != 1);
                }
                if (vibor_igroka == 1) {
                    do {
                        cout << "______________________________________________\n";
                        cout << "|                                            |\n";
                        cout << "| |1|ударить                                 |\n";
                        cout << "|____________________________________________|\n";
                        cin >> vibor_igroka;
                    } while (vibor_igroka != 1);
                }
                if (vibor_igroka == 1) {
                    do {
                        cout << "______________________________________________\n";
                        cout << "|                                            |\n";
                        cout << "| |1|ударить                                 |\n";
                        cout << "|____________________________________________|\n";
                        cin >> vibor_igroka;
                    } while (vibor_igroka != 1);
                }
                if (vibor_igroka == 1) {
                    do {
                        cout << "______________________________________________\n";
                        cout << "| дерево упало, вы наконец-то закончили      |\n";
                        cout << "| пора возвращаться                          |\n";
                        cout << "|                                            |\n";
                        cout << "| |1|возвращаться к аскалафу                 |\n";
                        cout << "|____________________________________________|\n";
                        cin >> vibor_igroka;
                    } while (vibor_igroka != 1);
                }
                if (vibor_igroka == 1) {
                    playerCoins = playerCoins + 1000;
                    do {
                        cout << "______________________________________________\n";
                        cout << "| вы пришли к аскалафу и он отблагодарил вас |\n";
                        cout << "| деньгами                                   |\n";
                        cout << "|                                            |\n";
                        cout << "| |1|уйти                                    |\n";
                        cout << "| |2|посмотреть количество мемкоинов         |\n";
                        cout << "|____________________________________________|\n";
                        cin >> vibor_igroka;
                    } while (vibor_igroka != 1 && vibor_igroka != 2);
                }
                if (vibor_igroka == 2) {
                    do {

                        cout << "______________________________________________\n";
                        cout << "| у вас " << playerCoins << "                                 | \n";
                        cout << "|                                            |\n";
                        cout << "| |1|продолжить                              |\n";
                        cout << "|____________________________________________|\n";
                        cin >> vibor_igroka2;
                    } while (vibor_igroka2 != 1);
                    if (vibor_igroka2 == 1) {
                        playerCoins = playerCoins + 1000;
                        do {
                            cout << "______________________________________________\n";
                            cout << "| вы пришли к аскалафу и он отблагодарил вас |\n";
                            cout << "| деньгами                                   |\n";
                            cout << "|                                            |\n";
                            cout << "| |1|уйти                                    |\n";
                            cout << "|____________________________________________|\n";
                            cin >> vibor_igroka;
                        } while (vibor_igroka != 1);
                    }
                }
                if (vibor_igroka == 1) {
                    do {
                        cout << "______________________________________________\n";
                        cout << "| когда вы уходили вы услышали за спиной     |\n";
                        cout << "| Аид: Аскалаф! КТО СРУБИЛ МОЮ ЛЕВКУ? ПОЧЕМУ |\n";
                        cout << "| ТЫ НЕ СЛЕДИЛ ЗА НЕЙ?!?                     |\n";
                        cout << "| Аскалаф: ее никто не срубал мой владыка.   |\n";
                        cout << "| Аид: МНЕ ЧЕРТЫ ДОЛОЖИЛИ ЧТО ОНА СРУБЛЕНА   |\n";
                        cout << "| ГОЛОВУ С ПЛЕЧ!!!                           |\n";
                        cout << "| черты хватают аскалафа и начинают его нести|\n";
                        cout << "|                                            |\n";
                        cout << "| |1|извини аскалаф, я не чем не смогу тебе  |\n";
                        cout << "| помочь.                                    |\n";
                        cout << "| |2|попытаться помочь аскалафу              |\n";
                        cout << "|____________________________________________|\n";
                        cin >> vibor_igroka;
                    } while (vibor_igroka != 1 && vibor_igroka != 2);
                }
                if (vibor_igroka == 2) {
                    cout << "______________________________________________\n";
                    cout << "| Эй аид! а ну отпусти аскалафа!             |\n";
                    cout << "| Аид: ТЫ! МЕРТВАЯ ДУША, ЭТО ТЫ СРУБИЛ ЛЕВКУ?|\n";
                    cout << "| А НУ СХВАТИТЬ ЕГО!                         |\n";
                    cout << "| вас хватают черты и теперь вы вечно будете |\n";
                    cout << "| падать в вечную яму                        |\n";
                    cout << "|____________________________________________|\n";
                    return 0;
                }
                if (vibor_igroka == 1) {
                    do {
                        cout << "______________________________________________\n";
                        cout << "| после выполнения всех заданий вы вспомнили |\n";
                        cout << "| что у аида есть еще и дочка у которой точно|\n";
                        cout << "| есть еще задания                           |\n";
                        cout << "|                                            |\n";
                        cout << "| |1|пойти к макарии                         |\n";
                        cout << "|____________________________________________|\n";
                        cin >> vibor_igroka;
                    } while (vibor_igroka4 != 1);
                    vibor_igroka = 0;
                    vibor_igroka2 = 0;
                    vibor_igroka3 = 0;
                    vibor_igroka5 = 0;
                }
            }

        }
        if (vibor_igroka4 == 1) {
            do {
                for (int i = 0; i < 1; i++) {
    cout << "______________________________________________\n";
    cout << "    Открыть меню путей прокачки?              \n";
    cout << "  1) Нет                      2) Да           \n";
    cout << "______________________________________________\n";
    cin >> a;
    if (a == 1) {
        break;
    }
    if (a == 2) {

        cout << "______________________________________________\n";
        if (b == 0) {
            cout << "     Вам не хватило очков для прокачки.       \n";
            cout << "   Очки можно получить, сходив в Оптику.      \n";
            this_thread::sleep_for(chrono::nanoseconds(3000000000));
            cout << "          Да ладно, смешно же.                \n";
            cout << "   Очки можно получить  по ходу сюжета.       \n";
            cout << "  После выполнения заданий и побед в боях     \n";
            cout << "  вы будете получать по одному очку.          \n";
            cout << "______________________________________________\n";
            this_thread::sleep_for(chrono::nanoseconds(3000000000));
            break;
        }

    }
    cout << "             1) ЗАЩИТА                       \n";
    cout << "  2)нАПАДЕНИЕ          3)ЭРУДИЦИЯ             \n";
    cout << "                                              \n";
    cout << "______________________________________________\n";
    cin >> a;

    if (a == 1) {
        defence = defence + 20;
        b--;
        cout << "             ЗАЩИТА равна:                    \n";
        cout << defence << "\n";
        cout << "             АТАКА равна:                     \n";
        cout << atk << "\n";
        cout << "             ЭРУДИЦИЯ равна:                  \n";
        cout << erud << "\n";
    }
    if (a == 2) {
        atk = atk + 15;
        b--;
        cout << "             ЗАЩИТА равна:                    \n";
        cout << defence << "\n";
        cout << "             АТАКА равна:                     \n";
        cout << atk << "\n";
        cout << "             ЭРУДИЦИЯ равна:                  \n";
        cout << erud << "\n";
       
    }
    if (a == 3) {
        erud = erud + 1;
        b--;

        cout << "             ЗАЩИТА равна:                    \n";
        cout << defence << "\n";
        cout << "             АТАКА равна:                     \n";
        cout << atk << "\n";
        cout << "             ЭРУДИЦИЯ равна:                  \n";
        cout << erud << "\n";
    }
}
                cout << "______________________________________________\n";
                cout << "| макария: мертвая душа? Зачем ты пришел ко  |\n";
                cout << "| мне?                                       |\n";
                cout << "|                                            |\n";
                cout << "| |1|мне нужны деньги                        |\n";
                cout << "|____________________________________________|\n";
                cin >> vibor_igroka;
            } while (vibor_igroka != 1);
            if (vibor_igroka == 1) {
                do {
                    cout << "______________________________________________\n";
                    cout << "| Хорошо иди и убей стража циклопов по имени |\n";
                    cout << "| Кампе.                                     |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|согласиться                             |\n";
                    cout << "|____________________________________________|\n";
                } while (vibor_igroka != 1);
            }
            if (vibor_igroka == 1) {
                do {
                    cout << "______________________________________________\n";
                    cout << "| вы пришли в Тар тар где были заключены все |\n";
                    cout << "| циклопы и нашли Кампе                      |\n";
                    cout << "|                                            |\n";
                    cout << "|                                            |\n";
                    cout << "|                                            |\n";//БОЙ С КАМПЕ
                    cout << "| |1|продолжить                              |\n";
                    cout << "|____________________________________________|\n";

                    cin >> vibor_igroka;
                    health = 1000;
                    enemyhealth = 600;
                    for (int i = 0; i < enemyhealth;) {
                        int a = 0;
                        if (health <= 0) {
                            cout << "|           Вы погибли.                    |\n";
                            return 0;
                        }
                        if (a == 15 + erud) {
                            cout << "|   Ваша защита была пробита              |\n";
                            cout << "|    и Кампе  убила вас смертью насмерть. |\n";
                            return 0;
                        }
                        cout << "|      Кампе издает чудовищные звуки.        |\n";
                        cout << "|    1) Атаковать?     2)Защищаться?         |\n";
                        cin >> fight;
                        if (fight == 1) {
                            cout << "|    Вы бъёте Кампе,                         |\n";
                            cout << "|                   но получаете порез.      |\n";
                            enemyhealth = enemyhealth - atk;
                            health = health - 175 + defence;
                        }
                        if (fight == 2) {
                            cout << "|    Вы отражаете удар стража,               |\n";
                            cout << "|             и, пользуясь моментом, бьёте.  |\n";
                            enemyhealth = enemyhealth - 25;
                            a++;
                        }
                        cout << "|        Ваше оставшееся HP = " << health << "             |\n";
                        cout << "|        Оставшееся HP врага = " << enemyhealth << "            |\n";
                    }

                } while (vibor_igroka != 1);
            }
            if (vibor_igroka == 1) {
                playerCoins = playerCoins + 500;
                do {
                    cout << "______________________________________________\n";
                    cout << "| после победы над кампе вы вернулись к дочке|\n";
                    cout << "| аида и она дала вам денег за выполненое за-|\n";
                    cout << "| дие                                        |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|теперь мне хватает денег чтобы купить   |\n";
                    cout << "| оружие и броню                             |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1);
            }
            if (vibor_igroka == 1) {
                atk = atk + 250;
                defence = defence + 500;
                do {
                    cout << "______________________________________________\n";
                    cout << "| вы пошли к месту встречи с гонцом гефеста и|\n";
                    cout << "| он продал вам оружие и броню.              |\n";
                    cout << "| вы их надели и сразу испытали чувство      |\n";// ДОБАВИТЬ УРОН + 250 и ХП +500 ( ИЛИ ЧТО ТО РЯДОМ С ЭТИМИ ЗНАЧЕНИЯМИ)
                    cout << "| власти над другими                         |\n";
                    cout << "| броня стала вам говорить что-то            |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|прислушаться к броне                    |\n";
                    cout << "|____________________________________________|\n";

                    cin >> vibor_igroka;
                } while (vibor_igroka != 1);
            }
            if (vibor_igroka == 1) {
                do {
                    cout << "______________________________________________\n";
                    cout << "| минатос, убей минатоса, а потом радаманта  |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|послушать броню |2|не слушать и убить   |\n";
                    cout << "| аида.                                      |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1 && vibor_igroka != 2);
                if (vibor_igroka == 2) {
                    vibor_igroka2 = 0;
                    vibor_igroka3 = 0;
                    vibor_igroka4 = 0;
                    vibor_igroka5 = 0;
                }
                if (vibor_igroka == 1) {
                    //ДРАКА С МИНАТОСОМ
                    health = 1000;
                    enemyhealth = 1600;
                    for (int i = 0; i < enemyhealth;) {
                        int a = 0;
                        if (health <= 0) {
                            cout << "|           Вы погибли.                    |\n";
                            return 0;
                        }
                        if (a == 15 + erud) {
                            cout << "|   Ваша защита была пробита              |\n";
                            cout << "|             и Минатос убил вас.         |\n";
                            return 0;
                        }
                        cout << "|      Минатос бросается на вас.             |\n";
                        cout << "|    1) Атаковать?     2)Защищаться?         |\n";
                        cin >> fight;
                        if (fight == 1) {
                            cout << "|    Вы бъёте Минатоса,                      |\n";
                            cout << "|                   но получаете порез.      |\n";
                            enemyhealth = enemyhealth - atk;
                            health = health - 250 + defence;
                        }
                        if (fight == 2) {
                            cout << "|    Вы отражаете удар Минатоса,             |\n";
                            cout << "|             и, пользуясь моментом, бьёте.  |\n";
                            enemyhealth = enemyhealth - 50;
                            a++;
                        }
                        cout << "|        Ваше оставшееся HP = " << health << "             |\n";
                        cout << "|        Оставшееся HP врага = " << enemyhealth << "            |\n";
                    }
                    do {
                        b++;

                        for (int i = 0; i < 1; i++) {
    cout << "______________________________________________\n";
    cout << "    Открыть меню путей прокачки?              \n";
    cout << "  1) Нет                      2) Да           \n";
    cout << "______________________________________________\n";
    cin >> a;
    if (a == 1) {
        break;
    }
    if (a == 2) {

        cout << "______________________________________________\n";
        if (b == 0) {
            cout << "     Вам не хватило очков для прокачки.       \n";
            cout << "   Очки можно получить, сходив в Оптику.      \n";
            this_thread::sleep_for(chrono::nanoseconds(3000000000));
            cout << "          Да ладно, смешно же.                \n";
            cout << "   Очки можно получить  по ходу сюжета.       \n";
            cout << "  После выполнения заданий и побед в боях     \n";
            cout << "  вы будете получать по одному очку.          \n";
            cout << "______________________________________________\n";
            this_thread::sleep_for(chrono::nanoseconds(3000000000));
            break;
        }

    }
    cout << "             1) ЗАЩИТА                       \n";
    cout << "  2)нАПАДЕНИЕ          3)ЭРУДИЦИЯ             \n";
    cout << "                                              \n";
    cout << "______________________________________________\n";
    cin >> a;

    if (a == 1) {
        defence = defence + 20;
        b--;
        cout << "             ЗАЩИТА равна:                    \n";
        cout << defence << "\n";
        cout << "             АТАКА равна:                     \n";
        cout << atk << "\n";
        cout << "             ЭРУДИЦИЯ равна:                  \n";
        cout << erud << "\n";
    }
    if (a == 2) {
        atk = atk + 15;
        b--;
        cout << "             ЗАЩИТА равна:                    \n";
        cout << defence << "\n";
        cout << "             АТАКА равна:                     \n";
        cout << atk << "\n";
        cout << "             ЭРУДИЦИЯ равна:                  \n";
        cout << erud << "\n";
       
    }
    if (a == 3) {
        erud = erud + 1;
        b--;

        cout << "             ЗАЩИТА равна:                    \n";
        cout << defence << "\n";
        cout << "             АТАКА равна:                     \n";
        cout << atk << "\n";
        cout << "             ЭРУДИЦИЯ равна:                  \n";
        cout << erud << "\n";
    }
}
                        cout << "______________________________________________\n";
                        cout << "| после победы над минатосом, броня вам гово-|\n";
                        cout << "| рит: радамант,убей теперь его              |\n";
                        cout << "|                                            |\n";
                        cout << "| |1|послушать броню |2|не слушать и убить   |\n";
                        cout << "| аида.                                      |\n";
                        cout << "|____________________________________________|\n";
                        cin >> vibor_igroka;
                    } while (vibor_igroka != 1 && vibor_igroka != 2);
                }
                if (vibor_igroka == 2) {
                    vibor_igroka2 = 0;
                    vibor_igroka3 = 0;
                    vibor_igroka4 = 0;
                    vibor_igroka5 = 0;
                }
                if (vibor_igroka == 1) {
                    //бой с РАДАМАНТОМ
                    health = 1000;
                    enemyhealth = 2600;
                    for (int i = 0; i < enemyhealth;) {
                        int a = 0;
                        if (health <= 0) {
                            cout << "|           Вы погибли.                    |\n";
                            return 0;
                        }
                        if (a == 15 + erud) {
                            cout << "|   Ваша защита была пробита              |\n";
                            cout << "|             и Радамант убил вас.        |\n";
                            return 0;
                        }
                        cout << "|      Радамант бросается на вас.            |\n";
                        cout << "|    1) Атаковать?     2)Защищаться?         |\n";
                        cin >> fight;
                        if (fight == 1) {
                            cout << "|    Вы бъёте Радаманта,                     |\n";
                            cout << "|                   но получаете порез.      |\n";
                            enemyhealth = enemyhealth - atk;
                            health = health - 300 + defence;
                        }
                        if (fight == 2) {
                            cout << "|    Вы отражаете удар Минатоса,             |\n";
                            cout << "|             и, пользуясь моментом, бьёте.  |\n";
                            enemyhealth = enemyhealth - 50;
                            a++;
                        }
                        cout << "|        Ваше оставшееся HP = " << health << "             |\n";
                        cout << "|        Оставшееся HP врага = " << enemyhealth << "            |\n";
                    }
                    do {
                        b++;
                        for (int i = 0; i < 1; i++) {
    cout << "______________________________________________\n";
    cout << "    Открыть меню путей прокачки?              \n";
    cout << "  1) Нет                      2) Да           \n";
    cout << "______________________________________________\n";
    cin >> a;
    if (a == 1) {
        break;
    }
    if (a == 2) {

        cout << "______________________________________________\n";
        if (b == 0) {
            cout << "     Вам не хватило очков для прокачки.       \n";
            cout << "   Очки можно получить, сходив в Оптику.      \n";
            this_thread::sleep_for(chrono::nanoseconds(3000000000));
            cout << "          Да ладно, смешно же.                \n";
            cout << "   Очки можно получить  по ходу сюжета.       \n";
            cout << "  После выполнения заданий и побед в боях     \n";
            cout << "  вы будете получать по одному очку.          \n";
            cout << "______________________________________________\n";
            this_thread::sleep_for(chrono::nanoseconds(3000000000));
            break;
        }

    }
    cout << "             1) ЗАЩИТА                       \n";
    cout << "  2)нАПАДЕНИЕ          3)ЭРУДИЦИЯ             \n";
    cout << "                                              \n";
    cout << "______________________________________________\n";
    cin >> a;

    if (a == 1) {
        defence = defence + 20;
        b--;
        cout << "             ЗАЩИТА равна:                    \n";
        cout << defence << "\n";
        cout << "             АТАКА равна:                     \n";
        cout << atk << "\n";
        cout << "             ЭРУДИЦИЯ равна:                  \n";
        cout << erud << "\n";
    }
    if (a == 2) {
        atk = atk + 15;
        b--;
        cout << "             ЗАЩИТА равна:                    \n";
        cout << defence << "\n";
        cout << "             АТАКА равна:                     \n";
        cout << atk << "\n";
        cout << "             ЭРУДИЦИЯ равна:                  \n";
        cout << erud << "\n";
       
    }
    if (a == 3) {
        erud = erud + 1;
        b--;

        cout << "             ЗАЩИТА равна:                    \n";
        cout << defence << "\n";
        cout << "             АТАКА равна:                     \n";
        cout << atk << "\n";
        cout << "             ЭРУДИЦИЯ равна:                  \n";
        cout << erud << "\n";
    }
}
                        cout << "______________________________________________\n";
                        cout << "| вы послушались броню и теперь не можете ее |\n";
                        cout << "| ослушаться, теперь убей всех богов олимпа  |\n";
                        cout << "|                                            |\n";
                        cout << "| |1|идти убивать аида                       |\n";
                        cout << "|____________________________________________|\n";
                        cin >> vibor_igroka5;
                    } while (vibor_igroka5 != 1);
                    vibor_igroka5 = vibor_igroka5 + 2;
                }
                if (vibor_igroka == 2) {
                    do {
                        cout << "______________________________________________\n";
                        cout << "| вы не стали слушать броню и пошли убивать  |\n";
                        cout << "| аида                                       |\n";
                        cout << "|                                            |\n";
                        cout << "| |1|Эй, аид, бог подземного царства, бог    |\n";
                        cout << "| мертвых, БОГ о котором гласят легенды,прими|\n";
                        cout << "| бой если ты не трус!                       |\n";
                        cout << "|____________________________________________|\n";
                        cin >> vibor_igroka;
                    } while (vibor_igroka != 1);
                    if (vibor_igroka == 1) {
                        cout << "______________________________________________\n";
                        cout << "| ХА-ХА-ХА обычный смертный пришел меня убить|\n";
                        cout << "| ты сейчас серьезно? Цербер в атаку         |\n";
                        cout << "|                                            |\n";
                        cout << "|____________________________________________|\n";
                        this_thread::sleep_for(chrono::nanoseconds(5000000000));
                        //БОЙ С ЦЕРБЕРОМ
                        health = 1000;
                        enemyhealth = 2500;
                        for (int i = 0; i < enemyhealth;) {
                            int a = 0;
                            if (health <= 0) {
                                cout << "|           Вы погибли.                    |\n";
                                return 0;
                            }
                            if (a == 15 + erud) {
                                cout << "|   Ваша защита была пробита              |\n";
                                cout << "|                и Аид убил вас.          |\n";
                                return 0;
                            }
                            cout << "|  Все три головы цербера таращатся на вас.  |\n";
                            cout << "|    1) Атаковать?     2)Защищаться?         |\n";
                            cin >> fight;
                            if (fight == 1) {
                                cout << "|    Вы бъёте одну из голов цербера,         |\n";
                                cout << "|                но другая вас кусает.       |\n";
                                enemyhealth = enemyhealth - atk;
                                health = health - 200 + defence;
                            }
                            if (fight == 2) {
                                cout << "|    Вы отражаете удар цербера,              |\n";
                                cout << "|             и, пользуясь моментом, бьёте.  |\n";
                                enemyhealth = enemyhealth - 50;
                                a++;
                            }
                            cout << "|        Ваше оставшееся HP = " << health << "             |\n";
                            cout << "|        Оставшееся HP врага = " << enemyhealth << "            |\n";
                        }
                        b++;
                        for (int i = 0; i < 1; i++) {
    cout << "______________________________________________\n";
    cout << "    Открыть меню путей прокачки?              \n";
    cout << "  1) Нет                      2) Да           \n";
    cout << "______________________________________________\n";
    cin >> a;
    if (a == 1) {
        break;
    }
    if (a == 2) {

        cout << "______________________________________________\n";
        if (b == 0) {
            cout << "     Вам не хватило очков для прокачки.       \n";
            cout << "   Очки можно получить, сходив в Оптику.      \n";
            this_thread::sleep_for(chrono::nanoseconds(3000000000));
            cout << "          Да ладно, смешно же.                \n";
            cout << "   Очки можно получить  по ходу сюжета.       \n";
            cout << "  После выполнения заданий и побед в боях     \n";
            cout << "  вы будете получать по одному очку.          \n";
            cout << "______________________________________________\n";
            this_thread::sleep_for(chrono::nanoseconds(3000000000));
            break;
        }

    }
    cout << "             1) ЗАЩИТА                       \n";
    cout << "  2)нАПАДЕНИЕ          3)ЭРУДИЦИЯ             \n";
    cout << "                                              \n";
    cout << "______________________________________________\n";
    cin >> a;

    if (a == 1) {
        defence = defence + 20;
        b--;
        cout << "             ЗАЩИТА равна:                    \n";
        cout << defence << "\n";
        cout << "             АТАКА равна:                     \n";
        cout << atk << "\n";
        cout << "             ЭРУДИЦИЯ равна:                  \n";
        cout << erud << "\n";
    }
    if (a == 2) {
        atk = atk + 15;
        b--;
        cout << "             ЗАЩИТА равна:                    \n";
        cout << defence << "\n";
        cout << "             АТАКА равна:                     \n";
        cout << atk << "\n";
        cout << "             ЭРУДИЦИЯ равна:                  \n";
        cout << erud << "\n";
       
    }
    if (a == 3) {
        erud = erud + 1;
        b--;

        cout << "             ЗАЩИТА равна:                    \n";
        cout << defence << "\n";
        cout << "             АТАКА равна:                     \n";
        cout << atk << "\n";
        cout << "             ЭРУДИЦИЯ равна:                  \n";
        cout << erud << "\n";
    }
}
                        cout << "______________________________________________\n";
                        cout << "| ЧТО?? КАК ТЫ ПОСМЕЛ УБИТЬ МОЕГО ЦЕРБЕРА    |\n";
                        cout << "| ТЕБЕ НЕ ЖИТЬ ЮНЕЦ                          |\n";
                        cout << "|                                            |\n";
                        cout << "|____________________________________________|\n";
                        //БОЙ С АИДОМ
                        health = 1000;
                        enemyhealth = 3000;
                        for (int i = 0; i < enemyhealth;) {
                            int a = 0;
                            if (health <= 0) {
                                cout << "|           Вы погибли.                    |\n";
                                return 0;
                            }
                            if (a == 15 + erud) {
                                cout << "|   Ваша защита была пробита              |\n";
                                cout << "|                и Аид убил вас.          |\n";
                                return 0;
                            }
                            cout << "|       Аид готовит свой двузубец.           |\n";
                            cout << "|    1) Атаковать?     2)Защищаться?         |\n";
                            cin >> fight;
                            if (fight == 1) {
                                cout << "|    Вы бъёте Аида,                           |\n";
                                cout << "|                   но получаете порез.      |\n";
                                enemyhealth = enemyhealth - atk;
                                health = health - 275 + defence;
                            }
                            if (fight == 2) {
                                cout << "|    Вы отражаете удар Аида,             |\n";
                                cout << "|             и, пользуясь моментом, бьёте.  |\n";
                                enemyhealth = enemyhealth - 50;
                                a++;
                            }
                            cout << "|        Ваше оставшееся HP = " << health << "             |\n";
                            cout << "|        Оставшееся HP врага = " << enemyhealth << "            |\n";
                        }
                        this_thread::sleep_for(chrono::nanoseconds(5000000000));
                        cout << "______________________________________________\n";
                        cout << "| после победы над аидом вы не стали его     |\n";
                        cout << "| убивать и ушли обратно в мир живых где     |\n";
                        cout << "| броня тут же раскололась на 2 части        |\n";
                        cout << "|____________________________________________|\n";
                        this_thread::sleep_for(chrono::nanoseconds(5000000000));
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "______________________________________________\n";
                        cout << "|              THE END!                      |\n";
                        cout << "|____________________________________________|\n";
                        this_thread::sleep_for(chrono::nanoseconds(2000000000));
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "\n";
                        cout << "______________________________________________\n";
                        cout << "|                  ТИТРЫ                     |\n";
                        cout << "| СЮЖЕТ,ДИАЛОГИ,ДЕНЬГИ-СИЛИННИК ВЛАД         |\n";
                        cout << "| ХАРАКТЕРИСТИКИ,БОИ-АНДРЕЕНКОВ АЛЕКСАНДР    |\n";
                        cout << "| ИНВЕНТАРЬ,МАГАЗИНЫ-СЕРОВ АЛЕКСАНДР         |\n";
                        cout << "|                                            |\n";
                        cout << "| СПАСИБО ЗА ИГРУ! ПРОДОЛЖЕНИЕ СЛЕДУЕТ ЕСЛИ  |\n";
                        cout << "| БУДУТ СПОНСОРЫ!(поставте 12 )              |\n";
                        cout << "|____________________________________________|\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        this_thread::sleep_for(chrono::nanoseconds(500000000));
                        cout << "\n";
                        return 0;
                    }
                }
            }
        }


        ////////////
        if (vibor_igroka5 == 3) {
            cout << "______________________________________________\n";
            cout << "| боги олимпа конечно сильны, но ваша сила   |\n";
            cout << "| придала вам уверености и вы пошли убивать  |\n";
            cout << "| Аид:ооо малец пришел который убил радаманта|\n";
            cout << "| и минатоса, моих судей теперь пришел убить |\n";
            cout << "| и меня? ну давай сразимся в чесном бою     |\n";
            cout << "|____________________________________________|\n";
            vibor_igroka = 1;//БОЙ С АИДОМ
            health = 1000;
            enemyhealth = 3000;
            for (int i = 0; i < enemyhealth;) {
                int a = 0;
                if (health <= 0) {
                    cout << "|           Вы погибли.                    |\n";
                    return 0;
                }
                if (a == 15 + erud) {
                    cout << "|   Ваша защита была пробита              |\n";
                    cout << "|                и Аид убил вас.          |\n";
                    return 0;
                }
                cout << "|       Аид готовит свой двузубец.           |\n";
                cout << "|    1) Атаковать?     2)Защищаться?         |\n";
                cin >> fight;
                if (fight == 1) {
                    cout << "|    Вы бъёте Аида,                          |\n";
                    cout << "|                   но получаете порез.      |\n";
                    enemyhealth = enemyhealth - atk;
                    health = health - 275 + defence;
                }
                if (fight == 2) {
                    cout << "|    Вы отражаете удар Аида,             |\n";
                    cout << "|             и, пользуясь моментом, бьёте.  |\n";
                    enemyhealth = enemyhealth - 50;
                    a++;
                }
                cout << "|        Ваше оставшееся HP = " << health << "             |\n";
                cout << "|        Оставшееся HP врага = " << enemyhealth << "            |\n";
            }
            if (vibor_igroka == 1) {
                do {
                    cout << "______________________________________________\n";
                    cout << "| после победы над аидом вы отрубили ему     |\n";
                    cout << "| голову и забрали ее броня вам говорит <убей|\n";
                    cout << "| зевса>                                     |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|идти убивать зевса                      |\n";
                    cout << "|____________________________________________|\n";
                } while (vibor_igroka != 1);
                if (vibor_igroka == 1) {
                    do {
                        cout << "______________________________________________\n";
                        cout << "| подняв голову вверх вы закричали ЗЕЕЕВС!   |\n";
                        cout << "| ВЫЙДИ НА БОЙ С ИЗВЕСНЫМ УБИЙЦЕЙ БОГОВ!!!   |\n";
                        cout << "| после этого перед вами появилась лестница в|\n";
                        cout << "| небеса                                     |\n";
                        cout << "|                                            |\n";
                        cout << "| |1|пойти на верх                           |\n";
                        cout << "|____________________________________________|\n";
                        cin >> vibor_igroka;
                    } while (vibor_igroka != 1);
                    if (vibor_igroka == 1) {
                        do {
                            cout << "______________________________________________\n";
                            cout << "| Зевс: кто ты смертный?                     |\n";
                            cout << "|                                            |\n";
                            cout << "| |1|напасть!                                |\n";
                            cout << "|____________________________________________|\n";
                            cin >> vibor_igroka;
                        } while (vibor_igroka != 1);//БОЙ С ЗЕВСОМ
                        if (vibor_igroka == 1) {
                            cout << "______________________________________________\n";
                            cout << "| вы убили аида и зевса, но на этом не решили|\n";
                            cout << "| останавливаться и продолжили дальше        |\n";
                            cout << "|                                            |\n";
                            cout << "|                                            |\n";
                            cout << "|____________________________________________|\n";
                            this_thread::sleep_for(chrono::nanoseconds(5000000000));
                            cout << "______________________________________________\n";
                            cout << "| ну а продолжение вы можете купить в стиме  |\n";
                            cout << "| серия игр называеться <god of war>         |\n";
                            cout << "|____________________________________________|\n";
                            this_thread::sleep_for(chrono::nanoseconds(5000000000));
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "______________________________________________\n";
                            cout << "|              THE END!                      |\n";
                            cout << "|____________________________________________|\n";
                            this_thread::sleep_for(chrono::nanoseconds(2000000000));
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "\n";
                            cout << "______________________________________________\n";
                            cout << "|                  ТИТРЫ                     |\n";
                            cout << "| СЮЖЕТ,ДИАЛОГИ,ДЕНЬГИ-СИЛИННИК ВЛАД         |\n";
                            cout << "| ХАРАКТЕРИСТИКИ,БОИ-АНДРЕЕНКОВ АЛЕКСАНДР    |\n";
                            cout << "| ИНВЕНТАРЬ,МАГАЗИНЫ-СЕРОВ АЛЕКСАНДР         |\n";
                            cout << "|                                            |\n";
                            cout << "| СПАСИБО ЗА ИГРУ! ПРОДОЛЖЕНИЕ СЛЕДУЕТ ЕСЛИ  |\n";
                            cout << "| БУДУТ СПОНСОРЫ!(поставте 12 )              |\n";
                            cout << "|____________________________________________|\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            this_thread::sleep_for(chrono::nanoseconds(500000000));
                            cout << "\n";
                            return 0;
                        }
                    }
                }
            }
        }
        if (vibor_igroka5 == 2) {
            do {
                cout << "______________________________________________\n";
                cout << "| боги олимпа конечно сильны, но ваша власть |\n";
                cout << "| придала вам уверености и вы пошли убивать  |\n";
                cout << "|                                            |\n";
                cout << "| |1|аида                                    |\n";
                cout << "|____________________________________________|\n";
                cin >> vibor_igroka;
            } while (vibor_igroka != 1);
        }
        if (vibor_igroka == 1) {//АИД
            do {
                cout << "______________________________________________\n";
                cout << "| вы пришли в подземное царство аида где вас |\n";
                cout << "| уже ждал аид, <Хо-Хо-Хо Неужели ты решил ко|\n";
                cout << "| мне прийдти? я ждал тебя, о тебе гласят    |\n";
                cout << "| легенды, король который с самой нищеты стал|\n";
                cout << "| самым богатым в мире. Цербер в атаку>      |\n";
                cout << "|                                            |\n";
                cout << "| |1|ты струсил? зачем отправлять цербера    |\n";
                cout << "|                                            |\n";
                cout << "|____________________________________________|\n";

                cin >> vibor_igroka2;
            } while (vibor_igroka2 != 1);
            if (vibor_igroka2 == 1) {
                do {
                    cout << "______________________________________________\n";
                    cout << "| величайший бог олимпа аид струсил? Да как  |\n";
                    cout << "| ты смеешь такое говорить?!                 |\n";
                    cout << "|                                            |\n";//бой с аидом
                    cout << "|____________________________________________|\n";
                    health = 1000;
                    enemyhealth = 3000;
                    for (int i = 0; i < enemyhealth;) {
                        int a = 0;
                        if (health <= 0) {
                            cout << "|           Вы погибли.                    |\n";
                            return 0;
                        }
                        if (a == 15 + erud) {
                            cout << "|   Ваша защита была пробита              |\n";
                            cout << "|                и Аид убил вас.          |\n";
                            return 0;
                        }
                        cout << "|       Аид готовит свой двузубец.           |\n";
                        cout << "|    1) Атаковать?     2)Защищаться?         |\n";
                        cin >> fight;
                        if (fight == 1) {
                            cout << "|    Вы бъёте Аида,                          |\n";
                            cout << "|                   но получаете порез.      |\n";
                            enemyhealth = enemyhealth - atk;
                            health = health - 275 + defence;
                        }
                        if (fight == 2) {
                            cout << "|    Вы отражаете удар Аида,             |\n";
                            cout << "|             и, пользуясь моментом, бьёте.  |\n";
                            enemyhealth = enemyhealth - 50;
                            a++;
                        }
                        cout << "|        Ваше оставшееся HP = " << health << "             |\n";
                        cout << "|        Оставшееся HP врага = " << enemyhealth << "            |\n";
                    }
                } while (vibor_igroka2 != 1);
            }
            if (vibor_igroka2 == 1) {
                do {
                    b++;
                    cout << "______________________________________________\n";
                    cout << "| *плевок крови* кхе кхе ты победил меня?    |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|получаеться так                         |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka2 != 1);
            }
            if (vibor_igroka2 == 1) {
                do {
                    for (int i = 0; i < 1; i++) {
    cout << "______________________________________________\n";
    cout << "    Открыть меню путей прокачки?              \n";
    cout << "  1) Нет                      2) Да           \n";
    cout << "______________________________________________\n";
    cin >> a;
    if (a == 1) {
        break;
    }
    if (a == 2) {

        cout << "______________________________________________\n";
        if (b == 0) {
            cout << "     Вам не хватило очков для прокачки.       \n";
            cout << "   Очки можно получить, сходив в Оптику.      \n";
            this_thread::sleep_for(chrono::nanoseconds(3000000000));
            cout << "          Да ладно, смешно же.                \n";
            cout << "   Очки можно получить  по ходу сюжета.       \n";
            cout << "  После выполнения заданий и побед в боях     \n";
            cout << "  вы будете получать по одному очку.          \n";
            cout << "______________________________________________\n";
            this_thread::sleep_for(chrono::nanoseconds(3000000000));
            break;
        }

    }
    cout << "             1) ЗАЩИТА                       \n";
    cout << "  2)нАПАДЕНИЕ          3)ЭРУДИЦИЯ             \n";
    cout << "                                              \n";
    cout << "______________________________________________\n";
    cin >> a;

    if (a == 1) {
        defence = defence + 20;
        b--;
        cout << "             ЗАЩИТА равна:                    \n";
        cout << defence << "\n";
        cout << "             АТАКА равна:                     \n";
        cout << atk << "\n";
        cout << "             ЭРУДИЦИЯ равна:                  \n";
        cout << erud << "\n";
    }
    if (a == 2) {
        atk = atk + 15;
        b--;
        cout << "             ЗАЩИТА равна:                    \n";
        cout << defence << "\n";
        cout << "             АТАКА равна:                     \n";
        cout << atk << "\n";
        cout << "             ЭРУДИЦИЯ равна:                  \n";
        cout << erud << "\n";
       
    }
    if (a == 3) {
        erud = erud + 1;
        b--;

        cout << "             ЗАЩИТА равна:                    \n";
        cout << defence << "\n";
        cout << "             АТАКА равна:                     \n";
        cout << atk << "\n";
        cout << "             ЭРУДИЦИЯ равна:                  \n";
        cout << erud << "\n";
    }
}
                    cout << "______________________________________________\n";
                    cout << "| нет, нет,нет НЕ ДУМАЙ ЧТО ВСЕ БУДЕТ ТАК    |\n";
                    cout << "| ПРОСТО                                     |\n";//2 стадия боя с аидом
                    cout << "|                                            |\n";
                    cout << "|____________________________________________|\n";
                    health = 1000;
                    enemyhealth = 4000;
                    for (int i = 0; i < enemyhealth;) {
                        int a = 0;
                        if (health <= 0) {
                            cout << "|           Вы погибли.                    |\n";
                            return 0;
                        }
                        if (a == 15 + erud) {
                            cout << "|   Ваша защита была пробита              |\n";
                            cout << "|                и Аид убил вас.          |\n";
                            return 0;
                        }
                        cout << "|Аид готовит свой двузубец,светящийся кровью.|\n";
                        cout << "|    1) Атаковать?     2)Защищаться?         |\n";
                        cin >> fight;
                        if (fight == 1) {
                            cout << "|    Вы бъёте Аида,                          |\n";
                            cout << "|                   но получаете порез.      |\n";
                            enemyhealth = enemyhealth - atk;
                            health = health - 275 + defence;
                        }
                        if (fight == 2) {
                            cout << "|    Вы отражаете удар Аида,             |\n";
                            cout << "|             и, пользуясь моментом, бьёте.  |\n";
                            enemyhealth = enemyhealth - 60;
                            a++;
                        }
                        cout << "|        Ваше оставшееся HP = " << health << "             |\n";
                        cout << "|        Оставшееся HP врага = " << enemyhealth << "            |\n";
                    }
                    cin >> vibor_igroka2;
                } while (vibor_igroka2 != 1);
            }
            if (vibor_igroka2 == 1) {
                b++;
                cout << "______________________________________________\n";
                cout << "| победы над аидом вам не хватило и вы пошли |\n";
                cout << "| дальше                                     |\n";
                cout << "|                                            |\n";
                cout << "| |2|зевса                                   |\n";
                cout << "|____________________________________________|\n";
                vibor_igroka = 2;

            }
            if (vibor_igroka == 2) {
                do {
                    cout << "______________________________________________\n";
                    cout << "| подняв голову вверх вы закричали ЗЕЕЕВС!   |\n";
                    cout << "| ВЫЙДИ НА БОЙ С ИЗВЕСНЫМ КОРОЛЕМ КОРОЛЕВСТВА|\n";
                    cout << "| после этого перед вами появилась лестница в|\n";
                    cout << "| небеса                                     |\n";
                    cout << "| Зевс: Ты кто мой мальчик?                  |\n";
                    cout << "|                                            |\n";
                    cout << "| |1|я тот кто известен фразой <из грязи в   |\n";
                    cout << "| князи>                                     |\n";
                    cout << "| |2|я тот кто убил его *отдать голову аида) |\n";
                    cout << "|____________________________________________|\n";
                } while (vibor_igroka != 1 && vibor_igroka != 2);
            }
            if (vibor_igroka == 1) {
                do {
                    cout << "______________________________________________\n";
                    cout << "|зевс: всеравно не понимаю кто ты, ну не суть|\n";
                    cout << "| ты точно хочешь со мной драться?           |\n";//БОЙ С ЗЕВСОМ
                    cout << "|                                            |\n";
                    cout << "| |1|да!я вызываю тебя на бой                |\n";
                    cout << "|____________________________________________|\n";
                    cin >> vibor_igroka;
                } while (vibor_igroka != 1);
            }
            if (vibor_igroka == 2) {
                do {
                    cout << "______________________________________________\n";
                    cout << "| зевс:ого ты убил моего брата похвально, но |\n";
                    cout << "| я сильнее                                  |\n";
                    cout << "|                                            |\n";//БОЙ С ЗЕВСОМ
                    cout << "| |1|начать бой                              |\n";
                    cout << "|____________________________________________|\n";
                } while (vibor_igroka != 1);
            }
            if (vibor_igroka == 1) {
                cout << "______________________________________________\n";
                cout << "| вы убили аида и зевса, но на этом не решили|\n";
                cout << "| останавливаться и продолжили дальше        |\n";
                cout << "|                                            |\n";
                cout << "|                                            |\n";
                cout << "|____________________________________________|\n";
                this_thread::sleep_for(chrono::nanoseconds(5000000000));
                cout << "______________________________________________\n";
                cout << "| ну а продолжение вы можете купить в стиме  |\n";
                cout << "| серия игр называеться <god of war>         |\n";
                cout << "|____________________________________________|\n";
                this_thread::sleep_for(chrono::nanoseconds(5000000000));
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "______________________________________________\n";
                cout << "|              THE END!                      |\n";
                cout << "|____________________________________________|\n";
                this_thread::sleep_for(chrono::nanoseconds(2000000000));
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "\n";
                cout << "______________________________________________\n";
                cout << "|                  ТИТРЫ                     |\n";
                cout << "| СЮЖЕТ,ДИАЛОГИ,ДЕНЬГИ-СИЛИННИК ВЛАД         |\n";
                cout << "| ХАРАКТЕРИСТИКИ,БОИ-АНДРЕЕНКОВ АЛЕКСАНДР    |\n";
                cout << "| ИНВЕНТАРЬ,МАГАЗИНЫ-СЕРОВ АЛЕКСАНДР         |\n";
                cout << "|                                            |\n";
                cout << "| СПАСИБО ЗА ИГРУ! ПРОДОЛЖЕНИЕ СЛЕДУЕТ ЕСЛИ  |\n";
                cout << "| БУДУТ СПОНСОРЫ!(поставте 12 )              |\n";
                cout << "|____________________________________________|\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                this_thread::sleep_for(chrono::nanoseconds(500000000));
                cout << "\n";
                return 0;
            }
        }
    }
}









// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
