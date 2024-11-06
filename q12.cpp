/*
Design the class(es) for the following scenario:
 An item list contains item code, name, rate, and quantity for several
items.
 Whenever a new item is added in the list uniqueness of item code is to be
checked.
 Time to time rate of the items may change.
 Whenever an item is issued or received existence of the item is checked
and quantity is updated.
 In case of issue, availability of quantity is also to be checked.
 User may also like to know price/quantity available for an item.
*/


#include <iostream>
#include <map>
#include <string>

const int pending = 0;
const int successful = 1;
const int failed = 2;

class Item;
class Issue;
class Receipt;

class Item {
public:
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
    Item(int itemCode, const std::string& name, int rate, int quantity)
        : _itemCode(itemCode), _name(name), _rate(rate), _quantity(quantity) {}

    void setQuantity(int newQuantity) {
        _quantity = newQuantity;
    }

    int _itemCode;
    std::string _name;
    int _rate;
    int _quantity;

    friend class ItemFactorySingleton;
    friend class Issue;
    friend class Receipt;
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
            return nullptr;
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
        return item ? new Receipt(item, delta) : nullptr;
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
        if (_instance == nullptr) {
            _instance = new ItemFactorySingleton();
        }

        return _instance;
    }

    Item* createItem(int itemCode, const std::string& name, int rate, int quantity) {
        if (isItemPresent(itemCode)) {
            return nullptr;
        }

        Item* newItem = new Item(itemCode, name, rate, quantity);
        items[itemCode] = newItem;
        return newItem;
    }

    bool isItemPresent(int itemCode) const {
        return items.find(itemCode) != items.end();
    }

    Item* getItem(int itemCode) {
        return isItemPresent(itemCode) ? items[itemCode] : nullptr;
    }

    int getPrice(int itemCode) const {
        return isItemPresent(itemCode) ? items.at(itemCode)->getRate() : -1;
    }

    int getQuantity(int itemCode) const {
        return isItemPresent(itemCode) ? items.at(itemCode)->getQuantity() : -1;
    }

private:
    ItemFactorySingleton() {}
    ItemFactorySingleton(const ItemFactorySingleton&) = delete;
    ItemFactorySingleton& operator=(const ItemFactorySingleton&) = delete;

    static ItemFactorySingleton *_instance;
    std::map<int, Item*> items;
};

ItemFactorySingleton* ItemFactorySingleton::_instance = nullptr;

int main() {
    

    return 0;
}
