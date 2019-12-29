//#include <Random.hxx>
//
//#include <symmTensor.hxx>
//
//#ifdef mingw
//#   include "rand48.h"
//#endif
//
//// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
//
//namespace tnbLib
//{
//
//	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
//
//#if INT_MAX    != 2147483647
//#    error "INT_MAX    != 2147483647"
//#    error "The random number generator may not work!"
//#endif
//
//#ifdef USE_RANDOM
//#   include <climits>
//#else
//#   include <cstdlib>
//#endif
//
//
//// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //
//
//// construct given seed
//	Random::Random(const label& seed)
//	{
//		if (seed > 1)
//		{
//			Seed = seed;
//		}
//		else
//		{
//			Seed = 1;
//		}
//
//#   ifdef USE_RANDOM
//		srandom((unsigned int)Seed);
//#   else
//		srand48(Seed);
//#   endif
//
//	}
//
//
//	int Random::bit()
//	{
//#   ifdef USE_RANDOM
//		if (random() > INT_MAX / 2)
//#   else
//		if (lrand48() > INT_MAX / 2)
//#   endif
//		{
//			return 1;
//		}
//		else
//		{
//			return 0;
//		}
//	}
//
//
//	scalar Random::scalar01()
//	{
//#   ifdef USE_RANDOM
//		return (scalar)random() / INT_MAX;
//#   else
//		return drand48();
//#   endif
//	}
//
//
//	vector Random::vector01()
//	{
//		vector rndVec;
//		for (direction cmpt = 0; cmpt < vector::nComponents; cmpt++)
//		{
//			rndVec.component(cmpt) = scalar01();
//		}
//
//		return rndVec;
//	}
//
//
//	sphericalTensor Random::sphericalTensor01()
//	{
//		sphericalTensor rndTen;
//		rndTen.ii() = scalar01();
//
//		return rndTen;
//	}
//
//
//	symmTensor Random::symmTensor01()
//	{
//		symmTensor rndTen;
//		for (direction cmpt = 0; cmpt < symmTensor::nComponents; cmpt++)
//		{
//			rndTen.component(cmpt) = scalar01();
//		}
//
//		return rndTen;
//	}
//
//
//	symmTensor4thOrder Random::symmTensor4thOrder01()
//	{
//		symmTensor4thOrder rndTen;
//		for (direction cmpt = 0; cmpt < symmTensor4thOrder::nComponents; cmpt++)
//		{
//			rndTen.component(cmpt) = scalar01();
//		}
//
//		return rndTen;
//	}
//
//
//	diagTensor Random::diagTensor01()
//	{
//		diagTensor rndTen;
//		for (direction cmpt = 0; cmpt < diagTensor::nComponents; cmpt++)
//		{
//			rndTen.component(cmpt) = scalar01();
//		}
//
//		return rndTen;
//	}
//
//
//	tensor Random::tensor01()
//	{
//		tensor rndTen;
//		for (direction cmpt = 0; cmpt < tensor::nComponents; cmpt++)
//		{
//			rndTen.component(cmpt) = scalar01();
//		}
//
//		return rndTen;
//	}
//
//
//	label Random::integer(const label lower, const label upper)
//	{
//#   ifdef USE_RANDOM
//		return lower + (random() % (upper + 1 - lower));
//#   else
//		return lower + (lrand48() % (upper + 1 - lower));
//#   endif
//	}
//
//
//	vector Random::position(const vector& start, const vector& end)
//	{
//		vector rndVec(start);
//
//		for (direction cmpt = 0; cmpt < vector::nComponents; cmpt++)
//		{
//			rndVec.component(cmpt) +=
//				scalar01()*(end.component(cmpt) - start.component(cmpt));
//		}
//
//		return rndVec;
//	}
//
//
//	void Random::randomise(scalar& s)
//	{
//		s = scalar01();
//	}
//
//
//	void Random::randomise(vector& v)
//	{
//		v = vector01();
//	}
//
//
//	void Random::randomise(sphericalTensor& st)
//	{
//		st = sphericalTensor01();
//	}
//
//
//	void Random::randomise(symmTensor& st)
//	{
//		st = symmTensor01();
//	}
//
//
//	void Random::randomise(symmTensor4thOrder& st)
//	{
//		st = symmTensor4thOrder01();
//	}
//
//
//	void Random::randomise(diagTensor& dt)
//	{
//		dt = diagTensor01();
//	}
//
//
//	void Random::randomise(tensor& t)
//	{
//		t = tensor01();
//	}
//
//
//	// return a normal Gaussian randon number
//	// with zero mean and unity variance N(0, 1)
//
//	scalar Random::GaussNormal()
//	{
//		static int iset = 0;
//		static scalar gset;
//		scalar fac, rsq, v1, v2;
//
//		if (iset == 0)
//		{
//			do
//			{
//				v1 = 2.0*scalar01() - 1.0;
//				v2 = 2.0*scalar01() - 1.0;
//				rsq = v1 * v1 + v2 * v2;
//			} while (rsq >= 1.0 || rsq == 0.0);
//
//			fac = sqrt(-2.0 * log(rsq) / rsq);
//			gset = v1 * fac;
//			iset = 1;
//
//			return v2 * fac;
//		}
//		else
//		{
//			iset = 0;
//
//			return gset;
//		}
//	}
//
//
//	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
//
//} // End namespace tnbLib
//
//// ************************************************************************* //