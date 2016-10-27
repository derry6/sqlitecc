/**
 * Copyright (c) 2012-2016 Derry (deyolu@yeah.net)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "sqlitecc/Database.h"

#include <sqlite3.h>
#include <string.h>

#include "sqlitecc/ResultSet.h"
#include "sqlitecc/Statement.h"

using namespace sqlitecc;

const int sqlitecc::O_RDONLY = SQLITE_OPEN_READONLY;
const int sqlitecc::O_RDWR   = SQLITE_OPEN_READWRITE;
const int sqlitecc::O_CREATE = SQLITE_OPEN_CREATE;
const int sqlitecc::O_URI    = SQLITE_OPEN_URI;

const int sqlitecc::OK  = SQLITE_OK;

void Database::initialize(const char* dbpath, int flags) {
    opened_ = false;
    int ret = sqlite3_open_v2(dbpath, &db_, flags, NULL);
    if( ret != OK ) {
        //
        sqlite3_close_v2(db_);
    }
    dbpath_ = std::string(dbpath);
    flags_ = flags;
    opened_ = true;
}

Database::~Database() {
     sqlite3_close_v2(db_);
}

int Database::execute(const char* sql) {
    int ret = sqlite3_exec(db_, sql, NULL, NULL, NULL);
    if( ret != OK ) {
        return -1;
    }
    return 0;
}

int Database::updatedRows() const {
    return sqlite3_total_changes(db_);
}

int Database::lastInsertRowId() const {
    return sqlite3_last_insert_rowid(db_);
}

bool Database::isTableExists(const char* table) {
    return true;
}

Statement* Database::prepareStatement(const char* sql) {
    sqlite3_stmt* stmt;
    int ret = sqlite3_prepare_v2(db_, sql, strlen(sql), &stmt, NULL);
    if( ret != OK ) {
        return NULL;
    }
    if( stmt == NULL )
        return NULL;
    return new Statement(db_, stmt);
}

int Database::errCode() const  {
    return sqlite3_errcode(db_);
}
const char* Database::errMsg() const  {
    return sqlite3_errmsg(db_);
}
