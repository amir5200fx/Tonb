#pragma once
#ifndef _NumAlg_GA_Header
#define _NumAlg_GA_Header

#include <NumAlg_Random.hxx>
#include <NumAlg_Module.hxx>
#include <Global_Serialization.hxx>
#include <Global_Done.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Standard_TypeDef.hxx>
#include <Standard_Real.hxx>

#include <vector>
#include <memory>

namespace tnbLib
{


	class NumAlg_GA_Base
	{

	public:

		class GA_Info
		{

			/*Private Data*/

			Standard_Integer theMaxNbGenerations_;
			Standard_Integer thePopSize_;
			Standard_Integer theNbParameters_;

			Standard_Real theMutation_;
			Standard_Real theSelection_;


			// Private functions and operators [2/7/2023 Payvand]

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int file_version)
			{
				ar& theMaxNbGenerations_;
				ar& thePopSize_;
				ar& theNbParameters_;

				ar& theMutation_;
				ar& theSelection_;
			}

		public:

			static TnbNumAlg_EXPORT const std::string extension;

			static TnbNumAlg_EXPORT Standard_Integer MAX_NB_GENERATIONS;
			static TnbNumAlg_EXPORT Standard_Integer POP_SIZE;
			static TnbNumAlg_EXPORT Standard_Integer NB_PARAMETERS;

			static TnbNumAlg_EXPORT Standard_Real DEFAULT_MUTATION;
			static TnbNumAlg_EXPORT Standard_Real DEFAULT_SELECTION;

			// default constructor [2/7/2023 Payvand]

			GA_Info()
				: theMaxNbGenerations_(MAX_NB_GENERATIONS)
				, thePopSize_(POP_SIZE)
				, theNbParameters_(NB_PARAMETERS)
				, theMutation_(DEFAULT_MUTATION)
				, theSelection_(DEFAULT_SELECTION)
			{}

			// constructors [2/7/2023 Payvand]


			// Public functions and operators [2/7/2023 Payvand]

			auto MaxNbGenerations() const
			{
				return theMaxNbGenerations_;
			}

			auto& MaxNbGenerations()
			{
				return theMaxNbGenerations_;
			}

			auto PopSize() const
			{
				return thePopSize_;
			}

			auto& PopSize()
			{
				return thePopSize_;
			}

			auto NbParameters() const
			{
				return theNbParameters_;
			}

			auto& NbParameters()
			{
				return theNbParameters_;
			}

			auto Mutation() const
			{
				return theMutation_;
			}

			auto& Mutation()
			{
				return theMutation_;
			}

			auto Selection() const
			{
				return theSelection_;
			}

			auto& Selection()
			{
				return theSelection_;
			}

			void SetMaxNbGenerations(const Standard_Integer theMaxNbGen)
			{
				theMaxNbGenerations_ = theMaxNbGen;
			}

			void SetPopSize(const Standard_Integer thePopSize)
			{
				thePopSize_ = thePopSize;
			}

			void SetNbParameters(const Standard_Integer theNbParams)
			{
				theNbParameters_ = theNbParams;
			}

			void SetMutation(const Standard_Real theMut)
			{
				theMutation_ = theMut;
			}

			void SetSelection(const Standard_Real theSelection)
			{
				theSelection_ = theSelection;
			}
		};


		class GA_ParameterLimit
		{

			/*Private Data*/

			Standard_Real theLower_;
			Standard_Real theUpper_;

		public:

			// default constructor [2/7/2023 Payvand]

			GA_ParameterLimit()
				: theLower_(RealFirst())
				, theUpper_(RealLast())
			{}

			// constructors [2/7/2023 Payvand]

			GA_ParameterLimit
			(
				const Standard_Real theLower,
				const Standard_Real theUpper
			)
				: theLower_(theLower)
				, theUpper_(theUpper)
			{}


			// Public functions and operators [2/7/2023 Payvand]

			auto Lower() const
			{
				return theLower_;
			}

			auto& Lower()
			{
				return theLower_;
			}

			auto Upper() const
			{
				return theUpper_;
			}

			auto& Upper()
			{
				return theUpper_;
			}

			void SetLower(const Standard_Real theLower)
			{
				theLower_ = theLower;
			}

			void SetUpper(const Standard_Real theUpper)
			{
				theUpper_ = theUpper;
			}
		};

	private:

		/*Private Data*/

		Standard_Boolean IsInitiated_;

		Standard_Integer theCurrentGen_;

	protected:

		// default constructor [2/7/2023 Payvand]

		NumAlg_GA_Base()
		{}

		// constructors [2/7/2023 Payvand]


		// Protected functions and operators [2/7/2023 Payvand]

		auto& IsInitiatedRef()
		{
			return IsInitiated_;
		}

		auto& CurrentGenRef()
		{
			return theCurrentGen_;
		}

	public:

		static TnbNumAlg_EXPORT unsigned short verbose;

		// Public functions and operators [2/7/2023 Payvand]

		auto IsInitiated() const
		{
			return IsInitiated_;
		}

		auto CurrentGeneration() const
		{
			return theCurrentGen_;
		}

	};

	template<class T, bool Bounded = false>
	class NumAlg_GA
		: public NumAlg_GA_Base
		, public Global_Done
	{

	public:

		using NumAlg_GA_Base::GA_ParameterLimit;

		typedef std::vector<Standard_Real> gaParameters;
		typedef std::vector<GA_ParameterLimit> limitList;
		typedef std::vector<std::shared_ptr<gaParameters>> population;

		template<bool Bounded = false>
		class GA_PopInfo
		{

			/*Private Data*/

			population thePopulation_;

		public:

			// default constructor [2/7/2023 Payvand]

			GA_PopInfo()
			{}

			// constructors [2/7/2023 Payvand]


			// Public functions and operators [2/7/2023 Payvand]

			const auto& Population() const
			{
				return thePopulation_;
			}

			auto& Population()
			{
				return thePopulation_;
			}

			virtual void AllocateMemory(const Standard_Integer n)
			{
				Population().resize(n);
			}

		};
		

		template<>
		class GA_PopInfo<true>
			: public GA_PopInfo<false>
		{

			/*Private Data*/

			limitList theLimits_;

		public:

			// default constructor [2/7/2023 Payvand]

			GA_PopInfo()
			{}

			// constructors [2/7/2023 Payvand]


			// Public functions and operators [2/7/2023 Payvand]

			const auto& Limits() const
			{
				return theLimits_;
			}

			auto& Limits()
			{
				return theLimits_;
			}

			void AllocateMemory(const Standard_Integer n) override
			{
				GA_PopInfo<false>::AllocateMemory(n);
				//theLimits_.resize(n);
			}
		};

		struct GA_StaticMemory
		{

			typedef std::vector<Standard_Real> realList;
			typedef std::vector<Standard_Integer> intList;

			intList ind;
			realList cost;
			realList odds;

			intList pa;
			intList ma;
			intList xp;

			realList pick1;
			realList pick2;
			realList r;

			intList ix;

			std::vector<realList> par2;

			realList temp_arr_1;
			realList temp_arr_2;

			intList mrow;
			intList mcol;

			Standard_Integer npar;
			Standard_Integer popsize;

			Standard_Integer keep;
			Standard_Integer m;
			Standard_Integer nmut;
		};

		typedef GA_PopInfo<Bounded> popInfo;

		typedef std::vector<Standard_Real> realList;
		typedef std::vector<Standard_Integer> intList;

		template< bool cond, typename U >
		using resolvedType = typename std::enable_if< cond, U >::type;

	private:

		std::shared_ptr<GA_Info> theGaInfo_;
		std::shared_ptr<popInfo> thePopInfo_;

		mutable GA_StaticMemory theMemory_;

		std::shared_ptr<T> theObject_;

		Standard_Real(*Value)(const realList&, const std::shared_ptr<T>& theObject);

		/*Private Data*/

		auto& Memory() const
		{
			return theMemory_;
		}

		void AllocateMemory()
		{
			if (GaInfo()->PopSize() % 2 != 0) GaInfo()->PopSize() += 1;

			PopInfo()->AllocateMemory(GaInfo()->PopSize());

			for (auto& x : PopInfo()->Population())
			{
				x = std::make_shared<gaParameters>();
				x->resize(GaInfo()->NbParameters());
			}

			Memory().npar = GaInfo()->NbParameters();
			Memory().popsize = GaInfo()->PopSize();

			Memory().keep = (Standard_Integer)(GaInfo()->Selection() * Memory().popsize);
			Memory().m = (Standard_Integer)ceil((double)(Memory().popsize - Memory().keep) / 2);
			Memory().nmut = (Standard_Integer)ceil((Memory().popsize - 1) * Memory().npar * GaInfo()->Mutation());

			Memory().ind.resize(Memory().popsize);
			Memory().cost.resize(Memory().popsize);
			Memory().odds.resize(Memory().keep + 1);

			Memory().pa.resize(Memory().m);
			Memory().ma.resize(Memory().m);
			Memory().xp.resize(Memory().m);

			Memory().pick1.resize(Memory().m);
			Memory().pick2.resize(Memory().m);
			Memory().r.resize(Memory().m);

			Memory().ix.resize((Standard_Integer)ceil(((Standard_Real)Memory().keep) / 2));

			Memory().par2.resize(Memory().popsize);
			for (auto& x : Memory().par2)
				x.resize(Memory().npar);

			Memory().temp_arr_1.resize(Memory().m);
			Memory().temp_arr_2.resize(Memory().nmut);

			Memory().mrow.resize(Memory().nmut);
			Memory().mcol.resize(Memory().nmut);
		}

		void Initialize(gaParameters& theParams) const
		{
			for (auto& x : theParams)
				x = (Standard_Real)NumAlg_Random::Randreal();
		}

		void Initialize(population& thePop) const
		{
			for (auto& x : thePop)
				Initialize(*x);
		}

		template<class U = void>
		resolvedType<Bounded, U>
			Normalize()
		{
			const auto& limits = PopInfo()->Limits();
			auto& pop = PopInfo()->Population();

			for (int i = 0; i < GaInfo()->PopSize(); i++)
				for (int j = 0; j < GaInfo()->NbParameters(); j++)
				{
					const auto lo = limits[j].Lower();
					const auto hi = limits[j].Upper();

					pop[i]->operator[](j) *= (hi - lo);
					pop[i]->operator[](j) += lo;
				}
		}

		template<class U = void>
		resolvedType<!Bounded, U>
			Normalize()
		{}

		template<class U = void>
		resolvedType<Bounded, U>
			MutNormalize(const intList& mrow, const intList& mcol, const realList& tmp)
		{
			/*const auto& limits = PopInfo()->Limits();
			auto& pop = PopInfo()->Population();

			for (int j = 0; j < mcol.size(); j++)
			{
				const auto lo = limits[mcol[j]].Lower();
				const auto hi = limits[mcol[j]].Upper();

				pop[j]->operator[](j) *= (hi - lo);
				pop[j]->operator[](j) += lo;

				pop[mrow[j]]->operator[](mcol[j]) = (hi - lo) * tmp[j] + lo;
			}*/
			auto& pop = PopInfo()->Population();

			for (int j = 0; j < mcol.size(); j++)
			{
				pop[mrow[j]]->operator[](mcol[j]) = tmp[j];
			}
		}

		template<class U = void>
		resolvedType<!Bounded, U>
			MutNormalize(const intList& mrow, const intList& mcol, const realList& tmp)
		{
			auto& pop = PopInfo()->Population();

			for (int j = 0; j < mcol.size(); j++)
			{
				pop[mrow[j]]->operator[](mcol[j]) = tmp[j];
			}
		}

		void Initiate()
		{
			AllocateMemory();

			// create initial population
			Initialize(PopInfo()->Population());

			// normalize values between hi and lo
			Normalize();

			IsInitiatedRef() = Standard_True;
		}


		static void sumPrefix(gaParameters& a)
		{
			forThose(i, 1, a.size() - 1)
				a[i] += a[i - 1];
		}

	public:

		// default constructor [2/7/2023 Payvand]

		NumAlg_GA()
		{
			thePopInfo_ = std::make_shared<popInfo>();
			NumAlg_Random::InitRand();
		}

		// Public functions and operators [2/7/2023 Payvand]

		const auto& GaInfo() const
		{
			return theGaInfo_;
		}

		const auto& PopInfo() const
		{
			return thePopInfo_;
		}

		const auto& Object() const
		{
			return theObject_;
		}

		void Iterate();
		void Perform();

		void SetGaInfo(const std::shared_ptr<GA_Info>& theInfo)
		{
			theGaInfo_ = theInfo;
		}

		void SetPopInfo(const std::shared_ptr<popInfo>& theInfo)
		{
			thePopInfo_ = theInfo;
		}

		void SetObject(const std::shared_ptr<T>& theObject)
		{
			theObject_ = theObject;
		}

		void SetFunction(Standard_Real(*theValue)(const realList&, const std::shared_ptr<T>&))
		{
			Value = theValue;
		}
	};
}

#include <NumAlg_GAI.hxx>

#endif // !_NumAlg_GA_Header
