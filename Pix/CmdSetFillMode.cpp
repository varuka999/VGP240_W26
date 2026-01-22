#include "CmdSetFillMode.h"
#include "Rasterizer.h"

bool CmdSetFillMode::Execute(const std::vector<std::string>& params)
{
    // Wireframe is the default
    FillMode fillMode = FillMode::Wireframe;

    if (params.size() > 0) // Avoid empty inputs
    {
        if (params[0] == "solid")
        {
            fillMode = FillMode::Solid;
        }
    }

    Rasterizer::Get()->SetFillMode(fillMode);

    return true;
}
