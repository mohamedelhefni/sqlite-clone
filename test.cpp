#include <iostream>
#include <string>
using namespace std;

enum MetaCommandResult
{
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
};

enum StatementType
{
    STATEMENT_INSERT,
    STATEMENT_SELECT
};

enum PrepareResult
{
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED_STATEMENT
};

class Statement
{
public:
    StatementType type;
    PrepareResult prepare(string &input)
    {
        if (input.substr(0, 6) == "insert")
        {
            this->type = STATEMENT_INSERT;
            return PREPARE_SUCCESS;
        }
        if (input.substr(0, 6) == "select")
        {
            this->type = STATEMENT_SELECT;
            return PREPARE_SUCCESS;
        }
        return PREPARE_UNRECOGNIZED_STATEMENT;
    };
    void execute()
    {
        switch (this->type)
        {
        case STATEMENT_INSERT:
            cout << "This is where we would do an insert." << endl;
            break;
        case STATEMENT_SELECT:
            cout << "This is where we would do a select." << endl;
            break;
        }
    }
};

MetaCommandResult do_meta_command(string input)
{
    if (input == ".exit")
    {
        exit(EXIT_SUCCESS);
    }
    else
    {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}

int main()
{
    bool exit = 0;
    while (exit == 0)
    {
        string input;
        cout << "db > ";
        getline(cin, input);

        if (input[0] == '.')
        {
            switch (do_meta_command(input))
            {
            case META_COMMAND_SUCCESS:
                continue;
            case META_COMMAND_UNRECOGNIZED_COMMAND:
                cout << "Uncategorized Command " << input << endl;
                continue;
            }
        }
        Statement statement;
        switch (statement.prepare(input))
        {
        case (PREPARE_SUCCESS):
            break;
        case (PREPARE_UNRECOGNIZED_STATEMENT):
            cout << "Unrecognized keyword at start of " << input << endl;
            continue;
        }
        statement.execute();
        cout << "Executed" << endl;
    }
}