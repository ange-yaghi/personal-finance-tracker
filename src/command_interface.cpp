#include <command_interface.h>
#include <transaction_form.h>

#include <iostream>
#include <string>

CommandInterface::CommandInterface()
{

}

CommandInterface::~CommandInterface()
{

}

void CommandInterface::DrawLine(CommandInterface::LINES line, int length, bool newLine)
{
	for (int i = 0; i < length; i++)
	{
		if (line == DOUBLE_LINE)
		{
			std::cout << "=";
		}
		else if (line == THIN_LINE)
		{
			std::cout << "-";
		}
		else if (line == STAR_LINE)
		{
			std::cout << "*";
		}
		else if (line == DOT_LINE)
		{
			std::cout << ".";
		}
		else if (line == SPACE_LINE)
		{
			std::cout << " ";
		}
	}
	if ((line != DOT_LINE &&
		line != SPACE_LINE) && newLine)
		std::cout << std::endl;
}

void CommandInterface::Run()
{
	while (true)
	{
		std::string command;
		std::cout << ">> ";
		std::getline(std::cin, command);

		if (command == "create txn")
		{
			CreateTransaction();
		}
	}

}

void CommandInterface::CreateTransaction()
{
	DrawLine(DOUBLE_LINE, LINE_WIDTH);

	TransactionForm form;
	form.SetDatabaseLayer(m_databaseLayer);
	form.Initialize();

	int intOutput;
	std::string stringOutput;

	SIMPLE_COMMAND command = ExecuteForm(&form, &intOutput, stringOutput);

	if (command == COMMAND_EMPTY)
	{

	}
}

CommandInterface::SIMPLE_COMMAND CommandInterface::ExecuteForm(Form *form, int *intOutput, std::string &stringOutput)
{
	int currentField = 0;
	int nFields = form->GetFieldCount();

	StringField confirmField;
	confirmField.SetFieldName(std::string("CONFIRM"));
	confirmField.SetInputType(FieldInput::INPUT_CONFIRM);

	bool confirmFieldFlag = false;

	while (true)
	{
		FieldInput *field;
		
		if (!confirmFieldFlag) field = form->GetField(currentField);
		else field = &confirmField;

		std::string stringOutput;
		SIMPLE_COMMAND command;
		int intOutput;
		command = ExecuteField(field, &intOutput, stringOutput);

		if (command == COMMAND_FORWARD)
		{
			currentField += intOutput;
			if (currentField >= nFields) currentField = nFields - 1;
		}

		else if (command == COMMAND_BACK)
		{
			currentField -= intOutput;
			if (currentField < 0) currentField = nFields - 1;
		}

		else if (command == COMMAND_EMPTY)
		{
			if (confirmFieldFlag)
			{
				return COMMAND_EMPTY;
			}

			if (currentField >= nFields - 1)
			{
				int nextField = form->GetNextEmptyField(currentField);

				if (nextField == -1)
				{
					confirmFieldFlag = true;
				}
				else currentField = nextField;
			}
			else
				currentField++;
		}

		else if (command == COMMAND_YES)
		{
			if (confirmFieldFlag)
			{
				return COMMAND_EMPTY;
			}
		}

		else if (command == COMMAND_NO)
		{
			if (confirmFieldFlag)
			{
				currentField = 0;
				confirmFieldFlag = false;
			}
		}

		else if (command == COMMAND_CANCEL)
		{
			return COMMAND_CANCEL;
		}
	}

	return COMMAND_EMPTY;
}

void CommandInterface::PrintField(std::string name)
{
	std::cout << name;
	DrawLine(DOT_LINE, 35 - name.length());
	std::cout << " ";
}

CommandInterface::SIMPLE_COMMAND CommandInterface::GetSimpleUserInput(int *parameter, std::string &stringParameter)
{
	std::string command;
	std::getline(std::cin, command);

	return ParseSimpleUserInput(command, parameter, stringParameter);
}

CommandInterface::SIMPLE_COMMAND CommandInterface::ParseSimpleUserInput(const std::string &input, int *parameter, std::string &stringParameter)
{
	if (input == ".")
	{
		return COMMAND_STOP;
	}
	else if (input == ",")
	{
		return COMMAND_NEXT;
	}
	else if (input == "")
	{
		return COMMAND_EMPTY;
	}
	else if (input == "!")
	{
		return COMMAND_CANCEL;
	}
	else if (input == "y")
	{
		return COMMAND_YES;
	}
	else if (input == "n")
	{
		return COMMAND_NO;
	}
	else
	{
		int length = input.length();
		int degree = 0;
		SIMPLE_COMMAND code = COMMAND_INVALID;
		for (int i = 0; i < length; i++)
		{
			if (input[i] == '<')
			{
				if (code != COMMAND_INVALID && code != COMMAND_BACK)
					return COMMAND_INVALID;
				code = COMMAND_BACK;
				degree++;
			}
			else if (input[i] == '>')
			{
				if (code != COMMAND_INVALID && code != COMMAND_FORWARD)
					return COMMAND_INVALID;
				code = COMMAND_FORWARD;
				degree++;
			}
		}
		*parameter = degree;
		return code;
	}
}

CommandInterface::SIMPLE_COMMAND CommandInterface::ExecuteField(FieldInput *field, int *parameter, std::string &stringParameter)
{
	PrintField(field->GetFieldName());

	INTERFACE_STATE currentState, nextState, prevState;
	
	if (field->HasValue()) currentState = STATE_ALREADY_HAS_VALUE;
	else currentState = STATE_INITIAL_INPUT;
	nextState = currentState;
	prevState = STATE_UNDEFINED;

	SIMPLE_COMMAND outputCommand = COMMAND_EMPTY;

	int suggestionIndex = 0;

	while (currentState != STATE_DONE)
	{
		if (currentState == STATE_INITIAL_INPUT)
		{
			std::string command;
			std::getline(std::cin, command);

			// First check to see if it's a command
			std::string stringOutput;
			int intOutput;
			CommandInterface::SIMPLE_COMMAND simpleCommand = ParseSimpleUserInput(command, &intOutput, stringOutput);
			bool processInput = true;

			if (simpleCommand != COMMAND_INVALID)
			{
				if (simpleCommand == COMMAND_BACK ||
					simpleCommand == COMMAND_NEXT ||
					simpleCommand == COMMAND_EMPTY ||
					simpleCommand == COMMAND_FORWARD)
				{
					*parameter = intOutput;
					stringParameter = stringOutput;
					return simpleCommand;
				}
				else if (simpleCommand == COMMAND_CANCEL)
				{
					processInput = false;
					nextState = STATE_CANCEL;
				}

				if (field->GetInputType() == FieldInput::INPUT_CONFIRM)
				{
					if (simpleCommand == COMMAND_YES ||
						simpleCommand == COMMAND_NO)
					{
						return simpleCommand;
					}
				}
			}

			if (processInput)
			{
				// If execution gets to this point the command is either 
				// not valid or not valid at this point
				bool validInput = field->SetUserSearch(command);

				if (validInput)
				{
					if (field->GetInputType() == FieldInput::INPUT_LOOKUP)
					{
						if (field->GetSuggestionCount() == 0)
							nextState = STATE_NO_SUGGESTIONS;
						else
						{
							nextState = STATE_SUGGESTION;
							suggestionIndex = 0;
						}
					}
					else
					{
						nextState = STATE_DONE;
					}
				}
				else nextState = STATE_INVALID_INPUT;
			}
		}
		else if (currentState == STATE_ALREADY_HAS_VALUE)
		{
			std::cout << "{" << field->GetCurrentValue() << "} ";

			int parameter;
			std::string stringOutput;
			SIMPLE_COMMAND cmd = GetSimpleUserInput(&parameter, stringOutput);

			if (cmd == COMMAND_EMPTY || cmd == COMMAND_STOP) nextState = STATE_SELECTED_VALUE;
			else if (cmd == COMMAND_NEXT)
			{
				nextState = STATE_INITIAL_INPUT;
				DrawLine(SPACE_LINE, 36);
			}
		}
		else if (currentState == STATE_INVALID_INPUT)
		{
			DrawLine(SPACE_LINE, 4);

			std::cout << "(Invalid)";

			DrawLine(SPACE_LINE, 23);
			nextState = STATE_INITIAL_INPUT;
		}
		else if (currentState == STATE_NO_SUGGESTIONS)
		{
			std::cout << "    " << "(No Suggestions)";
			DrawLine(SPACE_LINE, 16);
			nextState = STATE_INITIAL_INPUT;
		}
		else if (currentState == STATE_SUGGESTION)
		{

			int nSuggestions = field->GetSuggestionCount();

			if (suggestionIndex == nSuggestions - 1)
			{
				std::cout << "    " << "(Last Suggestion)";
				DrawLine(SPACE_LINE, 15);
			}
			else
				DrawLine(SPACE_LINE, 36);

			std::cout << field->GetSuggestion(suggestionIndex) << " ";

			int parameter;
			std::string stringOutput;
			SIMPLE_COMMAND cmd = GetSimpleUserInput(&parameter, stringOutput);
			if (cmd == COMMAND_EMPTY)
			{
				nextState = STATE_SELECTED_VALUE;
				field->UseSuggestion(suggestionIndex);
			}
			else if (cmd == COMMAND_STOP)
			{
				nextState = STATE_INITIAL_INPUT;
				DrawLine(SPACE_LINE, 36);
			}
			else if (cmd == COMMAND_NEXT)
			{
				suggestionIndex += 1;

				if (suggestionIndex >= nSuggestions)
				{
					suggestionIndex = nSuggestions - 1;
				}
				nextState = STATE_SUGGESTION;
			}
			else if (cmd == COMMAND_FORWARD)
			{
				suggestionIndex += parameter;

				if (suggestionIndex >= nSuggestions)
				{
					suggestionIndex = nSuggestions - 1;
				}
				nextState = STATE_SUGGESTION;
			}
			else if (cmd == COMMAND_BACK)
			{
				suggestionIndex -= parameter;

				if (suggestionIndex < 0)
				{
					suggestionIndex = 0;
				}
				nextState = STATE_SUGGESTION;
			}
		}
		else if (currentState == STATE_SELECTED_VALUE)
		{
			std::string value = field->GetCurrentValue();
			int length = value.length();

			if (prevState == STATE_ALREADY_HAS_VALUE)
			{
				length += 2;
			}

			DrawLine(SPACE_LINE, 36);
			DrawLine(STAR_LINE, length);

			nextState = STATE_DONE;
		}
		else if (currentState == STATE_CANCEL)
		{
			std::cout << "    ";
			std::cout << "(Cancel (y/n)?)";

			DrawLine(SPACE_LINE, 17);

			int parameter;
			std::string stringOutput;
			SIMPLE_COMMAND cmd = GetSimpleUserInput(&parameter, stringOutput);

			if (cmd == COMMAND_YES)
			{
				outputCommand = COMMAND_CANCEL;
				nextState = STATE_DONE;
			}
			else
			{
				DrawLine(SPACE_LINE, 36);
				nextState = prevState;
			}
		}

		prevState = currentState;
		currentState = nextState;
		nextState = currentState;
	}

	return outputCommand;
}

void CommandInterface::Execute()
{

}