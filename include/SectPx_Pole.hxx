#pragma once
#ifndef _SectPx_Pole_Header
#define _SectPx_Pole_Header

#include <SectPx_RegObj.hxx>
#include <SectPx_PoleType.hxx>
#include <Pnt2d.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	// Forward Declarations
	class SectPx_Pnt;

	class SectPx_Pole
		: public SectPx_RegObj
	{

		/*Private Data*/

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<SectPx_RegObj>(*this);
		}

	protected:

		template<class... _Types>
		SectPx_Pole(_Types&&... Args)
			: SectPx_RegObj(Args...)
		{}

	public:

		virtual Standard_Boolean IsInterior() const;

		virtual Standard_Boolean IsBoundary() const;

		virtual Pnt2d Coord() const = 0;

		virtual SectPx_PoleType Type() const = 0;

		virtual std::shared_ptr<SectPx_Pnt> Pnt() const = 0;

		sectPxLib::regObjType RegObjType() const override;

		Standard_Boolean IsPole() const override;

		static Standard_Boolean
			IsLess
			(
				const std::shared_ptr<SectPx_Pole>& theP0,
				const std::shared_ptr<SectPx_Pole>& theP1
			)
		{
			Debug_Null_Pointer(theP0);
			Debug_Null_Pointer(theP1);
			return theP0->Index() < theP1->Index();
		}
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::SectPx_Pole);

#endif // !_SectPx_Pole_Header
