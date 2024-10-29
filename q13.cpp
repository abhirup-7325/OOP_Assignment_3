/*
Design a BALANCE class with account number, balance and date of last update.
Consider a TRANSACTION class with account number, date of transaction,
amount and transaction type (W for withdrawal and D for deposit). If it is
withdrawal then check whether the amount is available or not. Transaction object
will make necessary update in the BALANCE class.
*/


#include <iostream>
#include <vector>
#include <set>
#include <stdexcept>
#include <string>


enum Status {
    pending,
    successful,
    failed
};


enum TransactionType {
    withdrawal,
    deposit
};


class Transaction;


class Balance {
public:
    Balance(int accountNumber, int initialBalance, std::string dateOfLastUpdate) {
        _accountNumber = accountNumber;
        _balance = initialBalance;
        _dateOfLastUpdate = dateOfLastUpdate;
    }

    int getBalance() const {
        return _balance;
    }

    std::string getDateOfLastUpdate() const {
        return _dateOfLastUpdate;
    }

    bool isWithdrawalPossible(int withdrawalAmount) {
        return (withdrawalAmount <= _balance);
    }

    int updateBalance(int delta) {
        _balance += delta;
    }

    void pushTransaction(Transaction* transaction) {
        TransactionLog.push_back(transaction);
    }

private:
    int _accountNumber;
    int _balance;
    std::string _dateOfLastUpdate;

    std::vector<Transaction *> TransactionLog;
};



class Transaction {
public:
    Transaction(Balance* balance, int amount, std::string _dateOfTransaction, char transactionType) {
        _balance = balance;
        _amount = amount;
        _dateOfTransaction = _dateOfTransaction;
        _status = Status::pending;

        if (transactionType == 'W') {
            _transactionType = TransactionType::withdrawal;
        } else if (transactionType == 'D') {
            _transactionType = TransactionType::deposit;
        } else {
            throw std::runtime_error("Invalid Transaction Type!");
        }
    }


    void performTransaction() {
        if (_transactionType == TransactionType::deposit) {
            performDeposit();
        } else {
            performWithdrawal();
        }

        if (_status == Status::successful) {
            _balance->pushTransaction(this);
        }
    }

private:
    Balance* _balance;
    std::string _dateOfTransaction;
    int _amount;
    Status _status;
    TransactionType _transactionType;

    void performDeposit() {
        _balance->updateBalance(_amount);
        _status = Status::successful;
    }


    void performWithdrawal() {
        if (_balance->isWithdrawalPossible(_amount)) {
            _balance->updateBalance(-_amount);
            _status = Status::successful;
        } else {
            _status = Status::failed;
        }
    }
};



class AccountFactorySingleton {
public:
    static AccountFactorySingleton* getInstance() {
        if (_accountFactory == nullptr) {
            _accountFactory = new AccountFactorySingleton();
        }

        return _accountFactory;
    }

    AccountFactorySingleton(const AccountFactorySingleton&) = delete;
    AccountFactorySingleton& operator=(const AccountFactorySingleton&) = delete;

    bool isAccountNumberUnique(int accountNumber) {
        return (_accountNumberSet.find(accountNumber) == _accountNumberSet.end());
    }

    Balance* createBalance(int accountNumber, int initialBalance) {
        if (isAccountNumberUnique(accountNumber)) {
            _accountNumberSet.insert(accountNumber);

            return new Balance(accountNumber, initialBalance, "N/A");
        } else {
            return nullptr;
        }
    }

private:
    static AccountFactorySingleton *_accountFactory;

    AccountFactorySingleton() = default;
    std::set<int> _accountNumberSet;
};

AccountFactorySingleton* AccountFactorySingleton::_accountFactory = nullptr;


int main() {
    AccountFactorySingleton* factory = AccountFactorySingleton::getInstance();

    Balance* balance1 = factory->createBalance(12345, 1000);

    if (balance1) {
        std::cout << "Account created with balance: " << balance1->getBalance() << std::endl;

        Transaction deposit(balance1, 200, "2024-10-30", 'D');
        deposit.performTransaction();
        std::cout << "Updated balance after deposit: " << balance1->getBalance() << std::endl;

        Transaction withdrawal(balance1, 300, "2024-10-30", 'W');
        withdrawal.performTransaction();
        std::cout << "Updated balance after withdrawal: " << balance1->getBalance() << std::endl;

        Transaction withdrawalFail(balance1, 1000, "2024-10-30", 'W');
        withdrawalFail.performTransaction();
        std::cout << "Final balance: " << balance1->getBalance() << std::endl;
    } else {
        std::cerr << "Failed to create account. Account number already exists." << std::endl;
    }

    delete balance1;

    return 0;
}
