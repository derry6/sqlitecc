/**
 * Copyright (c) 2012-2016 Derry (deyolu@yeah.net)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE
 * or copy at http://opensource.org/licenses/MIT)
 */

#include <sqlitecc/Database.h>
#include <sqlitecc/ResultSet.h>
#include <sqlitecc/Statement.h>

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

using namespace sqlitecc;

int main(int argc, char** argv ) {

    Database db("test.db", sqlitecc::O_RDWR|sqlitecc::O_CREATE);
    if( ! db.ok() ) {
        printf("opened failed\n");
        return 1;
    }

    std::string sql = "CREATE TABLE `test01` ("
                      "`id` INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "`name` TEXT NOT NULL,"
                      "`phone` TEXT UNIQUE,"
                      "`email` TEXT);";

    int ret = db.execute(sql);
    if( ret != 0 ) {
        printf("create table failed(%d): %s\n", db.errCode(), db.errMsg());
    }

    sql = "INSERT INTO `test01`(`name`,`phone`,`email`) VALUES(?,?,?);";

    Statement* stmt = db.prepareStatement(sql.c_str());

    srand(time(0));
    char str[32] = {0};
    snprintf(str, sizeof str, "%d", rand());

    stmt->bindText(1, str);
    stmt->bindText(2, str);
    stmt->bindText(3, str);

    ret = stmt->execute();
    printf("insert ret = %d\n", ret);

    ret = stmt->execute();
    if( ret < 0 ) {
        printf("insert failed(%d): %s\n", stmt->errCode(), stmt->errMsg());
    }

    delete stmt;

    sql = "SELECT * FROM `test01`;";
    stmt = db.prepareStatement(sql.c_str());

    ResultSet* result = stmt->executeQuery();
    while ( result->next() ) {
        int id = result->getInt("id");
        std::string name  = result->getString("name");
        std::string phone = result->getString("phone");
        std::string email = result->getString("email");
        printf("id = %d, name=%s, phone=%s email=%s\n", id, name.c_str(), phone.c_str(), email.c_str());
    }
    delete result;
    delete stmt;
    return 0;
}
