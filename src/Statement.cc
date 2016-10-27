/**
 * Copyright (c) 2012-2016 Derry (deyolu@yeah.net)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "sqlitecc/Statement.h"
#include "sqlitecc/ResultSet.h"

#include <sqlite3.h>

using namespace sqlitecc;

Statement::~Statement() {
    sqlite3_finalize(stmt_);
}

int Statement::bindInt(int col, int data) {
    return sqlite3_bind_int(stmt_, col, data);
}

int Statement::bindText(int col, const char* text, int size) {
    return sqlite3_bind_text(stmt_, col, text, size, NULL);
}

int Statement::bindDouble(int col, double data) {
    return sqlite3_bind_double(stmt_, col, data);
}

ResultSet* Statement::executeQuery() {
    return new ResultSet(stmt_);
}

int Statement::execute() {
    int ret = sqlite3_step(stmt_);
    if( ret == SQLITE_DONE ) {
        return sqlite3_changes(db_);
    } else {
        lastErr_ = ret;
    }
    return -1;
}

int Statement::errCode() const {
    return sqlite3_errcode(db_);
}
const char* Statement::errMsg() const  {
    return sqlite3_errmsg(db_);
}


