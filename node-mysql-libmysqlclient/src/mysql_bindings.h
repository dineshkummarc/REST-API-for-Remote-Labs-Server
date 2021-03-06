/*!
 * Copyright by Oleg Efimov and node-mysql-libmysqlclient contributors
 * See contributors list in README
 *
 * See license text in LICENSE file
 */

#ifndef NODE_MYSQL_H  // NOLINT
#define NODE_MYSQL_H

/**
 * Usefull macroses for unility operations
 * such as agrument checking and C=+ <-> V8 type convertions
 */

#define ADD_PROTOTYPE_METHOD(class, name, method) \
class ## _ ## name ## _symbol = NODE_PSYMBOL(#name); \
NODE_SET_PROTOTYPE_METHOD(constructor_template, #name, method);

// Only for fixing some cpplint.py errors:
// Lines should be <= 80 characters long
// [whitespace/line_length] [2]
// Lines should very rarely be longer than 100 characters
// [whitespace/line_length] [4]
#define V8EXC(str) Exception::Error(String::New(str))
#define THREXC(str) ThrowException(Exception::Error(String::New(str)))
#define THRTYPEEXC(str) ThrowException(Exception::TypeError(String::New(str)))
#define OBJUNWRAP ObjectWrap::Unwrap
#define V8STR(str) String::New(str)

#define REQ_INT_ARG(I, VAR) \
if (args.Length() <= (I) || !args[I]->IsInt32()) \
return ThrowException(Exception::TypeError( \
String::New("Argument " #I " must be an integer"))); \
int32_t VAR = args[I]->Int32Value();

#define REQ_UINT_ARG(I, VAR) \
if (args.Length() <= (I) || !args[I]->IsUint32()) \
return ThrowException(Exception::TypeError( \
String::New("Argument " #I " must be an integer"))); \
uint32_t VAR = args[I]->Uint32Value();

#define REQ_STR_ARG(I, VAR) \
if (args.Length() <= (I) || !args[I]->IsString()) \
return ThrowException(Exception::TypeError( \
String::New("Argument " #I " must be a string"))); \
String::Utf8Value VAR(args[I]->ToString());

#define REQ_BOOL_ARG(I, VAR) \
if (args.Length() <= (I) || !args[I]->IsBoolean()) \
return ThrowException(Exception::TypeError( \
String::New("Argument " #I " must be a boolean"))); \
bool VAR = args[I]->BooleanValue();

#define REQ_FUN_ARG(I, VAR) \
if (args.Length() <= (I) || !args[I]->IsFunction()) \
return ThrowException(Exception::TypeError( \
String::New("Argument " #I " must be a function"))); \
Local<Function> VAR = Local<Function>::Cast(args[I]);

#define REQ_EXT_ARG(I, VAR) \
if (args.Length() <= (I) || !args[I]->IsExternal()) \
return ThrowException(Exception::TypeError( \
String::New("Argument " #I " invalid"))); \
Local<External> VAR = Local<External>::Cast(args[I]);

#define MYSQLSYNC_DISABLE_MQ \
if (conn->multi_query) { \
    mysql_set_server_option(conn->_conn, MYSQL_OPTION_MULTI_STATEMENTS_OFF); \
    conn->multi_query = false; \
}

#define MYSQLSYNC_ENABLE_MQ \
if (!conn->multi_query) { \
    mysql_set_server_option(conn->_conn, MYSQL_OPTION_MULTI_STATEMENTS_ON); \
    conn->multi_query = true; \
}

#define MYSQL_NON_THREADSAFE_ERRORSTRING \
    "Asynchronous functions works only with threadsafe libmysqlclient_r"

#define MYSQLCONN_MUSTBE_CONNECTED \
    if (!conn->_conn) { \
        return THREXC("Not connected"); \
    }

#endif  // NODE_MYSQL_H  // NOLINT

