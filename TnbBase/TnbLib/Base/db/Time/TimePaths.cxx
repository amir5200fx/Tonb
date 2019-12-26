#include <TimePaths.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::TimePaths::TimePaths
(
	const fileName& rootPath,
	const fileName& caseName,
	const word& systemName,
	const word& constantName
)
	: processorCase_(caseName.find("processor") != string::npos)
	, rootPath_(rootPath)
	, case_(caseName)
	, system_(systemName)
	, constant_(constantName)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::fileName tnbLib::TimePaths::caseSystem() const
{
	if (processorCase_)
	{
		return ".." / system();
	}
	else
	{
		return system();
	}
}


tnbLib::fileName tnbLib::TimePaths::caseConstant() const
{
	if (processorCase_)
	{
		return ".." / constant();
	}
	else
	{
		return constant();
	}
}



// ************************************************************************* //
