#include <full_report_form.h>

namespace pft {

    FullReportForm::FullReportForm() {}
    FullReportForm::~FullReportForm() {}

    void FullReportForm::Copy(Form *target) {
        // UNIMPLEMENTED
    }

    void FullReportForm::Initialize() {
        Form::Initialize();

        m_folderName.SetFieldName(std::string("OUTPUT FOLDER"));
        m_folderName.SetInputType(FieldInput::INPUT_SHORT_STRING);

        m_fileName.SetFieldName(std::string("OUTPUT FILENAME"));
        m_fileName.SetInputType(FieldInput::INPUT_SHORT_STRING);

        m_classField.SetFieldName(std::string("CLASS"));
        m_classField.SetInputType(FieldInput::INPUT_LOOKUP);

        m_typeField.SetFieldName(std::string("TYPE"));
        m_typeField.SetInputType(FieldInput::INPUT_LOOKUP);

        m_budgetTypeField.SetFieldName(std::string("BUDGET TYPE"));
        m_budgetTypeField.SetInputType(FieldInput::INPUT_LOOKUP);

        m_startMonth.SetFieldName(std::string("START MONTH"));
        m_startMonth.SetInputType(FieldInput::INPUT_SHORT_STRING);
        m_startMonth.SetMonthOnly(true);

        m_endMonth.SetFieldName(std::string("END MONTH"));
        m_endMonth.SetInputType(FieldInput::INPUT_SHORT_STRING);
        m_endMonth.SetMonthOnly(true);

        /* Register all fields */
        RegisterField(&m_folderName);
        RegisterField(&m_fileName);
        RegisterField(&m_startMonth);
        RegisterField(&m_endMonth);
        RegisterField(&m_classField);
        RegisterField(&m_typeField);
        RegisterField(&m_budgetTypeField);
    }

} /* namespace pft */
