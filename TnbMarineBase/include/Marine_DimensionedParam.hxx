#pragma once
#ifndef _Marine_DimensionedParam_Header
#define _Marine_DimensionedParam_Header

#include <Standard_TypeDef.hxx>
#include <Global_Named.hxx>
#include <dimensionSet.hxx>
#include <Vec3d.hxx>
#include <Marine_Module.hxx>
#include <dimensionSet_Serialization.hxx>

namespace tnbLib
{

	class Marine_SpecifiedParam
	{

		/*Private Data*/

		Standard_Boolean IsSpecified_;

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & IsSpecified_;
		}

	protected:

		Marine_SpecifiedParam()
			: IsSpecified_(Standard_False)
		{}

		Marine_SpecifiedParam(const Standard_Boolean Sp)
			: IsSpecified_(Sp)
		{}

		void doSpecify()
		{
			IsSpecified_ = Standard_True;
		}

		void unSpecify()
		{
			IsSpecified_ = Standard_False;
		}

	public:

		Standard_Boolean IsSpecified() const
		{
			return IsSpecified_;
		}

	};


	// Forward Declarations
	template<class T>
	class Marine_DimensionedParam;

	template<class T>
	Ostream& operator<<(Ostream& os, const Marine_DimensionedParam<T>&);
	/*template<class T>
	Ostream& operator>>(Ostream& os, Marine_DimensionedParam<T>&);*/

	template<class T>
	class Marine_DimensionedParam
		: public Global_Named
		, public Marine_SpecifiedParam
	{

		/*Private Data*/

		dimensionSet theDimension_;

		T theValue_;


		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<Global_Named>(*this);
			ar & boost::serialization::base_object<Marine_SpecifiedParam>(*this);
			ar & theDimension_;
			ar & theValue_;
		}

	protected:

		//- defualt constructor

		Marine_DimensionedParam()
			: theDimension_(0,1,0,0,0)
		{}


		//- constructors

		Marine_DimensionedParam
		(
			const word& theName,
			const dimensionSet& theDim
		)
			: Global_Named(theName)
			, Marine_SpecifiedParam(Standard_False)
			, theDimension_(theDim)
		{}

		Marine_DimensionedParam
		(
			const word& theName,
			const dimensionSet& theDim,
			const T& theValue
		)
			: Global_Named(theName)
			, Marine_SpecifiedParam(Standard_True)
			, theDimension_(theDim)
			, theValue_(theValue)
		{}

	public:


		const dimensionSet& Dimension() const
		{
			return theDimension_;
		}

		dimensionSet& Dimension()
		{
			return theDimension_;
		}

		const T& Value() const
		{
			if (!IsSpecified())
			{
				FatalErrorIn(" Standard_Real Value() const")
					<< " not specified value for the " << "'" << Name() << "'"
					<< abort(FatalError);
			}

			return theValue_;
		}

		T& Value()
		{
			if (!IsSpecified()) doSpecify();
			return theValue_;
		}

		const T& operator()() const
		{
			return Value();
		}

		T& operator()()
		{
			return Value();
		}

		Standard_Boolean operator!() const
		{
			return !IsSpecified();
		}

	};


	namespace marineLib
	{

		typedef Marine_DimensionedParam<Standard_Real> realParam;
		typedef Marine_DimensionedParam<Vec3d> vec3Param;
	}
}

#include <Marine_DimensionedParamI.hxx>

#endif // !_Marine_DimensionedParam_Header
