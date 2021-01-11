#pragma once
#ifndef _NumAlg_AdaptiveInteg_Info_Header
#define _NumAlg_AdaptiveInteg_Info_Header

#include <Standard_TypeDef.hxx>
#include <Global_AccessMethod.hxx>
#include <Global_Serialization.hxx>
#include <NumAlg_Module.hxx>

namespace tnbLib
{

	template<class Function, bool RefInfo>
	class NumAlg_AdaptiveInteg;

	class NumAlg_AdaptiveInteg_Info
	{

		template<class Function, bool RefInfo>
		friend class NumAlg_AdaptiveInteg;

		/*Private Data*/

		Standard_Boolean IsConverged_;

		Standard_Real theTolerance_;
		Standard_Real theResult_;

		Standard_Integer theMaxNbIterations_;
		Standard_Integer theNbInitIterations_;


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & IsConverged_;
			ar & theTolerance_;
			ar & theResult_;
			ar & theMaxNbIterations_;
			ar & theNbInitIterations_;
		}

	protected:

		Standard_Boolean& Change_IsConverged()
		{
			return IsConverged_;
		}

		Standard_Real& ChangeResult()
		{
			return theResult_;
		}

		void Reset()
		{
			IsConverged_ = Standard_False;

			theResult_ = 0;
		}

	public:

		static TnbNumAlg_EXPORT const Standard_Real DEFAULT_TOLERANCE;
		static TnbNumAlg_EXPORT const Standard_Integer DEFAULT_MAX_ITERATIONS;
		static TnbNumAlg_EXPORT const Standard_Integer DEFAULT_INIT_ITERATIONS;

		TnbNumAlg_EXPORT NumAlg_AdaptiveInteg_Info();

		Standard_Boolean IsConverged() const
		{
			return IsConverged_;
		}

		Standard_Real Result() const
		{
			return theResult_;
		}

		//- Macros
		GLOBAL_ACCESS_SINGLE(Standard_Real, Tolerance)
			GLOBAL_ACCESS_SINGLE(Standard_Integer, MaxNbIterations)
			GLOBAL_ACCESS_SINGLE(Standard_Integer, NbInitIterations)
	};
}

#endif // !_NumAlg_AdaptiveInteg_Info_Header
