#include <paycheck_form.h>

#include <transaction.h>
#include <transaction_class.h>
#include <account.h>
#include <counterparty.h>
#include <transaction_type.h>

#include <database_layer.h>

namespace pft {

    PaycheckForm::PaycheckForm() {}
    PaycheckForm::~PaycheckForm() {}

    void PaycheckForm::Initialize() {
        Form::Initialize();

        m_nameField.SetFieldName(std::string("NAME"));
        m_nameField.SetInputType(FieldInput::INPUT_SHORT_STRING);

        m_parentClassField.SetFieldName(std::string("PARENT CLASS"));
        m_parentClassField.SetInputType(FieldInput::INPUT_LOOKUP);

        m_basePayClass.SetFieldName(std::string("BASE PAY CLASS"));
        m_basePayClass.SetInputType(FieldInput::INPUT_LOOKUP);

        m_citClass.SetFieldName(std::string("CIT CLASS"));
        m_citClass.SetInputType(FieldInput::INPUT_LOOKUP);

        m_cppClass.SetFieldName(std::string("CPP CLASS"));
        m_cppClass.SetInputType(FieldInput::INPUT_LOOKUP);

        m_eiClass.SetFieldName(std::string("EI CLASS"));
        m_eiClass.SetInputType(FieldInput::INPUT_LOOKUP);

        m_afterTaxDeductionsClass.SetFieldName(std::string("AFTER TAX DED. CLASS"));
        m_afterTaxDeductionsClass.SetInputType(FieldInput::INPUT_LOOKUP);

        m_directDepositClass.SetFieldName(std::string("DIRECT DEPOSIT CLASS"));
        m_directDepositClass.SetInputType(FieldInput::INPUT_LOOKUP);

        m_containerType.SetFieldName(std::string("CONTAINER TYPE"));
        m_containerType.SetInputType(FieldInput::INPUT_LOOKUP);

        m_typeField.SetFieldName(std::string("CHILD TYPE"));
        m_typeField.SetInputType(FieldInput::INPUT_LOOKUP);

        m_amountField.SetFieldName(std::string("TOTAL AMOUNT"));
        m_amountField.SetInputType(FieldInput::INPUT_DOUBLE);

        m_basePayAmount.SetFieldName(std::string("BASE PAY"));
        m_basePayAmount.SetInputType(FieldInput::INPUT_DOUBLE);

        m_citAmount.SetFieldName(std::string("CIT"));
        m_citAmount.SetInputType(FieldInput::INPUT_DOUBLE);

        m_cppAmount.SetFieldName(std::string("CPP"));
        m_cppAmount.SetInputType(FieldInput::INPUT_DOUBLE);

        m_eiAmount.SetFieldName(std::string("EI"));
        m_eiAmount.SetInputType(FieldInput::INPUT_DOUBLE);

        m_afterTaxDeductionsAmount.SetFieldName(std::string("AFTER TAX DEDUCTIONS"));
        m_afterTaxDeductionsAmount.SetInputType(FieldInput::INPUT_DOUBLE);

        m_parentIdField.SetFieldName(std::string("PARENT ENTITY ID"));
        m_parentIdField.SetInputType(FieldInput::INPUT_INT);

        m_destinationAccount.SetFieldName(std::string("DESTINATION ACCOUNT"));
        m_destinationAccount.SetInputType(FieldInput::INPUT_LOOKUP);

        m_intermediateAccount.SetFieldName(std::string("INTERMEDIATE ACCOUNT"));
        m_intermediateAccount.SetInputType(FieldInput::INPUT_LOOKUP);

        m_intermediateCounterparty.SetFieldName(std::string("INTERMEDIATE COUNTERPARTY"));
        m_intermediateCounterparty.SetInputType(FieldInput::INPUT_LOOKUP);

        m_taxCounterparty.SetFieldName(std::string("TAX COUNTERPARTY"));
        m_taxCounterparty.SetInputType(FieldInput::INPUT_LOOKUP);

        m_employer.SetFieldName(std::string("EMPLOYER"));
        m_employer.SetInputType(FieldInput::INPUT_LOOKUP);

        m_dateField.SetFieldName(std::string("DATE"));
        m_dateField.SetInputType(FieldInput::INPUT_SHORT_STRING);

        m_preTaxAllocationsClass.SetFieldName(std::string("PRE-TAX ALLOCATIONS CLASS"));
        m_preTaxAllocationsClass.SetInputType(FieldInput::INPUT_LOOKUP);

        m_preTaxAllocationsAmount.SetFieldName(std::string("PRE-TAX ALLOCATIONS"));
        m_preTaxAllocationsAmount.SetInputType(FieldInput::INPUT_DOUBLE);

        /* Register all fields */
        RegisterField(&m_nameField);
        RegisterField(&m_parentClassField);
        RegisterField(&m_basePayClass);
        RegisterField(&m_citClass);
        RegisterField(&m_cppClass);
        RegisterField(&m_eiClass);
        RegisterField(&m_afterTaxDeductionsClass);
        RegisterField(&m_directDepositClass);
        RegisterField(&m_preTaxAllocationsClass);
        RegisterField(&m_containerType);
        RegisterField(&m_typeField);
        RegisterField(&m_amountField);
        RegisterField(&m_basePayAmount);
        RegisterField(&m_citAmount);
        RegisterField(&m_cppAmount);
        RegisterField(&m_eiAmount);
        RegisterField(&m_afterTaxDeductionsAmount);
        RegisterField(&m_preTaxAllocationsAmount);
        RegisterField(&m_parentIdField);
        RegisterField(&m_destinationAccount);
        RegisterField(&m_intermediateAccount);
        RegisterField(&m_intermediateCounterparty);
        RegisterField(&m_taxCounterparty);
        RegisterField(&m_employer);
        RegisterField(&m_dateField);
    }

    void PaycheckForm::Copy(Form *target) {
        // UNIMPLEMENTED
    }

    void PaycheckForm::PopulateTransactions(Transaction *container, Transaction *basePay, Transaction *cit, Transaction *cpp, Transaction *ei,
        Transaction *directDeposit, Transaction *directDepositReciprocal, Transaction *postTaxDeductions, Transaction *preTaxAllocations) {
        // TOP LEVEL TRANSACTION
        container->SetStringAttribute(std::string("NAME"), m_nameField.GetCurrentValue());
        container->SetCurrencyAttribute(std::string("AMOUNT"), m_amountField.GetDoubleValue());

        container->SetIntAttribute(std::string("COUNTERPARTY_ID"), m_employer.GetCurrentSuggestion()->Id);
        container->SetIntAttribute(std::string("CLASS_ID"), m_parentClassField.GetCurrentSuggestion()->Id);
        container->SetIntAttribute(std::string("TYPE_ID"), m_containerType.GetCurrentSuggestion()->Id);
        container->SetIntAttribute(std::string("ACCOUNT_ID"), m_destinationAccount.GetCurrentSuggestion()->Id);

        container->SetIntAttribute(std::string("PARENT_ENTITY_ID"), m_parentIdField.GetIntValue());
        container->SetStringAttribute(std::string("DATE"), m_dateField.GetCurrentValue());

        // BASE PAY
        basePay->SetStringAttribute(std::string("NAME"), m_nameField.GetCurrentValue() + " (BASE PAY)");
        basePay->SetCurrencyAttribute(std::string("AMOUNT"), m_basePayAmount.GetDoubleValue());

        basePay->SetIntAttribute(std::string("COUNTERPARTY_ID"), m_employer.GetCurrentSuggestion()->Id);
        basePay->SetIntAttribute(std::string("CLASS_ID"), m_basePayClass.GetCurrentSuggestion()->Id);
        basePay->SetIntAttribute(std::string("TYPE_ID"), m_typeField.GetCurrentSuggestion()->Id);
        basePay->SetIntAttribute(std::string("ACCOUNT_ID"), m_intermediateAccount.GetCurrentSuggestion()->Id);

        basePay->SetStringAttribute(std::string("DATE"), m_dateField.GetCurrentValue());

        // CIT
        cit->SetStringAttribute(std::string("NAME"), m_nameField.GetCurrentValue() + " (CIT)");
        cit->SetCurrencyAttribute(std::string("AMOUNT"), m_citAmount.GetDoubleValue());

        cit->SetIntAttribute(std::string("COUNTERPARTY_ID"), m_taxCounterparty.GetCurrentSuggestion()->Id);
        cit->SetIntAttribute(std::string("CLASS_ID"), m_citClass.GetCurrentSuggestion()->Id);
        cit->SetIntAttribute(std::string("TYPE_ID"), m_typeField.GetCurrentSuggestion()->Id);
        cit->SetIntAttribute(std::string("ACCOUNT_ID"), m_intermediateAccount.GetCurrentSuggestion()->Id);

        cit->SetStringAttribute(std::string("DATE"), m_dateField.GetCurrentValue());

        // CPP
        cpp->SetStringAttribute(std::string("NAME"), m_nameField.GetCurrentValue() + " (CPP)");
        cpp->SetCurrencyAttribute(std::string("AMOUNT"), m_cppAmount.GetDoubleValue());

        cpp->SetIntAttribute(std::string("COUNTERPARTY_ID"), m_taxCounterparty.GetCurrentSuggestion()->Id);
        cpp->SetIntAttribute(std::string("CLASS_ID"), m_cppClass.GetCurrentSuggestion()->Id);
        cpp->SetIntAttribute(std::string("TYPE_ID"), m_typeField.GetCurrentSuggestion()->Id);
        cpp->SetIntAttribute(std::string("ACCOUNT_ID"), m_intermediateAccount.GetCurrentSuggestion()->Id);

        cpp->SetStringAttribute(std::string("DATE"), m_dateField.GetCurrentValue());

        // EI
        ei->SetStringAttribute(std::string("NAME"), m_nameField.GetCurrentValue() + " (EI)");
        ei->SetCurrencyAttribute(std::string("AMOUNT"), m_eiAmount.GetDoubleValue());

        ei->SetIntAttribute(std::string("COUNTERPARTY_ID"), m_taxCounterparty.GetCurrentSuggestion()->Id);
        ei->SetIntAttribute(std::string("CLASS_ID"), m_eiClass.GetCurrentSuggestion()->Id);
        ei->SetIntAttribute(std::string("TYPE_ID"), m_typeField.GetCurrentSuggestion()->Id);
        ei->SetIntAttribute(std::string("ACCOUNT_ID"), m_intermediateAccount.GetCurrentSuggestion()->Id);

        ei->SetStringAttribute(std::string("DATE"), m_dateField.GetCurrentValue());

        // AFTER TAX DEDUCTIONS
        postTaxDeductions->SetStringAttribute(std::string("NAME"), m_nameField.GetCurrentValue() + " (POST-TAX DEDUCTIONS)");
        postTaxDeductions->SetCurrencyAttribute(std::string("AMOUNT"), m_afterTaxDeductionsAmount.GetDoubleValue());

        postTaxDeductions->SetIntAttribute(std::string("COUNTERPARTY_ID"), m_employer.GetCurrentSuggestion()->Id);
        postTaxDeductions->SetIntAttribute(std::string("CLASS_ID"), m_afterTaxDeductionsClass.GetCurrentSuggestion()->Id);
        postTaxDeductions->SetIntAttribute(std::string("TYPE_ID"), m_typeField.GetCurrentSuggestion()->Id);
        postTaxDeductions->SetIntAttribute(std::string("ACCOUNT_ID"), m_intermediateAccount.GetCurrentSuggestion()->Id);

        postTaxDeductions->SetStringAttribute(std::string("DATE"), m_dateField.GetCurrentValue());

        // DIRECT DEPOSIT
        directDeposit->SetStringAttribute(std::string("NAME"), m_nameField.GetCurrentValue() + " (DEPOSIT)");
        directDeposit->SetCurrencyAttribute(std::string("AMOUNT"), m_amountField.GetDoubleValue());

        directDeposit->SetIntAttribute(std::string("COUNTERPARTY_ID"), m_intermediateCounterparty.GetCurrentSuggestion()->Id);
        directDeposit->SetIntAttribute(std::string("CLASS_ID"), m_directDepositClass.GetCurrentSuggestion()->Id);
        directDeposit->SetIntAttribute(std::string("TYPE_ID"), m_typeField.GetCurrentSuggestion()->Id);
        directDeposit->SetIntAttribute(std::string("ACCOUNT_ID"), m_destinationAccount.GetCurrentSuggestion()->Id);

        directDeposit->SetStringAttribute(std::string("DATE"), m_dateField.GetCurrentValue());

        // DIRECT DEPOSIT RECIPROCAL
        directDepositReciprocal->SetStringAttribute(std::string("NAME"), m_nameField.GetCurrentValue() + " (DEPOSIT RECIPROCAL)");
        directDepositReciprocal->SetCurrencyAttribute(std::string("AMOUNT"), -m_amountField.GetDoubleValue());

        directDepositReciprocal->SetIntAttribute(std::string("COUNTERPARTY_ID"), m_intermediateCounterparty.GetCurrentSuggestion()->Id);
        directDepositReciprocal->SetIntAttribute(std::string("CLASS_ID"), m_directDepositClass.GetCurrentSuggestion()->Id);
        directDepositReciprocal->SetIntAttribute(std::string("TYPE_ID"), m_typeField.GetCurrentSuggestion()->Id);
        directDepositReciprocal->SetIntAttribute(std::string("ACCOUNT_ID"), m_intermediateAccount.GetCurrentSuggestion()->Id);

        directDepositReciprocal->SetStringAttribute(std::string("DATE"), m_dateField.GetCurrentValue());

        // PRE-TAX ALLOCATIONS
        preTaxAllocations->SetStringAttribute(std::string("NAME"), m_nameField.GetCurrentValue() + " (PRE-TAX ALLOCATIONS)");
        preTaxAllocations->SetCurrencyAttribute(std::string("AMOUNT"), m_preTaxAllocationsAmount.GetDoubleValue());

        preTaxAllocations->SetIntAttribute(std::string("COUNTERPARTY_ID"), m_employer.GetCurrentSuggestion()->Id);
        preTaxAllocations->SetIntAttribute(std::string("CLASS_ID"), m_preTaxAllocationsClass.GetCurrentSuggestion()->Id);
        preTaxAllocations->SetIntAttribute(std::string("TYPE_ID"), m_typeField.GetCurrentSuggestion()->Id);
        preTaxAllocations->SetIntAttribute(std::string("ACCOUNT_ID"), m_intermediateAccount.GetCurrentSuggestion()->Id);

        preTaxAllocations->SetStringAttribute(std::string("DATE"), m_dateField.GetCurrentValue());
    }

} /* namespace pft */
