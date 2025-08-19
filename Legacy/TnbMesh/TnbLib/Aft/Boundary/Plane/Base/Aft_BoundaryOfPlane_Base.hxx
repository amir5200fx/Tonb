#pragma once
#ifndef _Aft_BoundaryOfPlane_Base_Header
#define _Aft_BoundaryOfPlane_Base_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <Global_Done.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	template<class BndType>
	class Aft_BoundaryOfPlane_Base
		: public Global_Indexed
		, public Global_Named
		, public Global_Done
	{

		/*Private Data*/

		Standard_Boolean theSimpleCheck_;
		Standard_Boolean theInnerCheck_;
		Standard_Boolean theOrientCheck_;
		Standard_Boolean theNbPtsCheck_;


		//- private functions and operators 

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<Global_Indexed>(*this);
			ar & boost::serialization::base_object<Global_Named>(*this);
			ar & boost::serialization::base_object<Global_Done>(*this);

			ar & theSimpleCheck_;
			ar & theInnerCheck_;
			ar & theOrientCheck_;
			ar & theNbPtsCheck_;
		}

	protected:


		//- default constructor

		Aft_BoundaryOfPlane_Base()
			: theSimpleCheck_(Standard_False)
			, theInnerCheck_(Standard_False)
			, theOrientCheck_(Standard_False)
			, theNbPtsCheck_(Standard_False)
		{}


		//- private functions and operators

		void SetSimpleCheck(const Standard_Boolean check)
		{
			theSimpleCheck_ = check;
		}

		void SetInnerCheck(const Standard_Boolean check)
		{
			theInnerCheck_ = check;
		}

		void SetOrientCheck(const Standard_Boolean check)
		{
			theOrientCheck_ = check;
		}

		void SetNbPtsCheck(const Standard_Boolean check)
		{
			theNbPtsCheck_ = check;
		}


		static Standard_Boolean CheckWireOrientation
		(
			const std::vector<std::shared_ptr<BndType>>& theEdges,
			const Standard_Boolean ccw
		);

		static Standard_Boolean CheckWireNbPts
		(
			const std::vector<std::shared_ptr<BndType>>& theEdges
		);

		static Standard_Boolean CheckSimplicity
		(
			const std::vector<std::shared_ptr<BndType>>& theEdges
		);

	public:

		//- constructors


		//- public functions and operators

		auto SimpleCheck() const
		{
			return theSimpleCheck_;
		}

		auto InnerCheck() const
		{
			return theInnerCheck_;
		}

		auto OrientCheck() const
		{
			return theOrientCheck_;
		}

		auto NbPtsCheck() const
		{
			return theNbPtsCheck_;
		}
	};
}


#include <Aft_BoundaryOfPlane_BaseI.hxx>

#endif // !_Aft_BoundaryOfPlane_Base_Header
