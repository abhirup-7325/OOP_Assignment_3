#include <iostream>
#include <map>
#include <string>

const int pending = 0;
const int successful = 1;
const int failed = 2;

class Item {
public:
    Item(int itemCode, const std::string& name, int rate, int quantity)
        : _itemCode(itemCode), _name(name), _rate(rate), _quantity(quantity) {}

    void setQuantity(int newQuantity) {
        _quantity = newQuantity;
    }

    void setRate(int newRate) {
        _rate = newRate;
    }

    int getRate() const {
        return _rate;
    }

    int getQuantity() const {
        return _quantity;
    }

    int getItemCode() const {
        return _itemCode;
    }

    std::string getName() const {
        return _name;
    }

private:
    int _itemCode;
    std::string _name;
    int _rate;
    int _quantity;
};

class Transaction {
public:
    virtual void performTransaction() = 0;
    virtual ~Transaction() {}
};

class Issue : public Transaction {
public:
    static Issue* createIssue(Item* item, int delta) {
        if (item && item->getQuantity() >= delta) {
            return new Issue(item, delta);
        } else {
            return NULL;
        }
    }

    void performTransaction() {
        if (_status != pending) {
            return;
        }

        if (_item->getQuantity() < _delta) {
            _status = failed;
        } else {
            _item->setQuantity(_item->getQuantity() - _delta);
            _status = successful;
        }
    }

private:
    Issue(Item* item, int delta) : _item(item), _delta(delta), _status(pending) {}

    Item* _item;
    int _delta;
    int _status;
};

class Receipt : public Transaction {
public:
    static Receipt* createReceipt(Item* item, int delta) {
        return item ? new Receipt(item, delta) : NULL;
    }

    void performTransaction() {
        if (_status != pending) {
            return;
        }

        _item->setQuantity(_item->getQuantity() + _delta);
        _status = successful;
    }

private:
    Receipt(Item* item, int delta) : _item(item), _delta(delta), _status(pending) {}

    Item* _item;
    int _delta;
    int _status;
};

class ItemFactorySingleton {
public:
    static ItemFactorySingleton* getInstance() {
        static ItemFactorySingleton instance;
        return &instance;
    }

    Item* createItem(int itemCode, const std::string& name, int rate, int quantity) {
        if (isItemPresent(itemCode)) {
            return NULL;
        }

        Item* newItem = new Item(itemCode, name, rate, quantity);
        items[itemCode] = newItem;
        return newItem;
    }

    bool isItemPresent(int itemCode) const {
        return items.find(itemCode) != items.end();
    }

    Item* getItem(int itemCode) {
        return isItemPresent(itemCode) ? items[itemCode] : NULL;
    }

    int getPrice(int itemCode) const {
        return isItemPresent(itemCode) ? items.at(itemCode)->getRate() : -1;
    }

    int getQuantity(int itemCode) const {
        return isItemPresent(itemCode) ? items.at(itemCode)->getQuantity() : -1;
    }

private:
    ItemFactorySingleton() {};
    ItemFactorySingleton(const ItemFactorySingleton&);
    ItemFactorySingleton& operator=(const ItemFactorySingleton&);
    std::map<int, Item*> items;
};

int main() {
    ItemFactorySingleton* factory = ItemFactorySingleton::getInstance();

    Item* item1 = factory->createItem(101, "Laptop", 1000, 10);
    Item* item2 = factory->createItem(102, "Phone", 500, 20);

    if (item1) {
        Issue* issue1 = Issue::createIssue(item1, 5);
        if (issue1) {
            issue1->performTransaction();
            delete issue1;
        }
    }

    if (item2) {
        Receipt* receipt1 = Receipt::createReceipt(item2, 10);
        if (receipt1) {
            receipt1->performTransaction();
            delete receipt1;
        }
    }

    std::cout << "Laptop Quantity: " << factory->getQuantity(101) << "\n";
    std::cout << "Phone Quantity: " << factory->getQuantity(102) << "\n";

    delete item1;
    delete item2;

    return 0;
}
