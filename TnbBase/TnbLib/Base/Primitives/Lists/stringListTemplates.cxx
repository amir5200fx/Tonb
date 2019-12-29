#include <labelList.hxx>

#include <sys/types.h>
#include <regex.h>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	template<class StringList>
	labelList findStrings(const string& regexp, const StringList& sl)
	{
		labelList matches(sl.size());

		regex_t *preg = new regex_t;

		if (regcomp(preg, regexp.c_str(), REG_EXTENDED) != 0)
		{
			WarningIn("findStrings(const string& regexp, const stringList& sl)")
				<< "Failed to compile regular expression " << regexp
				<< endl;

			return matches;
		}

		size_t nmatch = 1;
		regmatch_t pmatch[1];

		label matchi = 0;
		forAll(sl, i)
		{
			if
				(
					regexec(preg, sl[i].c_str(), nmatch, pmatch, 0) == 0
					&& (pmatch[0].rm_so == 0 && pmatch[0].rm_eo == label(sl[i].size()))
					)
			{
				matches[matchi++] = i;
			}
		}

		matches.setSize(matchi);

		regfree(preg);
		delete preg;

		return matches;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //
