//
// Created by Haoyu Gu on 2016-10-06.
//

#include "Account.h"
#include "../../Utils/sharedLib.h"
#include "../../Utils/Logger.h"
#include "../../Utils/headers.h"

Account::Account() {
    balance = 0.0;
    states = 0.0;
    accountType = Account::AccountType::Unknown;
}

Account::~Account() {

}

double Account::getBalance() {
    Logger::sharedInstance().logwft(__FILE__, __LINE__, __FUNCTION__ ,"");
    return balance;
}

bool Account::open(std::string& errMsg) {
    Logger::sharedInstance().logwft(__FILE__, __LINE__, __FUNCTION__ ,"");
    if (!states) {
        balance = 0.0;
        states = true;
        return true;
    }
    else {
        errMsg = "Account already exists.";
        return false;
    }
}

bool Account::close(std::string& errMsg) {
    Logger::sharedInstance().logwft(__FILE__, __LINE__, __FUNCTION__ ,"");
    if (states) {
        if (balance==0) {
            states = false;
            return true;
        }
        else {
            errMsg = "Account balance is not 0.";
            return false;
        }
    }
    else {
        errMsg = "Account doesn't exist.";
        return false;
    }
}

bool Account::isOpen() {
    Logger::sharedInstance().logwft(__FILE__, __LINE__, __FUNCTION__ ,"");
    return states;
}

Account::AccountType Account::getType() {
    Logger::sharedInstance().logwft(__FILE__, __LINE__, __FUNCTION__ ,"");
    return accountType;
}

bool Account::deposit(void* client, double amount, std::string &errMsg) {
    Logger::sharedInstance().logwft(__FILE__, __LINE__, __FUNCTION__ ,"");
    if (!states) {
        errMsg = "This account doesn't exist.";
        return false;
    }
    double verify = balance;
    balance+=amount;
    if (abs(balance-verify-amount)<0.00001){
        ((Client *)client)->addTransaction(Logger::sharedInstance().getTimeInLogFormat()+
                                           ":Deposit: "+sharedLib::strFromInt(amount)+
                                           " Balance: "+sharedLib::strFromInt(balance));
        ((Client *)client)->writeToFile();
        return true;
    }
    else {
        balance = verify;
        errMsg = "Failed to deposit.";
        return false;
    }
}

bool Account::transferReceive(void* srcClient, void* destClient, double amount, std::string &errMsg) {
    Logger::sharedInstance().logwft(__FILE__, __LINE__, __FUNCTION__ ,"");
    if (!states) {
        errMsg = "This account doesn't exist.";
        return false;
    }
    double verify = balance;
    balance+=amount;
    if (abs(balance-verify-amount)<0.00001){
        ((Client *)destClient)->addTransaction(Logger::sharedInstance().getTimeInLogFormat()+
                                           ":Receive funds: "+sharedLib::strFromInt(amount)+
                                           " From :"+((Client*)srcClient)->getUid()+
                                           " Balance: "+sharedLib::strFromInt(balance));
        ((Client *)destClient)->writeToFile();
        return true;
    }
    else {
        balance = verify;
        errMsg = "verification failed.";
        return false;
    }
}

bool Account::withdraw(void* client, double amount, std::string &errMsg) {
    Logger::sharedInstance().logwft(__FILE__, __LINE__, __FUNCTION__ ,"");
    if (!states) {
        errMsg = "This account doesn't exist.";
        return false;
    }
    if (amount<=balance) {
        double verify = balance;
        balance-=amount;
        if (abs(balance-verify-amount)<0.00001 && balance>=0) {
            ((Client *) client)->addTransaction(Logger::sharedInstance().getTimeInLogFormat() +
                                                ":Withdraw: " + sharedLib::strFromInt(amount) +
                                                " Balance: " + sharedLib::strFromInt(balance));
            ((Client *)client)->writeToFile();
            return true;
        }
        else {
            errMsg = "Failed to withdraw.";
            balance = verify;
            return false;
        }
    }
    else {
        errMsg = "insufficient funds.";
        return false;
    }
}

bool Account::transfer(void* srcClient, void* destClient, Account* destAccount, double amountWithdraw, double amountDeposit, std::string &errMsg) {
    Logger::sharedInstance().logwft(__FILE__, __LINE__, __FUNCTION__ ,"");
    if (!states) {
        errMsg = "This account doesn't exist.";
        return false;
    }
    if (destAccount) {
        if (balance>= amountWithdraw) {
            double verifySelf = balance;
            double verifyDest = destAccount->getBalance();
            balance-=amountWithdraw;
            std::string err;
            bool res = destAccount->transferReceive(srcClient, destClient, amountDeposit, err);
            if (res) {
                if ((verifyDest+amountDeposit-destAccount->getBalance())<0.00001 && (verifySelf-amountWithdraw-balance)<0.00001 && balance>=0) {
                    ((Client *)srcClient)->addTransaction(Logger::sharedInstance().getTimeInLogFormat()+
                                                           ":Transfer funds: "+sharedLib::strFromInt(amountDeposit)+
                                                           " To :"+((Client*)destClient)->getUid()+
                                                           " Balance: "+sharedLib::strFromInt(balance));
                    ((Client *)srcClient)->writeToFile();
                    ((Client *)destClient)->writeToFile();
                    return true;
                }
                else {
                    errMsg = "Verification failed.";
                    return false;
                }
            }
            else {
                errMsg = "Destination account rejected.";
                balance = verifySelf;
                return false;
            }
        }
        else {
            errMsg = "insufficient funds.";
            return false;
        }
    }
    else {
        errMsg = "invalid target account.";
        return false;
    }
}