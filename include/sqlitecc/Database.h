/**
 * Copyright (c) 2012-2016 Derry (deyolu@yeah.net)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE
 * or copy at http://opensource.org/licenses/MIT)
 */

#ifndef _SQLITECC_DATABASE_H_
#define _SQLITECC_DATABASE_H_

#include <string>

struct sqlite3;
struct sqlite3_context;

namespace sqlitecc {

// The flags for sqlite3_open_v2()
extern const int O_RDONLY;
extern const int O_RDWR;
extern const int O_CREATE;
extern const int O_URI;

extern const int OK;

class Statement;

class Database {
    public:
        Database(const char* dbpath, int flags) {
            initialize(dbpath, flags);
        }
        Database(const std::string& dbpath, int flags) {
             initialize(dbpath.c_str(), flags);
        }

        ~Database();

        bool ok() const {
            return opened_;
        }

        const char* dbPath() const { return dbpath_.c_str(); }

        int execute(const char* sql);
        int execute(const std::string& sql) { return execute(sql.c_str());}

        int updatedRows() const;

        int lastInsertRowId() const ;

        bool isTableExists(const char* table);

        Statement* prepareStatement(const char* sql);

        int errCode() const ;
        const char* errMsg() const ;

    private:
        void initialize(const char* dbpath, int flags);

    private:
        std::string dbpath_;
        int         flags_;
        sqlite3*    db_;
        bool opened_;
};


} // namespace sqlitecc


#endif // _SQLITECC_DATABASE_H_


