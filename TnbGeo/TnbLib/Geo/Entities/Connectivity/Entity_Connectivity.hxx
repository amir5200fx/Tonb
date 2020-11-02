#pragma once
#ifndef _Entity_Connectivity_Header
#define _Entity_Connectivity_Header

#include <Standard_TypeDef.hxx>
#include <Geo_Module.hxx>
#include <Global_Serialization.hxx>
#include <Istream.hxx>

#include <vector>

namespace tnbLib
{

	template<int Dim>
	class Entity_Connectivity
	{

		/*Private Data*/

		Standard_Integer theV_[Dim];


		/*private functions and operators*/

		friend class boost::serialization::access;
		void save(TNB_oARCH_TYPE& ar, const unsigned int version) const;
		void load(TNB_iARCH_TYPE& ar, const unsigned int version);

		void serialize(TNB_oARCH_TYPE& ar, const unsigned int file_version)
		{
			boost::serialization::split_member(ar, *this, file_version);
		}

		void serialize(TNB_iARCH_TYPE& ar, const unsigned int file_version)
		{
			boost::serialization::split_member(ar, *this, file_version);
		};

	public:

		static const Standard_Integer nbCmpts = Dim;

		Entity_Connectivity()
		{}

		Standard_Integer Value
		(
			const Standard_Integer theIndex
		) const
		{
			return theV_[theIndex];
		}

		Standard_Integer& Value
		(
			const Standard_Integer theIndex
		)
		{
			return theV_[theIndex];
		}

		Standard_Boolean IsDegenerated() const;

		template<int Dim>
		friend Istream& operator>>(Istream& is, Entity_Connectivity<Dim>& theEntity);
	};

	template<int Dim>
	Istream & operator>>(Istream & is, Entity_Connectivity<Dim>& theEntity)
	{
		string comma;
		int x[Dim];

		is.readBegin("Istream & operator>>(Istream & is, Entity_Connectivity<Dim>& theEntity)");
		for (int i = 1; i < Dim; i++)
		{
			is >> x[i - 1] >> comma;
		}
		is >> x[Dim - 1];
		is.readEnd("Istream & operator>>(Istream & is, Entity_Connectivity<Dim>& theEntity)");

		for (int i = 0; i < Dim; i++)
			theEntity.Value(i) = x[i];

		// Check state of Istream
		is.check("Istream & operator>>(Istream & is, Entity_Connectivity<Dim>& theEntity)");
		return is;
	}

	namespace connectivity
	{

		typedef Entity_Connectivity<2> dual;
		typedef Entity_Connectivity<3> triple;
		typedef Entity_Connectivity<4> quadruple;
		typedef Entity_Connectivity<5> quintuple;
		typedef Entity_Connectivity<6> sextuple;
		typedef Entity_Connectivity<7> septuple;
		typedef Entity_Connectivity<8> octuple;

	}

	template<>
	inline Standard_Boolean connectivity::dual::IsDegenerated() const
	{
		return Value(0) == Value(1);
	}

	template<>
	inline Standard_Boolean connectivity::triple::IsDegenerated() const
	{
		if (Value(0) == Value(1)) return Standard_True;
		else if (Value(0) == Value(2)) return Standard_True;
		else if (Value(1) == Value(2)) return Standard_True;
		return Standard_False;
	}

	template<int Dim>
	Standard_Integer MaxID(const std::vector<Entity_Connectivity<Dim>>&);

	template<int Dim>
	std::vector<Entity_Connectivity<Dim>>
		CombineConnectivities
		(
			const std::vector<Entity_Connectivity<Dim>>& theC0,
			const std::vector<Entity_Connectivity<Dim>>& theC1
		);

	std::vector<connectivity::dual> dualConnectivityList(const Standard_Integer theNbEdges);

	std::vector<connectivity::dual> dualConnectivityList_Chain(const Standard_Integer theNbEdges, const Standard_Boolean IsClosed = Standard_False);

}

#include <Entity_ConnectivityI.hxx>

#endif // !_Entity_Connectivity_Header
