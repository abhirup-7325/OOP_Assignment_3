#include <iostream>
#include <vector>
#include <set>
#include <stdexcept>
#include <string>

const int STATUS_PENDING = 0;
const int STATUS_SUCCESSFUL = 1;
const int STATUS_FAILED = 2;

const int TRANSACTION_WITHDRAWAL = 0;
const int TRANSACTION_DEPOSIT = 1;

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

    void updateBalance(int delta) {
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
    Transaction(Balance* balance, int amount, std::string dateOfTransaction, char transactionType) {
        _balance = balance;
        _amount = amount;
        _dateOfTransaction = dateOfTransaction;
        _status = STATUS_PENDING;

        if (transactionType == 'W') {
            _transactionType = TRANSACTION_WITHDRAWAL;
        } else if (transactionType == 'D') {
            _transactionType = TRANSACTION_DEPOSIT;
        } else {
            throw std::runtime_error("Invalid Transaction Type!");
        }
    }

    void performTransaction() {
        if (_transactionType == TRANSACTION_DEPOSIT) {
            performDeposit();
        } else {
            performWithdrawal();
        }

        if (_status == STATUS_SUCCESSFUL) {
            _balance->pushTransaction(this);
        }
    }

private:
    Balance* _balance;
    std::string _dateOfTransaction;
    int _amount;
    int _status;
    int _transactionType;

    void performDeposit() {
        _balance->updateBalance(_amount);
        _status = STATUS_SUCCESSFUL;
    }

    void performWithdrawal() {
        if (_balance->isWithdrawalPossible(_amount)) {
            _balance->updateBalance(-_amount);
            _status = STATUS_SUCCESSFUL;
        } else {
            _status = STATUS_FAILED;
        }
    }
};

class AccountFactorySingleton {
public:
    static AccountFactorySingleton* getInstance() {
        if (_accountFactory == NULL) {
            _accountFactory = new AccountFactorySingleton();
        }
        return _accountFactory;
    }

    bool isAccountNumberUnique(int accountNumber) {
        return (_accountNumberSet.find(accountNumber) == _accountNumberSet.end());
    }

    Balance* createBalance(int accountNumber, int initialBalance) {
        if (isAccountNumberUnique(accountNumber)) {
            _accountNumberSet.insert(accountNumber);
            return new Balance(accountNumber, initialBalance, "N/A");
        } else {
            return NULL;
        }
    }

private:
    AccountFactorySingleton() {}

    AccountFactorySingleton(const AccountFactorySingleton&);
    AccountFactorySingleton& operator=(const AccountFactorySingleton&);

    static AccountFactorySingleton* _accountFactory;
    std::set<int> _accountNumberSet;
};

AccountFactorySingleton* AccountFactorySingleton::_accountFactory = NULL;

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
