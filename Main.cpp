#include "MainForm.h"

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace lvceditor;

    [STAThread]
    void main()
    {
        Application::EnableVisualStyles();
        Application::SetCompatibleTextRenderingDefault(false);

        MainForm form;
        Application::Run(% form);
    }
