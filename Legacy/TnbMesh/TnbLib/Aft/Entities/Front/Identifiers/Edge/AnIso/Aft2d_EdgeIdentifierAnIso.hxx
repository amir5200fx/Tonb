#pragma once
#ifndef _Aft2d_EdgeIdentifierAnIso_Header
#define _Aft2d_EdgeIdentifierAnIso_Header

#include <Aft_EntityIdentifier.hxx>
#include <Aft2d_NodeAnIso.hxx>

namespace tnbLib
{

	struct Aft2d_EdgeIdentifierAnIso_Traits
	{
		typedef Pnt2d ptType;
	};

	template<>
	class Aft_EntityIdentifier<Aft2d_NodeAnIso, true>
		: public Aft_EntityIdentifier<Aft2d_EdgeIdentifierAnIso_Traits, true>
	{

		typedef Entity2d_Metric1 metric;

		/*Private Data*/

		metric theMetric_;


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<Aft_EntityIdentifier<Aft2d_EdgeIdentifierAnIso_Traits, true>>(*this);
			ar & theMetric_;
		}

	public:


		// default constructor [5/12/2022 Amir]

		Aft_EntityIdentifier()
		{}


		// constructors [5/12/2022 Amir]


		// public functions and operators [5/12/2022 Amir]

		const metric& EffectiveMetric() const
		{
			return theMetric_;
		}

		metric& EffectiveMetric()
		{
			return theMetric_;
		}

		void SetEffectiveMetric(const metric& theMetric)
		{
			theMetric_ = theMetric;
		}

		virtual Standard_Boolean IsPoleSingular() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsLineSingular() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsSingular() const
		{
			return Standard_False;
		}
	};

	typedef Aft_EntityIdentifier<Aft2d_NodeAnIso, true>
		Aft2d_EdgeIdentifierAnIso;
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Aft2d_EdgeIdentifierAnIso);

#endif // !_Aft2d_EdgeIdentifierAnIso_Header