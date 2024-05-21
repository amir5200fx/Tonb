#include <Geo2dIO_CSV.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

bool tnbLib::Geo2dIO_CSV::IsComment(const std::string& line)
{
    return !line.empty() && line[0] == '#';
}

tnbLib::Pnt2d tnbLib::Geo2dIO_CSV::ParseLine(const std::string& line)
{
    std::stringstream ss(line);
    std::string token;
    double x = 0.0, y = 0.0;
    if (std::getline(ss, token, ','))
    {
        x = std::stod(token);
    }
    if (std::getline(ss, token, ','))
    {
        y = std::stod(token);
    }
    return { x, y };
}

void tnbLib::Geo2dIO_CSV::Read(const std::string& filename, std::string& comments, std::vector<Pnt2d>& coordinates)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        FatalErrorIn(FunctionSIG) << endl
            << " Error opening file: " << filename << endl
            << abort(FatalError);
    }

    std::string line;
    while (std::getline(file, line))
    {
        if (IsComment(line))
        {
            comments += line + "\n";
        }
        else
        {
            coordinates.push_back(ParseLine(line));
        }
    }

    file.close();
}

void tnbLib::Geo2dIO_CSV::Write(const std::string& filename, const std::string& comments,
                              const std::vector<Pnt2d>& coordinates)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        FatalErrorIn(FunctionSIG) << endl
            << " Error opening file: " << filename << endl
            << abort(FatalError);
    }

    if (!comments.empty())
    {
        file << comments;
    }

    for (const auto& coord : coordinates)
    {
        file << coord.X() << "," << coord.Y() << endl;
    }

    file.close();
}
