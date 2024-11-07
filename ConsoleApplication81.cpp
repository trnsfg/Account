#include <iostream>
#include <cstring>

class Account {
private:
    char owner[100];
    char accountNumber[20];
    double interestRate;
    double deductionRate;
    double balance;
    static int count;

public:
    Account(const char* owner, const char* accountNumber,
        double interestRate, double deductionRate, double balance) {
        strcpy_s(this->owner, sizeof(this->owner), owner);
        strcpy_s(this->accountNumber, sizeof(this->accountNumber), accountNumber);

        this->interestRate = interestRate;
        this->deductionRate = deductionRate;
        this->balance = balance;

        count++;
    }

    ~Account() {
        count--;
    }

    static int getCount() {
        return count;
    }

    const char* getOwner() const { return owner; }
    const char* getAccountNumber() const { return accountNumber; }
    double getInterestRate() const { return interestRate; }
    double getDeductionRate() const { return deductionRate; }
    double getBalance() const { return balance; }

    void setOwner(const char* newOwner) {
        strcpy_s(owner, sizeof(owner), newOwner);
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            std::cout << "Insufficient funds!" << std::endl;
            return false;
        }
        balance -= amount;
        return true;
    }

    void deposit(double amount) {
        balance += amount;
    }

    void applyInterest() {
        balance += balance * (interestRate / 100);
    }

    void transferToUSD(double amountUAH) {
        double amountUSD = amountUAH / 36.5;
        if (amountUAH <= balance) {
            balance -= amountUAH;
            std::cout << "Transferred " << amountUSD << " USD" << std::endl;
        }
        else {
            std::cout << "Insufficient funds for USD transfer!" << std::endl;
        }
    }

    void transferToEUR(double amountUAH) {
        double amountEUR = amountUAH / 39.5;
        if (amountUAH <= balance) {
            balance -= amountUAH;
            std::cout << "Transferred " << amountEUR << " EUR" << std::endl;
        }
        else {
            std::cout << "Insufficient funds for EUR transfer!" << std::endl;
        }
    }

    void getBalanceInWords() const {
        int intPart = static_cast<int>(balance);
        int kopiyky = static_cast<int>((balance - intPart) * 100);

        std::cout << "Balance in words: ";

        if (intPart == 0) {
            std::cout << "zero";
        }
        else {
            if (intPart >= 1000) {
                int thousands = intPart / 1000;
                std::cout << thousands << " thousand ";
                intPart %= 1000;
            }
            if (intPart >= 100) {
                int hundreds = intPart / 100;
                std::cout << hundreds << " hundred ";
                intPart %= 100;
            }
            if (intPart >= 10) {
                int tens = intPart / 10;
                std::cout << tens << " tens ";
                intPart %= 10;
            }
            if (intPart > 0) {
                std::cout << intPart << " ";
            }
            std::cout << "hryvnias ";
        }

        if (kopiyky > 0) {
            std::cout << "and " << kopiyky << " kopecks";
        }

        std::cout << std::endl;
    }

    void display() const {
        std::cout << "Owner: " << owner << std::endl;
        std::cout << "Account Number: " << accountNumber << std::endl;
        std::cout << "Interest Rate: " << interestRate << "%" << std::endl;
        std::cout << "Deduction Rate: " << deductionRate << "%" << std::endl;
        std::cout << "Balance: " << balance << " UAH" << std::endl;
    }
};

int Account::count = 0;

int main() {
    Account acc1("ktoto1", "UA1234567890", 5.0, 1.0, 1000.0);
    Account acc2("ktoto2", "UA0987654321", 3.0, 0.5, 5000.0);

    acc1.display();
    acc2.display();


    acc1.deposit(500.0);
    acc2.deposit(1000.0);

    acc2.withdraw(1500.0);

    acc1.applyInterest();

    acc2.transferToUSD(2000.0);

    acc1.transferToEUR(1000.0);

    acc1.getBalanceInWords();

    std::cout << "Number of accounts created: " << Account::getCount() << std::endl;

    return 0;
}
