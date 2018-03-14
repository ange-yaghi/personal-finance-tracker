#ifndef COMMAND_INTERFACE_H
#define COMMAND_INTERFACE_H

#include "field_input.h"

#include <check_balance_form.h>
#include <total_calculation_form.h>
#include <breakdown_calculation_form.h>
#include <paycheck_form.h>
#include <full_report_form.h>

#include <string>
#include <sstream>

class DatabaseLayer;
class Form;
class TotalBreakdown;
class CommandInterface
{
public:

	static const int LINE_WIDTH = 60;

	enum LINES
	{
		DOUBLE_LINE,
		THIN_LINE,
		STAR_LINE,
		DOT_LINE,
		SPACE_LINE,
	};

	enum SIMPLE_COMMAND
	{
		COMMAND_BACK,
		COMMAND_FORWARD,
		COMMAND_STOP,
		COMMAND_CANCEL,
		COMMAND_YES,
		COMMAND_NO,
		COMMAND_NEXT,
		COMMAND_EMPTY,
		COMMAND_INVALID
	};

	enum INTERFACE_STATE
	{
		STATE_UNDEFINED,
		STATE_INITIAL_INPUT,
		STATE_ALREADY_HAS_VALUE,
		STATE_INVALID_INPUT,
		STATE_CANCEL,
		STATE_CANCELLED,
		STATE_NO_SUGGESTIONS,
		STATE_SUGGESTION,
		STATE_SELECTED_VALUE,
		STATE_DONE,
	};

public:
	CommandInterface();
	~CommandInterface();

	void Run();

	void CreateTransaction();
	void EditTransaction(int id);
	void CreateTransfer();
	void CreatePaycheck();
	void CopyAllOfType();
	void CheckBalance(bool skipForm);
	void CalculateTotal(bool skipForm);
	void CalculateBreakdown(bool skipForm);
	void GenerateFullReport(bool skipForm);

	void PrintTransaction(Transaction *transaction);

	void PrintField(std::string name, LINES line=DOT_LINE);

	void PrintBreakdown(TotalBreakdown *breakdown, std::stringstream &ss, int level);
	void PrintFullReport(TotalBreakdown *breakdowns, std::stringstream &ss, int level);

	void SetDatabase(DatabaseLayer *database) { m_databaseLayer = database; }

protected:

	SIMPLE_COMMAND GetSimpleUserInput(int *parameter, std::string &stringParameter);
	SIMPLE_COMMAND ParseSimpleUserInput(const std::string &input, int *parameter, std::string &stringParameter);
	SIMPLE_COMMAND ExecuteField(FieldInput *field, int *parameter, std::string &stringParameter);
	SIMPLE_COMMAND ExecuteForm(Form *form, int *intOutput, std::string &stringOutput);

	void DrawLine(LINES lineType, int length, bool newLine=true);
	void Execute();

protected:

	DatabaseLayer *m_databaseLayer;

	FullReportForm m_fullReportForm;

	CheckBalanceForm m_checkBalanceForm;
	bool m_checkBalanceFormInitialized;

	TotalCalculationForm m_calculateTotalForm;
	bool m_calculateTotalFormInitialized;

	BreakdownCalculationForm m_breakdownCalculationForm;
	bool m_breakdownFormInitialized;

	PaycheckForm m_paycheckForm;
	bool m_paycheckFormInitialized;

};

#endif /* COMMAND_INTERFACE_H */