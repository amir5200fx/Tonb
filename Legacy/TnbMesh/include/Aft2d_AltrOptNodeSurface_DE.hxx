#pragma once
#ifndef _Aft2d_AltrOptNodeSurface_DE_Header
#define _Aft2d_AltrOptNodeSurface_DE_Header

#include <Aft2d_AltrOptNodeSurface.hxx>
#include <Aft2d_AltrOptNodeSurface_DE_Info.hxx>
#include <Pnt2d.hxx>

#include <vector>

namespace tnbLib
{

	class Aft2d_AltrOptNodeSurface_DE_Info;

	class Aft2d_AltrOptNodeSurface_DE
		: public Aft2d_AltrOptNodeSurface
	{

		/*Private Data*/

		std::pair<Standard_Real, Standard_Real> theUV0_;
		std::pair<Standard_Real, Standard_Real> theUV1_;

		std::shared_ptr<Aft2d_AltrOptNodeSurface_DE_Info> theInfo_;


		// private functions and operators [6/12/2022 Amir]

		TnbMesh_EXPORT double Iter(const std::vector<double>&) const;

		TNB_SERIALIZATION(TnbMesh_EXPORT);

	public:

		static TnbMesh_EXPORT const std::shared_ptr<Aft2d_AltrOptNodeSurface_DE_Info> DEFAULT_INFO;

		// default constructor [6/12/2022 Amir]

		Aft2d_AltrOptNodeSurface_DE()
			: theInfo_(DEFAULT_INFO)
			, theUV0_(std::make_pair(0,0))
			, theUV1_(std::make_pair(0,0))
		{}


		// constructors [6/12/2022 Amir]

		explicit Aft2d_AltrOptNodeSurface_DE
		(
			const std::shared_ptr<Aft2d_AltrOptNodeSurface_DE_Info>& theInfo
		)
			: theInfo_(theInfo)
		{}

		// public functions and operators [6/12/2022 Amir]

		const auto& UV0() const
		{
			return theUV0_;
		}

		const auto& UV1() const
		{
			return theUV1_;
		}

		const auto& DEInfo() const
		{
			return theInfo_;
		}

		TnbMesh_EXPORT void Perform();

		void OverrideInfo(const std::shared_ptr<Aft2d_AltrOptNodeSurface_DE_Info>& theInfo)
		{
			theInfo_ = theInfo;
		}
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Aft2d_AltrOptNodeSurface_DE);

#endif // !_Aft2d_AltrOptNodeSurface_DE_Header
