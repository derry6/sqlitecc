/**
 * Copyright (c) 2012-2016 Derry (deyolu@yeah.net)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE
 * or copy at http://opensource.org/licenses/MIT)
 */

#ifndef _SQLITECC_STATEMENT_H_
#define _SQLITECC_STATEMENT_H_

#include <string>

struct sqlite3;
struct sqlite3_stmt;

namespace sqlitecc {

class ResultSet;

class Statement {
    public:
        explicit Statement(sqlite3* db, sqlite3_stmt* stmt)
            : db_(db),
              stmt_(stmt)
        {
            //
        }
        ~Statement();

        int bindInt(int col, int data);

        int bindText(int col, const char* text, int size);
        int bindText(int col, const std::string& text ) {
            return bindText(col, text.c_str(), static_cast<int>(text.size()) );
        }

        int bindDouble(int col, double data);

        ResultSet* executeQuery();

        int execute();

        int errCode() const;
        const char* errMsg() const ;

        sqlite3* db() const { return db_; }

    private:
        sqlite3* db_;
        sqlite3_stmt* stmt_;
        int lastErr_;
};

}



#endif // _SQLITECC_STATEMENT_H_
