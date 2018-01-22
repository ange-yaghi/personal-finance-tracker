#include <database_layer.h>
#include <command_interface.h>

#include <iostream>

int main()
{
	DatabaseLayer dbLayer;
	dbLayer.OpenDatabase();
	std::cout << "Bank sum: " << dbLayer.GetBankSum("2018-01-11") << std::endl;

	CommandInterface cmd;
	cmd.SetDatabase(&dbLayer);
	cmd.Run();
	
	return 0;
}
