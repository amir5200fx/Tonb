#pragma once
#ifndef _Entity_Connectivity_Header
#define _Entity_Connectivity_Header

#include <Geo_Module.hxx>
#include <Global_Serialization.hxx>
#include <Istream.hxx>

#include <vector>
#include <array>

namespace tnbLib
{

	template<int Dim, int Reduct = 0>
	class Entity_Connectivity
	{
	public:
		typedef std::array<Standard_Integer, Dim> Array;
	private:
		/*Private Data*/
		Array theCmpts_;

		/*private functions and operators*/
		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& theCmpts_;
		}

	public:

		static const Standard_Integer nbCmpts = Dim;

		// default constructor
		Entity_Connectivity() = default;

		// constructors
		Entity_Connectivity(Array cmpts)
			: theCmpts_(std::move(cmpts))
		{}

		// Public functions and operators
		[[nodiscard]] auto Value(const Standard_Integer theIndex) const { return theCmpts_.at(theIndex); }
		auto& Value(const Standard_Integer theIndex) { return theCmpts_.at(theIndex); }

		[[nodiscard]] const auto& Cmpts() const { return theCmpts_; }
		auto& CmptsRef() { return theCmpts_; }

		[[nodiscard]] Standard_Boolean IsDegenerated() const;
		[[nodiscard]] Entity_Connectivity Reversed() const;

		void Reverse();

		template<int Dim, int Reduct>
		friend Istream& operator>>(Istream& is, Entity_Connectivity<Dim, Reduct>& theEntity);
	};

	template<int Dim, int Reduct>
	Istream & operator>>(Istream & is, Entity_Connectivity<Dim, Reduct>& theEntity)
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
		typedef Entity_Connectivity<4, 1> quadruple_3d;
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

	template<>
	TnbGeo_EXPORT Standard_Boolean connectivity::quadruple::IsDegenerated() const;
	template <>
	TnbGeo_EXPORT Standard_Boolean connectivity::quadruple_3d::IsDegenerated() const;
	template <>
	TnbGeo_EXPORT Standard_Boolean connectivity::octuple::IsDegenerated() const;

	template<int Dim, int Reduct>
	Standard_Integer MaxID(const std::vector<Entity_Connectivity<Dim, Reduct>>&);

	template<int Dim, int Reduct>
	std::vector<Entity_Connectivity<Dim, Reduct>>
		CombineConnectivities
		(
			const std::vector<Entity_Connectivity<Dim>>& theC0,
			const std::vector<Entity_Connectivity<Dim>>& theC1
		);

	template<int Dim, int Reduct>
	std::vector<Entity_Connectivity<Dim, Reduct>>
		CombineConnectivities
		(
			std::vector<Entity_Connectivity<Dim>>&& theC0,
			std::vector<Entity_Connectivity<Dim>>&& theC1
		);

	TnbGeo_EXPORT std::vector<connectivity::dual> dualConnectivityList(const Standard_Integer theNbEdges);
	TnbGeo_EXPORT std::vector<connectivity::dual> dualConnectivityList_Chain(
		const Standard_Integer theNbEdges, const Standard_Boolean IsClosed = Standard_False);

	TnbGeo_EXPORT connectivity::triple raise(const connectivity::dual&);
	TnbGeo_EXPORT connectivity::quadruple raise(const connectivity::triple&);
	TnbGeo_EXPORT connectivity::sextuple raise(const connectivity::quadruple&);
	TnbGeo_EXPORT connectivity::octuple raise(const connectivity::sextuple&);
}

#include <Entity_ConnectivityI.hxx>

#endif // !_Entity_Connectivity_Header
