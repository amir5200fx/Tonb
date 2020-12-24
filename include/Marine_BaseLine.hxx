#pragma once
#ifndef _Marine_BaseLine_Header
#define _Marine_BaseLine_Header

#include <Marine_Entity.hxx>
#include <Geo_Serialization.hxx>

#include <gp_Ax1.hxx>
#include <gp_Ax2.hxx>

namespace tnbLib
{

	class Marine_BaseLine
		: public Marine_Entity
	{

		/*Private Data*/

		gp_Ax1 theBaseLib_;


		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<Marine_Entity>(*this);
			ar & theBaseLib_;
		}

	public:

		static TnbMarine_EXPORT const gp_Ax1 null;

		TnbMarine_EXPORT Marine_BaseLine();

		Marine_BaseLine(const gp_Ax1& theAx)
			: Marine_Entity(0, "base line")
			, theBaseLib_(theAx)
		{}

		TnbMarine_EXPORT Marine_BaseLine(const gp_Ax2& theSystem);

		TnbMarine_EXPORT Standard_Boolean IsNull() const;

		const auto& BaseLine() const
		{
			return theBaseLib_;
		}

		auto& BaseLine()
		{
			return theBaseLib_;
		}
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Marine_BaseLine);

#endif // !_Marine_BaseLine_Header
