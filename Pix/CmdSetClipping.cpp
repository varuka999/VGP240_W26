#include "CmdSetClipping.h"
#include "Clipper.h"

bool CmdSetClipping::Execute(const std::vector<std::string>& params)
{
    bool clipping = true;

    if (params.size() > 0)
    {
        if (params[0] == "false")
        {
            clipping = false;
        }
    }

    Clipper::Get()->SetClipping(clipping);

    return true;
}