#include <Aft2d_FrontGlobalData.hxx>

#include <Aft2d_Edge.hxx>

namespace tnbLib
{
	template<>
	template<>
	void Aft2d_EdgePriorityList::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int /*file_version*/
			)
	{
		ar & theData_;
	}

	template<>
	template<>
	void Aft2d_EdgePriorityList::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int /*file_version*/
			)
	{
		ar & theData_;

		LengthValue = &Aft2d_Edge::Length;
	}
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh_RegisterCurrentFront<tnbLib::Aft2d_Edge>)
{
	ar & theCurrentFronts_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh_RegisterCurrentFront<tnbLib::Aft2d_Edge>)
{
	ar & theCurrentFronts_;
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh_RegisterNextFront<tnbLib::Aft2d_Edge>)
{
	ar & theNextFronts_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh_RegisterNextFront<tnbLib::Aft2d_Edge>)
{
	ar & theNextFronts_;
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh_RegisterCertaintyCavitie<tnbLib::Aft2d_Edge>)
{
	ar & theCertaintyCavities_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh_RegisterCertaintyCavitie<tnbLib::Aft2d_Edge>)
{
	ar & theCertaintyCavities_;
}

template<>
TNB_SAVE_IMPLEMENTATION(tnbLib::Mesh_RegisterUnCertaintyCavitie<tnbLib::Aft2d_Edge>)
{
	ar & theUnCertaintyCavities_;
}

template<>
TNB_LOAD_IMPLEMENTATION(tnbLib::Mesh_RegisterUnCertaintyCavitie<tnbLib::Aft2d_Edge>)
{
	ar & theUnCertaintyCavities_;
}