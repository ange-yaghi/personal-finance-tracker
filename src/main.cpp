#include <database_layer.h>
#include <command_interface.h>

#include <iostream>

#ifndef RELEASE_BUILD
#define HOME_PATH "../../"
#else 
#define HOME_PATH "./"
#endif /* RELEASE_BUILD */

int main() {
    pft::DatabaseLayer dbLayer;
	dbLayer.SetHomePath(HOME_PATH);
    dbLayer.OpenDatabase("FinanceDatabase.db");

    pft::CommandInterface cmd;
    cmd.SetDatabase(&dbLayer);
    cmd.Run();
    
    return 0;
}
