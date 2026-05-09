#include <Aft3d_FrontGlobalData.hxx>

#include <Aft3d_Facet.hxx>

namespace tnbLib
{

	template<>
	template<>
	void Aft3d_FacetPriorityList::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int /*file_version*/
			)
	{
		ar& theData_;
	}

	template<>
	template<>
	void Aft3d_FacetPriorityList::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int /*file_version*/
			)
	{
		ar& theData_;

		LengthValue = &Aft3d_Facet::Length;
	}
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh_RegisterNextFront<tnbLib::Aft3d_Facet>)
{
	ar& theNextFronts_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh_RegisterNextFront<tnbLib::Aft3d_Facet>)
{
	ar& theNextFronts_;
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh_RegisterCertaintyCavitie<tnbLib::Aft3d_Facet>)
{
	ar& theCertaintyCavities_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh_RegisterCertaintyCavitie<tnbLib::Aft3d_Facet>)
{
	ar& theCertaintyCavities_;
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh_RegisterUnCertaintyCavitie<tnbLib::Aft3d_Facet>)
{
	ar& theUnCertaintyCavities_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh_RegisterUnCertaintyCavitie<tnbLib::Aft3d_Facet>)
{
	ar& theUnCertaintyCavities_;
}