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
#include <memory>

const int STATUS_PENDING = 0;
const int STATUS_SUCCESSFUL = 1;
const int STATUS_FAILED = 2;

const int TRANSACTION_WITHDRAWAL = 0;
const int TRANSACTION_DEPOSIT = 1;

class Transaction;

class Balance {
public:
    int getBalance() const {
        return _balance;
    }

    std::string getDateOfLastUpdate() const {
        return _dateOfLastUpdate;
    }

    bool isWithdrawalPossible(int withdrawalAmount) const {
        return (withdrawalAmount <= _balance);
    }

    void pushTransaction(Transaction* transaction) {
        TransactionLog.push_back(transaction);
    }

private:
    Balance(int accountNumber, int initialBalance, const std::string& dateOfLastUpdate) 
        : _accountNumber(accountNumber), _balance(initialBalance), _dateOfLastUpdate(dateOfLastUpdate) {}

    int _accountNumber;
    int _balance;
    std::string _dateOfLastUpdate;
    std::vector<Transaction *> TransactionLog;

    void updateBalance(int delta) {
        _balance += delta;
    }

    friend class AccountFactorySingleton;
    friend class Transaction;
};

class Transaction {
public:
    Transaction(Balance* balance, int amount, const std::string& dateOfTransaction, char transactionType) 
        : _balance(balance), _amount(amount), _dateOfTransaction(dateOfTransaction), _status(STATUS_PENDING) {

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
            _performDeposit();
        } else {
            _performWithdrawal();
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

    void _performDeposit() {
        _balance->updateBalance(_amount);
        _status = STATUS_SUCCESSFUL;
    }

    void _performWithdrawal() {
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
        if (_accountFactory == nullptr) {
            _accountFactory = new AccountFactorySingleton();
        }
        return _accountFactory;
    }

    bool isAccountNumberUnique(int accountNumber) const {
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
    AccountFactorySingleton() {}

    AccountFactorySingleton(const AccountFactorySingleton&) = delete;
    AccountFactorySingleton& operator=(const AccountFactorySingleton&) = delete;

    static AccountFactorySingleton* _accountFactory;
    std::set<int> _accountNumberSet;
};

AccountFactorySingleton* AccountFactorySingleton::_accountFactory = nullptr;

int main() {
    
    
    return 0;
}
