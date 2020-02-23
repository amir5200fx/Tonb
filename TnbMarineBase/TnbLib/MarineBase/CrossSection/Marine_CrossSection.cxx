#include <Marine_CrossSection.hxx>

tnbLib::Marine_CrossSection::Marine_CrossSection
(
	const gp_Ax2 & theSystem
)
	: theSystem_(theSystem)
	, theMinTolerance_(1.0E-6)
	, theMaxTolerance_(1.0E-3)
{
}
