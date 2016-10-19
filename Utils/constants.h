//
// Created by Haoyu Gu on 2016-10-06.
//

#ifndef BANK_CONSTANTS_H
#define BANK_CONSTANTS_H

#define MIN_USER_ID_LENGTH 5
#define MIN_USER_PWD_LENGTH 5
#define MAX_USER_ID_LENGTH 1000
#define MAX_USER_PWD_LENGTH 1000

#define MAX_LOGIN_PASSWORD_RETRY 5

static int LOGGER_FILE_RECOMMEND_CLEAR_SIZE=1024*1024; //in bytes

static double CHEQUING_THRESHOLD_AMOUNT=1000;
static double CHEQUING_BELOW_THRESHOLD_FEE=2.0;

#endif //BANK_CONSTANTS_H
