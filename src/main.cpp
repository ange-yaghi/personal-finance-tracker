#include "../include/pft.h"

#include <iostream>

#ifndef RELEASE_BUILD
#define HOME_PATH "../../"
#else 
#define HOME_PATH "./"
#endif /* RELEASE_BUILD */

int main() {
    pft::SqliteDatabase dbLayer;
	dbLayer.SetHomePath(HOME_PATH);
    dbLayer.OpenDatabase("FinanceDatabase.db");

    pft::ConsoleIo console;

    pft::CommandInterface cmd;
    cmd.SetIoLayer(&console);
    cmd.SetDatabase(&dbLayer);
    cmd.Run();

    dbLayer.Close();
    
    return 0;
}
