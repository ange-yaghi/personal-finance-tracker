#include <command_interface.h>

// Forms
#include <transaction_form.h>
#include <check_balance_form.h>
#include <transfer_form.h>
#include <paycheck_form.h>

#include <transaction.h>
#include <account.h>
#include <counterparty.h>
#include <transaction_class.h>
#include <transaction_type.h>

#include <database_layer.h>

// Libraries
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

CommandInterface::CommandInterface()
{
	m_checkBalanceFormInitialized = false;
	m_calculateTotalFormInitialized = false;
	m_breakdownFormInitialized = false;
	m_paycheckFormInitialized = false;
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

		std::stringstream ss(command);
		std::string mainToken;
		std::string secondToken;

		ss >> mainToken;
		ss >> secondToken;

		if (mainToken == "create" || mainToken == "cr")
		{
			if (secondToken == "txn")
			{
				CreateTransaction();
			}
			else if (secondToken == "transfer")
			{
				CreateTransfer();
			}
			else if (secondToken == "paycheck")
			{
				CreatePaycheck();
			}
		}

		else if (mainToken == "copy")
		{
			if (secondToken == "type")
			{

			}
		}

		else if (mainToken == "edit" || mainToken == "ed")
		{
			if (secondToken == "transaction" || secondToken == "txn")
			{
				std::string txn;
				std::getline(std::cin, txn);

				std::stringstream ss;
				ss << txn;

				int txnid;
				ss >> txnid;

				EditTransaction(txnid);
			}
		}

		else if (mainToken == "check" || mainToken == "chk")
		{
			if (secondToken == "balance" || secondToken == "bal")
			{
				std::string argument;

				if (ss.eof())
					CheckBalance(false);
				else
				{
					ss >> argument;

					if (argument == "-")
						CheckBalance(true);
					else
					{
						// TODO: invalid argument warning
						CheckBalance(false);
					}
				}
			}
		}

		else if (mainToken == "calculate" || mainToken == "calc")
		{
			if (secondToken == "total")
			{
				std::string argument;

				if (ss.eof())
					CalculateTotal(false);
				else
				{
					ss >> argument;

					if (argument == "-")
						CalculateTotal(true);
					else
					{
						// TODO: invalid argument warning
						CalculateTotal(false);
					}
				}
			}

			else if (secondToken == "breakdown")
			{
				std::string argument;

				if (ss.eof())
					CalculateBreakdown(false);
				else
				{
					ss >> argument;

					if (argument == "-")
						CalculateBreakdown(true);
					else
					{
						// TODO: invalid argument warning
						CalculateBreakdown(false);
					}
				}
			}
		}

		else if (mainToken == "output")
		{
			if (secondToken == "report")
			{
				std::string argument;

				if (ss.eof())
					GenerateFullReport(false);
				else
				{
					ss >> argument;

					if (argument == "-")
						GenerateFullReport(true);
					else
					{
						// TODO: invalid argument warning
						GenerateFullReport(false);
					}
				}
			}
		}
	}

}

void CommandInterface::CheckBalance(bool skipForm)
{
	if (!m_checkBalanceFormInitialized)
	{
		m_checkBalanceForm.SetDatabaseLayer(m_databaseLayer);
		m_checkBalanceForm.Initialize();
		m_checkBalanceFormInitialized = true;

		// TODO: display a warning if skipForm is set to true
		skipForm = false;
	}

	SIMPLE_COMMAND command = COMMAND_EMPTY;

	if (!skipForm)
	{
		int intOutput;
		std::string stringOutput;
		SIMPLE_COMMAND command = ExecuteForm(&m_checkBalanceForm, &intOutput, stringOutput);
	}

	if (command == COMMAND_EMPTY)
	{
		std::string date = m_checkBalanceForm.GetDate();
		int account = m_checkBalanceForm.GetAccount();
		int type = m_checkBalanceForm.GetType();
		int balance = m_databaseLayer->GetAccountBalance(account, date.c_str());
		bool neg = balance < 0;
		int dollars = balance / 100;
		int cents = ((neg ? -balance : balance) % 100);

		std::cout << "$" << (balance) / 100 << ".";
		if (cents < 10)
			std::cout << "0";
		
		std::cout << cents;
		if (cents % 10 == 0)
			std::cout << "0";
		std::cout << std::endl;
	}
}

void CommandInterface::CalculateTotal(bool skipForm)
{
	if (!m_calculateTotalFormInitialized)
	{
		m_calculateTotalForm.SetDatabaseLayer(m_databaseLayer);
		m_calculateTotalForm.Initialize();
		m_calculateTotalFormInitialized = true;

		// TODO: display a warning if skipForm is set to true
		skipForm = false;
	}

	SIMPLE_COMMAND command = COMMAND_EMPTY;

	if (!skipForm)
	{
		int intOutput;
		std::string stringOutput;
		SIMPLE_COMMAND command = ExecuteForm(&m_calculateTotalForm, &intOutput, stringOutput);
	}

	if (command == COMMAND_EMPTY)
	{
		std::string date = m_calculateTotalForm.GetDate();
		int tClass = m_calculateTotalForm.GetClass();
		int type = m_calculateTotalForm.GetType();
		int balance = m_databaseLayer->GetTotalAmountMonth(tClass, type, date.c_str());
		bool neg = balance < 0;
		int dollars = balance / 100;
		int cents = ((neg ? -balance : balance) % 100);

		std::cout << "$" << (balance) / 100 << ".";
		if (cents < 10)
			std::cout << "0";

		std::cout << cents;
		if (cents % 10 == 0)
			std::cout << "0";
		std::cout << std::endl;
	}
}

void CommandInterface::CalculateBreakdown(bool skipForm)
{
	if (!m_breakdownFormInitialized)
	{
		m_breakdownCalculationForm.SetDatabaseLayer(m_databaseLayer);
		m_breakdownCalculationForm.Initialize();
		m_breakdownFormInitialized = true;

		// TODO: display a warning if skipForm is set to true
		skipForm = false;
	}

	SIMPLE_COMMAND command = COMMAND_EMPTY;

	if (!skipForm)
	{
		int intOutput;
		std::string stringOutput;
		SIMPLE_COMMAND command = ExecuteForm(&m_breakdownCalculationForm, &intOutput, stringOutput);
	}

	if (command == COMMAND_EMPTY)
	{
		std::string date = m_breakdownCalculationForm.GetDate();
		std::string fname = m_breakdownCalculationForm.GetOutputFile();
		int tClass = m_breakdownCalculationForm.GetClass();
		int budgetType = m_breakdownCalculationForm.GetBudgetType();
		int mainType = m_breakdownCalculationForm.GetMainType();

		TotalBreakdown totalBreakdown;
		m_databaseLayer->CalculateTotalBreakdown(&totalBreakdown, tClass, mainType, budgetType, date.c_str());

		std::stringstream ss;
		ss << "CLASS" << "\t";
		ss << "REAL" << "\t" << "BUDGET" << std::endl;
		
		PrintBreakdown(&totalBreakdown, ss, 0);

		// Write to file
		std::ofstream f(fname);
		f << ss.str();
		f.close();
	}
}

void CommandInterface::GenerateFullReport(bool skipForm)
{
	if (!m_fullReportForm.IsInitialized())
	{
		m_fullReportForm.SetDatabaseLayer(m_databaseLayer);
		m_fullReportForm.Initialize();

		// TODO: display a warning if skipForm is set to true
		skipForm = false;
	}

	SIMPLE_COMMAND command = COMMAND_EMPTY;

	if (!skipForm)
	{
		int intOutput;
		std::string stringOutput;
		SIMPLE_COMMAND command = ExecuteForm(&m_fullReportForm, &intOutput, stringOutput);
	}

	if (command == COMMAND_EMPTY)
	{
		std::string startMonthString = m_fullReportForm.GetStartMonth();
		std::string endMonthString = m_fullReportForm.GetEndMonth();
		std::string fname = m_fullReportForm.GetOutputFile();
		int tClass = m_fullReportForm.GetClass();
		int tType = m_fullReportForm.GetType();
		int budgetType = m_fullReportForm.GetBudgetType();

		int startYear;
		int endYear;
		int startMonth;
		int endMonth;
		int currentMonth;
		int currentYear;

		DatabaseLayer::ParseMonth(startMonthString, &startYear, &startMonth);
		DatabaseLayer::ParseMonth(endMonthString, &endYear, &endMonth);

		currentMonth = startMonth;
		currentYear = startYear;

		std::vector<std::string> months;
		while (true)
		{
			std::string month = DatabaseLayer::IntToString(currentYear) + "-" + DatabaseLayer::IntToString(currentMonth);
			months.push_back(month);

			if (currentMonth == endMonth && currentYear == endYear) break;

			currentMonth++;
			if (currentMonth > 12)
			{
				currentYear++;
				currentMonth = 1;
			}
		}

		TotalBreakdown totalBreakdown;
		m_databaseLayer->CalculateMonthlyBreakdown(&totalBreakdown, months, tClass, tType, budgetType);

		std::stringstream ss;
		ss << "CLASS" << "\t";

		for (int i = 0; i < months.size(); i++)
		{
			ss << months[i] << "\t";
		}

		ss << "BUDGET" << "\t" << "TOTAL";

		ss << std::endl;

		PrintFullReport(&totalBreakdown, ss, 0);

		// Write to file
		std::ofstream f(fname);
		f << ss.str();
		f.close();
	}

}

void CommandInterface::PrintTransaction(Transaction *transaction)
{	
	TransactionClass transactionClass;
	Account account;
	Counterparty counterparty;
	TransactionType type;

	transactionClass.Initialize();
	account.Initialize();
	counterparty.Initialize();
	type.Initialize();

	// Populate related objects
	m_databaseLayer->GetAccount(transaction->GetIntAttribute(std::string("ACCOUNT_ID")), &account);
	m_databaseLayer->GetCounterparty(transaction->GetIntAttribute(std::string("COUNTERPARTY_ID")), &counterparty);
	m_databaseLayer->GetClass(transaction->GetIntAttribute(std::string("CLASS_ID")), &transactionClass);
	m_databaseLayer->GetType(transaction->GetIntAttribute(std::string("TYPE_ID")), &type);

	PrintField("ID");
	std::cout << transaction->GetIntAttribute(std::string("ID")) << std::endl;

	PrintField("NAME");
	std::cout << transaction->GetStringAttribute(std::string("NAME")) << std::endl;

	PrintField("TYPE");
	std::cout << type.GetStringAttribute(std::string("NAME")) << std::endl;

	PrintField("CLASS");
	std::cout << transactionClass.GetStringAttribute(std::string("NAME")) << std::endl;

	PrintField("PARENT_ENTITY_ID");
	std::cout << transaction->GetIntAttribute(std::string("PARENT_ENTITY_ID")) << std::endl;

	PrintField("ACCOUNT");
	std::cout << account.GetStringAttribute(std::string("NAME")) << std::endl;

	PrintField("COUNTERPARTY");
	std::cout << counterparty.GetStringAttribute(std::string("NAME")) << std::endl;

	PrintField("AMOUNT");
	std::cout << "$" << transaction->GetCurrencyAttribute(std::string("AMOUNT")) << std::endl;

	PrintField("DATE");
	std::cout << transaction->GetStringAttribute(std::string("DATE")) << std::endl;

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
		Transaction newTransaction;
		newTransaction.Initialize();
		form.PopulateTransaction(&newTransaction);

		m_databaseLayer->InsertTransaction(&newTransaction);

		DrawLine(STAR_LINE, LINE_WIDTH);
		std::cout << "NEW TRANSACTION" << std::endl;
		DrawLine(THIN_LINE, LINE_WIDTH);
		PrintTransaction(&newTransaction);
		DrawLine(DOUBLE_LINE, LINE_WIDTH);
	}
}

void CommandInterface::EditTransaction(int id)
{
	DrawLine(DOUBLE_LINE, LINE_WIDTH);

	Transaction t;
	t.Initialize();
	m_databaseLayer->GetTransaction(id, &t);

	TransactionForm form;
	form.SetDatabaseLayer(m_databaseLayer);
	form.Initialize();
	form.Populate(&t);

	int intOutput;
	std::string stringOutput;

	SIMPLE_COMMAND command = ExecuteForm(&form, &intOutput, stringOutput);

	if (command == COMMAND_EMPTY)
	{
		form.PopulateTransaction(&t);
		m_databaseLayer->UpdateTransaction(&t);
	}
}

void CommandInterface::CreateTransfer()
{
	DrawLine(DOUBLE_LINE, LINE_WIDTH);

	TransferForm form;
	form.SetDatabaseLayer(m_databaseLayer);
	form.Initialize();

	int intOutput;
	std::string stringOutput;

	SIMPLE_COMMAND command = ExecuteForm(&form, &intOutput, stringOutput);

	if (command == COMMAND_EMPTY)
	{
		Transaction container;
		Transaction debit;
		Transaction credit;

		container.Initialize();
		debit.Initialize();
		credit.Initialize();

		form.PopulateTransactions(&container, &credit, &debit);

		m_databaseLayer->InsertTransaction(&container);

		// Connect the children to the parent transaction
		debit.SetIntAttribute(std::string("PARENT_ENTITY_ID"), container.GetIntAttribute(std::string("ID")));
		credit.SetIntAttribute(std::string("PARENT_ENTITY_ID"), container.GetIntAttribute(std::string("ID")));

		m_databaseLayer->InsertTransaction(&debit);
		m_databaseLayer->InsertTransaction(&credit);
	}

}

void CommandInterface::CreatePaycheck()
{
	DrawLine(DOUBLE_LINE, LINE_WIDTH);

	if (!m_paycheckFormInitialized)
	{
		m_paycheckForm.SetDatabaseLayer(m_databaseLayer);
		m_paycheckForm.Initialize();

		m_paycheckFormInitialized = true;
	}

	int intOutput;
	std::string stringOutput;

	SIMPLE_COMMAND command = ExecuteForm(&m_paycheckForm, &intOutput, stringOutput);

	if (command == COMMAND_EMPTY)
	{
		Transaction container;
		Transaction basePay;
		Transaction cit;
		Transaction cpp;
		Transaction ei;
		Transaction postTax;
		Transaction directDeposit;
		Transaction directDepositRec;
		Transaction preTaxAllocations;

		container.Initialize();
		basePay.Initialize();
		cit.Initialize();
		cpp.Initialize();
		ei.Initialize();
		directDeposit.Initialize();
		postTax.Initialize();
		directDepositRec.Initialize();
		preTaxAllocations.Initialize();

		m_paycheckForm.PopulateTransactions(&container, &basePay, &cit, &cpp, &ei, &directDeposit, &directDepositRec, &postTax, &preTaxAllocations);

		m_databaseLayer->InsertTransaction(&container);

		// Connect the children to the parent transaction
		basePay.SetIntAttribute(std::string("PARENT_ENTITY_ID"), container.GetIntAttribute(std::string("ID")));
		cit.SetIntAttribute(std::string("PARENT_ENTITY_ID"), container.GetIntAttribute(std::string("ID")));
		cpp.SetIntAttribute(std::string("PARENT_ENTITY_ID"), container.GetIntAttribute(std::string("ID")));
		cit.SetIntAttribute(std::string("PARENT_ENTITY_ID"), container.GetIntAttribute(std::string("ID")));
		ei.SetIntAttribute(std::string("PARENT_ENTITY_ID"), container.GetIntAttribute(std::string("ID")));
		directDeposit.SetIntAttribute(std::string("PARENT_ENTITY_ID"), container.GetIntAttribute(std::string("ID")));
		directDepositRec.SetIntAttribute(std::string("PARENT_ENTITY_ID"), container.GetIntAttribute(std::string("ID")));
		postTax.SetIntAttribute(std::string("PARENT_ENTITY_ID"), container.GetIntAttribute(std::string("ID")));
		preTaxAllocations.SetIntAttribute(std::string("PARENT_ENTITY_ID"), container.GetIntAttribute(std::string("ID")));

		m_databaseLayer->InsertTransaction(&basePay);
		m_databaseLayer->InsertTransaction(&postTax);
		m_databaseLayer->InsertTransaction(&cit);
		m_databaseLayer->InsertTransaction(&cpp);
		m_databaseLayer->InsertTransaction(&ei);
		m_databaseLayer->InsertTransaction(&preTaxAllocations);
		m_databaseLayer->InsertTransaction(&directDeposit);
		m_databaseLayer->InsertTransaction(&directDepositRec);
	}
}

void CommandInterface::CopyAllOfType()
{

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
			if (currentField >= nFields)
				currentField = nFields - 1;			
		}

		else if (command == COMMAND_BACK)
		{
			if (confirmFieldFlag)
			{
				confirmFieldFlag = false;
				currentField -= (intOutput - 1);
			}
			else
			{
				currentField -= intOutput;
				if (currentField < 0)
					currentField = nFields - 1;
			}
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

void CommandInterface::PrintField(std::string name, LINES line)
{
	std::cout << name;
	DrawLine(line, 35 - name.length());
	std::cout << " ";
}

void CommandInterface::PrintBreakdown(TotalBreakdown *breakdown, std::stringstream &ss, int level)
{
	for (int i = 0; i < level; i++)
	{
		ss << " ";
	}

	TransactionClass tClass;
	tClass.Initialize();

	m_databaseLayer->GetClass(breakdown->GetClass(), &tClass);

	ss << tClass.GetStringAttribute(std::string("NAME"));
	ss << "\t";

	int nTypes = breakdown->GetTypeCount();

	for (int i = 0; i < nTypes; i++)
	{
		int amount = breakdown->GetAmount(i);
		ss << amount / 100 << "." << ((amount < 0) ? -amount : amount) % 100 << "\t";
	}

	ss << std::endl;

	int nChildren = breakdown->GetChildCount();
	for (int i = 0; i < nChildren; i++)
	{
		PrintBreakdown(breakdown->GetChild(i), ss, level + 1);
	}
}

void CommandInterface::PrintFullReport(TotalBreakdown *breakdown, std::stringstream &ss, int level)
{

	for (int i = 0; i < level; i++)
	{
		ss << "    ";
	}

	TransactionClass tClass;
	tClass.Initialize();

	m_databaseLayer->GetClass(breakdown->GetClass(), &tClass);

	ss << tClass.GetStringAttribute(std::string("NAME"));
	ss << "\t";

	int nTypes = breakdown->GetTypeCount();
	int total = 0;
	int totalBudget = 0;

	for (int i = 0; i < nTypes; i++)
	{
		int amount = breakdown->GetAmount(i);
		int budget = breakdown->GetBudget(i);
		ss << amount / 100 << "." << ((amount < 0) ? -amount : amount) % 100;

		if (i != (nTypes - 1))
		{
			ss << "\t";
		}

		total += amount;
		totalBudget += budget;
	}

	ss << "\t" << totalBudget / 100 << "." << ((totalBudget < 0) ? -totalBudget : totalBudget) % 100;
	ss << "\t" << total / 100 << "." << ((total < 0) ? -total : total) % 100;

	ss << std::endl;

	int nChildren = breakdown->GetChildCount();
	for (int i = 0; i < nChildren; i++)
	{
		PrintFullReport(breakdown->GetChild(i), ss, level + 1);
	}
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
			else
			{
				nextState = STATE_ALREADY_HAS_VALUE;
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