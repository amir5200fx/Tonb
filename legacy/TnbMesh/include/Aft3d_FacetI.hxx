#pragma once

inline
void tnbLib::legLib::Aft3d_Facet::SetIsCavity(const Standard_Boolean isIt)
{
	isCavity_ = isIt;
}

inline 
void tnbLib::legLib::Aft3d_Facet::SetAsNonCavity()
{
	SetIsCavity(Standard_False);
}

inline
void tnbLib::legLib::Aft3d_Facet::SetAsCavity()
{
	SetIsCavity(Standard_True);
}

namespace tnbLib
{
	namespace legLib
	{
		inline auto facet_comp = [](const std::shared_ptr<Aft3d_Facet>& facet0, const std::shared_ptr<Aft3d_Facet>& facet1)
		{
			return facet0->Index() < facet1->Index();
		};
	}
}
