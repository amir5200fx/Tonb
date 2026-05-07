#pragma once
#ifndef _NumAlg_NelderMeadCoeffs_Header
#define _NumAlg_NelderMeadCoeffs_Header

#include <NumAlg_Module.hxx>
#include <Global_Serialization.hxx>

#include <Global_TypeDef.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

#include <opencascade/gp.hxx>

namespace tnbLib
{

	class NumAlg_NelderMeadCoeffs
	{

		/*Private Data*/

		Standard_Real theReflection_;
		Standard_Real theExpansion_;
		Standard_Real theContraction_;
		Standard_Real theShrink_;


		// private functions and operators [5/6/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & theReflection_;
			ar & theExpansion_;
			ar & theContraction_;
			ar & theShrink_;
		}

	public:

		static TnbNumAlg_EXPORT const Standard_Real DEFAULT_REFLECTION;
		static TnbNumAlg_EXPORT const Standard_Real DEFAULT_EXPANSION;
		static TnbNumAlg_EXPORT const Standard_Real DEFAULT_CONTRACTION;
		static TnbNumAlg_EXPORT const Standard_Real DEFAULT_SHRINK;

		// default constructor [5/6/2022 Amir]

		NumAlg_NelderMeadCoeffs()
			: theReflection_(DEFAULT_REFLECTION)
			, theExpansion_(DEFAULT_EXPANSION)
			, theContraction_(DEFAULT_CONTRACTION)
			, theShrink_(DEFAULT_SHRINK)
		{}


		// constructors [5/6/2022 Amir]



		// public functions and operators [5/6/2022 Amir]

		auto ReflectionCoeff() const
		{
			return theReflection_;
		}

		auto ExpansionCoeff() const
		{
			return theExpansion_;
		}

		auto ContractionCoeff() const
		{
			return theContraction_;
		}

		auto ShrinkCoeff() const
		{
			return theShrink_;
		}

		void SetReflectionCoeff(const Standard_Real x)
		{
			if (x <= gp::Resolution())
			{
				FatalErrorIn("void SetReflection(const Standard_Real x)")
					<< "Invalid coefficient for reflection" << endl
					<< abort(FatalError);
			}

			theReflection_ = x;
		}

		void SetExpansionCoeff(const Standard_Real x)
		{
			if (x <= (Standard_Real)1.0)
			{
				FatalErrorIn("void SetExpansion(const Standard_Real x)")
					<< "Invalid coefficient for expansion" << endl
					<< " - the x > 1.0" << endl
					<< abort(FatalError);
			}
			theExpansion_ = x;
		}

		void SetContractionCoeff(const Standard_Real x)
		{
			if (x <= gp::Resolution() OR x > (Standard_Real)1.0)
			{
				FatalErrorIn("void SetContractionCoeff(const Standard_Real x)")
					<< "Invalid coefficient for contraction" << endl
					<< " - the x <= 0.0 or x > 1.0" << endl
					<< abort(FatalError);
			}
			theContraction_ = x;
		}

		void SetShrinkCoeff(const Standard_Real x)
		{
			theShrink_ = x;
		}
	};
}

#endif // !_NumAlg_NelderMeadCoeffs_Header
