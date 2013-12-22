#include "cl_standard_paths.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>

clStandardPaths::clStandardPaths()
{
}

clStandardPaths::~clStandardPaths()
{
}

clStandardPaths& clStandardPaths::Get()
{
    static clStandardPaths codelitePaths;
    return codelitePaths;
}

wxString clStandardPaths::GetUserDataDir() const
{
#ifdef __WXGTK__

#ifndef NDEBUG
    // Debug mode
    wxFileName fn(wxStandardPaths::Get().GetUserDataDir());
    fn.SetFullName(".codelite-dbg");
    return fn.GetFullPath();
    
#else
    // Release mode
    return wxStandardPaths::Get().GetUserDataDir();
    
#endif
#else // Windows / OSX
    return wxStandardPaths::Get().GetUserDataDir();
#endif
}
