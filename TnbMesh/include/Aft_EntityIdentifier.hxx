#pragma once
#ifndef _Aft_EntityIdentifier_Header
#define _Aft_EntityIdentifier_Header

#include <Global_Serialization.hxx>
#include <Global_TypeDef.hxx>

#include <xtr1common>

namespace tnbLib
{

	template<class NodeType, bool GeomInfo = false>
	class Aft_EntityIdentifier
	{

		typedef typename NodeType::ptType Point;

		/*Private Data*/

		Standard_Real theCharLength_;
		Standard_Boolean IsOnCavity_;


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & theCharLength_;
			ar & IsOnCavity_;
		}

	public:

		Aft_EntityIdentifier()
			: theCharLength_(0)
			, IsOnCavity_(Standard_False)
		{}

		Standard_Real CharLength() const
		{
			return theCharLength_;
		}

		Standard_Real& CharLength()
		{
			return theCharLength_;
		}

		Standard_Boolean IsOnCavity() const
		{
			return IsOnCavity_;
		}

		void SetCharLength(const Standard_Real theLength)
		{
			//Debug_If_Condition(theLength <= 0);
			theCharLength_ = theLength;
		}

		void MarkEntityAsCavity()
		{
			IsOnCavity_ = Standard_True;
		}

		void RemoveEntityAsCavity()
		{
			IsOnCavity_ = Standard_False;
		}
	};

	template<class NodeType>
	class Aft_EntityIdentifier<NodeType, true>
		: public Aft_EntityIdentifier<NodeType, false>
	{

		typedef typename NodeType::ptType Point;

		/*Private Data*/

		Point theCentre_;


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<Aft_EntityIdentifier<NodeType, false>>(*this);
			ar & theCentre_;
		}

	public:

		Aft_EntityIdentifier()
		{}

		const Point& Centre() const
		{
			return theCentre_;
		}

		Point& Centre()
		{
			return theCentre_;
		}


		void SetCentre(const Point& theCentre)
		{
			theCentre_ = theCentre;
		}
	};


}

#endif // !_Aft_EntityIdentifier_Header