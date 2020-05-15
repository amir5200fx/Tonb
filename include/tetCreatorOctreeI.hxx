#pragma once
namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	inline void tetCreatorOctree::checkAndAppendTet(const partTet pt)
	{
		bool valid(true);
		for (label n = 0; n < 4; ++n)
			if (pt[n] < 0)
			{
				valid = false;
				break;
			}

		if (valid)
		{
			tets_.append(pt);

# ifdef DEBUGTets
			Info << "Added tet " << (tets_.size() - 1) << " is "
				<< tets_[tets_.size() - 1] << endl;
# endif
		}
	}
}

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //