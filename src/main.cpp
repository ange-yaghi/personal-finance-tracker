#include <database_layer.h>
#include <command_interface.h>

#include <iostream>

int main()
{
	DatabaseLayer dbLayer;
	dbLayer.OpenDatabase();

	CommandInterface cmd;
	cmd.SetDatabase(&dbLayer);
	cmd.Run();
	
	return 0;
}
